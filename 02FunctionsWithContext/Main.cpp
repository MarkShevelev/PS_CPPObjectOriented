#include <iostream>
#include <algorithm>
#include <cstdlib>

void print_int(int x) {
	std::cout << x << " ";
}

//���� ����������� ��������� � ���� ��������� ������������ ��� �������� ����,
//���������� ��� ���������� ��� �� ������������� � ������������ ����������� ����������������

//���������� ������ � ���������� ������� ����������

//��������� ���������� ������, ��������� �������� std::generate
int zero() {
	return 0;
}

void zerofill_array_test() {
	int arr[10];
	std::generate(arr, arr + 10, zero); //std::generate ��������� ���������� ������� � ��������� �� �������
	std::for_each(arr, arr + 10, print_int);
	std::cout << std::endl;
}

//�� ����� �� ��������� ����� ������, ���� �������� �������, ������� ���������� ������ ��������
int unity() {
	return 1;
}

void unityfill_array_test() {
	int arr[10];
	std::generate(arr, arr + 10, unity);
	std::for_each(arr, arr + 10, print_int);
	std::cout << std::endl;
}

//������ �� �� ����� ��������� ������������ ������ ������, ������ �����, ������� �� �������� �� ����� ����������
//��������� ��� �� �������������
int any_number(int x) {
	return x;
}

void anyfill_array_test() {
	std::cout << "Enter to number to fill: " << std::endl;
	int user_fill;
	std::cin >> user_fill;
	
	int arr[10];

	//???
	//std::generate(arr, arr + 10, any_number); //����� ��������� ������ ����������
	//�������� � ���, ��� std::generate ����� �������� ������ ������� ��� ����������
	//���� � ������� ����� �������� ��������, �� std::generate �� ����� ������ ��� �����
	//�� �� �����, ���� ��� ��������...

	std::for_each(arr, arr + 10, print_int);
	std::cout << std::endl;
}

//�� �������� � �������������� ��������:
//������� ��������� ������� x, �� �� ������ �������� �� ����� ��������
/*
int any_number() {
	return x;
}
*/
//x - ������ ������������ ���������, ����� �������, ������ �� �����
//� ������ �� ������������ ������ - ���������� ������� ���������

int global_x;
int any_number_global() {
	return global_x;
}

void anyfill_global_array_test() {
	std::cout << "Enter to number to fill: " << std::endl;
	int user_fill;
	std::cin >> user_fill;

	int arr[10];
	//������������� ���������� ��������
	global_x = user_fill;
	std::generate(arr, arr + 10, any_number_global); //std::generate �������� ������� ��� ����������, � ��� ������� ������ �������� �� ����������� ������������
	std::for_each(arr, arr + 10, print_int);
	std::cout << std::endl;
}

//������� ������������� ������ ��������� ���������� �������� "����������"
//�������, ������� �������� ������ ������-�� ���, ����� �������� ����������, ��������, �� ����������� ������������, �������� "������� � ����������" ��� "������� � ����������"
//�� �����, ������ �������� ������ � ��������� ���������� �������� "����������" ��� "����������": ��������� ��������, ���������� �������� � �.�.

//������ � ������������ ����������� � ���������� �������� � � ����� ��, ���� ������ ��������

//��������� �������, ������� ����� ��� ������ ��������� ������ ���������� ��������� ���� �������������� ����������
/*
int arithm() {
	int tmp = c;
	c += d;
	return tmp;
}
*/
//��� ������� �������� ��� ��������� ���������� c � d, ������� �������� � �������� ����������
//��������� ���������, ������� ����� ��������� ��� ������
struct ArithmContext {
	int c, d;
};

//��������� ������� ���, ����� ��� ��������� ����� ���������
int arithm(void *address) {//����� �� ������ �����, ��� ������� ��������! (������������)
	ArithmContext *context = (ArithmContext*)address;
	int tmp = context->c;
	context->c += context->d;
	return tmp;
}

//�������� ���� �������� generate, ������� ����� �����, ��� ������� ������� ��������
//my_generate �� ����� ������ � ��������� generator (������������), �� ����� ��� �� ��������� � ���� ��� ��������
void my_generate(int *begin, int *end, int(*generator)(void*), void *generator_context) {
	while (begin != end) {
		*begin++ = generator(generator_context);//��� ������ ������� �������� ������� �������� � generator
	}
}

void generate_with_context_test() {
	std::cout << "Enter the first element of the progression and the difference: " << std::endl;
	int user_a, user_d;
	std::cin >> user_a >> user_d;

	int arr[10];

	//������ ��������
	ArithmContext context = { user_a,user_d }; //�� �����, ����� �������� ��� �����, � my_generate - ��� :)
	my_generate(arr, arr + 10, arithm, &context); //�������� my_generate � ���������
	std::for_each(arr, arr + 10, print_int);
	std::cout << std::endl;
}

//�������� ������� ��������� ��������� ����� � ���������
//��������� ��������� ����� � �������� ��������� ������� ���� ��������� ����������
/*
int rand_in_range() {
	return rand()%(max-min+1) + min;
}
*/
//max � min - ��������� ����������
//������ ���������
struct RangeContext {
	int min, max;
};

//�������, ��������� ��������
int rand_in_range(void *address) {
	RangeContext *context = (RangeContext*)address;
	return rand() % (context->max - context->min + 1) + context->min;
}

void rand_in_range_test() {
	std::cout << "Enter the range min max: " << std::endl;
	int min, max;
	std::cin >> min >> max;

	int arr[10];

	srand(1023);

	//������ ��������
	RangeContext context = { min, max }; //�� �����, ����� �������� ��� �����, � my_generate - ��� :)
	my_generate(arr, arr + 10, rand_in_range, &context); //�������� my_generate � ���������
	std::for_each(arr, arr + 10, print_int);
	std::cout << std::endl;
}


int main() {
	if (false) zerofill_array_test();
	if (false) unityfill_array_test();
	//if (false) anyfill_array_test(); //��� ������� �������� �������������� ������ ����������!!!
	if (false) anyfill_global_array_test();
	if (false) generate_with_context_test();
	if (false) rand_in_range_test();

	return 0;
}