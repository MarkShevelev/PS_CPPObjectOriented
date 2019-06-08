#include <iostream>
#include <string>

//Помимо композиции между классами или объектами на основе классов могут быть выстроены ещё более тесные отношения- наследование
//Наследование - это способ построения классов (или объектов) на основе уже существующих
//В C++, как и в других языка, основанных на идее классов, наследование происходит между классами

struct Base {
	int x;
	int sum_with(int y) const { return x + y;  }
};

struct Derived : Base { //класс Base называют базовым или родительским (иногда super class) для класса Derived
	int y;
	int mul_to(int x) const { return x * y; }
};
//Класс Derived называют выведенным или дочерним (иногда sub class) от класса Base
//Derived выведен из Base; Base - базовый класс для Derived
//Derived - дочерний класс от Base; Base - родительский для Derived
//Derived - это sub class от Base; Base - это super class для Derived
//Derived наследует классу Base

//Наследование выражается в том, что каждый объект класса Derived получает все свойства, поля и методы, класса Base
void inheritance_test() {
	Base b;
	Derived d;
	b.x = 3; 
	std::cout << "Base call: " << b.sum_with(1) << std::endl;

	d.y = 3;
	std::cout << "Derived call: " << d.mul_to(2) << std::endl;

	d.x = 3; //хотя в классе Derived не было определено поля x, но класс Derived получил его "в наследство" от класса Base
	//как и метод sum_with
	std::cout << "Base method call from Derived: " << d.sum_with(1) << std::endl;
}

//В языке C++ наследование достигается настоящей композицией, т.е. внутри объекта класса Derived существует полноценный объект класса Base
//Внутри дочернего класса можно вызывать методы родительского, как и в случае включение
//Внутри дочернего класса нельзя вызывать private методы родительского, как и в случае включение
//Внутри дочернего класса можно (!) вызывать protected методы родительского

struct BaseWithProtected {
	int pub_var;
	int sqr() const { return pub_var * pub_var;  }

protected:
	double protected_var;
	double sqr_() const { return protected_var * protected_var;  }
};

//Данный код не компилируется!!!
/*struct CompositeBaseWithProtected {
	BaseWithProtected agregant;
	void set_arg(double arg) { agregant.protected_var = arg; }
	double dsqr(double a) const { return sqr_(); }
};*/

struct DerivedFromBaseWithProtected : BaseWithProtected{
	void set_arg(double arg) { protected_var = arg; }
	double dsqr() const { return sqr_(); }
};

void protected_access_test() {
	DerivedFromBaseWithProtected d;
	d.pub_var = 4;
	std::cout << d.sqr() << std::endl;
	//d.protected_var = 1.3;//мы не можем обратиться к protected_var, т.к. она доступна толко внутри наследника

	d.set_arg(1.3); //мы взываем открытый метод, который внутри обращается к protected полям родительского класса
	std::cout << d.dsqr() << std::endl;
}

//Наследование в С++ бывает разное: public, protected и private
//В зависимости от этого другие классы могут получить, а могут и не получить, доступ к "унаследованным методам и полям" 

struct Name {
	std::string first_name, middle_name, last_name;
};

struct Student : private Name {
	Student(std::string const &first_name, std::string const &middle_name, std::string const &last_name) {
		Name::first_name = first_name;
		Name::middle_name = middle_name;
		Name::last_name = last_name;
	}

	std::string full_name() const { return first_name + " " + middle_name + " " + last_name; }
};

void private_inheritance_test() {
	Student s("Gabriel","Jose","Garsia Markes");
	//std::cout << s.first_name << std::endl;//мы не можем обратиться к открытым членам класса Name, т.к. наследование было private
	std::cout << s.full_name() << std::endl; //но внутри своих методов класс Student может обращаться к элементам Name
	//всё равно, что Name был бы private членов внутри Student
}

//наследование для классов и структур отличается именно модификацией доступа
//классы по умолчанию наследуют своим родительским классам приватно (слово дописано : private Base), а структуры - открыто (слово дописано : public Base)

//Наследование очень часто используется для добавление новых возможностей к уже существующим классам
struct PrintableName : Name {//для структур наследование открыто по умолчанию
	void print() { std::cout << (first_name + " " + middle_name + " " + last_name) << std::endl; }
}; //мы создали новый класс PrintableName на основе уже существующего класса Name, добавив к нему новый метод

int main() {
	if (false) inheritance_test();
	if (false) protected_access_test();
	if (false) private_inheritance_test();
}


