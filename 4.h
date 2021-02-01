/// Задание 4 (Базовый уровень)
/// Реализовать простую шаблонную циклическую очередь, безопасную для одновременной записи и чтения из двух потоков
/// (один читает, другой пишет), не использующей механизм взаимной блокировки потоков
#ifndef UFourth
#define UFourth
//===================
#include <cstdint>
#include <thread>
//===================
template <class T>
class Queue
{
private:
	bool* state;
	T* buffer;
	volatile int32_t tailPos;
	volatile size_t Current;
	volatile size_t Size;

public:
	Queue(const size_t& size) : Size(size), tailPos(0), Current(0)
	{
		buffer = static_cast<T*>(std::calloc(size + 1, sizeof(T)));
		state = static_cast<bool*>(std::calloc(size + 1, sizeof(bool)));
	}
	~Queue()
	{
		for(int i=0;i<Size;i++)
			if(state[i]) buffer[i].~T();

		free(buffer); free(state);
	}

	// Добавить элемент
	bool Push(const T& value)
	{
		if (state[tailPos])
			return false;
		
		if (tailPos == Size)
			if (!Current)
				return false;
			else
				tailPos = 0;

		state[tailPos] = true;

		new(buffer + tailPos++) T(value);
		
		return true;
	}

	// Взять элемент
	bool Pop(T& value)
	{
		if (Current == Size)
			Current = 0;
		
		if (!state[Current])
			return false;

		value = buffer[Current];

		
		state[Current] = false;
		buffer[Current++].~T();
		
		return true;
	}
};
#endif