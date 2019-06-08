#include <iostream>
#include <string>

//������ ���������� ����� �������� ��� ��������� �� ������ ������� ����� ���� ��������� ��� ����� ������ ���������- ������������
//������������ - ��� ������ ���������� ������� (��� ��������) �� ������ ��� ������������
//� C++, ��� � � ������ �����, ���������� �� ���� �������, ������������ ���������� ����� ��������

struct Base {
	int x;
	int sum_with(int y) const { return x + y;  }
};

struct Derived : Base { //����� Base �������� ������� ��� ������������ (������ super class) ��� ������ Derived
	int y;
	int mul_to(int x) const { return x * y; }
};
//����� Derived �������� ���������� ��� �������� (������ sub class) �� ������ Base
//Derived ������� �� Base; Base - ������� ����� ��� Derived
//Derived - �������� ����� �� Base; Base - ������������ ��� Derived
//Derived - ��� sub class �� Base; Base - ��� super class ��� Derived
//Derived ��������� ������ Base

//������������ ���������� � ���, ��� ������ ������ ������ Derived �������� ��� ��������, ���� � ������, ������ Base
void inheritance_test() {
	Base b;
	Derived d;
	b.x = 3; 
	std::cout << "Base call: " << b.sum_with(1) << std::endl;

	d.y = 3;
	std::cout << "Derived call: " << d.mul_to(2) << std::endl;

	d.x = 3; //���� � ������ Derived �� ���� ���������� ���� x, �� ����� Derived ������� ��� "� ����������" �� ������ Base
	//��� � ����� sum_with
	std::cout << "Base method call from Derived: " << d.sum_with(1) << std::endl;
}

//� ����� C++ ������������ ����������� ��������� �����������, �.�. ������ ������� ������ Derived ���������� ����������� ������ ������ Base
//������ ��������� ������ ����� �������� ������ �������������, ��� � � ������ ���������
//������ ��������� ������ ������ �������� private ������ �������������, ��� � � ������ ���������
//������ ��������� ������ ����� (!) �������� protected ������ �������������

struct BaseWithProtected {
	int pub_var;
	int sqr() const { return pub_var * pub_var;  }

protected:
	double protected_var;
	double sqr_() const { return protected_var * protected_var;  }
};

//������ ��� �� �������������!!!
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
	//d.protected_var = 1.3;//�� �� ����� ���������� � protected_var, �.�. ��� �������� ����� ������ ����������

	d.set_arg(1.3); //�� ������� �������� �����, ������� ������ ���������� � protected ����� ������������� ������
	std::cout << d.dsqr() << std::endl;
}

//������������ � �++ ������ ������: public, protected � private
//� ����������� �� ����� ������ ������ ����� ��������, � ����� � �� ��������, ������ � "�������������� ������� � �����" 

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
	//std::cout << s.first_name << std::endl;//�� �� ����� ���������� � �������� ������ ������ Name, �.�. ������������ ���� private
	std::cout << s.full_name() << std::endl; //�� ������ ����� ������� ����� Student ����� ���������� � ��������� Name
	//�� �����, ��� Name ��� �� private ������ ������ Student
}

//������������ ��� ������� � �������� ���������� ������ ������������ �������
//������ �� ��������� ��������� ����� ������������ ������� �������� (����� �������� : private Base), � ��������� - ������� (����� �������� : public Base)

//������������ ����� ����� ������������ ��� ���������� ����� ������������ � ��� ������������ �������
struct PrintableName : Name {//��� �������� ������������ ������� �� ���������
	void print() { std::cout << (first_name + " " + middle_name + " " + last_name) << std::endl; }
}; //�� ������� ����� ����� PrintableName �� ������ ��� ������������� ������ Name, ������� � ���� ����� �����

int main() {
	if (false) inheritance_test();
	if (false) protected_access_test();
	if (false) private_inheritance_test();
}


