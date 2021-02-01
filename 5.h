/// Задание 5
/// Релизовать вспомогательную шаблонную функцию,
/// реализующую выполнение заданной лямбда-функции для каждого члена заданного экземпляра std::tuple
#ifndef _UThird
#define _UThird
//===================
#include <tuple>
//===================
using namespace std;

template <size_t I = 0, typename ... Ts, typename F>
void tuple_foreach(tuple<Ts...> tup, const F& f)
{
	if constexpr (I == sizeof...(Ts)) return;
	else 
	{
		f(get<I>(tup));
		tuple_foreach<I + 1>(tup, f);
	}
}
#endif