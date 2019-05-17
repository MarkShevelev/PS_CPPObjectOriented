#include <iostream>
#include <string>
#include <vector>

//мы уже знакомы с пон€тием шаблона функции
//шаблон функции - это специальное описание, по которому компил€тор может создать функцию

//например функци€, возвод€ща€ в квадрат значени€ любого типа, дл€ которого можно вызвать оператор *
template <typename T>
auto Sqr(T const &t) {
	return t * t;
}

class MyComplex {
public:
	MyComplex(): MyComplex(0.,0.) { }
	MyComplex(double x, double y): x(x), y(y) { }
	MyComplex& operator*=(MyComplex const &oth) {
		double x = this->x*oth.x - this->y*oth.y, y = this->x*oth.y + this->y*oth.x;
		this->x = x; this->y = y;
		return *this;
	}
	
	friend std::ostream& operator<<(std::ostream &os, MyComplex const &z);
	friend std::istream& operator>>(std::istream &is, MyComplex &z);

private:
	double x, y;
};

std::ostream& operator<<(std::ostream &os, MyComplex const &z) {
	return os << z.x << " + " << z.y << "*I";
}
std::istream& operator>>(std::istream &is, MyComplex &z) {
	return is >> z.x >> z.y;
}
MyComplex operator*(MyComplex const &lha, MyComplex const &rha) {
	MyComplex tmp(lha);
	tmp *= rha;
	return tmp;
}

void sqr_template_test() {
	MyComplex a;
	std::cin >> a;
	std::cout << Sqr(a) << std::endl;

	double d;
	std::cin >> d;
	std::cout << Sqr(d) << std::endl;
}

//такой же механизм возможен и при определении классов
//мы можем написать шаблон с параметрами, который будет генерировать класс
template <typename T> //объ€вл€ем, что дальнейшее определение будет шаблоном и содержит неизвестный тип T
class Velocity {
public:
	Velocity() = default; //попытаетс€ инициализировать значени€ vx и vy значени€ми по умолчанию
	Velocity(T const &vx, T const &vy): vx(vx), vy(vy) { }

	Velocity& operator+=(Velocity const &oth) {
		vx += oth.vx; vy += oth.vy;
		return *this;
	}

	template<typename T>
	friend std::ostream& operator<<(std::ostream &os, Velocity<T> const &v);

	template<typename T>
	friend std::istream& operator>>(std::istream &is, Velocity<T> &v);

private:
	T vx, vy;
};

template<typename T> //так как в реализации тип T неизвестен, то оператор вывода должен быть шаблонным
std::ostream& operator<<(std::ostream &os, Velocity<T> const &v) {
	return os << "(" << v.vx << "," << v.vy << ")";
}

template<typename T>
std::istream& operator>>(std::istream &is, Velocity<T> &v) {
	return is >> v.vx >> v.vy;
}

void template_class_test() {
	//при создании объекта мы должны указать в угловых скобках типах
	Velocity<int> v_int(0, 1);
	Velocity<double> v_dbl(-1.1, 4.6);
	std::cout << "Velocity<int>: " << v_int << std::endl << "Velocity<double>: " << v_dbl << std::endl;
}

//мы уже сталкивались с шаблонами классов в стандартной библиотеке
//например, класс vector

//шаблоны классов, как и шаблоны функций, могут иметь несколько параметров
//определим шаблон класса, который позвол€ет хранить пару значений произвольных типов
template<typename T, typename U>
struct MyPair {
	T first;
	U second;
};

//параметры шаблона могут быть и обычными типами
//с помощью этого подхода мы можем создать шаблон класса, который хранит набор объектов на стеке, что может значительно ускорить работу с этими данными
template <typename T, size_t size>
class StackArray {
public:
	T operator[](size_t idx) const { return data[idx]; }
	T& operator[](size_t idx) { return data[idx]; }
	size_t Size() { return size; }

private:
	T data[size];
};

void stack_array_test() {
	size_t const size = 10;
	StackArray<int,size> arr;
	int variable = -1;

	for (int i = 0; i != size; ++i)
		arr[i] = i;

	for (int i = 0; i != size; ++i)
		std::cout << arr[i] << ' ';
	std::cout << std::endl;
}

int main() {
	if (false) sqr_template_test();
	if (false) template_class_test();
	if (true) stack_array_test();

	return 0;
}