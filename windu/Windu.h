// This header includes the stuff that is always supposed to work,
// and furthermore introduces some nice tools
using namespace std;
	
#if __cplusplus >= 201103L
// Members of support_operation should test whether or not an operator works for a
// given class
#include <iostream>
struct support_operation {
	template<class T>
	static auto test_write(T * p) -> decltype(std::cout << *p, std::true_type());

	template<class>
	static auto test_write(...) -> std::false_type;

	template<class T>
	static auto test_read(T * p) -> decltype(std::cin >> *p, std::true_type());

	template<class>
	static auto test_read(...) -> std::false_type;
};

template<class T>
struct test_write : decltype(support_operation::test_write<T>(0))
{};

template<class T>
struct test_read : decltype(support_operation::test_read<T>(0))
{};

#include "Histogram.h"
#include "HistCalc.h"
#include "Event.h"
#include "EventList.h"

#else
#pragma message "\n---\nWindu requires C++11, but you are compiling using an older standard!\n"\
				"Please compile using gcc v. > 4.7 with the -std=c++11 flag.\n---\n"
#endif