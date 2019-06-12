#include <iostream>
#include <string>

//В общем случае понятие полиморфизма означает, что какой-то объект в вашей программе может вести себя по-разному
//В это понятие вкладывается большое количество различных вариаций
//Например, перегрузку функций иногда называют ad-hoc полиморфизмом, т.е. полиморфизм состоит в том, что имя функции ведёт себя специальным образом для каждого выбранного типа, одно и то же имя меняет своё поведение
//Шаблонные функции и классы в C++ иногда называют параметрическим полиморфизмом, т.к. функции и классы меняют своё поведение в зависимости от параметра
//Ситуацию, когда один объект может выступать в роли другого называют полиморфизмом подтипов

//Рассмотрим последний вид полиморфизма подробнее
struct Name {
	Name(std::string const &first, std::string const &middle, std::string const &family): first_name(first), middle_name(middle), family_name(family) { }
	std::string first_name, middle_name, family_name;
};

class PrintableName : public Name {
public:
	PrintableName(std::string const &first, std::string const &middle, std::string const &family): Name(first,middle,family) { }
	void print(std::ostream &os) const { os << first_name << " " << middle_name << " " << family_name; }
};

//Мы можем легко передавать объекты типа PrintableName в функции, которые ожидают Name
void print_name(Name const &name) {
	std::cout << name.first_name;
}

void print_name_test() {
	Name ray("Ray","John","Strangeway");
	PrintableName jose("Jose", "Lopes", "De Vega");

	print_name(ray); std::cout << std::endl;
	print_name(jose); std::cout << std::endl;
}

//почему в функции print_name не возникает ошибки?
//Дело в том, что компилятор понимает: раз PrintableName наследует с модификатором public классу Name, значит все поля и методы, которыми можно воспользоваться в Name, существуют как открытые поля и методы в PrintableName!
//Компилятору остаётся создать верный машинный код, чтобы правильно рассчитать смещения
//В теории типов такая ситуация называется "подтип"
//Говорят, что PrintableName является подтипом Name, если все свойства, верные для Name, верны и для PrintableName
//Если PrintableName подтип Name, то Name - супертип для PrintableName

//Чем хороши подтипы?
//Если мы создадим алгоритм, который будет опираться только на свойства супертипа, то мы могли бы ожидать, что в него можно передавать различные подтипы, а алгоритм будет работать как прежде
//Что мы и видели выше
//Такой подход к написанию кода позволил бы нам существенно снизить связанность различных частей программы

//Если у некоторого типа есть один и более подтипов, то говорят, что супертип - это полиморфный тип
//Например, тип Name - это полиморфный тип
//Ситуацию, когда реальный тип объектов может быть разным, а мы опираемся только на супертип, называют "полиморфизмом подтипов"
//Полиморфим позволяет расширять программу, добавляя новые возможности, но при этом активно используя старые

//Класс с новыми особенностями
class Student : public Name {
public:
	Student(std::string const &first, std::string const &middle, std::string const &family, std::string const &department): Name(first,middle,family), department(department) { }

	std::string const & get_department() const { return department; }

private:
	std::string department;
};

//функция, которая опирается на новое поведение Student
void print_student(Student const &s) {
	print_name(s); //используем возможности, определённые ранее
	std::cout << " from department " << s.get_department();
}

void print_student_test() {
	Student wulf("Willam", "Allan", "Wulf", "Computer science");
	print_student(wulf); std::cout << std::endl;
	print_name(wulf); std::cout << std::endl; //по-прежнему можем воспользоваться алгоритмом печати имени
}

//Важно отметить, что работает такой подход только при открытом наследовании, с модификатором public
//В остальных случаях полиморфизм работать не будет, т.к. свойства класса родителя должны быть доступны через объект дочернего класса, а private или protected наследование этого не допускают

//Если с данными всё успешно работает, то с методами в C++ всё не просто
//Создадим алгоритм, опирающийся на свойства суперкласса и какой-нибудь подкласс
struct Predicate { //класс получает int производит проверку условия в методе check, все числа подходят
	bool check(int i) const { return true;  }
};

//функция, которая выражает алгоритм, полагающийся только на метод check из класса Predicate
bool all_check(int *arr, size_t size, Predicate const &p) {
	for (size_t pos = 0; pos != size; ++pos)
		if (!p.check(arr[pos])) return false;
	return true;
}

struct Positive : Predicate { //класс Positive Наследует Predicate и даёт другую реализацию для check
	bool check(int i) const { return i > 0; }
};

void all_check_test() {
	int arr[] = { 1,3,-1,-2,2,-3 };
	Predicate p;
	Positive pp;

	std::cout << std::boolalpha << all_check(arr, 6, p) << std::endl;
	std::cout << std::boolalpha << all_check(arr, 6, pp) << std::endl;
}

//Программа успешно скомпилировалась и функция all_check усешно приняла как Predicate, так и его наследника - Positive
//Однако результат работы all_check оказался одинаковым, словно мы и не меняли функцию check
//Что произошло?
//Всё дело в "статическом связывании"
//Когда происходит компиляция функции all_check, то адрес метода подставляется линкером, т.е. вне зависимости от того какой объект будет передан в функцию, вызван будет всегда один и тот же метод
//Полиморфизма, изменения поведения, не получилось
//Так как данные читаются из память по определённым адресам и в этой памяти могут содержаться различные данные для различных объектов, то мы видим полиморфизм, но по определённым адресам в сегменте кода всегда содержится один и тот же код

//Эту проблему можно было бы обойти с помощью указателей на функции!
//Если бы вместо того, чтобы писать новую функцию, мы бы переписали данные указателя на функцию, по которому нужно произвести вызов, то мы бы получили поведение, аналогичное поведению с данными!

bool good(int x) { return true; }
bool positive(int x) { return x > 0; }
typedef bool(*predicate_t)(int);

struct FPPredicate {
	FPPredicate() { to_call = good; }

	bool check(int x) const { return to_call(x); } //внутри метода check, который будет статически связан, мы вызываем функциию проверки, читая данные из поля адреса

protected:
	predicate_t to_call;
};

//функция, которая опирается только на возможности FPPredicate
bool all_check(int *arr, size_t size, FPPredicate const &p) {
	for (size_t pos = 0; pos != size; ++pos)
		if (!p.check(arr[pos])) return false;
	return true;
}

struct FPPositive: FPPredicate {
	FPPositive() { to_call = positive; } //мы изменим поведение check, задав новый адрес исполняемого сегмента кода
};

void fp_all_check_test() {
	int arr[] = { 1,3,-1,-2,2,-3 };
	FPPredicate p;
	FPPositive pp;

	std::cout << std::boolalpha << all_check(arr, 6, p) << std::endl;
	std::cout << std::boolalpha << all_check(arr, 6, pp) << std::endl;
}
//Теперь поведение стало ожидаемым!

//Для того, чтобы не делать подобных ходов самому, в C++ предусмотрен синтаксис, который позволяет организовать подобный вызов метода через указатель на функцию прозрачным образом
//Отметив метод в базовом классе ключевым словом virtual можно получить ожидаемое поведение в выведенных классах

struct VMPredicate {
	virtual bool check(int x) const { return true; } //в базовом классе отмечаем метод check как virtual
};

struct VMPositive : VMPredicate {
	bool check(int x) const { return x > 0; } //в выведенном классе ничего дополнительно делать не нужно, достаточно написать другую реализацию для метода, отмеченного как virtual в базовом классе
};

bool all_check(int *arr, size_t size, VMPredicate const &p) {
	for (size_t pos = 0; pos != size; ++pos)
		if (!p.check(arr[pos])) return false;
	return true;
}

void virtual_method_all_check_test() {
	int arr[] = { 1,3,-1,-2,2,-3 };
	VMPredicate p;
	VMPositive pp;

	std::cout << std::boolalpha << all_check(arr, 6, p) << std::endl;
	std::cout << std::boolalpha << all_check(arr, 6, pp) << std::endl;
}
//Мы получаем ожидаемое поведение без дополнительных сложностей
//Обратите внимание, что достаточно указать ключеввое слово virtual только в базовом классе
//Как только мы отметим какой-либо метод ключевым словом virtual, то его вызов будет происходить посредством указателя на функцию, который хранится в специальном месте внутри объекта - в "таблице виртуальных функций"

//Виртуальный метод может быть не один, класс может содержать как виртуальные, так и обычные методы
class Figure {
public:
	Figure(std::string const &name): name(name) { }
	std::string const & what_am_i() const { return name; } //обычный метод, статическое связывание
	virtual double periphery() const { return 0.; } //виртуальный метод, он будет вызван посредством указателя
	virtual double area() const { return 0.; }

private:
	std::string const name;
};

class Circle : public Figure {
public:
	Circle(double r): Figure("Circle"), r(r), circle_string("I'am a Circle") { }
	
	std::string const & what_am_i() const { return circle_string; } //этот метод будет вызван статическим связыванием
	
	double periphery() const { return 3.14*r*2.; } //эти методы будут вызваны через указатели
	double area() const { return 3.14*r*r; }

private:
	double r;
	std::string const circle_string;
};

class Rectangle : public Figure {
public:
	Rectangle(double w, double h) : Figure("Rectangle"), w(w), h(h), rectangle_string("I'am a Rectangle") { }

	std::string const & what_am_i() const { return rectangle_string; } //этот метод будет вызван статическим связыванием

	double periphery() const { return 2*(w+h); } //эти методы будут вызваны через указатели
	double area() const { return w*h; }

private:
	double w, h;
	std::string const rectangle_string;
};

void figure_print(Figure const &fig) {
	std::cout << fig.what_am_i() << " with periphery = " << fig.periphery() << " and with area = " << fig.area() << std::endl;
}

void figure_print_test() {
	Figure f("Empty");
	Circle cir(1.);
	Rectangle rect(1., 2.);

	figure_print(f); figure_print(cir); figure_print(rect);
	std::cout << "Cir method: " << cir.what_am_i() << std::endl;
	std::cout << "Rect method: " << rect.what_am_i() << std::endl;
}
//Виртуальные методы сработали по принципу динамического связывания, они были вызвана по адресу, который установлен в дочернем классе
//Невиртуальные методы сработали по принциппу статического связывания, т.е. при компиляции в функции figure_print был подставлен адрес сегмента кода, связанного с классом Figure

int main() {
	if (false) print_name_test();
	if (false) print_student_test();
	if (false) all_check_test();
	if (false) fp_all_check_test();
	if (false) virtual_method_all_check_test();
	if (false) figure_print_test();

	return 0;
}