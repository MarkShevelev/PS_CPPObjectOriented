#include <iostream>
//В некоторых случаях приходится производить перобразования типов, которые связаны между собой отношениями наследования

//Если мы преобразуем тип от наследного к родительскому, то оно может быть произведено автоматически, неявно, такое преобразование называют upcasting (преобразование вверх по иерархии)
struct Base {
	virtual void say() const { std::cout << "Base" << std::endl; }
	virtual ~Base()  { }
};

struct Derived : Base {
	void say() const override { std::cout << "Derived" << std::endl; }
};

void upcasting_test() {
	Derived d;
	d.say();

	Base b = d; //здесь произойдёт преобразование через конструирование - static_cast
	b.say(); //сработает Base::say() - построен новый объект, нет полиморфизма

	Base &b_ref = d; //здесь произойдёт преобразование через адреса, т.е. новый объект не будет построен, а будет выведен верный адрес вложенного в Derived объекта типа Base
	b_ref.say(); //сработает Derived::say() - полиморфизм подтипов

	Base *b_ptr = &d; //здесь произойдёт то же самое - выведение верного адреса вложенного объекта
	b_ptr->say(); //сработает Derived::say() - полиморфизм подтипов
}

//Если есть необходимость обратного преобразования - от базового класса к выведенному - то оно не может быть неявным, т.к. на этапе компиляции разрешить такое преобразование невозможно
//В этом случае мы можем сделать преобразование явно
//Преобразование от базового класса к выведенному называется downcasting (преобразование вниз по иерархии)

struct Figure { //Интерфейс
	virtual double area() const = 0;
	virtual ~Figure() { }
};

class Circle  : public Figure {
public:
	Circle(double r): r(r) { }
	double area() const override { return 3.1415*r*r; }
	double radius() const { return r;	} //уникальный метод класса Circle

private:
	double r;
};

class Rectangle  : public Figure {
public:
	Rectangle(double w, double h): w(w), h(h) { }
	double area() const override { return w * h; }
	double width() const { return w; } //уникальный метод класса Rectangle
	double heigth() const { return h; } //уникальный метод класса Rectangle

private:
	double w, h;
};

void downcasting_test() {
	{
		Figure &fig_ref = *(new Circle(1.)); //создаём объект типа Circle, но сохраняем ссылку на него с базовым типом
		std::cout << "Area = " << fig_ref.area() << std::endl;
		//fig_ref.radius(); //ошибка компиляции! Нельзя вызвать метод .cir, т.к. Figure о нём ничего не знает
		//Circle &cir_ref = fig_ref; //такое преобразование не может  быть неявным
		
		Circle &cir_ref = static_cast<Circle&>(fig_ref); //но мы можем выполнить его явно
		std::cout << "Radius = " << cir_ref.radius();

		delete &fig_ref;
	}

	{
		Figure *fig_ptr = new Rectangle(1., 2.);
		std::cout << "Area = " << fig_ptr->area() << std::endl;
		//Rectangle *rec_ptr = fig_ptr; //невозможно преобразовать неявно
		Rectangle *rec_ptr = static_cast<Rectangle*>(fig_ptr); //явно можно выполнить преобразование и с указателем
		std::cout << "Width/Heigth = " << rec_ptr->width() << "/" << rec_ptr->heigth() << std::endl;

		delete fig_ptr;
	}
}


//Преобразование типов возможно и при множественном наследовании
struct Shape {
	virtual bool contains(double x, double y) const = 0;
	virtual ~Shape() { }
};

class Position {
public:
	Position(double x, double y) :x(x), y(y) { }

	double getX() const { return x; }
	double getY() const { return y; }

private:
	double const x, y;
};

#include <cmath>
class PositionedRectangle : public Position, public Rectangle, public Shape {
public:
	PositionedRectangle(double x, double y, double w, double h) : Position(x, y), Rectangle(w, h) { }
	bool contains(double x, double y) const override {
		return (x > Position::getX() && x < (Position::getX()+Rectangle::width()) && y > Position::getY() && y < (Position::getY()+Rectangle::heigth()));
	}
};

class PositionedCircle : public Position, public Circle, public Shape {
public:
	PositionedCircle(double x, double y, double r) : Position(x, y), Circle(r) { }
	bool contains(double x, double y) const override {
		return hypot(x - Position::getX(), y - Position::getY()) < Circle::radius();
	}
};

#include <string>
std::string in_out(double x, double y, Shape const &shape) {
	return shape.contains(x, y) ? "inside" : "outside";
}

void multiple_inheritance_cast_test() {
	Shape *shapeA = new PositionedCircle(0., 0., 1.);          //неявный upcast
	Shape *shapeB = new PositionedRectangle(0., 0., 1., 1.);   //неявный upcast
	std::cout << "The point (0.8,0.8) is \n"
		<< in_out(0.8, 0.8, *shapeA) << " the shapeA " << '\n'
		<< in_out(0.8, 0.8, *shapeB) << " the shapeB " << '\n'
		<< std::endl;

	//PositionedCircle *cir_ptr = shapeA; //невозможно неявно сделать преобразование
	PositionedCircle *poscir_ptr = static_cast<PositionedCircle*>(shapeA); //но можно явно!
	//Circle *cir_ptr = static_cast<Circle*>(shapeA); //невозможно!
	//Хотя мы знаем, что наш объект является наследником Circle и может быть к нему приведён, компилятор неразрешает такое преобразование даже явно, т.к. это преобразование не является ни upcast, ни downcast
	
	Circle *cir_ptr = (Circle*)(shapeA); //КРАЙНЕ ОПАСНЫЙ КОД!!!
	//в конструкции выше будет применён reinterpret_cast<Circle*>
	//он всегда допустим, но последствия его использования непредсказуемы!!!
	//std::cout << cir_ptr->radius() << std::endl; //неопределённое поведение!!!
}

//static_cast может уберечь нас от неверного преобразования, если оно в принципе невозможно, как в случае попытки перейти от Shape к Circle при множественном наследовании
//однако static_cast опирается только на знания статической информации о типах и не может предсказать неверные действия программиста
void wrong_downcast_test() {
	Figure *fig = nullptr;
	std::cout 
		<< "1)Circle\n"
		<< "2)Recatangle\n" 
		<< std::endl;
	int x;
	std::cin >> x;
	switch (x) {
	case 1:
		fig = new Circle(1.);
		break;
	case 2:
		fig = new Rectangle(2., 2.);
		break;
	default:
		std::cout << "Unknown figure!" << std::endl;
		return;
	}

	Circle *cir_ptr = static_cast<Circle*>(fig); //нет ошибки! всегда успешно, т.к. Circle и Figure - классы одной иерархии, производится downcast
	//Однако реальный тип объекта, на который указывает fig может быть разным
	//Тип зависит от выбора пользователя и не может быть предсказан
	std::cout << cir_ptr->radius() << std::endl;
}

int main() {
	if (false) upcasting_test();
	if (false) downcasting_test();
	if (false) multiple_inheritance_cast_test();
	if (true) wrong_downcast_test();

	return 0;
}