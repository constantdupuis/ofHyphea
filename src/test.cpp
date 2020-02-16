#include "test.h"
#include "ofMain.h"

template <class T>
test<T>::test()
{
	cout << "test::test\n";
}

template <class T>
test<T>::test(int data)
{
	cout << "test::test "<< data << "\n";
}

template <class T>
void test<T>::toto()
{
	cout << "test::toto\n";
}
