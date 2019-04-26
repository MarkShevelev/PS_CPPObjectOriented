#include <iostream>
#include <algorithm>
#include <vector>
#include <string>


//Мы знаем, что с использованием стандартных алгоритмов можно быстро решать задачи простых статистик в наборе данных, представленных массивом

//для считывания значений
int ask() {
	int user_input;
	std::cin >> user_input;
	return user_input;
}

//для возведения в квадрат
int sqr(int x) { return x * x;  }

//для печати значений
template <typename T>
void print(T x) { std::cout << x << ' ';  }

void algorithm_test() {
	int arr[10]; //создаём массив из 10 элементов
	std::generate(arr, arr + 10, ask);//запрашиваем элементы с клавиатуры
	std::transform(arr, arr + 10, arr, sqr); //возводим в квадрат
	std::for_each(arr, arr + 10, print<int>); //печатаем элементы
	std::cout << std::endl;
}

//при работе с массивами, мы обращаемся к промежутку массива как к промежутку адресов
//при работе с вектором нам придётся использовать иную идею - итераторы
void vector_algorithm_test() {
	std::vector<int> vec(10); //вектор из 10 элементов
	std::generate(vec.begin(), vec.end(), ask); //.begin() - метод для получения специального объекта - итератора, который "указывает" на начало вектора, а .end(), соответственно на конец, т.е. на элемент сразу за концом вектора
	std::transform(vec.begin(), vec.end(), vec.begin(),sqr);
	std::for_each(vec.begin(), vec.end(), print<int>);
	std::cout << std::endl;
}

//для универсальности алгоритмов они не являются функциями, ориентированными на указатели
//стандартные алгоритмы - это шаблонные функции, которые могут быть сконструированы для промежутка, указанного в любом типе
//пример возможной реализации for_each
template<typename Iter,typename Fn>
void my_for_each(Iter begin, Iter end, Fn callback) {
	for (; begin != end; ++begin) //для того, чтобы данный алгоритм успешно работал с итераторами, достаточно того, чтобы на типе Iter можно было применять операции ++ != и *(разыменование) 
		callback(*begin);
}

//проверим наш алгоритм на std::vector и на массиве
void my_for_each_test() {
	std::vector<double> vec = { 1.1,2.2,3.3,-1.1,-2.2,-3.3 };
	char arr[6] = "Hello";

	my_for_each(vec.begin(), vec.end(), print<double>);
	std::cout << std::endl;
	my_for_each(arr, arr + 5, print<char>);
	std::cout << std::endl;
}

//некоторые из необходимых для my_for_each операторов мы уже умеем перегружать
//необхоимо научиться перегружать оператор *

class AsteriskOverload {
	int i;
public:
	AsteriskOverload(int i): i(i) { }

	int operator*() const { //если в круглых скобках нет параметра, то это оператор разыменования, если есть - умножения
		return i;
	}
};

void asterisk_operator_test() {
	AsteriskOverload asl(7);
	//std::cout << asl << std::endl;//сам объект нельзя вывести на экран...
	std::cout << *asl << std::endl; //а разыменование можно, т.к. при применении звёздочки получается целое число
}

//предположим, мы хотим взять целы числа в промеждутке от min до max и напечать нашим алгоритмом my_for_each
//мы не можем написать std::my_for_each(min,max,print<int>); т.к. transform будет пытаться применить операцию разыменования
/*void naive_my_for_each_test() {
	my_for_each(-10, 0, print<int>);
}*/
//класс, который моделирует диапазон чисел

//создадим класс Counter для этой цели
class Counter {
	int const start;
	int current;
	
public:
	Counter(int start) : start(start), current(start) { }

	Counter& operator++() {
		++current;
		return *this;
	}

	int operator*() {
		return current;
	}

	bool operator==(Counter const &oth) {
		return oth.current == current;
	}

	bool operator!=(Counter const &oth) {
		return !(oth.current == current);
	}
};

void counter_my_for_each_test() {
	my_for_each(Counter(-10), Counter(0), print<int>);
}

//итераторы, которые используются в стандартной библиотеке должны дополнительно указать ряд своих свойств

#include <iterator>
class IterCounter {
	int const start;
	int current;

public:
	typedef int       value_type;
	typedef int       difference_type;
	typedef int*      pointer;
	typedef int&      reference;

	typedef std::forward_iterator_tag  iterator_category;

	IterCounter(int start) : start(start), current(start) { }

	IterCounter& operator++() {
		++current;
		return *this;
	}

	IterCounter& operator++(int v) {
		IterCounter tmp(*this);
		++*this;
		return tmp;
	}

	int& operator*() {
		return current;
	}

	int operator*() const {
		return current;
	}

	bool operator==(IterCounter const &oth) {
		return oth.current == current;
	}

	bool operator!=(IterCounter const &oth) {
		return !(oth.current == current);
	}
};

void itercounter_test() {
	std::for_each(Counter(-10), Counter(0), print<int>);
}

//в некоторых случаях от итератора требуется дополнительно перегрузить оператор ->
//например, если мы работаем в векторе со структурами

struct Person {
	std::string name, familyname;
	bool operator==(Person const &p) {
		return name == p.name && familyname == p.familyname;
	}
};

void vector_iterator_test() {
	std::vector<Person> persons({ {"Boris","Bolkan"}, {"Dean","Corson"}, {"Liana","Telfer"}, {"Viktor","Fargas"} });
	std::vector<Person>::iterator res = std::find(persons.begin(), persons.end(), Person{ "Liana","Telfer" });
	//алгоритм find возвращает итератор на нужный нам элемент
	//выведем на экран данные
	std::cout << (*res).name << " " << (*res).familyname << std::endl; //это допустимо, но мы бы хотели использовать привычный механизм ->
	std::cout << res->name << " " << res->familyname << std::endl; //обратим внимание, что -> применяется к типу std::vector<Person>::iterator, который вовсе не обязан быть указателем
}

int main() {
	if (false) my_for_each_test();
	if (false) asterisk_operator_test();
	if (false) counter_my_for_each_test();
	if (false) itercounter_test();
	if (false) vector_iterator_test();

	return 0;
}
