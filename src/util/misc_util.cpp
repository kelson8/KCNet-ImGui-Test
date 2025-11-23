#include "misc_util.h"

#include <iostream>
#include <random>
#include <string>

#ifdef _WIN32
// Added to header
//#include <Windows.h>
#include <Psapi.h>
#include <TlHelp32.h>
#endif

// https://www.delftstack.com/howto/cpp/check-cpp-version/
#ifdef __cplusplus

/// <summary>
/// Get the current C++ version set in the program.
/// TODO Why does this display C++98 when I have a newer version selected?
/// </summary>
/// <returns>The C++ version as a string.</returns>
std::string MiscUtil::CPlusPlusVersion() {
	switch (__cplusplus) {
	case 199711L:
		return "C++98";
		break;
	case 201103L:
		return "C++11";
		break;
	case 201402L:
		return "C++14";
		break;
	case 201703L:
		return "C++17";
		break;
		
	}
}

#endif //__cplusplus

#define NEW_RANDOM_NUMBER_GEN

/// <summary>
/// Convert a float to a string, instead of using std::to_string everywhere.
/// </summary>
/// <param name="value">The float to convert</param>
/// <returns>The float converted to string</returns>
std::string
MiscUtil::floatToString(float value)
{
	std::stringstream ss;
	ss << value;
	return ss.str();
}

std::string
MiscUtil::AddressToString(void* address)
{
	std::stringstream ss;
	ss << address;
	return ss.str();
}

/// <summary>
/// Generate a random number, this takes a minimum and maximum value
/// https://stackoverflow.com/questions/29381843/generate-random-number-in-range-min-max
/// </summary>
/// <param name="min">The minimum number to generate.</param>
/// <param name="max">The maximum number to generate.</param>
/// <returns>A random number between min and max.</returns>
int
MiscUtil::GenerateRandomNumber(int min, int max)
{

#ifdef NEW_RANDOM_NUMBER_GEN
	// Use std::random_device to seed the generator
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(min, max);
	return distrib(gen);
#else
	srand(time(0));
	// Get a random number between min and max
	int randomNum = min + rand() % (max - min + 1);
	return randomNum;
#endif
}


#ifdef _WIN32

/// <summary>
/// Get the base address, and display it in the console.
/// TODO Fix this to work, it works in my ReVC tests.
/// </summary>
//void
//MiscUtil::LogBaseAddress(LPCSTR exeName)
//{
//	// New
//	uintptr_t baseAddress = 0;
//	DWORD processID = 0;
//
//	std::cout << "Attempting to get module handle for: \"" << exeName << "\"" << std::endl; // Debug output
//
//	HMODULE hModule = GetModuleHandleA(exeName);
//	if (hModule) {
//		MODULEINFO moduleInfo;
//		if (GetModuleInformation(GetCurrentProcess(), hModule, &moduleInfo, sizeof(moduleInfo))) {
//			uintptr_t baseAddress = reinterpret_cast<uintptr_t>(moduleInfo.lpBaseOfDll);
//
//			std::cout << "Base address of " << exeName << ": " << std::hex << baseAddress << std::endl;
//		}
//		else {
//			std::cerr << "Failed to get Module information" << std::endl;
//		}
//
//	}
//	else {
//		DWORD error = GetLastError();
//		std::cout << "Exe name: " << exeName << std::endl;
//		std::cerr << "Failed to get base address. Error code: " << error << std::endl;
//	}
//}

// New

void
MiscUtil::LogBaseAddress(const char* exeName)
{
	std::cout << "Base address for " << exeName << ": 0x" << this->GetModuleBaseAddress(exeName) << std::endl;
}



/// <summary>
/// Get the base address by itself without logging it.
/// This should always get the base module address.
/// </summary>
/// <param name="exeName">The exe name to get the base address from</param>
/// <returns>The exe module base address</returns>
//uintptr_t
//MiscUtil::GetModuleBaseAddress(const char* exeName)
//{
//	HMODULE hModule = GetModuleHandleA(exeName);
//	if (hModule) {
//		MODULEINFO moduleInfo;
//		if (GetModuleInformation(GetCurrentProcess(), hModule, &moduleInfo, sizeof(moduleInfo))) {
//			return reinterpret_cast<uintptr_t>(moduleInfo.lpBaseOfDll);
//		}
//	}
//	return 0; // Return 0 on failure
//}

// New

/// <summary>
/// This seems to work, although ReVC reports a different value when being logged.
/// TODO Look into this
/// </summary>
/// <param name="exeName"></param>
/// <returns></returns>
uintptr_t MiscUtil::GetModuleBaseAddress(const char* exeName) {
	uintptr_t baseAddress = 0;
	DWORD processID = 0;

	// 1. Get the Process ID (PID)
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot != INVALID_HANDLE_VALUE) {
		PROCESSENTRY32 processEntry;
		processEntry.dwSize = sizeof(PROCESSENTRY32);

		if (Process32First(hSnapshot, &processEntry)) {
			do {
				if (_stricmp(processEntry.szExeFile, exeName) == 0) {
					processID = processEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnapshot, &processEntry));
		}
		CloseHandle(hSnapshot);
	}

	if (processID != 0) {
		// 2. Open the Process
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
		if (hProcess != NULL) {
			HMODULE hModules[1024];
			DWORD bytesNeeded;

			// 3. Enumerate Modules
			if (EnumProcessModules(hProcess, hModules, sizeof(hModules), &bytesNeeded)) {
				for (unsigned int i = 0; i < bytesNeeded / sizeof(HMODULE); ++i) {
					char moduleName[MAX_PATH];
					if (GetModuleBaseNameA(hProcess, hModules[i], moduleName, sizeof(moduleName) / sizeof(char))) {
						if (_stricmp(moduleName, exeName) == 0) {
							MODULEINFO moduleInfo;
							// 4. Get Module Information
							if (GetModuleInformation(hProcess, hModules[i], &moduleInfo, sizeof(moduleInfo))) {
								baseAddress = reinterpret_cast<uintptr_t>(moduleInfo.lpBaseOfDll);
								break;
							}
						}
					}
				}
			}
			CloseHandle(hProcess);
		}
	}
	return baseAddress;
}

#endif //_WIN32
