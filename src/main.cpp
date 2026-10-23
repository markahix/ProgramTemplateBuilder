#include "utilities.h"

int main(int argc, char** argv)
{
    // get location
    // get binary_name
    Settings settings(argc,argv);
       
    // generate directory hierarchy
    CreateDirectoryStructure(settings.location);

    // generate Makefile
    CreateMakefile(settings.location, settings.binary_name);

    // generate basic code templates and standard functionalities.
    WriteSourceFiles(settings.location, settings.binary_name);

    // Validate basic compilation is successful
    TestCompile(settings);

    // Generate README.md
    GenerateReadme(settings);

    // Generate .gitignore.
    GitSetup(settings);

    // Perform git init, first commit, and if able, push to remote repository.
    GitFinisher(settings);
    return 0;
}