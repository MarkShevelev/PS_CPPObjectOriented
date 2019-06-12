#include <iostream>
#include <string>
#include <vector>

//»ногда мы хотим размещать в динамической пам€ти объекты реального типа, а сохран€ть только интерфейсы
//–ассмотрим пример с фигурами
//ƒобавим к каждому классу нетривиальный деструктор дл€ нагл€дности

struct Figure {
	virtual double periphery() const = 0; 
	virtual double area() const = 0;

	~Figure() { std::cout << "Figure destructor" << std::endl; }
};

class Circle : public Figure {
public:
	Circle(double r) :r(r) { }

	double periphery() const override { return 3.14*r*2.; }
	double area() const override { return 3.14*r*r; }

	~Circle() { std::cout << "Circle destructor" << std::endl; }

private:
	double r;
};

class Rectangle : public Figure {
public:
	Rectangle(double w, double h) : w(w), h(h) { }

	double periphery() const { return 2 * (w + h); }
	double area() const { return w * h; }

	~Rectangle() { std::cout << "Rectangle destructor" << std::endl; }

private:
	double w, h;
};

//следующа€ функци€ подсчитывает полную площадь фигур
double full_area(std::vector<Figure*> const &figures) {
	double area = 0.;
	for (auto fig : figures)
		area += fig->area();
	return area;
}

//«адача: пользователь через командный интерфейс вводит название фигуры и данные дл€ неЄ, она добавл€етс€ к набору фигур
//есть две дополнительные команды: exit и area
//exit - выход из программы
//area - полна€ площадь всех фигур

void dynamic_memory_test() {
	std::vector<Figure*> figures;

	bool proceed = true;
	while (proceed) {
		std::string command;
		std::cin >> command;

		if ("exit" == command) { proceed = false; continue; }
		if ("area" == command) {
			std::cout << "Full area: " << full_area(figures) << std::endl;
			continue;
		}
		if ("cir" == command) {
			//мы не можем разместить Circle в автоматической пам€ти, т.к. он должен жить между итераци€ми
			//наиболее очевидный выход - использование динамической пам€ти
			int radius;
			std::cin >> radius;
			auto cir_ptr = new Circle(radius);
			//указатель сохран€ем в векторе
			figures.push_back(cir_ptr);
			continue;
		}
		if ("rect" == command) {
			int w,h;
			std::cin >> w >> h;
			auto rect_ptr = new Rectangle(w,h);
			figures.push_back(rect_ptr);
			continue;
		}

		std::cout << "Unknown command" << std::endl;
	}

	for (auto fig_ptr : figures) //освобождаем пам€ть
		delete fig_ptr;
}

//¬ этой программе есть одно слабое место
//≈сли бы наши дочерние классы обладали бы нетривиальными деструкторами, то мы бы получили утечку ресурсов, т.к. деструкторы реальных объектов не были вызваны
//ћы видели, что вызваны были только деструкторы базового интерфейса

int main() {
	if (false) dynamic_memory_test();

	return 0;
}