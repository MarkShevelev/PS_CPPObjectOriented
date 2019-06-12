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
	std::cout << name.first_name << std::endl;
}

void print_name_test() {
	Name ray("Ray","John","Strangeway");
	PrintableName jose("Jose", "Lopes", "De Vega");

	print_name(ray);
	print_name(jose);
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



int main() {
	if (false) print_name_test();

	return 0;
}