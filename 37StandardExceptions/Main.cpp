//� ����� C++ ���������� ������� ����������� ����������
/*
std::exception <exception> interface (debatable if you should catch this)
	std::bad_alloc <new> failure to allocate storage
		std::bad_array_new_length <new> invalid array length
	std::bad_cast <typeinfo> execution of an invalid dynamic-cast
	std::bad_exception <exception> signifies an incorrect exception was thrown
	std::bad_function_call <functional> thrown by "null" std::function
	std::bad_typeid <typeinfo> using typeinfo on a null pointer
	std::bad_weak_ptr <memory> constructing a shared_ptr from a bad weak_ptr
	std::logic_error <stdexcept> errors detectable before the program executes
		std::domain_error <stdexcept> parameter outside the valid range
		std::future_error <future> violated a std::promise/std::future condition
		std::invalid_argument <stdexcept> invalid argument
		std::length_error <stdexcept> length exceeds its maximum allowable size
		std::out_of_range <stdexcept> argument value not in its expected range
	std::runtime_error <stdexcept> errors detectable when the program executes
		std::overflow_error <stdexcept> arithmetic overflow error.
		std::underflow_error <stdexcept> arithmetic underflow error.
		std::range_error <stdexcept> range errors in internal computations
		std::regex_error <regex> errors from the regular expression library.
		std::system_error <system_error> from operating system or other C API
			std::ios_base::failure <ios> Input or output error
*/

//� ���� ����������� ���������� ���� ���� ����� ������: std::exception
//std::exception - ��� ���������, ������� ���������� ���� ����� ����������� �����
//char const * what() const 
//���� ����� ��������� �������� ���������� �� ��������� �������� � ���� ������ ��

//����������� std::exception ����� ��������� �� ��� ������� ������:
//i) std::runtime_error � ��� ����������
//    ��� ������ �������� � ���� ������, ������� ��������� ��������� �������� ������� ����������,
//    �.�. �����, ������� ������ ��� ����������� ������ ���������/����������� �� ����� ����������
//    ��������, ������ std::ios_base::failure ��������� ��� ������ ������ � ������, � ������ ����������� �������, �.�. ��� ����� ���� ������� ���������� ���������� ��
//ii) std::logic_error � ��� ����������
//    ��� ������ ������� � ���� ������, �������� ��������� ������������� ������, ��������� � �������� ����������� ����
//    ��������, std::out_of_range ��������� ��� ������ � ������� vector, ���� � ����� .at() ��������� �������� ������� ����������� ���-�� ��������� � �������
//    ����� ������ ����� ����� ��������, ���� ����� ���, ��� ������� .at(), �������� ������ ������� � ������
//iii) ���������������� �������� ������ �� std::exception, ��������, std::bad_alloc
//    ��� ������ ������������� �� ������� ������ ���������, ������� ���������� � �������� ���������� � �� ������ ������� � ���� ������ �������
//    �������� std::bad_alloc �������������, ��� �� ������� �������� ���������� ������, std::bad_exception �������������, ��� ������� ��� ����� ����������� ����������, ������� �� ����������������� �� ����������

//���������� ������� ������ � ������������

//������ �� ����������� �����������
//������: ��������� ������ ������� � ��������� ������� �������� ����� �� ��� �� ������
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
void vector_exception_test() {
	unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();

	std::vector<int> number_holder; //��� ������ ��������� �� �����, ���� �� �� ������� �������, �� ���������� ��� �� �������
	int max_number = 0;

	//�������� ���� ��������� � �������� ���� try, ������� ����� ����������� "��������������� ������"
	try {
		{//���������� ��������� ���������� �����
			std::default_random_engine e(seed);
			max_number = std::uniform_int_distribution<int>(0, 20)(e);
		}

		for (size_t i = 0; i != max_number; ++i)
			number_holder.push_back(0); //������ ����� push_back ����� �������� � std::bad_alloc

		{
			std::default_random_engine e(seed+1);
			std::uniform_int_distribution<int> dist(0, 20); //��������� ��������� ��������

			for (size_t cnt = 0; cnt != 5; ++cnt)
				number_holder.at(dist(e)) = 1; //������ ����� ��������� �� ���������
				
		}

		for (auto i : number_holder)
			std::cout << i << ' ';
		std::cout << std::endl;
	}
	catch (std::out_of_range &e) {
		std::cout << "Wrong index error: " << e.what() << std::endl;
	}
	catch (std::bad_alloc &e) { //��������������� ������, ��������� ����� ���������
		std::cout << "Memory allocation error: " << e.what() << std::endl;
	}
	catch (...) {
		std::cout << "Unpredictable exception has been thrown" << std::endl;
	}
}

int main() {
	if (true) vector_exception_test();

	return 0;
}
