#include <iostream>

#include "FileSystem/FileSystem.h"


int main(int argc, char** argv)
{
    std::cout << "Hello world\n";
    OutputFileStream stream = FileSystem::WriteFile("NewFolder/NewFolder/File.txt");
    if (!stream)
        return -1;

    return 0;
}
