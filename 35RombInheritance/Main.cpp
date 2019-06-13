#include <iostream>
#include <string>

//рассмотрим следующую ситуацию при наследовании
class Person {
public:
	Person(std::string const &name): name(name) { }

	virtual void walk(std::string const &to) const { std::cout << name << " walks to " << to << std::endl; }

public:
	std::string const name;
};

class Professional : public Person {
public:
	Professional(std::string const &occupation, std::string const &name): Person(name), occupation(occupation) { }

	void walk(std::string const &to) const override { std::cout << occupation << " walks to " << to << std::endl; }

private:
	std::string const occupation;
};

class Civilian : public Person {
public:
	Civilian(std::string const &country, std::string const &name) : Person(name), country(country) { }

	void walk(std::string const &to) const override { std::cout << country << " resident walks to the " << to << std::endl; }

private:
	std::string const country;
};

class CivilianProfessional : public Civilian, public Professional {
public:
	CivilianProfessional(std::string const &country, std::string const &occupation, std::string const &name): Civilian(country,name), Professional(occupation,name) { }
};

void professional_walk(Professional const &prof, std::string const &to) {
	prof.walk(to); //нет проблем при вызове, вызывается переопределённый метод класса Professional
}

void civilian_walk(Civilian const &civ, std::string const &to) {
	civ.walk(to);
}

void diamod_inheritance_test() {
	CivilianProfessional cp("Russian", "Policeman", "Alexander");

	//при вызове функций не происходит никаких проблем
	civilian_walk(cp, "bus station");
	professional_walk(cp,"bus station");

	//cp.walk("bus station"); //ошибка компиляции!
	//компилятор не может выбрать, какой именно метод необходимо вызывать из класса Civilian или из класса Professional

	cp.Civilian::walk("bus station"); //явно вызываем метод walk из класса Civilian
	cp.Professional::walk("bus station");
}

//при ромбовидном наследовании есть ещё одна проблема: имя name повторяется внутри объекта дважды, в двух разных вложенных классов
void diamond_inheritance_data_test() {
	CivilianProfessional cp("Russian", "Policeman", "Alexander");

	std::string const &civ_name = cp.Civilian::name;
	std::string const &prof_name = cp.Professional::name;

	std::cout << "Civilian: " << civ_name << " " << std::addressof(civ_name) << std::endl;
	std::cout << "Professional: " << prof_name << " " << std::addressof(prof_name) << std::endl;
}

//Переменная очевидно хранит одно и то же значение, но это две разные переменные, которые имеют два разны адреса

//Проблему с переменной можно решить с помощью "виртуального наследования"
struct First {
	First(std::string const &name): name(name) { }
	virtual void who() const { std::cout << "First: " << name << std::endl; }
	std::string const name;
};

struct SecondA : virtual public First { //ключевое слово virtual говорит, что объект будет создан только в последнем классе в иерархии
	SecondA(std::string const &name): First(name) { }
	void who() const override { std::cout << "SecondA: " << name << std::endl; }
};

struct SecondB : virtual public First {
	SecondB(std::string const &name) : First(name) { }
	void who() const override { std::cout << "SecondB: " << name << std::endl; }
};

struct Diamond: virtual public SecondA, virtual public SecondB { 
	Diamond(std::string const &name): SecondA(name), SecondB(name), First(name) { } //реально конструктор вызывается именно для First!!!
	void who() const override { std::cout << "Diamond: " << name << std::endl; }
};

void virtual_inheritance_test() {
	Diamond d("Andrey");
	d.who();

	std::string const &a_name = d.SecondA::name;
	std::string const &b_name = d.SecondB::name;

	std::cout << "SecondA: " << a_name << " " << std::addressof(a_name) << std::endl;
	std::cout << "SecondB: " << b_name << " " << std::addressof(b_name) << std::endl;
} //в случае виртуального наследования данные создаются единожды, значения и адреса одинаковы

int main() {
	if (false) diamod_inheritance_test();
	if (false) diamond_inheritance_data_test();
	if (false) virtual_inheritance_test();

	return 0;
}