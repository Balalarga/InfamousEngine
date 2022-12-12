#include <iostream>

#include "FileSystem/FileSystem.h"

int main(int argc, char** argv)
{
    std::cout << "Hello world\n";

    OutputFileStream stream = FileSystem::WriteFile("GeneratedFromCodeDirectory/GeneratedFile.txt");
    if (!stream)
        return -1;

    int a = 11;
    stream << a;

    return 0;
}
