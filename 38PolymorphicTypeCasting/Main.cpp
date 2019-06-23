#include <iostream>
//¬ некоторых случа€х приходитс€ производить перобразовани€ типов, которые св€заны между собой отношени€ми наследовани€

//≈сли мы преобразуем тип от наследного к родительскому, то оно может быть произведено автоматически, не€вно, такое преобразование называют upcasting (преобразование вверх по иерархии)
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

	Base b = d; //здесь произойдЄт преобразование через конструирование - static_cast
	b.say(); //сработает Base::say() - построен новый объект, нет полиморфизма

	Base &b_ref = d; //здесь произойдЄт преобразование через адреса, т.е. новый объект не будет построен, а будет выведен верный адрес вложенного в Derived объекта типа Base
	b_ref.say(); //сработает Derived::say() - полиморфизм подтипов

	Base *b_ptr = &d; //здесь произойдЄт то же самое - выведение верного адреса вложенного объекта
	b_ptr->say(); //сработает Derived::say() - полиморфизм подтипов
}

//≈сли есть необходимость обратного преобразовани€ - от базового класса к выведенному - то оно не может быть не€вным, т.к. на этапе компил€ции разрешить такое преобразование невозможно
//¬ этом случае мы можем сделать преобразование €вно
//ѕреобразование от базового класса к выведенному называетс€ downcasting (преобразование вниз по иерархии)

struct Figure { //»нтерфейс
	virtual double area() const = 0;
	virtual ~Figure() { }
};

class Circle  : public Figure {
public:
	Circle(double r): r(r) { }
	double area() const override { return 3.1415*r*r; }
	double radius() { return r;	} //уникальный метод класса Circle

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
		Figure &fig_ref = *(new Circle(1.)); //создаЄм объект типа Circle, но сохран€ем ссылку на него с базовым типом
		std::cout << "Area = " << fig_ref.area() << std::endl;
		//fig_ref.radius(); //ошибка компил€ции! Ќельз€ вызвать метод .cir, т.к. Figure о нЄм ничего не знает
		//Circle &cir_ref = fig_ref; //такое преобразование не может  быть не€вным
		
		Circle &cir_ref = static_cast<Circle&>(fig_ref); //но мы можем выполнить его €вно
		std::cout << "Radius = " << cir_ref.radius();

		delete &fig_ref;
	}

	{
		Figure *fig_ptr = new Rectangle(1., 2.);
		std::cout << "Area = " << fig_ptr->area() << std::endl;
		//Rectangle *rec_ptr = fig_ptr; //невозможно преобразовать не€вно
		Rectangle *rec_ptr = static_cast<Rectangle*>(fig_ptr); //€вно можно выполнить преобразование и с указателем
		std::cout << "Width/Heigth = " << rec_ptr->width() << "/" << rec_ptr->heigth() << std::endl;

		delete fig_ptr;
	}
}


//ѕреобразование типов возможно и при множественном наследовании
class Position {
public:
	Position(int x, int y) :x(x), y(y) { }

	int getX() const { return x; }
	int getY() const { return y; }

private:
	int const x, y;
};

class PositionedRectangle : public Position, public Rectangle {
public:
	PositionedRectangle(int x, int y, int w, int h) : Position(x, y), Rectangle(w, h) { }
};

int main() {
	if (false) upcasting_test();
	if (false) downcasting_test();

	return 0;
}