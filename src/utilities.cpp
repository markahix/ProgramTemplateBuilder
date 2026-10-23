#include "utilities.h"

Settings::Settings(int argc, char** argv)
{
        location="./";
        binary_name="new_program";
        remote_git_location="";
        for (int i = 1; i < argc; i++)
        {
            if ((std::string)argv[i] == "--location")
            {
                location = (std::string)argv[i+1];
                i++;
                continue;
            }
            if ((std::string)argv[i] == "--binary")
            {
                binary_name = (std::string)argv[i+1];
                i++;
                continue;
            }
            if ((std::string)argv[i] == "--remote")
            {
                remote_git_location = (std::string)argv[i+1];
                i++;
                continue;
            }
            std::cout << "Unrecognized command line argument: " << (std::string)argv[i] << std::endl;
        }

}

Settings::~Settings()
{

}

void CreateDirectoryStructure(std::string location)
{
    fs::path workdir(location);
    fs::create_directory(workdir);
    fs::create_directory(workdir / "src/");
    fs::create_directory(workdir / "include/");
    fs::create_directory(workdir / "obj/");
    fs::create_directory(workdir / "bin/");
}

void CreateMakefile(std::string location, std::string binary_name)
{
    fs::path Makefile(location);
    Makefile /= "Makefile";
    std::ofstream ofile(Makefile,std::ios::out);
    if (!ofile.is_open())
    {
        std::cerr << "Unable to open " << Makefile << " for writing.  Terminating job. " << std::endl;
    }
    ofile << R"""(CC=g++

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
INS_DIR := /usr/local/bin

EXE := $(BIN_DIR)/)""" << binary_name << R"""(
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CPPFLAGS := -Iinclude -MMD -MP
CFLAGS   := -Wall
LDFLAGS  := -Llib -static
LDLIBS   := -lm -lstdc++fs

.PHONY: all clean install

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) -std=c++17 $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

install: $(EXE)
	ln -sf $(abspath $(EXE)) $(INS_DIR)/)""" << binary_name << R"""(

-include $(OBJ:.o=.d)
)""";
    ofile.close();
}

void write_main_cpp(std::string location, std::string binary_name)
{
    fs::path sourcefile = location;
    sourcefile /= "src/main.cpp";
    std::ofstream outfile(sourcefile,std::ios::out);
    if (!outfile.is_open())
    {
        std::cerr << "Unable to open " << sourcefile << " for writing. Terminating job. " << std::endl;
        exit(1);
    }
    outfile << R"""(
/*
  main.cpp for )""" + binary_name + R"""(
*/

#include "utilities.h"

int main(int argc, char** argv)
{
    // Parse command line arguments into Settings class object.
    Settings settings(argc, argv);


    return 0;
}
    )""";
    // Fill in file content here.
    outfile.close();

}

void write_utilities_cpp(std::string location)
{
    fs::path sourcefile = location;
    sourcefile /= "src/utilities.cpp";
    std::ofstream outfile(sourcefile,std::ios::out);
    if (!outfile.is_open())
    {
        std::cerr << "Unable to open " << sourcefile << " for writing. Terminating job. " << std::endl;
        exit(1);
    }
    // Fill in file content here.
    outfile << R"""(
#include "utilities.h"

Settings::Settings(int argc, char** argv)
{
    for (int i = 1; i < argc; i++)
    {
        // handling of default globals first.
        if ((std::string)argv[i] == "--debug")
        {
            DEBUG = true;
        }
        if ((std::string)argv[i] == "--hpc-mode")
        {
            HPC_MODE = true;
        }
        if ((std::string)argv[i] == "--container")
        {
            CONTAINER_MODE = true;
        }
        if (((std::string)argv[i] == "--verbose") || ((std::string)argv[i] == "-v"))
        {
            VERBOSE_LOGGING = true;
        }
        if ((std::string)argv[i] == "--dryrun")
        {
            DRYRUN = true;
        }
        // Additional command line arguments should be handled below.  
        // This section is ONLY for parsing the command line into variables, values, and settings.
        // Do *not* attempt to perform additional calculations or make decisions within this function, 
        // as it can lead to crashes and unexpected behaviors.
    }
}

Settings::~Settings()
{
}
)""";
    outfile.close();

}

void write_globals_h(std::string location)
{
    fs::path sourcefile = location;
    sourcefile /= "include/globals.h";
    std::ofstream outfile(sourcefile,std::ios::out);
    if (!outfile.is_open())
    {
        std::cerr << "Unable to open " << sourcefile << " for writing. Terminating job. " << std::endl;
        exit(1);
    }
    outfile << R"""(#ifndef GLOBALS_H
#define GLOBALS_H
/* Global variables like DEBUG go in this file.  
// Recommend using CAPS for variable names defined herein.
*/

extern bool DEBUG;
extern bool HPC_MODE;
extern bool CONTAINER_MODE;
extern bool VERBOSE_LOGGING;
extern bool DRYRUN;

#endif
)""";
    outfile.close();
}

void write_globals_cpp(std::string location)
{
    fs::path sourcefile = location;
    sourcefile /= "src/globals.cpp";
    std::ofstream outfile(sourcefile,std::ios::out);
    if (!outfile.is_open())
    {
        std::cerr << "Unable to open " << sourcefile << " for writing. Terminating job. " << std::endl;
        exit(1);
    }
    // Fill in file content here.
    outfile << R"""(
#include "globals.h"
/* 
// Initial (default) values for all globals go here.
*/
bool DEBUG = false;
bool HPC_MODE = false;
bool CONTAINER_MODE = false;
bool VERBOSE_LOGGING = false;
bool DRYRUN = false;

)""";
    outfile.close();

}

void write_constants_h(std::string location)
{
    fs::path sourcefile = location;
    sourcefile /= "include/constants.h";
    std::ofstream outfile(sourcefile,std::ios::out);
    if (!outfile.is_open())
    {
        std::cerr << "Unable to open " << sourcefile << " for writing. Terminating job. " << std::endl;
        exit(1);
    }
    outfile << R"""(#ifndef CONSTANTS_H
#define CONSTANTS_H
/* 
// Predefined constants go in this file.  
// Constants include physical/mathematical constants, conversion coefficients, etc.
// Recommend using CAPS for variable names defined herein.
*/
const double PI = 3.141592653;

#endif
)""";
    outfile.close();
}

void write_utilities_h(std::string location)
{
    fs::path sourcefile = location;
    sourcefile /= "include/utilities.h";
    std::ofstream outfile(sourcefile,std::ios::out);
    if (!outfile.is_open())
    {
        std::cerr << "Unable to open " << sourcefile << " for writing. Terminating job. " << std::endl;
        exit(1);
    }
    outfile << R"""(#ifndef UTILITIES_H
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
#include "config.h"
#include "globals.h"
#include "constants.h"
namespace fs = std::filesystem;

class Settings
{
    public:
        Settings(int argc, char** argv);
        ~Settings();

};

#endif
)""";
    outfile.close();

}

void write_config_h(std::string location)
{
    fs::path sourcefile = location;
    sourcefile /= "include/config.h";

    std::ofstream outfile(sourcefile,std::ios::out);
    if (!outfile.is_open())
    {
        std::cerr << "Unable to open " << sourcefile << " for writing. Terminating job. " << std::endl;
        exit(1);
    }
    outfile << R"""(#ifndef CONFIG_H
#define CONFIG_H
// Standard system configuration information goes in this file.  
// Recommend using CAPS for variable names defined herein.
#endif)""";
    outfile.close();
}


void WriteSourceFiles(std::string location, std::string binary_name)
{
    // source files (.cpp)
    write_main_cpp(location,binary_name);
    write_utilities_cpp(location);
    write_globals_cpp(location);

    // header files (.h)
    write_utilities_h(location);
    write_config_h(location);
    write_globals_h(location);
    write_constants_h(location);

}

// Generate basic README.md template for user to fill
void GenerateReadme(Settings settings)
{
    fs::path sourcefile = settings.location;
    sourcefile /= "README.md";
    std::ofstream outfile(sourcefile,std::ios::out);
    if (!outfile.is_open())
    {
        std::cerr << "Unable to open " << sourcefile << " for writing. Terminating job. " << std::endl;
        exit(1);
    }
    std::string folder_name = sourcefile.parent_path().filename();
    outfile << "# " << folder_name << std::endl;
    outfile << "This is the initial README for `" << settings.binary_name << "`." << std::endl << std::endl;
    outfile << "### Usage " << std::endl;
    outfile << "```"<<std::endl << settings.binary_name << " \\ " << std::endl;
    outfile << R"""(    [--debug] \
    [--hpc-mode] \
    [--container] \
    [--verbose | -v] \
    [--dryrun]
```

Command Line Arguments:
- `--debug` turns on debug mode, which prints absolutely everything it can to `stdout`.
- `--hpc-mode` identifies the program as being run from a supercomputer or HPC, often with job-scheduling.  Useful for ensuring jobs are not run on login nodes, etc.
- `--container` is when the program is installed within a container like Docker or Singularity - can be helpful for modifying input and output handling.
- `--verbose` or `-v` increases the amount of detail in the logging to `stdout`/`stderr`.  Not as much as `debug`, but more than the basics.
- `--dryrun` is a quick flag for situations when the program should simply report what it would be doing without necessarily doing those tasks - useful for ensuring expected behaviors before performing long tasks.
)""";
}
// bool DEBUG = false;
// bool HPC_MODE = false;
// bool CONTAINER_MODE = false;
// bool VERBOSE_LOGGING = false;
// bool DRYRUN = false;

// Generate .gitignore and perform git setup
void GitSetup(Settings settings)
{
    fs::path sourcefile = settings.location;
    sourcefile /= ".gitignore";

    std::ofstream outfile(sourcefile,std::ios::out);
    if (!outfile.is_open())
    {
        std::cerr << "Unable to open " << sourcefile << " for writing. Terminating job. " << std::endl;
        exit(1);
    }
    outfile << R"""(.vscode/
bin/
obj/
)""";
    outfile.close();

}

void GitFinisher(Settings settings)
{
    fs::path start_loc = fs::current_path();
    fs::current_path(settings.location);
    // do the git stuff here.
    system("git init");
    system("git add .");
    system("git commit -m \"initial commit \"");
    system("git branch -M main");
    if (settings.remote_git_location != "")
    {
        std::stringstream buffer;
        buffer.str("");
        buffer << "git remote add origin "<<settings.remote_git_location<<"; git push origin main";
        system(buffer.str().c_str());
    }
    fs::current_path(start_loc);
}

void TestCompile(Settings settings)
{
    fs::path start_loc = fs::current_path();
    fs::current_path(settings.location);
    system("make");
    if (!fs::exists("bin/"+settings.binary_name))
    {
        std::cerr << "Baseline Compilation did NOT succeed.  Check code base and system environment." << std::endl;
    }
    fs::current_path(start_loc);
}