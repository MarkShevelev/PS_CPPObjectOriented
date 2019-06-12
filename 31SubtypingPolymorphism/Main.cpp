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



int main() {
	if (false) print_name_test();
	if (false) print_student_test();
	if (false) all_check_test();

	return 0;
}