#include <iostream>

//помимо инициализации в C++ есть специальный механизм дл€ "деинициализации" (уничтожени€) объектов,
//этот механизм выражаетс€ наличием у каждого объекта специального метода - деструктора
//если конструктор вызываетс€ один раз до того, как мы начинаем использовать объект, вызывать методы,
//то деструктор - это его противоположность
//деструктор вызваетс€ один раз перед тем, как объект станет недоступен, умрЄт

class WithDestructor {
private:
	int index;

public:
	WithDestructor(int in_index) { index = in_index;  std::cout << "Construct: " << index << std::endl; }

	//деструктор объ€вл€етс€ без возвращаемого типа, как конструктор, а название его совпадает с названием класса, но предварительно ставитс€ знак ~
	~WithDestructor() { std::cout << "Destructor: " << index << std::endl; }
};

void destructor_test1() {
	WithDestructor object1(1);

	{
		WithDestructor object2(2);
	}

	WithDestructor object3(3);
}

int main() {
	if (true) destructor_test1();

	return 0;
}