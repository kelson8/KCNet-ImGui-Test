#include <string>
#include <iostream>
#include <fstream>
#include "text_file_functions.h"

// Add in ImGui for output text file to screen.
#include "imgui.h"
#include "imgui_impl_dx9.h"

// Checking if the file exists breaks without this
// https://stackoverflow.com/questions/19321804/this-function-or-variable-may-be-unsafe-visual-studio
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

// https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exists-using-standard-c-c11-14-17-c
inline bool TextFileFunctions::fileExistCheck(const std::string& name)
{
    if (FILE* file = fopen(name.c_str(), "r"))
    {
        fclose(file);
        return true;
    }
    else
    {
        return false;
    }
}

// https://cplusplus.com/doc/tutorial/files/
// Todo Try to print this to a ImGui text box.
void TextFileFunctions::readTextFile(std::string file)
{
    std::string line;
    std::ifstream myfile(file);

    if (TextFileFunctions::fileExistCheck(file))
    {
        if (myfile.is_open())
        {
            while (std::getline(myfile, line))
            {
                std::cout << line << '\n';
            }
            myfile.close();
        }
        else
        {
            std::cout << "Unable to open file!";
        }
    }
    else
    {
        std::cout << "File doesn't exist!";
    }

    //else cout << "Unable to open file!";
}


#ifndef _TEST
#define _TEST
#endif

// This works
// Some code from Google AI:///
void TextFileFunctions::outputTextFileContents(const char* filePath) {
    std::ifstream myfile(filePath);

    if (myfile.is_open())
    {
        std::string line;
        std::string content;

        // Output file contents
        while (std::getline(myfile, line))
        {
            content += line + "\n";
        }
        // Close the file
        myfile.close();

        ImGui::Text("\"%s\" File contents: \n%s", filePath, &content);
        //ImGui::InputTextMultiline();
    }
    else
    {
        ImGui::Text("Error opening file %s", filePath);
    }
}

// Add test function for this, I need to figure out how to return an array like this.
#ifdef _TEST
// This prints the text file output to the console but spams it, I probably won't use this much.
void TextFileFunctions::printTextOutput(std::string file)
{
    std::string line;
    std::ifstream myfile(file);


    if (TextFileFunctions::fileExistCheck(file))
    {
        if (myfile.is_open())
        {
            while (std::getline(myfile, line))
            {
                // Disabled for now
                //std::cout << line << '\n';
                //return line;
            }

            //return line;
            myfile.close();
        }
        else
        {
            std::cout << "Unable to open file!";
        }
    }
    else
    {
        std::cout << "File doesn't exist!";
    }
}

// https://www.digitalocean.com/community/tutorials/return-array-in-c-plus-plus-function
//void* test()
//{
//
//}


#else

//static std::string testString1(std::string file std::string text)
//std::string TextFileFunctions::testString1(std::string file)

// This doesn't fully work yet, once I finish it, it'll show up on a ImGui tab.
//std::string TextFileFunctions::printTextOutput(std::string file)
void TextFileFunctions::printTextOutput(std::string file)
{
    std::string line;
    std::ifstream myfile(file);

    if (TextFileFunctions::fileExistCheck(file))
    {
        if (myfile.is_open())
        {
            while (std::getline(myfile, line))
            {
                std::cout << line << '\n';
                //return line;
            }

            //return line;
            myfile.close();
        }
        else
        {
            std::cout << "Unable to open file!";
        }
    }
    else
    {
        std::cout << "File doesn't exist!";
    }
}
#endif //_TEST

