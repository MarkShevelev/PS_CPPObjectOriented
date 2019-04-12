#include <iostream>

//перегрузка операторов - важный механизм, позвол€ющий сделать запись вызовов методов и функций более удобной

//перегрузка бинарных арифметических операций
class Velocity {
	double x, y;

public:
	Velocity(double x, double y) {
		Velocity::x = x;
		Velocity::y = y;
	}

	Velocity() : Velocity(0., 0.) {
	}

	void print() {
		std::cout << "(" << x << "," << y << ")" << std::endl;
	}
	//данна€ функци€ создаЄт новый объект Velocity, внутренние данные которого есть сумма данных текущего и вход€щего объектов
	Velocity summation(Velocity const &oth) {
		return Velocity(this->x + oth.x, this->y + oth.y);
	}

	//тот же самый метод, но в виде оператора
	Velocity operator+(Velocity const &oth) {
		return Velocity(this->x + oth.x, this->y + oth.y);
	}
};

void velocity_test() {
	double x1, y1, x2, y2;
	std::cout << "The first velocity components: " << std::flush;
	std::cin >> x1 >> y1;
	Velocity v1(x1, y1);

	std::cout << "The second velocity components: " << std::flush;
	std::cin >> x2 >> y2;
	Velocity v2(x2, y2);

	std::cout << "Total velocity components: " << std::endl;
	std::cout << "Direct call: "; v1.summation(v2).print();
	std::cout << "Operator call: "; (v1 + v2).print();
	std::cout << "Explicit operator call: "; v1.operator+(v2).print();
}

//таким способом можно перегружать все арифметические операторы: + - * = /
//добавим операторы умножени€ и делени€ скорости на число
class VelocityB {
	double x, y;

public:
	VelocityB(double x, double y) {
		VelocityB::x = x;
		VelocityB::y = y;
	}

	VelocityB() : VelocityB(0., 0.) {
	}

	void print() {
		std::cout << "(" << x << "," << y << ")" << std::endl;
	}
	
	//набор перегруженных арифметических операторов
	VelocityB operator+(VelocityB const &oth) {
		return VelocityB(this->x + oth.x, this->y + oth.y);
	}

	VelocityB operator*(double d) {
		return VelocityB(d*this->x, d*this->y);
	}

	VelocityB operator/(double d) {
		return VelocityB(this->x / d, this->y / d);
	}
};

void velocityB_test() {
	VelocityB v1(10, 10);
	VelocityB v2(10, 10);

	auto v3 = v1 / 10;
	auto v4 = v2 * 10;
	v3.print(); v4.print();

	//однако в обратную сторону уножение работать не будет
	//auto v5 = 10 * v1; //ошибка компил€ции!
	//это св€зано с тем, что компил€тор не может выполнить вызов
	//10.operator+(v1), т.к. 10 - число int, а int не содержит методов...
}

//чтобы разрешить проблему с перестановкой числа и скорости в предыдущем примере,
//воспользуемс€ возможностью определ€ть перегруженные операторы в виде глобальных функций
VelocityB operator*(double lha, VelocityB &v) {
	return v * lha;
}

void velocityB_globalfunction_test() {
	VelocityB v1(10, 10);
	(21 * v1).print(); //т.к. точка имеет более высокий приоритет, то круглые скобки необходимы
}

int main() {
	if (false) velocity_test();
	if (false) velocityB_test();
	if (false) velocityB_globalfunction_test();

	return 0;
}