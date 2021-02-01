/// Задание 3 (Базовый уровень)
/// Предложить реализацию класса-наследника абстрактного класса потокового ввода/вывода, обеспечивающего ввод/вывод через драйвер UART
#ifndef UThird
#define UThird
//===================
#include "1.h"
#include "4.h"
#include <vector>
//===================

class UARTio : myio
{
private:
	virtual DWORD WINAPI ReadThread(LPVOID) override;
	virtual DWORD WINAPI WriteThread(LPVOID) override;
	DWORD counter;
	HANDLE COMport;
	HANDLE readThread;
	HANDLE writeThread;
	OVERLAPPED overlapped;
	OVERLAPPED overlappedwr;
	unsigned char *bufwr;
	unsigned __int32 sizewr;

public:
	UARTio() {};
	~UARTio() { Close(); }
	Queue<unsigned __int8> BufferRead;

	virtual void BeginReadAsync() override;
	virtual void EndReadAsync() override;

	virtual void BeginWriteAsync(unsigned __int8* _bufwr, unsigned __int32 size) override;

	virtual void Close() override;
};
#endif