#include <iostream>
#include <string>

//В некоторых ситуациях, количество вариантов, которые может принимать значение, ограниченно
//Рассмотрим следующую структуру
struct EmployeeA {
	std::string name;
	int salary;
	std::string gender; //может принимать только два значения male или female
};

//использование строки кажется избыточным, можно заменить её на bool
struct EmployeeB {
	std::string name;
	int salary;
	bool is_male; //true - male и false - female
};

//Что если работник не указал пол? Нам понадобится дополнительное значение, но bool позволяет хранить только два значения
//Мы можем перейти к типу int
struct EmployeeC {
	std::string name;
	int salary;
	int gender; //нам придётся договориться, что 0 - неопределно, 1 - male, 2 - female
};

//при использовании типа int мы рискуем попасть в ловушку, когда анализируя код, мы не сможем понять какой именно пол был указан, так как договорённость может быть не отражена в коде

//Выходом из этой ситуации является специальный тип - перечисление (enumeration)

//Определим enumeration с тремя значениями
enum gender_t { MALE, FEMALE, UNKNOWN }; //эта запись вводит новый тип данных с тремя значениями

struct EmployeeD {
	std::string name;
	gender_t gender; //переменная типа gender_t
	int salary;
};

void employee_enum_test() {
	EmployeeD designer;
	designer.name = "Anna";
	designer.salary = 1000;
	designer.gender = FEMALE; //обратите внимание, что значения описываются в коде идентификаторами, что делает его более удобным для понимания

	EmployeeD developer;
	developer.name = "Bert";
	developer.salary = 1500;
	developer.gender = MALE;

	//попробуем вывести данные на экран
	std::cout << developer.name << " " << developer.gender << " " << developer.salary << std::endl;
}

//при выводе на экран мы не увидели идентификатора, мы видим число
//на самом деле все enum переводятся в числовое представление при компиляции
//при необходимости мы можем сами назначить эти значения
enum color_t {RED = -1, GREEN = 0, BLUE = 2};

void int_values_set_test() {
	color_t red = RED, green = GREEN, blue = BLUE;
	std::cout << red << " " << green << " " << blue << std::endl;
}

//так как значения enum - это числа, то enum можно использовать в операторе выбора switch
std::string to_string(color_t color) {
	switch (color) {
	case RED: return "red";
	case GREEN: return "green";
	case BLUE: return "blue";
	}
	//unreachable code
}

void switch_test() {
	color_t red = RED, green = GREEN, blue = BLUE;
	std::cout << to_string(red) << " " << to_string(green) << " " << to_string(blue) << std::endl;
}

//для enum можно перегружать арифметические операции
color_t& operator++(color_t &color) {
	switch (color) {
	case RED: return color = GREEN;
	case GREEN: return color = BLUE;
	case BLUE: return color = RED;
	}
	//unreachable code
}

//Но нельзя перегружать операторы, которые являются только методами, например, скобки [] и ()

void increment_test() {
	color_t red = RED, green = GREEN, blue = BLUE;
	std::cout << to_string(++red) << " " << to_string(++green) << " " << to_string(++blue) << std::endl;
}

//числа можно преобразовывать в элементы enum
enum week_t {MON=0,TUE,WED,THU,FRI,SAT,SUN}; //день недели начнётся с ноля и далле будут прибавляться по единице
//таким образом, SUN = 6

week_t& operator++(week_t &w) {
	return w = week_t((w + 1) % 7);// w+1 приведёт к неявному преобразованию в int, week_t() преобразует снова к типу week_t
}

week_t& operator--(week_t &w) {
	return w = week_t(0 != w ? (w-1) : SUN);
}

week_t operator+(week_t w, int offset) {
	if (offset > 0)
		return week_t((w + offset) % 7);
	return week_t((7 + w - (-offset % 7)) % 7);
}

std::ostream& operator<<(std::ostream &os, week_t w) {
	switch (w) {
	case MON: os << "Mon."; break;
	case TUE: os << "Tue."; break;
	case WED: os << "Wed."; break;
	case THU: os << "Thu."; break;
	case FRI: os << "Fri."; break;
	case SAT: os << "Sat."; break;
	case SUN: os << "Sun."; break;
	}
	return os;
}

//подход с использованием enum вместо чисел позволяет избавиться от субъективности в сопоставлении значения числу
//счёт дней недели можно было начинать по-разному: с нуля или с единицы - enum избавляет от этой проблемы
//при дальнейшем использовании enum week_t нам нет необходимости знать какими именно числами представлены дни недели

//описанные выше примеры обладают существенными недостатками
//enum gender2_t {MALE,FEMALE,UNKNOWN};//определение нового enum с такими же идентификаторами может привести к неполадкам в компиляции старого кода

void drawback_test() {
	week_t day = week_t(MALE+1);//из-за неявного преобразования к типу int мы можем незаметно использовать идентификаторы одного типа для определения идентификаторов другого типа
	if (FEMALE == day) //сравниваются целочисленные представления
		std::cout << "women's day is " << day << std::endl;
}

//В С++ существует специальный тип enum class, который избавлен от этого недостатка
enum class lexer_t { DIGIT, LETTER, PUNCT };
enum class token_t { DIGIT, LETTER, PUNCT };

void enum_class_test() {
	token_t tok = token_t::DIGIT; //для каждого идентификатора необходимо указать из какого он типа
	//lexer_t lex = lexer_t(token_t::NUMBER + 1); //нет неявного преобразования из token_t в int!
	lexer_t lex = lexer_t(2);
	//std::cout << tok << " " << lex << std::endl; //нет неявного преобразования из lexer_t или token_t в int!
	std::cout << static_cast<int>(tok) << " " << static_cast<int>(lex) << std::endl; //явное возможно!
}

int main() {
	if (false) employee_enum_test();
	if (false) int_values_set_test();
	if (false) switch_test();
	if (false) increment_test();
	if (false) drawback_test();
	if (false) enum_class_test();

	return 0;
}