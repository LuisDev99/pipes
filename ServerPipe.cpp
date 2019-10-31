// NamedPipeServer.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
	puts("NAMED PIPE SERVER\n*****************");
	// NamedPipe Local Variable
	HANDLE hCreateNamedPipe;
	char szInputBuffer[1023];
	char szOutputBuffer[1023];
	DWORD dwszInputBuffer = sizeof(szInputBuffer);
	DWORD dwszOutputBuffer = sizeof(szOutputBuffer);

	// ConnectNamedPipe Local Variable
	BOOL bConnectNamedPipe;

	// WriteFile Local Variable
	BOOL bWriteFile;
	char szWriteFileBuffer[1023] = "Hello from NamedPipe Server!";
	DWORD dwWriteBufferSize = sizeof(szWriteFileBuffer);
	DWORD dwNoBytesWrite;

	// Flush Buffer
	BOOL bFlushFileBuffer;

	// ReadFile Local Variable
	BOOL bReadFile;
	char szReadFileBuffer[1023];
	DWORD dwReadBufferSize = sizeof(szWriteFileBuffer);
	DWORD dwNoBytesRead;

	// CreateNamedPipe - Step 1
	hCreateNamedPipe = CreateNamedPipe(
		"\\\\.\\pipe\\MYNAMEDPIPE",
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
		PIPE_UNLIMITED_INSTANCES,
		dwszOutputBuffer,
		dwszInputBuffer,
		0,
		NULL
	);

	if (hCreateNamedPipe == INVALID_HANDLE_VALUE) {
		cout << "NamedPipe creation failed with error number: " << GetLastError() << endl;
	}
	cout << "NamedPipe creation is successful" << endl;

	// ConnectNamedPipe - Step 2
	bConnectNamedPipe = ConnectNamedPipe(hCreateNamedPipe, NULL);
	if (bConnectNamedPipe == FALSE) {
		cout << "Connection failed with error number: " << GetLastError() << endl;
	}
	cout << "ConnectNamedPipe connection is successful" << endl;

	// WriteFile Operation - Step 3
	bWriteFile = WriteFile(
		hCreateNamedPipe,
		szWriteFileBuffer,
		dwWriteBufferSize,
		&dwNoBytesWrite,
		NULL
	);

	if (bWriteFile == FALSE) {
		cout << "WriteFile Failed = " << GetLastError() << endl;
	}
	cout << "WriteFile is successful" << endl;

	// Flush the File Buffer - Step 4
	bFlushFileBuffer = FlushFileBuffers(hCreateNamedPipe);
	if (bFlushFileBuffer == FALSE) {
		cout << "FlushFileBuffer failed with error number: " << GetLastError() << endl;
	}
	cout << "FlushFileBuffer is successful" << endl;

	// ReadFile - Step 5
	bReadFile = ReadFile(
		hCreateNamedPipe,
		szReadFileBuffer,
		dwReadBufferSize,
		&dwNoBytesRead,
		NULL
	);

	if (bReadFile == FALSE) {
		cout << "ReadFile Failed = " << GetLastError() << endl;
	}
	cout << "ReadFile is successful" << endl;

	cout << "DATA READING FROM CLIENT -> " << szReadFileBuffer << endl;

	// DisconnectNamedPipe - Step 6
	DisconnectNamedPipe(hCreateNamedPipe);

	// CloseHandle- Step 7
	CloseHandle(hCreateNamedPipe);

	system("PAUSE");
	return 0;
}