#include <iostream>
#include <string>
#include <vector>

//Мы уже встречались со сложной ситуацией при работе с полиморфными типами
//Если реальный тип объекта динамический, например, его выбирает пользователь, то мы вынуждены создавать такие объекты в динамической памяти, а в контейнере сохранять только указатели базового типа

struct Figure { //интерфейс фигуры, который определяет наличие метода area()
	virtual double area() const = 0;
	virtual ~Figure() { } 
};

class Circle final: public Figure {
public:
	Circle(double r) : r(r) { }
	double area() const override { return 3.1415*r*r; }
	~Circle() { std::cout << "Circle destroyed" << std::endl; }

private:
	double r;
};

class Rectangle final: public Figure {
public:
	Rectangle(double w, double h): w(w), h(h) { }
	double area() const override { return w * h; }
	~Rectangle() { std::cout << "Rectangle destroyed" << std::endl; }

private:
	double w, h;
};

double full_area(std::vector<Figure*> figures) {
	double area = 0.;
	for (auto fig : figures)
		area += fig->area();
	return area;
}

void polymorphic_choice_test() {
	std::vector<Figure*> figures; //вектор для сохранения адресов

	bool proceed = true;
	do {
		std::string command;
		std::cin >> command;

		if ("exit" == command) { proceed = false; continue; }
		if ("cir" == command) {
			double radius;
			std::cin >> radius;
			figures.push_back(new Circle(radius));
			continue;
		}
		if ("rect" == command) {
			double width, height;
			std::cin >> width >> height;
			figures.push_back(new Rectangle(width, height));
			continue;
		}
		if ("area" == command) { std::cout << full_area(figures) << std::endl; continue; }

		std::cout << "Unknown command!" << std::endl;
	} while (proceed);

	for (auto fig : figures) //необходимый код для возвращения памяти !!!
		delete fig;
}

//Мы знаем, что для каждого объекта, который выходит из области видимости вызывается деструктор
//К сожалению, указатели типа языка C не имеют деструкторов
//Однако, ничто не мешает нам создать "вручную" специальный класс, объекты которого будут удалять динамическую память

#include <algorithm> //swap
template<typename T>
class MyAutoPtr final {
public:
	MyAutoPtr(): MyAutoPtr(nullptr) { }
	MyAutoPtr(T *obj): obj(obj) { }
	~MyAutoPtr() { if (nullptr != obj) delete obj; }
	T& operator*() { return *obj; }
	T const& operator*() const { return *obj; }
	T* operator->() { return obj; }
	T const * operator->() const { return obj; }

	MyAutoPtr(MyAutoPtr const &src) = delete;
	MyAutoPtr& operator=(MyAutoPtr const &src) = delete;

	MyAutoPtr(MyAutoPtr &&src) : obj(src.obj) { src.obj = nullptr; }
	MyAutoPtr& operator=(MyAutoPtr &&src) {
		MyAutoPtr tmp(std::move(src));
		std::swap(obj, tmp.obj);
		return *this;
	}

private:
	T *obj;
};

void myautoptr_test() {
	std::vector<MyAutoPtr<Figure>> figures; //вектор, содержащий специальные объекты, которые сами освободят динамическую память, которую захватят в конструкторе

	bool proceed = true;
	do {
		std::string command;
		std::cin >> command;

		if ("exit" == command) { proceed = false; continue; }
		if ("cir" == command) {
			double radius;
			std::cin >> radius;
			figures.push_back(new Circle(radius));
			continue;
		}
		if ("rect" == command) {
			double width, height;
			std::cin >> width >> height;
			figures.push_back(new Rectangle(width, height));
			continue;
		}
		if ("area" == command) { 
			double area = 0.;
			for (auto &auto_ptr : figures) {
				area += auto_ptr->area();
			}
			std::cout << area << std::endl;
			continue;
		}

		std::cout << "Unknown command!" << std::endl;
	} while (proceed);

	//данный код больше не является необходимым
	/*for (auto fig : figures) 
		delete fig;*/
}


//В стандартной библиотеке C++ есть стандартный шаблон unique_ptr, который позволяет подобно написанному нами MyAutoPtr автоматически уничтожать объекты, при выходе из области видимости или завершении жизни объектов, которые их содержат
#include <memory>
void unique_ptr_test() {
	std::unique_ptr<Rectangle> prtRect(new Rectangle(1., 2.));
	{
		std::unique_ptr<Circle> ptrCir(new Circle(1.));
	}
	//unique_ptr поддерживают "ковариантность"
	std::unique_ptr<Figure> figure;
	{
		std::unique_ptr<Circle> ptrCir(new Circle(2.));
		figure = std::move(ptrCir); //присваивание невозможно, но возможно перемещение
	}
	std::cout << figure->area() << std::endl;
}

int main() {
	if (false) polymorphic_choice_test();
	if (false) myautoptr_test();
	if (false) unique_ptr_test();

	return 0;
}