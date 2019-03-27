#include <iostream>
#include <algorithm>

//����������� ����� ���� ��������� ������ ������ �� ������� ��� ������������� ��������
//�� ������ �������, ������� ����������� ��� ��������������� �������� ����� ��������������
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

//����� ��� ������ ������� ��������, ������� ������� �� ������� ��� ������ �����
//�� ����� �������, �������  ����������� ��� �������� �������� ����� �������
int* filter_even(int *begin, int *end) {
	auto res = begin;
	while (begin != end) {
		if (!(0 == *begin%2)) { //��������� ���������� ������ � ���� ������������ �������!
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

//� ����� ���������� ���� ����� ���������, ������� �� ������� �� ����, �� ������ ������� �� ������� ��������
//�������� ������ �������
//�� �� ����� ������� ����� �������� �������������, ���� �� ���������� ������� � �������� ���������
/*
int* filter(int *begin, int *end, <�������>) {
	auto res = begin;
	while (begin != end) {
		if (!(<�������>)) { 
			*res = *begin;
			++res;
		}
		++begin;
	}
	return res;
}
*/
//�������� ��������� ������ �������� "������������"
//��� ����� ���������, ������� �� ������� �� ����, � ������ ��������� ������� ��� ����� ����, � ������ �� ��������� �� �������
//��� �� �����, ����� ��������� � ���������� ������������ �������, �����, ��� ��� ����� ��������� ��� ������� ����������� ��������!

//��� ������� ���� �������� � ����� �� ������������ ����������� ����������� - ��������� �� �������
//��������� � ����� ���� ���� ����������
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
//bool (*condition)(int) - ����������� �������������� �����������, ������� ��������� �����������, ��� ���� �������� �������� ������� � �������� ����

bool is_positive(int x) { //������ ������ �������, ������������ bool � ����������� ���� int, ����� ���� ��������� � ���� bool (*condition)(int) 
	return x > 0;
}

bool is_even(int x) {
	return 0 == x % 2;
}

void filter_function_pointer_test() {
	int arr[10] = { 1,200,-1,0,3,-2,5,-4,-1,-2 };
	//�� ����� ������������ ���� � �� �� ������� filter_function_pointer ��� ���������� �� ��������� ��������
	{
		auto new_end = filter_function_pointer(arr, arr + 10, is_positive); //������� �������� �������!
		for (auto it = arr, end = new_end; it != end; ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
	}

	{
		auto new_end = filter_function_pointer(arr, arr + 10, is_even); //������� �������� �������!
		for (auto it = arr, end = new_end; it != end; ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
	}
}

//����������� ��������� ����� ������� �� ��������, �.�. ��������� � ������������ ��������� ��� ������ ����� ������, �� ������ ������������� ���� - �������� ����������������� � �������� �������������
//��������, ���� �������� ������������� ����������� �� ������ �������� - ����� ������� ��� - ��� ����� ���������� �������� ������� �������, � ���� ���������� ��������� �� ��� ����������� ���������
bool is_greater_than_hundred(int x) {
	return x > 100;
}

void filter_greater_than_hundred_test() {
	int arr[10] = { 1,200,-1,0,3,-2,5,-4,-1,-2 };
	auto new_end = filter_function_pointer(arr, arr + 10, is_greater_than_hundred); //������� �������� �������!
	for (auto it = arr, end = new_end; it != end; ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

//������ ����������� ��������� C/C++ �������� �� ����� ��������
//��������, ����������� �������� std::for_each �� ��������� algorithm ��������� ��������� ����� ������� � ������� �������� �������
void print_int(int x) { //���� ������� � �����������, ��� �� ����� ���������� ��������
	std::cout << x << " ";
}

void for_each_test() {
	int arr[10] = { 1,200,-1,0,3,-2,5,-4,-1,-2 };
	std::for_each(arr, arr + 10, print_int);
	std::cout << std::endl;
}

//���� ���������� ������������� ������ �������, �� ���������� �������� std::transform
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