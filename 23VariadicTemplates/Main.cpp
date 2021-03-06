#include <iostream>
#include <string>

//��� ������ ���������� ����������� �������
//��������, ���������� ����, ��� �� ����� �������� �������, ������� ����������� ��������� �����
//����� ��� ������� ����� ���������, ��� �������� ������� - ��� �����, �� �������� �� ����� ��������� ���������

template <size_t num>
size_t tpl_factorial(); //������� �� ����� ��������� ���������, �.�. �� ��� ��������� � �������� �������

//��� ��� ����������� ����� ������� ����������?
//����� ��������������� �������� n! = n*(n-1)!

template <size_t num>
size_t tpl_factorial() {
	return num * tpl_factorial<num - 1>(); //������ �������� ��������� � �������, �� ������ ����� ������� � ������ ���������� �������
}

//��� ������������� ���� ��������?
//�� �� ����� ��������� �������:
//if (1 == num) return 1;
//�� ����� ��������������� ���, ��� ��� ������� ������������� ���������� ������� ������ �, � �� ����� ������
template<>
size_t tpl_factorial<1>() {
	return 1;
}

void tpl_factorial_test() {
	std::cout << tpl_factorial<5>() << std::endl;
}

//���� ������������� ������ ������������� ����������� ����������� ������� ����������� �������� �� ��������� �������

//���� ������� ������������ ��� �������� �������� � ���������� ������ ����������
//������� ���������� ������: �������� �������, ������� ������� �������� �� ������������� ����� ����������

//�� ����� ����� �������� �������, ������� ������� �������� �� ���� ����������
template <typename T>
auto my_max(T const &lha, T const &rha) { return lha > rha ? lha : rha; }

//�� ���� ����� �� �������� ������������� ������� ������� ��� ��� ����������
template <typename T>
auto my_max(T const &first, T const &second, T const &third) { return my_max(first, my_max(second, third)); }

//������ ��������� ������� ��� ������ ���������� �������: ��������� ������ my_max � ����� �����������
//����� �� �� ���-�� ������������ ���� ������ ��� ������������� ����� �������� ����������?
//��, ��� ����� ����������� ����������� ���������
//template <typename... Types>, ��� typename... - ��� ��� ���������� "���" ��������� ����������, ����������� � ����� ���
#include <array>
template<typename T, typename... Types>
auto my_max(Types... args) {
	//�� ����� "�����������" �� � ������
	std::array<T, sizeof...(Types)> args_as_array = { args... };
	auto curr_max = args_as_array[0];
	for (auto &el : args_as_array)
		curr_max = my_max(el, curr_max);
	return curr_max;
}

void array_unpack_test() {
	std::cout << my_max<int>(7, -2, 3, -1, 0, 5) << std::endl;
}
//���� � ��� ���� ������������� ����� ���������, �� �� ����� �� ��������� �� � ���������, � ������� ������� � ������������ ������ ����������

//���������� ���� �������� ��������� ������ � ��� �������, ����� ���� ������ ���������, 
//���� ��� ���� �� ��������, �� ���������� � ������ ���� �� ����������

//���������� ���� ������: ���������� �� ������ ������������ ����� ���������� ������������ ����
//����� ��� ����������� ��������� ����������� ������!
//���� �������� ��������
template <typename T>
void print_any(T arg) {
	std::cout << arg;
}

//��� �������� - ��� ������� �� ������� � N �����������, � ������ � N-1 ����������
template <typename First, typename... Rest> //First - ��� ������ �������� �������, � ... Rest - ��� ��, ��� ����� ����
void print_any(First arg, Rest... args) {
	print_any(arg); //�������� ������ ��������, ����� ����������� �������: ������ ������ ����� ����
	print_any(args...);//������� ��, ��� ��������
}

void print_any_test() {
	print_any("Hello ", 42, " World", '!', 3.1415);
}

//����������� ������� ����� ��������� ��������� ������ � ������������ ������ � ����� ����������
template <typename... Args>
struct AnyStruct { };

template <typename T, typename... Rest>
struct AnyStruct<T,Rest...> {
	T head;
	AnyStruct<Rest...> tail;
};

//������ �� ����� ��������� ��������� � ������������ ������ ���������� ������ "�� ����"
void any_struct_test() {
	AnyStruct<int, std::string, double> a;
	a.head = 5;
	a.tail.head = "Hello World!";
	a.tail.tail.head = 3.1415;

	print_any(a.head, a.tail.head, a.tail.tail.head);
}

//� STL ���������� ��������������� ����������� ��� �������� ����� ��������
#include <tuple>
void tuple_test() {
	auto data = make_tuple(42, std::string("Hello World!"), 3.1415); //make_tuple ��������� ������� tuple � �������������� ������������ �����
	//����� �� ������ ����� ��� .tail � ����������� ���������� ������������� ���������-�������� (helper)
	std::cout << std::get<0>(data) << " " << std::get<1>(data) << " " << std::get<2>(data) << std::endl;
}

//tuple ����� ���� ������� ���������, ����� ������ ���������� ������ ����������
void tuple_tie_test() {
	std::string name1 = "Anna"; int age1 = 25;
	std::string name2; int age2;
	std::cin >> name2 >> age2;

	auto first = std::tie(name1, age1), second = std::tie(name2, age2);
	std::cout << (first == second ? "Equal" : "Different") << std::endl;
	if (first != second)
		std::cout << (first < second ? "First before Second" : "Second before First") << std::endl;
}

int main() {
	if (false) tpl_factorial_test();
	if (false) array_unpack_test();
	if (false) print_any_test();
	if (false) any_struct_test();
	if (false) tuple_tie_test();

	return 0;
}