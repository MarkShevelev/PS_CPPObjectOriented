#include <iostream>

//простейший класс, моделирующий счётчик
class IntCounter {
	int i;
public:
	IntCounter(int i) { IntCounter::i = i; }
	IntCounter() : IntCounter(0) { }

	int next() { return i++; }
	void reset() { i = 0; }
};

//работа с указателями и размещение объектов в динамической памяти
void pointers_to_objects() {
	IntCounter c;           //создание объекта
	IntCounter &c_ref = c;  //ссылка на объект
	IntCounter *c_ptr = &c; //указатель на объект

	//при работе со ссылками код эквивалентен работе с объектами
	for (int p = 0; p != 10; ++p)
		std::cout << c_ref.next() << " ";
	std::cout << std::endl;

	//при работе с указателями можно использовать разыменование (*) и ->
	for (int p = 0; p != 10; ++p)
		std::cout << c_ptr->next() << " ";
	std::cout << std::endl;

	//создание объектов в динамической памяти
	IntCounter *new_default = new (std::nothrow) IntCounter(); //без параметров
	IntCounter *new_param = new (std::nothrow) IntCounter(-10); //с параметром
	IntCounter *new_array = new (std::nothrow) IntCounter[10];

	delete new_default;
	delete new_param;
	delete[] new_array;

}

//простой класс для вывода значения указателя this
class ThisAware {
	int index;
public:
	ThisAware(int index) {
		ThisAware::index = index;
	}

	void print() {
		std::cout << index << ": " << this << std::endl;
	}
};

//this - это ключевое слово, которое позволяет получить адрес объекта, на котором был вызван метод
void this_test() {
	ThisAware a1(1), a2(2), a3(3);
	std::cout << &a1 << " ";
	a1.print();

	std::cout << &a2 << " ";
	a2.print();

	std::cout << &a3 << " ";
	a3.print();
} 

//использование ключевого слова this, для того чтобы разрешать внутренние имена
class ThisAware2 {
	int index;
public:
	ThisAware2(int index) {
		//this - адрес, к нему можно применять разыменование
		this->index = index;
	}

	void print() {
		std::cout << this->index << ": " << this << std::endl;
	}
};

//использование ключевого слова this на определение совпадения объектов
class ThisAware3 {
	int index;
public:
	ThisAware3(int index) {
		this->index = index;
	}

	bool check(ThisAware3 *address) {
		return this == address;
	}
};

void address_check_test() {
	ThisAware3 a(1);
	ThisAware3 b(2);
	ThisAware3 &a_ref = a;

	std::cout << std::boolalpha << a.check(&b) << " " << a.check(&a_ref) << std::endl;
}

int main() {
	if (false) pointers_to_objects();
	if (false) this_test();
	if (false) address_check_test();

	return 0;
}