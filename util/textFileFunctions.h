#pragma once
class TextFileFunctions {
public:
	inline static bool fileExistCheck(const std::string& name);
	static void readTextFile(std::string file);
	static std::string printTextOutput(std::string file);
};
