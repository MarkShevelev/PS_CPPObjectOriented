#include <iostream>
#include <string>

//� ��������� ���������, ���������� ���������, ������� ����� ��������� ��������, �����������
//���������� ��������� ���������
struct EmployeeA {
	std::string name;
	int salary;
	std::string gender; //����� ��������� ������ ��� �������� male ��� female
};

//������������� ������ ������� ����������, ����� �������� � �� bool
struct EmployeeB {
	std::string name;
	int salary;
	bool is_male; //true - male � false - female
};

//��� ���� �������� �� ������ ���? ��� ����������� �������������� ��������, �� bool ��������� ������� ������ ��� ��������
//�� ����� ������� � ���� int
struct EmployeeC {
	std::string name;
	int salary;
	int gender; //��� ������� ������������, ��� 0 - �����������, 1 - male, 2 - female
};

//��� ������������� ���� int �� ������� ������� � �������, ����� ���������� ���, �� �� ������ ������ ����� ������ ��� ��� ������, ��� ��� ������������� ����� ���� �� �������� � ����

//������� �� ���� �������� �������� ����������� ��� - ������������ (enumeration)

//��������� enumeration � ����� ����������
enum gender_t { MALE, FEMALE, UNKNOWN }; //��� ������ ������ ����� ��� ������ � ����� ����������

struct EmployeeD {
	std::string name;
	gender_t gender; //���������� ���� gender_t
	int salary;
};

void employee_enum_test() {
	EmployeeD designer;
	designer.name = "Anna";
	designer.salary = 1000;
	designer.gender = FEMALE; //�������� ��������, ��� �������� ����������� � ���� ����������������, ��� ������ ��� ����� ������� ��� ���������

	EmployeeD developer;
	developer.name = "Bert";
	developer.salary = 1500;
	developer.gender = MALE;

	//��������� ������� ������ �� �����
	std::cout << developer.name << " " << developer.gender << " " << developer.salary << std::endl;
}

//��� ������ �� ����� �� �� ������� ��������������, �� ����� �����
//�� ����� ���� ��� enum ����������� � �������� ������������� ��� ����������
//��� ������������� �� ����� ���� ��������� ��� ��������
enum color_t {RED = -1, GREEN = 0, BLUE = 2};

void int_values_set_test() {
	color_t red = RED, green = GREEN, blue = BLUE;
	std::cout << red << " " << green << " " << blue << std::endl;
}

//��� ��� �������� enum - ��� �����, �� enum ����� ������������ � ��������� ������ switch
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

//��� enum ����� ����������� �������������� ��������
color_t& operator++(color_t &color) {
	switch (color) {
	case RED: return color = GREEN;
	case GREEN: return color = BLUE;
	case BLUE: return color = RED;
	}
	//unreachable code
}

//�� ������ ����������� ���������, ������� �������� ������ ��������, ��������, ������ [] � ()

void increment_test() {
	color_t red = RED, green = GREEN, blue = BLUE;
	std::cout << to_string(++red) << " " << to_string(++green) << " " << to_string(++blue) << std::endl;
}

//����� ����� ��������������� � �������� enum
enum week_t {MON=0,TUE,WED,THU,FRI,SAT,SUN}; //���� ������ ������� � ���� � ����� ����� ������������ �� �������
//����� �������, SUN = 6

week_t& operator++(week_t &w) {
	return w = week_t((w + 1) % 7);// w+1 ������� � �������� �������������� � int, week_t() ����������� ����� � ���� week_t
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

//������ � �������������� enum ������ ����� ��������� ���������� �� �������������� � ������������� �������� �����
//���� ���� ������ ����� ���� �������� ��-�������: � ���� ��� � ������� - enum ��������� �� ���� ��������
//��� ���������� ������������� enum week_t ��� ��� ������������� ����� ������ ������ ������� ������������ ��� ������

//��������� ���� ������� �������� ������������� ������������
//enum gender2_t {MALE,FEMALE,UNKNOWN};//����������� ������ enum � ������ �� ���������������� ����� �������� � ���������� � ���������� ������� ����

void drawback_test() {
	week_t day = week_t(MALE+1);//��-�� �������� �������������� � ���� int �� ����� ��������� ������������ �������������� ������ ���� ��� ����������� ��������������� ������� ����
	if (FEMALE == day) //������������ ������������� �������������
		std::cout << "women's day is " << day << std::endl;
}

//� �++ ���������� ����������� ��� enum class, ������� �������� �� ����� ����������
enum class lexer_t { DIGIT, LETTER, PUNCT };
enum class token_t { DIGIT, LETTER, PUNCT };

void enum_class_test() {
	token_t tok = token_t::DIGIT; //��� ������� �������������� ���������� ������� �� ������ �� ����
	//lexer_t lex = lexer_t(token_t::NUMBER + 1); //��� �������� �������������� �� token_t � int!
	lexer_t lex = lexer_t(2);
	//std::cout << tok << " " << lex << std::endl; //��� �������� �������������� �� lexer_t ��� token_t � int!
	std::cout << static_cast<int>(tok) << " " << static_cast<int>(lex) << std::endl; //����� ��������!
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