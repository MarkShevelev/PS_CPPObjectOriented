#include <iostream>
#include <algorithm>

//помимо инициализации в C++ есть специальный механизм для "деинициализации" (уничтожения) объектов,
//этот механизм выражается наличием у каждого объекта специального метода - деструктора
//если конструктор вызывается один раз до того, как мы начинаем использовать объект, вызывать методы,
//то деструктор - это его противоположность
//деструктор вызвается один раз перед тем, как объект станет недоступен, умрёт

class WithDestructor {
private:
	int index;

public:
	WithDestructor(int in_index) { index = in_index;  std::cout << "Construct: " << index << std::endl; }

	//деструктор объявляется без возвращаемого типа, как конструктор, а название его совпадает с названием класса, но предварительно ставится знак ~
	~WithDestructor() { std::cout << "Destructor: " << index << std::endl; }
};

void destructor_test1() {
	WithDestructor object1(1);

	{
		WithDestructor object2(2);
	}

	WithDestructor object3(3);
}

//В отличие от конструктора в классе может быть описан только один деструктор и он обязательно вызывается без параметров

//добавление деструкторов помогло в С++ справиться с проблемами управления ресурсами, например, динамической памятью
class IntArray {
	int *data;
	size_t size;

public:
	IntArray(size_t in_size) { 
		size = 0; 
		//конструктор занимает необходимые данные
		if (nullptr != (data = new (std::nothrow) int[in_size]))
			size = in_size;
	}

	size_t getSize() { return size; }

	int get(size_t idx) {
		return data[idx];
	}

	void set(size_t idx, int x) {
		data[idx] = x;
	}

	//метод для изменения контролируемой динамической памяти
	bool resize(size_t new_size) {
		int *tmp = new (std::nothrow) int[new_size];
		if (nullptr == tmp) return false;
		std::copy(data, data + size, tmp);
		delete[] data;
		data = tmp;
		size = new_size;
		return true;
	}

	~IntArray() {
		//деструктор возвращает память системе
		delete[] data;
	}
};

void destructor_test2() {
	IntArray arr(1);
	if (0 == arr.getSize()) {
		std::cout << "Can't initialize array" << std::endl;
		return;
	}

	int user_input; size_t pos = 0;
	do {
		std::cin >> user_input;
		if (0 == user_input) break;
		if (pos == arr.getSize() && !arr.resize(arr.getSize()*2)) {
			std::cout << "Not enought memory!" << std::endl;
			break;
		}

		arr.set(pos++, user_input);
		std::cout << arr.getSize() << std::endl;
	} while (true);
}

int main() {
	if (false) destructor_test1();
	if (false) destructor_test2();

	return 0;
}