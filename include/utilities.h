#ifndef UTILITIES_H
#define UTILITIES_H

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <filesystem>
#include <map>
#include <unistd.h>
#include <sstream>

namespace fs = std::filesystem;

class Settings
{
    public:
        Settings(int argc, char** argv);
        ~Settings();
        std::string location;
        std::string binary_name;
        std::string remote_git_location;
};

// Handle Directories
void CreateDirectoryStructure(Settings settings);

// Write non-source files.
void CreateMakefile(Settings settings);

// Write source cpp files.
void WriteSourceFiles(Settings settings);

// Validate successful baseline compilation
void TestCompile(Settings settings);

// Generate basic README.md template for user to fill
void GenerateReadme(Settings settings);

// Generate .gitignore and perform git setup
void GitSetup(Settings settings);
void GitFinisher(Settings settings);


#endif