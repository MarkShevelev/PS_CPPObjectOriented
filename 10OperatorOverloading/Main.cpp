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
}

int main() {
	if (false) velocity_test();

	return 0;
}