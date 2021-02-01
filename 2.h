/// Задание 2 (Базовый уровень)
/// Предложить интерфейс для класса-драйвера UART, обеспечивающий прием/передачу данных,
/// настройку параметров UART и конфигурирование пинов
#ifndef USecond
#define USecond
//===================
#include <windows.h>
#include <iostream>
//===================
class iUART
{
public:
	// Жив ли порт
	virtual bool isAlive() = 0;
	// Настройка параметров
	virtual bool Configure(DCB) = 0;
	virtual bool Configure(unsigned __int32 BaudRate, unsigned __int32 ByteSize, unsigned __int8 StopBits, unsigned __int8 Parity) = 0;
	// Конфигурирование пинов
	virtual bool SetGPIO(unsigned __int8 gpio, bool state) = 0;

	// Запись в устройство
	// Записать 1 байт
	virtual bool WriteByte(unsigned __int8) = 0;
	// Записать N байт 
	virtual bool WriteBuff(unsigned __int8*, unsigned __int32) = 0;

	// Чтение из устройства c таймаутом
	// Считать 1 байт
	virtual unsigned __int8 ReadByte(unsigned __int32 timeout) = 0;
	// Считывать, пока не встретится end character
	virtual unsigned __int8* ReadBuff(unsigned __int8 ec, unsigned __int32 timeout) = 0;
	// Считать N байт
	virtual unsigned __int8* ReadBuff(unsigned __int32 n, unsigned __int32 timeout) = 0;
};
#endif
/*
реализация.h

class UART : iUART
{
private:
	HANDLE hCOM;

public:
	UART(wstring PortName, DCB config);
	UART(wstring PortName, unsigned __int32 BaudRate, unsigned __int32 ByteSize, unsigned __int8 StopBits, unsigned __int8 Parity);

	virtual bool isAlive() override;
	virtual bool Configure(DCB config) override;
	virtual bool Configure(unsigned __int32 BaudRate, unsigned __int32 ByteSize, unsigned __int8 StopBits, unsigned __int8 Parity) override;

	virtual bool WriteByte(unsigned __int8 byte) override;
	virtual bool WriteBuff(unsigned __int8* buff, unsigned __int32 size) override;

	virtual unsigned __int8 ReadByte(unsigned __int32 timeout = 5000) override;
	virtual unsigned __int8* ReadBuff(unsigned __int8 ec, unsigned __int32 timeout = 5000) override;
	virtual unsigned __int8* ReadBuff(unsigned __int32 count, unsigned __int32 timeout = 5000) override;
};
//===================
реализация.срр

UART::UART(wstring PortName, unsigned __int32 BaudRate, unsigned __int32 ByteSize, unsigned __int8 StopBits, unsigned __int8 Parity)
{
	hCOM = ::CreateFile(PortName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (hCOM == INVALID_HANDLE_VALUE)
		cerr << "Wrong port name\n";

	if (!Configure(BaudRate, ByteSize, StopBits, Parity))
		cerr << "Failed to initialize\n";
}

UART::UART(wstring PortName, DCB config)
{
	hCOM = ::CreateFile(PortName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (hCOM == INVALID_HANDLE_VALUE)
		cerr << "Wrong port name\n";

	if (!Configure(config))
		cerr << "Failed to initialize\n";
}

bool UART::Configure(unsigned __int32 BaudRate, unsigned __int32 ByteSize, unsigned __int8 StopBits, unsigned __int8 Parity)
{
	DCB dcbSerialParams = { 0 };
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	dcbSerialParams.BaudRate = BaudRate;
	dcbSerialParams.ByteSize = ByteSize;
	dcbSerialParams.StopBits = StopBits;
	dcbSerialParams.Parity = Parity;

	return SetCommState(hCOM, &dcbSerialParams);
}

bool UART::isAlive()
{
	DCB dcbSerialParams = { 0 };
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	return GetCommState(hCOM, &dcbSerialParams);
}

bool UART::Configure(DCB config)
{
	return SetCommState(hCOM, &config);
}


bool UART::WriteByte(unsigned __int8 byte)
{
	DWORD Written;
	if (WriteFile(hCOM, (unsigned __int8*)byte, 1, &Written, NULL))
		return Written;
	return false;
}

bool UART::WriteBuff(unsigned __int8* byte, unsigned __int32 size)
{
	DWORD Written;
	if (WriteFile(hCOM, byte, size, &Written, NULL))
		return Written == size;
	return false;
}

unsigned __int8 UART::ReadByte(unsigned __int32 timeout)
{
	DWORD count;
	unsigned __int8 sReceivedChar;
	unsigned __int64 start = GetTickCount64();

	while (start + timeout >= GetTickCount64())
		if (ReadFile(hCOM, &sReceivedChar, 1, &count, NULL))
			if (count)
				return sReceivedChar;
	return -1;
}

unsigned __int8* UART::ReadBuff(unsigned __int8 ec, unsigned __int32 timeout)
{
	DWORD count;
	unsigned __int8 sReceivedChar;
	unsigned __int8* buffer = (unsigned __int8*)malloc(255);;
	unsigned __int64 start = GetTickCount64();

	while (start + timeout >= GetTickCount64())
		if (ReadFile(hCOM, &sReceivedChar, 1, &count, NULL))
			if (count == ec)
				return buffer;
}

unsigned __int8* UART::ReadBuff(unsigned __int32 vCount, unsigned __int32 timeout)
{
	DWORD count = 0;
	DWORD overcount;
	unsigned __int8* sReceivedChar;
	unsigned __int8* buffer = (unsigned __int8*)malloc(255);
	bool overread = false;
	unsigned __int64 start = GetTickCount64();

	while (start + timeout >= GetTickCount64())
		if (ReadFile(hCOM, &sReceivedChar, vCount, &overcount, NULL))
			if (!overread && overcount >= vCount)
				return sReceivedChar;
			else
			{
				for (int i = 0; i < overcount; i++)
					buffer[count + i] = sReceivedChar[i];
				count += overcount;
				if (count >= vCount) return buffer;
			}
}
*/