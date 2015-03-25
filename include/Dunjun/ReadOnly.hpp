#ifndef DUNJUN_READONLY_HPP
#define DUNJUN_READONLY_HPP

#include <utility>

namespace Dunjun
{
// NOTE(bill) TODO(bill): Not complete but works for most needs
//
// Makes member variables read-only except for that `Super` class
template <class T, class Super>
class ReadOnly
{
public:
	operator const T&() const { return data; }

private:
	friend Super;

	ReadOnly()
	: data{}
	{
	}

	ReadOnly(const T& t)
	: data{t}
	{
	}

	ReadOnly(T&& t)
	: data{std::move(t)}
	{
	}

	ReadOnly& operator=(const T& t)
	{
		data = t;
		return *this;
	}

	T* operator&() { return &data; }

	template <class U>
	U& operator*()
	{
		return *data;
	}

	bool operator==(const T& t) const { return data == t; }
	bool operator!=(const T& t) const { return !operator==(t); }

	// Does use not the `m_` prefix as it accessable within the Super class so
	// it is not technically private for that class (friend)
	// This will be the only exception to the private member variable prefix
	// rule of `m_`
	T data;
};

// Example:
//
// #include <cstdio>

// struct Thing
// {
// 	Thing()
// 	: x()
// 	{
// 	}

// 	Thing(int x)
// 	: x(x)
// 	{
// 	}

// 	void incrementX()
// 	{
// 		x.data++; // get raw data from x
// 	}

// 	ReadOnly<int, Thing> x;
// };

// void func()
// {
// 	Thing a(2);               // Initialize a.x = 2;
// 	printf("%i\n", (int)a.x); // 2 (cast a.x as `int` as a.x is technically a
// 	                          // `ReadOnly<int, Thing>` not an `int`)
// 	// a.x = 7; // error
// 	a.incrementX();
// 	printf("%i\n", (int)a.x); // 3
// }

} // namespace Dunjun

#endif
