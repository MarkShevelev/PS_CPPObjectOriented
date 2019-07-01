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
	cin >> min >> max;
	vector<int> numbers(20);
	generate(numbers.begin(), numbers.end(), RandomInRange(min, max));
	for_each(numbers.begin(), numbers.end(), print<int>);
	cout << endl;

	sort(numbers.begin(), numbers.end());
	for_each(numbers.begin(), numbers.end(), print<int>);
	cout << endl;
}

//������ ��������� ������ ��-�������� ��������, �.�. ���������� ��������� ����� RandomInRange, ������� ������������ ������ ���� ���
//������ ��� ����� ������� � C++ ������������ ����������� ���������, ������� ��������� ���������� ������ ����� � ��� �����, ��� �� ������������

void random_in_range_lambda_test() {
	using namespace std;

	
	vector<int> numbers(20);
	{
		int min, max;
		cin >> min >> max;
		default_random_engine engine;
		uniform_int_distribution<int> distribution(min,max);
		generate(numbers.begin(), numbers.end(), 
			[&engine,&distribution] {	return distribution(engine); } //���������� ������� � ������������� ���������� () � ������� ������-���������
		);
	}


	for_each(numbers.begin(), numbers.end(), 
		[](int x) { cout << x << ' '; } //���������� ������� � ������������� ���������� () � ������� ������-���������
	);
	std::cout << std::endl;

	sort(numbers.begin(), numbers.end());
	for_each(numbers.begin(), numbers.end(), 
		[](int x) { cout << x << ' '; } //���������� ������� � ������������� ���������� () � ������� ������-���������
	);
	cout << endl;
}

//������ ��������� ������������ ������������, ��������� �� ��� ��� ������ [](){}
//[ ] - ���������� ������ ��������� ����������, ������� ���������� �� ���������� ������ ������ ���������
//( ) - ���������� ������ ����������, ������� ��� ������ ������� �������� � ������� ������
//{ } - ���������� ���� ��������� ()
//����� �������� ����� ���� �������������� ������������
//[] () mutable throw() -> int { }
//mutable ��������� �������� ������ � ����, throw() - ������������� ��������� ����������, -> int - ��������� ������������ ���
//�������������, ������� ������������ ���, �� �������� �������������

//���������� ��������� �������� "�������" ������

//������ ���� ������ ������������ � �� ������
//������ ���������� ��� �����, ��������������� �������
void capture_by_copy_and_reference() { 
	using namespace std;
	vector<int> numbers = { 1,2,3,-2,-3,0,4 };
	for (auto i : numbers)
		cout << i << ' ';
	cout << endl;

	{//������ �� ����������� ��� �������� ������������� �����
		cout << "count positive is " << count_if(numbers.begin(), numbers.end(), [](int x) { return x > 0; }) << endl;
	}

	{//������� ����� � ����������, ���������� ��������� ���� �����
		int min, max;
		cin >> min >> max;
		//�� ����� �� ��������� ����, ����� ������ �����������, � ������������ ����������� ��������� [=]
		//��� ���� ����� ��������� ������������ ��� ���������� ����������
		cout << "count in (" << min << "," << max << ") is " << count_if(numbers.begin(), numbers.end(), [=](int x) { return x > min && x < max; }) << endl;
	}

	{//��� ������� �� ������, �� ����� ������ ������, ������� ��������� ��� ������ ���������
		int p = 0;
		//��� ������� ���� ���������� ���������� ������������ ��������� [&]
		for_each(numbers.begin(), numbers.end(), [&](int x) { cout << ++p << ' '; } );
		cout << '\n' << p << endl;
	}
}

//������ this
//� ������ ��������� ������ ��������� ���������� ������ �������, �� ����� ��������� ��������� �� ������ (this)
class CaptureTest final {
public:
	CaptureTest(size_t count_numbers, int min , int max) : numbers(count_numbers), min(min), max(max) {
		int p = 0;
		//p - ��������� ������, �� ����� ����������� ����������� [&p]
		std::generate(numbers.begin(), numbers.end(), [&p] { return p++; }); //���� �������� ������ ���, �� ����� �������� ()
	}

	void print() const {
		std::for_each(numbers.begin(), numbers.end(), [](int x) { std::cout << x << ' '; }); //���������� ������� ���������� ����������� �� �����
		std::cout << std::endl;
	}

	int count_in_range() const {
		//��������� min � max ������, �.�. ��� �� �������� ���������� �����������
		//return count_if(numbers.begin(), numbers.end(), [min,max](int x) { return x > min && x < max; });
		
		//����� ��������� ��������! �������� ��������� �� ������
		return count_if(numbers.begin(), numbers.end(), [this](int x) { return x > min && x < max; });
	}

	
private:
	std::vector<int> numbers;
	int const min, max;
};

void this_capture_test() {
	CaptureTest ct(20, -10, 10);
	ct.print();
	std::cout << ct.count_in_range() << std::endl;
}


int main() {
	if (false) random_in_range_class_test();
	if (false) random_in_range_lambda_test();
	if (false) capture_by_copy_and_reference();
	if (false) this_capture_test();

	return 0;
}