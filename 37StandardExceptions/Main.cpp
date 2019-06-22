//В языке C++ существует система стандартных исключений
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

//у всех стандартных исключений есть один общий предок: std::exception
//std::exception - это интерфейс, который определяет один чисто виртуальный метод
//char const * what() const 
//этот метод позволяет получить информацию об ошибочной ситуации в виде строки Си

//Наследников std::exception можно разделить на три большие группы:
//i) std::runtime_error и его наследники
//    эта группа включает в себя классы, которые описывают ошибочные ситуации времени исполнения,
//    т.е. такие, которые нельзя или чрезвычайно сложно проверить/предсказать на этапе компиляции
//    например, ошибка std::ios_base::failure возникает при ошибке работы с файлом, её нельзя предсказать заранее, т.к. она может быть вызвана конкретным состоянием ОС
//ii) std::logic_error и его наследники
//    эта группа ключает в себя классы, кототоые описывают предсказуемые ошибки, связанные с неверным построением кода
//    например, std::out_of_range возникает при работе с классом vector, если в метод .at() передаётся значение индекса превышающее кол-во элементов в векторе
//    такой ошибки легко можно избежать, если перед тем, как вызвать .at(), сравнить размер вектора и индекс
//iii) непосредственные дочерние классы от std::exception, например, std::bad_alloc
//    эти классы сигнализируют об ошибках работы программы, которые происходят в процессе исполнения и их нельзя отнести к двум другим группам
//    например std::bad_alloc сигнализирует, что не удалось выделить достаточно памяти, std::bad_exception сигнализирует, что функция или метод сгенеровали исключение, которое не предусматривалось их контрактом

//Рассмотрим примеры работы с исключениями

//работа со стандартным контейнером
//Задача: заполняем вектор числами и случайным образом изменяем часть из них на другие
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
void vector_exception_test() {
	unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();

	std::vector<int> number_holder; //эти данные создаются на стеке, если их не удастся создать, то исключения уже не помогут
	int max_number = 0;

	//поместим нашу программу в основной блок try, который будет отлавливать "невосстановимые ошибки"
	try {
		{//генерируем случайное количество чисел
			std::default_random_engine e(seed);
			max_number = std::uniform_int_distribution<int>(0, 20)(e);
		}

		for (size_t i = 0; i != max_number; ++i)
			number_holder.push_back(0); //каждый вызов push_back может привести к std::bad_alloc

		{
			std::default_random_engine e(seed+1);
			std::uniform_int_distribution<int> dist(0, 20); //генератор случайных индексов

			for (size_t cnt = 0; cnt != 5; ++cnt)
				number_holder.at(dist(e)) = 1; //индекс может оказаться за пределами
				
		}

		for (auto i : number_holder)
			std::cout << i << ' ';
		std::cout << std::endl;
	}
	catch (std::out_of_range &e) {
		std::cout << "Wrong index error: " << e.what() << std::endl;
	}
	catch (std::bad_alloc &e) { //невосстановимая ошибка, программа будет завершена
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
