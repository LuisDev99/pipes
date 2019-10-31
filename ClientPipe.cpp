// NamedPipeClient.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
    puts("NAMED PIPE CLIENT\n***************");
    // Local Variable Definitions
    HANDLE hCreateFile;

    // ReadFile Local Variable Definitions
    BOOL bReadFile;
    DWORD dwNoBytesRead;
    char szReadFileBuffer[1023];
    DWORD dwReadFileBufferSize = sizeof(szReadFileBuffer);
    
    // WriteFile Local Variable Definitions
    BOOL bWriteFile;
    DWORD dwNoBytesWrite;
    char szWriteFileBuffer[1023] = "Hello from NamedPipe Client!";
    DWORD dwWriteFileBufferSize = sizeof(szWriteFileBuffer);

    // CreateFile for Pipe
    hCreateFile = CreateFile(
        "\\\\.\\pipe\\MYNAMEDPIPE",
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (INVALID_HANDLE_VALUE == hCreateFile) {
        cout << "NamedPipeCreateFile.txt file creation has failed with error number: " << GetLastError() << endl;
        return -1;
    }

    cout << "NamedPipeCreateFile.txt file creation is successful" << endl;

    // ReadFile
    bReadFile = ReadFile(
        hCreateFile,
        szReadFileBuffer,
        dwReadFileBufferSize,
        &dwNoBytesRead,
        NULL
    );

    if (bReadFile == FALSE) {
        cout << "ReadFile has failed with error number: " << GetLastError() << endl;
    }

    cout << "ReadFile is successful" << endl;
    cout << "DATA READING FROM SERVER -> " << szReadFileBuffer << endl;

    // WriteFile
    bWriteFile = WriteFile(
        hCreateFile,
        szWriteFileBuffer,
        dwWriteFileBufferSize,
        &dwNoBytesWrite,
        NULL
    );

    if (bWriteFile == FALSE) {
        cout << "WriteFile has failed with error number: " << GetLastError() << endl;
        return -1;
    }

    6:22 - 6:47

    6:21:69      8:27:49

    8:39:41 - 8:40:60

    8:43:92 - 8:54:79

    10:29:81 - 10:57:74
    
    cout << "WriteFile is successful" << endl;

    CloseHandle(hCreateFile);
    system("PAUSE");
    return 0;
}