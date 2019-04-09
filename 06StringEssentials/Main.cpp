#include <iostream>
#include <string>

//������ �� �������� ����� �� ����� ������ � ������� ������� ������������
//�� ������ ��-�� ����, ��� ������� ������ � ������� �������
//�++ ������ ��� �������� �� ���� ��� � ������������
void construct_string() {
	std::string s1; //������ ������
	std::string s2('a', 10); //������ ������ 10, ����������� �������� 'a'
	std::string s3("Hello World!"); //�������� ������ �++ �� ������� ��������, ������������ ����
	std::string s4(s3); //����� ������ s3

	//������ �������� ������ ������� ������������ ������,
	//��� ������ ������ �� ������� ��������� ������ ����� ����������� ������������

	//������ �������� ����� �������, ��� ����� ���� �������� �� ����� ����� �������� ������
	std::cout << "s1: " << s1 << "\ns2: " << s2 << "\ns3: " << s3 << "\ns4: " << s4 << std::endl;

	//��� � ������� ��������, ������ ����� ��������� � ����������
	std::string in;
	std::cin >> in;
	std::cout << "in: " << in;

	//����� get ������� std::cin ��������� ������ ������ � ������-�����
	char buff[100];
	std::cin.get(buff, 100, '\n');//�������� �� ����� 99 �������� �� '\n' (�������� ������)

	//������� std::getline ������ ������ � ����������� ������ std::string
	std::string in2;
	std::getline(std::cin, in2, '\n'); //������ ������ � ����������� ������
	//���������� ����������� ������ ������������ �������������
}

//������ � ��������� ������, ��������
void accessing_string() {
	std::string s("Hello String!");

	//������ � ��������� ������ �������������� �������� at � []
	for (std::string::size_type pos = 0; pos != s.size(); ++pos)
		std::cout << s[pos] << "  " << s.at(pos) << std::endl;
	//������� ����� [] � .at ������� � ���, ��� .at ���������� �������� ������ �� ������� ������� ������

	//���� ����������� �������� ������ � ������� � ���������� ��������
	std::cout << s.front() << "<...>" << s.back() << std::endl;

	//��� ������������� ����� �������� ������ � ������� ���������� ������
	//s.data()[1] = 'h';//�++ 17
	std::cout << s.c_str() << std::endl;
}

//������ ����� ���������� �� ������ ���������� ����� �����
void compare_string() {
	std::string s1("Abba");
	std::string s2("Bbba");

	std::cout << std::boolalpha << (s1 == s2) << " " << (s1 > s2) << " " << (s1 < s2) << std::endl;

	//����� ������������ ����� compare, ������� ���� ����� ��������� ������� strcmp �� ����� ��
	std::string user_input;
	std::cin >> user_input;
	if (0 == user_input.compare(s1))
		std::cout << "Yes" << std::endl;
	else
		std::cout << "No" << std::endl;
}

//������ ����� ��������������
void modification_string() {
	std::string a, b;
	std::cin >> a >> b;

	//������ ����� ��������� ������ � �������������� ��������� +, ������� ������ ����� ������
	std::string sum = a + b;
	std::cout << "a+b: " << sum << std::endl;

	//����� ��������� ������ � ��� ������������ ������
	std::string c;
	std::cin >> c;
	c += a;
	std::cout << "c + a: " << c << std::endl;
	c.append(b);
	std::cout << "c + a + b: " << c << std::endl;

	//� ������ ����� ��������� ��������� ������� � �����
	std::cout << a << " ";
	a.push_back('#');
	std::cout << a << " ";

	//� ��������� ��������� ������
	a.pop_back();
	std::cout << a << std::endl;

	//������� ����� � ��������
	a.insert(2, b);
	std::cout << "a insert b: " << a << std::endl;
}

//replace
void replace_string() {
	std::string str = "Hello World!";
	str.replace(6, 5, "Replace");
	std::cout << str << std::endl;
}

//substring
void substring_string() {
	std::string str = "Hello World!";
	std::cout << str.substr(6) << std::endl;
	std::cout << str.substr(0, 5) << std::endl;
}

int main() {
	if (false) construct_string();
	if (false) accessing_string();
	if (false) compare_string();
	if (false) modification_string();
	if (false) replace_string();
	if (false) substring_string();

	return 0;
}