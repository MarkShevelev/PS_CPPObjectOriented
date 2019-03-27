#include <iostream>
#include <algorithm>

//Предположим перед нами поставили задачу убрать из массива все положительные элементы
//Мы создаём функцию, которая располагает все неположительные элементы перед положительными
int* filter_positive(int *begin, int *end) {
	auto res = begin;
	while (begin != end) {
		if (!(*begin > 0)) {
			*res = *begin;
			++res;
		}
		++begin;
	}
	return res;
}

void test_filter_positive() {
	int arr[10] = { 1,200,-1,0,3,-2,5,-4,-1,-2};
	auto new_end = filter_positive(arr, arr + 10);
	for (auto it = arr, end = new_end; it != end; ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

//Затем нас просят создать алгоритм, который убирает из массива все чётные числа
//Мы пишем функцию, которая  располагает все нечётные элементы перед чётными
int* filter_even(int *begin, int *end) {
	auto res = begin;
	while (begin != end) {
		if (!(0 == *begin%2)) { //алгоритмы отличаются только в этой единственной строчке!
			*res = *begin;
			++res;
		}
		++begin;
	}
	return res;
}

void test_filter_even() {
	int arr[10] = { 1,200,-1,0,3,-2,5,-4,-1,-2 };
	auto new_end = filter_even(arr, arr + 10);
	for (auto it = arr, end = new_end; it != end; ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

//У обоих алгоритмов есть общая структура, которая не зависит от того, по какому условию мы убираем элементы
//меняется только условие
//мы бы могли сделать такой алгоритм универсальным, если бы передавали условие в качестве параметра
/*
int* filter(int *begin, int *end, <условие>) {
	auto res = begin;
	while (begin != end) {
		if (!(<условие>)) { 
			*res = *begin;
			++res;
		}
		++begin;
	}
	return res;
}
*/
//Подобные алгоритмы иногда называют "полиморфными"
//Это такие алгоритмы, которые не зависят от того, с какими конкретно данными они имеют дело, а только от некоторых их свойств
//нам не важно, какое конкретно в фильтрации используется условие, важно, что его можно проверить для каждого конкретного элемента!

//для решения этой проблемы в языке Си используются специальные конструкции - указатели на функции
//перепишем в таком виде нашу фильтрацию
int* filter_function_pointer(int *begin, int *end, bool(*condition)(int)) {
	auto res = begin;
	while (begin != end) {
		if (!(condition(*begin))) {
			*res = *begin;
			++res;
		}
		++begin;
	}
	return res;
}
//bool (*condition)(int) - специальная синтаксическая конструкция, которая указывает компилятору, что этот параметр является адресом в сегменте кода

bool is_positive(int x) { //только адреса функций, возвращающих bool и принимающие один int, могут быть сохранены в типе bool (*condition)(int) 
	return x > 0;
}

bool is_even(int x) {
	return 0 == x % 2;
}

void filter_function_pointer_test() {
	int arr[10] = { 1,200,-1,0,3,-2,5,-4,-1,-2 };
	//мы можем использовать одну и ту же функцию filter_function_pointer для фильтрации по различным условиям
	{
		auto new_end = filter_function_pointer(arr, arr + 10, is_positive); //передаём название функции!
		for (auto it = arr, end = new_end; it != end; ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
	}

	{
		auto new_end = filter_function_pointer(arr, arr + 10, is_even); //передаём название функции!
		for (auto it = arr, end = new_end; it != end; ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
	}
}

//полиморфные алгоритмы очень полезны на практике, т.к. позволяют с минимальными затратами сил решать новые задачи, на основе существующего кода - повышают переиспользование и качество сопровождения
//например, если появится необходимость фильтровать по новому признаку - числа меньшие ста - нам будет достаточно написать функцию условия, а саму фильтрацию проводить по уже написанному алгоритму
bool is_greater_than_hundred(int x) {
	return x > 100;
}

void filter_greater_than_hundred_test() {
	int arr[10] = { 1,200,-1,0,3,-2,5,-4,-1,-2 };
	auto new_end = filter_function_pointer(arr, arr + 10, is_greater_than_hundred); //передаём название функции!
	for (auto it = arr, end = new_end; it != end; ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

//многие стандартные алгоритмы C/C++ работают по этому принципу
//например, стандартный алгоритм std::for_each из заголовка algorithm позволяет применить любую функцию к каждому элементу массива
void print_int(int x) { //хотя функция и применяется, она не может возвращать значение
	std::cout << x << " ";
}

void for_each_test() {
	int arr[10] = { 1,200,-1,0,3,-2,5,-4,-1,-2 };
	std::for_each(arr, arr + 10, print_int);
	std::cout << std::endl;
}

//если необходимо преобразовать данные массива, то существует алгоритм std::transform
int sqr_int(int x) {
	return x * x;
}

void transform_test() {
	int origin[10] = { 1,200,-1,0,3,-2,5,-4,-1,-2 };
	int destination[10];
	std::transform(origin, origin + 10, destination, sqr_int);
	std::for_each(destination, destination + 10, print_int);
	std::cout << std::endl;
}

int main() {
	if (false) test_filter_positive();
	if (false) test_filter_even();
	if (false) filter_function_pointer_test();
	if (false) filter_greater_than_hundred_test();
	if (false) for_each_test();
	if (false) transform_test();

	return 0;
}