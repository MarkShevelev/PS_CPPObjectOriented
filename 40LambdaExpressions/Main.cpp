#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

//�� ��� ������������� ��������� ������� �� ��������� algorithm
//��� ��������� ��������� �������� � ������������ C++, ��������� ������� � ������� � ������������� ���������� operator()

//���������� ������ � ���������� ������� ���������� ������� � ����������
int random_in_range(int min, int max) {
	using namespace std;
	std::default_random_engine eng;
	return uniform_int_distribution<int>(min, max)(eng);
}

//������� random_in_range �������� ����� �����������
//i) � ������ ������������ � ���������� ���� generate, ������� ������� �������, �� ����������� ���������
//ii) ��� ������������ ������������� ������� ��������� �������������� ��������� ������� �� �������� �������� std::default_random_engine � std::uniform_int_distribution

//�� ����� ������ ��� ��������, ��������� �����
class RandomInRange final {
public:
	RandomInRange(int min, int max): distribution(min,max) { }
	int operator()() const { return distribution(engine); }

private:
	mutable std::default_random_engine engine;
	std::uniform_int_distribution<int> distribution;
};
//����� ��������� ��� "��������� �������������� ������" � ����� ������� � ������� ������ ����������� ��������� - ������ ������� ������, ��� ��������� ������������ ������� ������ � ��������� generate
//����� �������� ������� ���������� ������ std::default_random_engin � std::uniform_int_distribution ����������� � ���������������� ��� ������� ��������� ������� ������, ��� ������� ��������� �������

//������� ��� ������ ����� ����� �� �����
template<typename T>
void print(T x) { std::cout << x << ' '; }

void random_in_range_class_test() {
	using namespace std;

	int min, max;
	std::cin >> min >> max;
	vector<int> numbers(20);
	generate(numbers.begin(), numbers.end(), RandomInRange(min, max));
	for_each(numbers.begin(), numbers.end(), print<int>);
	std::cout << std::endl;

	sort(numbers.begin(), numbers.end());
	for_each(numbers.begin(), numbers.end(), print<int>);
	std::cout << std::endl;
}

//������ ��������� ������ ��-�������� ��������, �.�. ���������� ��������� ����� RandomInRange, ������� ������������ ������ ���� ���
//������ ��� ����� ������� � C++ ������������ ����������� ���������, ������� ��������� ���������� ������ ����� � ��� �����, ��� �� ������������

void random_in_range_lambda_test() {
	using namespace std;

	
	vector<int> numbers(20);
	{
		int min, max;
		std::cin >> min >> max;
		default_random_engine engine;
		uniform_int_distribution<int> distribution(min,max);
		generate(numbers.begin(), numbers.end(), 
			[&engine,&distribution]() {	return distribution(engine); } //���������� ������� � ������������� ���������� () � ������� ������-���������
		);
	}


	for_each(numbers.begin(), numbers.end(), 
		[](int x) { std::cout << x << ' '; } //���������� ������� � ������������� ���������� () � ������� ������-���������
	);
	std::cout << std::endl;

	sort(numbers.begin(), numbers.end());
	for_each(numbers.begin(), numbers.end(), 
		[](int x) { std::cout << x << ' '; } //���������� ������� � ������������� ���������� () � ������� ������-���������
	);
	std::cout << std::endl;
}

int main() {
	if (false) random_in_range_class_test();
	if (false) random_in_range_lambda_test();

	return 0;
}