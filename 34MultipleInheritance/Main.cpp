#include <iostream>
#include <string>

//Технически множественное наследование - это ситуация, когда класс наследует не одному, а нескольким родительским классам

struct PositivePredicate {
	bool check(int x) const { return x > 0; }
};

struct EvenPredicate {
	bool check(int x) const { return 0 == x % 2; }
};

struct EvenPositivePredicate : private PositivePredicate, private EvenPredicate {
	bool check(int x) const { return PositivePredicate::check(x) && EvenPredicate::check(x); }
};

void multiple_private_inheritance_test() {
	int i;
	std::cin >> i;
	std::cout << std::boolalpha << EvenPositivePredicate().check(i) << std::endl;
}

//При множественном наследовании мы получаем свойства уже не одного класса, а нескольких
//Наследовать можно любому количеству классов, но нельзя наследовать дважды одному и тому же классу
/*
struct DoublePositivePredicate: private PositivePredicate, private PositivePredicate {
	bool check(int x) const { return PositivePredicate::check(x); }
};
*/
//Очевидно, что такое наследование абсурдно, мы уже имеем все свойства класса PositivePredicate, нет возможности различить один экземпляр агрегируемого PositivePredicate от другого
struct FirstPositivePredicate : private PositivePredicate {
	bool check(int x) const { return PositivePredicate::check(x); }
};

struct SecondPositivePredicate : private FirstPositivePredicate, private PositivePredicate {
	bool check(int x) const { return PositivePredicate::check(x) && FirstPositivePredicate::check(x); }
};

//Пример выше показывает, что мы можем дважды унаследовать одному и тому же классу посредством нескольких поколений:
//сначала мы наследуем первый раз классу PositivePredicate, создавая дочерний класс FirstPositivePredicate, который теперь содержит в себе агрегант PositivePredicate,
//Затем мы наследуем ещё раз PositivePredicate, но у нас нет дважды повторяющегося класса, агреганты хотя и содержатся внутри SecondPositivePredicate дважды, но их можно различить: один - непосредственный предок, ко второму мы получаем доступ, указав второго предка, который обратиться к своему агреганту

//Открытое множественное наследование может помочь создать объекты, которые обладают одновременно различными свойствами
class Rectangle {
public:
	Rectangle(int w, int h): w(w), h(h) { }

	int getW() const { return w; }
	int getH() const { return h; }

private:
	int const w, h;
};

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

	bool in_rect(int x, int y) const { return x > getX() && x < getX() + getW() && y > getY() && y < getY() + getH(); }
};

void rectangle_area(Rectangle const &rect) {
	std::cout << "Area: " << rect.getH()*rect.getW() << std::endl;
}

void position_distance(Position const &lha, Position const &rha) {
	std::cout << "Distance: " << std::hypot(lha.getX() - rha.getX(), lha.getY() - rha.getY());
}

void multiple_public_inheritance_test() {
	PositionedRectangle a(0, 0, 10, 20), b(0, 1, 20, 30);
	rectangle_area(a); rectangle_area(b);
	position_distance(a, b);
}

//Объекты класса PositionedRectangle сохранили свойства как класса Rectangle, так и класса Position

//Важным отличием множественного наследования является вопрос о взятии адреса
//При одиночном наследовании адрес вложенного объекта базового класса всегда совпадает с адресом самого объекта выведенного класса
void multiple_inheritance_address_test() {
	PositionedRectangle pr(0, 0, 10, 10);
	void *pr_ptr = &pr;
	Position *pos_ptr = &pr;
	Rectangle *rect_ptr = &pr; //это присваивание приведёт к интересному результату

	std::cout << std::boolalpha
		<< "PositionedRectangle ? Position: " << (&pr == pos_ptr) << '\n' 
		<< "PositionedRectangle ? Rectangle: " << (&pr == rect_ptr) << '\n'
		<< "PositionedRectangle ? Rectangle: " << (pr_ptr == rect_ptr) << std::endl;
	std::cout << &pr << '\n' << pos_ptr << '\n' << rect_ptr << std::endl;
}
//реальный адрес, который хранится в переменной pr_ptr, отличается от адреса объекта pr, но при сравнении rect_ptr с адресом pr можно получить верный ответ

int main() {
	if (false) multiple_private_inheritance_test();
	if (false) multiple_public_inheritance_test();
	if (false) multiple_inheritance_address_test();

	return 0;
}