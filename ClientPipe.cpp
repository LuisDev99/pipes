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
        "\\\\.\\pipe\\MYNAMEDPIPE",  //Si no compila por esta linea, usar este parametro: L"\\\\.\\pipe\\MYNAMEDPIPE",
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
    
    cout << "WriteFile is successful" << endl;

    CloseHandle(hCreateFile);
    system("PAUSE");
    return 0;
}