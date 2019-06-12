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
	std::cout << name.first_name << std::endl;
}

void print_name_test() {
	Name ray("Ray","John","Strangeway");
	PrintableName jose("Jose", "Lopes", "De Vega");

	print_name(ray);
	print_name(jose);
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



int main() {
	if (false) print_name_test();

	return 0;
}