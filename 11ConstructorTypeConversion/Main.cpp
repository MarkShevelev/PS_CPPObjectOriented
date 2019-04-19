#include <iostream>
#include <string>

//в языке C++ в некоторых ситуациях компилятор может принять решение преобразовать один тип данных в другой
//такое поведение называется "неявным преобразованием"
//например, C++ производит неявные преобразования типов в арифметических операциях

void overload_print(int i) {
	std::cout << "INT" << std::endl;
}

void overload_print(short sh) {
	std::cout << "SHORT" << std::endl;
}

void arithmetic_conversion_test() {
	short sh1 = 1, sh2 = 1;
	overload_print(sh1 + sh2); //а здесь напечатется INT
}

//такие же преобразования компилятор может производить и с классами

class Counter {
	int counter;
public:
	Counter(int begin) { //обратим внимание на этот конструктор, он принимает единственный параметр типа int
		counter = begin;
	}

	int next() { return counter++; }
};

void print_ten_counts(Counter c) {
	for (int i = 0; i != 10; ++i)
		std::cout << c.next() << ' ';
	std::cout << std::endl;
}

void print_ten_counts_test() {
	Counter c(10);
	print_ten_counts(c);

	int i = 10;
	print_ten_counts(i); //как не удивительно, но этот вызов функции работает!
}

//это называется неявным преобразованием посредством конструктора
//если в классе есть конструктор с одним параметром, то копмилятор может использовать его для преобразования типа
//например, так работает преобразование массива символов в строку
void print_string(std::string s) {
	std::cout << s << std::endl;
}

void print_string_test() {
	std::string s1("Hello"); //обратим внимание, что у строки std::string есть конструктор с одним параметром char const *
	print_string(s1);

	char const *s2 = "World!";
	print_string(s2); //именно его компилятор использует в этом вызове, неявно создавая новый объкт
}

//с использованием  copy-list-initialization такое неявное преобразование из списка параметров в объект возможно для конструкторов с несколькими параметрами
class Point {
	double x, y;
public:
	Point(double x, double y) {
		Point::x = x;
		Point::y = y;
	}

	void print() {
		std::cout << "(" << x << "," << y << ")" << std::endl;
	}
};

void print_point(Point p) {
	p.print();
}

void print_point_test() {
	Point p(1., -1);
	print_point(p);

	print_point({ 2.,-2 });
}

//в некоторых ситуациях такое поведение может оказаться нежелательным
//тогда мы можем указать компилятору, что какой-то конструктор нельзя использовать для неявного преобразования
class Date {
	int month, day;

public:
	explicit Date(int month, int day) {
		Date::month = month;
		Date::day = day;
	}

	int get_month() { return month; }
	int get_day() { return day; }
};

void print_date(Date d) {
	std::cout << d.get_month() << "-" << d.get_day() << std::endl;
}

void print_date_test() {
	Date d(10, 5);
	print_date(d);

	//print_date({ 12,31 }); //ошибка компиляции! невозможно применить copy-list-initializer
	//по-прежнему можно вызвать конструирование временного объекта явно
	print_date(Date{ 12,31 });
}

int main() {
	if (false) arithmetic_conversion_test();
	if (false) print_ten_counts_test();
	if (false) print_string_test();
	if (false) print_point_test();
	if (false) print_date_test();
}