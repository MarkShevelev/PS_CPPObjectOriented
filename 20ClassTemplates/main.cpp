#include <iostream>
#include <string>

//мы уже знакомы с понятием шаблона функции
//шаблон функции - это специальное описание, по которому компилятор может создать функцию

//например функция, возводящая в квадрат значения любого типа, для которого можно вызвать оператор *
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

int main() {
	if (false) sqr_template_test();

	return 0;
}