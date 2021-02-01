/// Задание 1 (Базовый уровень)
/// Предложить интерфейс абстрактного базового класса (интерфейса) потокового ввода/вывода
#ifndef UFirst
#define UFirst
//===================
#include <windows.h>
//===================
using namespace std;
class myio 
{
private:
	// Потоки чтения/записи
	virtual DWORD WINAPI ReadThread(LPVOID) = 0;
	virtual DWORD WINAPI WriteThread(LPVOID) = 0;

public:
	// Старт потоков
	virtual void BeginReadAsync() = 0;
	virtual void BeginWriteAsync(unsigned __int8* bufwr, unsigned __int32 size) = 0;
	// Закрытие потоков
	virtual void EndReadAsync() = 0;

	// Закрывает потоки и очищает все ресурсы
	virtual void Close() = 0;
};
#endif