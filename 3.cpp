#include "3.h"

DWORD WINAPI UARTio::ReadThread(LPVOID)
{
	COMSTAT comstat;
	DWORD btr, temp, mask, signal;
	overlapped.hEvent = CreateEvent(NULL, true, true, NULL);
	SetCommMask(COMport, EV_RXCHAR);
	while (1)
	{
		WaitCommEvent(COMport, &mask, &overlapped);
		signal = WaitForSingleObject(overlapped.hEvent, INFINITE);
		if (signal == WAIT_OBJECT_0)
			if (GetOverlappedResult(COMport, &overlapped, &temp, true))
				if ((mask & EV_RXCHAR) != 0)
				{
					ClearCommError(COMport, &temp, &comstat);
					btr = comstat.cbInQue;
					unsigned __int8 bufrd[256];
					if (btr)
					{
						ReadFile(COMport, bufrd, btr, &temp, &overlapped);
						counter += btr;
						for (int i = 0; i < btr; i++)
							BufferRead.Push(bufrd[i]);
					}
				}
		Sleep(0);
	}
}

DWORD WINAPI UARTio::WriteThread(LPVOID)
{
	DWORD temp;
	overlappedwr.hEvent = CreateEvent(NULL, true, true, NULL);
	WriteFile(COMport, bufwr, sizewr, &temp, &overlappedwr);
	WaitForSingleObject(overlappedwr.hEvent, INFINITE);
	SuspendThread(writeThread);
	CloseHandle(overlappedwr.hEvent);
}

void UARTio::BeginReadAsync()
{	 
	readThread = CreateThread(NULL, 0, ReadThread, NULL, 0, NULL);
}	 
	 
void UARTio::EndReadAsync()
{	 
	if (readThread)
		TerminateThread(readThread, 0);
	CloseHandle(overlapped.hEvent); 
	CloseHandle(readThread);
}	 
	 
void UARTio::BeginWriteAsync(unsigned __int8* _bufwr, unsigned __int32 _size)
{	 
	bufwr = _bufwr; sizewr = _size;
	writeThread = CreateThread(NULL, 0, WriteThread, NULL, CREATE_SUSPENDED, NULL);
}	 
	 
void UARTio::Close()
{	 
	EndReadAsync();
	if (writeThread)
		TerminateThread(writeThread, 0);
	CloseHandle(writeThread);
	CloseHandle(overlappedwr.hEvent);
	PurgeComm(COMport, PURGE_TXCLEAR);
	CloseHandle(COMport);
}