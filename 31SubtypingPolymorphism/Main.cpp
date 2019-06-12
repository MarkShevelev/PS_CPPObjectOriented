#include <iostream>
#include <string>

//� ����� ������ ������� ������������ ��������, ��� �����-�� ������ � ����� ��������� ����� ����� ���� ��-�������
//� ��� ������� ������������ ������� ���������� ��������� ��������
//��������, ���������� ������� ������ �������� ad-hoc �������������, �.�. ����������� ������� � ���, ��� ��� ������� ���� ���� ����������� ������� ��� ������� ���������� ����, ���� � �� �� ��� ������ ��� ���������
//��������� ������� � ������ � C++ ������ �������� ��������������� �������������, �.�. ������� � ������ ������ ��� ��������� � ����������� �� ���������
//��������, ����� ���� ������ ����� ��������� � ���� ������� �������� ������������� ��������

//���������� ��������� ��� ������������ ���������
struct Name {
	Name(std::string const &first, std::string const &middle, std::string const &family): first_name(first), middle_name(middle), family_name(family) { }
	std::string first_name, middle_name, family_name;
};

class PrintableName : public Name {
public:
	PrintableName(std::string const &first, std::string const &middle, std::string const &family): Name(first,middle,family) { }
	void print(std::ostream &os) const { os << first_name << " " << middle_name << " " << family_name; }
};

//�� ����� ����� ���������� ������� ���� PrintableName � �������, ������� ������� Name
void print_name(Name const &name) {
	std::cout << name.first_name;
}

void print_name_test() {
	Name ray("Ray","John","Strangeway");
	PrintableName jose("Jose", "Lopes", "De Vega");

	print_name(ray); std::cout << std::endl;
	print_name(jose); std::cout << std::endl;
}

//������ � ������� print_name �� ��������� ������?
//���� � ���, ��� ���������� ��������: ��� PrintableName ��������� � ������������� public ������ Name, ������ ��� ���� � ������, �������� ����� ��������������� � Name, ���������� ��� �������� ���� � ������ � PrintableName!
//����������� ������� ������� ������ �������� ���, ����� ��������� ���������� ��������
//� ������ ����� ����� �������� ���������� "������"
//�������, ��� PrintableName �������� �������� Name, ���� ��� ��������, ������ ��� Name, ����� � ��� PrintableName
//���� PrintableName ������ Name, �� Name - �������� ��� PrintableName

//��� ������ �������?
//���� �� �������� ��������, ������� ����� ��������� ������ �� �������� ���������, �� �� ����� �� �������, ��� � ���� ����� ���������� ��������� �������, � �������� ����� �������� ��� ������
//��� �� � ������ ����
//����� ������ � ��������� ���� �������� �� ��� ����������� ������� ����������� ��������� ������ ���������

//���� � ���������� ���� ���� ���� � ����� ��������, �� �������, ��� �������� - ��� ����������� ���
//��������, ��� Name - ��� ����������� ���
//��������, ����� �������� ��� �������� ����� ���� ������, � �� ��������� ������ �� ��������, �������� "������������� ��������"
//���������� ��������� ��������� ���������, �������� ����� �����������, �� ��� ���� ������� ��������� ������

//����� � ������ �������������
class Student : public Name {
public:
	Student(std::string const &first, std::string const &middle, std::string const &family, std::string const &department): Name(first,middle,family), department(department) { }

	std::string const & get_department() const { return department; }

private:
	std::string department;
};

//�������, ������� ��������� �� ����� ��������� Student
void print_student(Student const &s) {
	print_name(s); //���������� �����������, ����������� �����
	std::cout << " from department " << s.get_department();
}

void print_student_test() {
	Student wulf("Willam", "Allan", "Wulf", "Computer science");
	print_student(wulf); std::cout << std::endl;
	print_name(wulf); std::cout << std::endl; //��-�������� ����� ��������������� ���������� ������ �����
}

//����� ��������, ��� �������� ����� ������ ������ ��� �������� ������������, � ������������� public
//� ��������� ������� ����������� �������� �� �����, �.�. �������� ������ �������� ������ ���� �������� ����� ������ ��������� ������, � private ��� protected ������������ ����� �� ���������

//���� � ������� �� ������� ��������, �� � �������� � C++ �� �� ������
//�������� ��������, ����������� �� �������� ����������� � �����-������ ��������
struct Predicate { //����� �������� int ���������� �������� ������� � ������ check, ��� ����� ��������
	bool check(int i) const { return true;  }
};

//�������, ������� �������� ��������, ������������ ������ �� ����� check �� ������ Predicate
bool all_check(int *arr, size_t size, Predicate const &p) {
	for (size_t pos = 0; pos != size; ++pos)
		if (!p.check(arr[pos])) return false;
	return true;
}

struct Positive : Predicate { //����� Positive ��������� Predicate � ��� ������ ���������� ��� check
	bool check(int i) const { return i > 0; }
};

void all_check_test() {
	int arr[] = { 1,3,-1,-2,2,-3 };
	Predicate p;
	Positive pp;

	std::cout << std::boolalpha << all_check(arr, 6, p) << std::endl;
	std::cout << std::boolalpha << all_check(arr, 6, pp) << std::endl;
}

//��������� ������� ���������������� � ������� all_check ������ ������� ��� Predicate, ��� � ��� ���������� - Positive
//������ ��������� ������ all_check �������� ����������, ������ �� � �� ������ ������� check
//��� ���������?
//�� ���� � "����������� ����������"
//����� ���������� ���������� ������� all_check, �� ����� ������ ������������� ��������, �.�. ��� ����������� �� ���� ����� ������ ����� ������� � �������, ������ ����� ������ ���� � ��� �� �����
//������������, ��������� ���������, �� ����������
//��� ��� ������ �������� �� ������ �� ����������� ������� � � ���� ������ ����� ����������� ��������� ������ ��� ��������� ��������, �� �� ����� �����������, �� �� ����������� ������� � �������� ���� ������ ���������� ���� � ��� �� ���

//��� �������� ����� ���� �� ������ � ������� ���������� �� �������!
//���� �� ������ ����, ����� ������ ����� �������, �� �� ���������� ������ ��������� �� �������, �� �������� ����� ���������� �����, �� �� �� �������� ���������, ����������� ��������� � �������!

bool good(int x) { return true; }
bool positive(int x) { return x > 0; }
typedef bool(*predicate_t)(int);

struct FPPredicate {
	FPPredicate() { to_call = good; }

	bool check(int x) const { return to_call(x); } //������ ������ check, ������� ����� ���������� ������, �� �������� �������� ��������, ����� ������ �� ���� ������

protected:
	predicate_t to_call;
};

//�������, ������� ��������� ������ �� ����������� FPPredicate
bool all_check(int *arr, size_t size, FPPredicate const &p) {
	for (size_t pos = 0; pos != size; ++pos)
		if (!p.check(arr[pos])) return false;
	return true;
}

struct FPPositive: FPPredicate {
	FPPositive() { to_call = positive; } //�� ������� ��������� check, ����� ����� ����� ������������ �������� ����
};

void fp_all_check_test() {
	int arr[] = { 1,3,-1,-2,2,-3 };
	FPPredicate p;
	FPPositive pp;

	std::cout << std::boolalpha << all_check(arr, 6, p) << std::endl;
	std::cout << std::boolalpha << all_check(arr, 6, pp) << std::endl;
}
//������ ��������� ����� ���������!

//��� ����, ����� �� ������ �������� ����� ������, � C++ ������������ ���������, ������� ��������� ������������ �������� ����� ������ ����� ��������� �� ������� ���������� �������
//������� ����� � ������� ������ �������� ������ virtual ����� �������� ��������� ��������� � ���������� �������

struct VMPredicate {
	virtual bool check(int x) const { return true; } //� ������� ������ �������� ����� check ��� virtual
};

struct VMPositive : VMPredicate {
	bool check(int x) const { return x > 0; } //� ���������� ������ ������ ������������� ������ �� �����, ���������� �������� ������ ���������� ��� ������, ����������� ��� virtual � ������� ������
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
//�� �������� ��������� ��������� ��� �������������� ����������
//�������� ��������, ��� ���������� ������� ��������� ����� virtual ������ � ������� ������
//��� ������ �� ������� �����-���� ����� �������� ������ virtual, �� ��� ����� ����� ����������� ����������� ��������� �� �������, ������� �������� � ����������� ����� ������ ������� - � "������� ����������� �������"

//����������� ����� ����� ���� �� ����, ����� ����� ��������� ��� �����������, ��� � ������� ������
class Figure {
public:
	Figure(std::string const &name): name(name) { }
	std::string const & what_am_i() const { return name; } //������� �����, ����������� ����������
	virtual double periphery() const { return 0.; } //����������� �����, �� ����� ������ ����������� ���������
	virtual double area() const { return 0.; }

private:
	std::string const name;
};

class Circle : public Figure {
public:
	Circle(double r): Figure("Circle"), r(r), circle_string("I'am a Circle") { }
	
	std::string const & what_am_i() const { return circle_string; } //���� ����� ����� ������ ����������� �����������
	
	double periphery() const { return 3.14*r*2.; } //��� ������ ����� ������� ����� ���������
	double area() const { return 3.14*r*r; }

private:
	double r;
	std::string const circle_string;
};

class Rectangle : public Figure {
public:
	Rectangle(double w, double h) : Figure("Rectangle"), w(w), h(h), rectangle_string("I'am a Rectangle") { }

	std::string const & what_am_i() const { return rectangle_string; } //���� ����� ����� ������ ����������� �����������

	double periphery() const { return 2*(w+h); } //��� ������ ����� ������� ����� ���������
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
//����������� ������ ��������� �� �������� ������������� ����������, ��� ���� ������� �� ������, ������� ���������� � �������� ������
//������������� ������ ��������� �� ��������� ������������ ����������, �.�. ��� ���������� � ������� figure_print ��� ���������� ����� �������� ����, ���������� � ������� Figure

int main() {
	if (false) print_name_test();
	if (false) print_student_test();
	if (false) all_check_test();
	if (false) fp_all_check_test();
	if (false) virtual_method_all_check_test();
	if (false) figure_print_test();

	return 0;
}