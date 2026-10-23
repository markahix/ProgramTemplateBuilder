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

    return 0;
}