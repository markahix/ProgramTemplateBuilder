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
};

// Handle Directories
void CreateDirectoryStructure(std::string location);

// Write non-source files.
void CreateMakefile(std::string location, std::string binary_name);

// Write source cpp files.
void WriteSourceFiles(std::string location, std::string binary_name);




#endif