#include <iostream>
#include <algorithm>
#include <vector>


//�� �����, ��� � �������������� ����������� ���������� ����� ������ ������ ������ ������� ��������� � ������ ������, �������������� ��������

//��� ���������� ��������
int ask() {
	int user_input;
	std::cin >> user_input;
	return user_input;
}

//��� ���������� � �������
int sqr(int x) { return x * x;  }

//��� ������ ��������
template <typename T>
void print(T x) { std::cout << x << ' ';  }

void algorithm_test() {
	int arr[10]; //������ ������ �� 10 ���������
	std::generate(arr, arr + 10, ask);//����������� �������� � ����������
	std::transform(arr, arr + 10, arr, sqr); //�������� � �������
	std::for_each(arr, arr + 10, print<int>); //�������� ��������
	std::cout << std::endl;
}

//��� ������ � ���������, �� ���������� � ���������� ������� ��� � ���������� �������
//��� ������ � �������� ��� ������� ������������ ���� ���� - ���������
void vector_algorithm_test() {
	std::vector<int> vec(10); //������ �� 10 ���������
	std::generate(vec.begin(), vec.end(), ask); //.begin() - ����� ��� ��������� ������������ ������� - ���������, ������� "���������" �� ������ �������, � .end(), �������������� �� �����, �.�. �� ������� ����� �� ������ �������
	std::transform(vec.begin(), vec.end(), vec.begin(),sqr);
	std::for_each(vec.begin(), vec.end(), print<int>);
	std::cout << std::endl;
}

//��� ��������������� ���������� ��� �� �������� ���������, ���������������� �� ���������
//����������� ��������� - ��� ��������� �������, ������� ����� ���� ��������������� ��� ����������, ���������� � ����� ����
//������ ��������� ���������� for_each
template<typename Iter,typename Fn>
void my_for_each(Iter begin, Iter end, Fn callback) {
	for (; begin != end; ++begin) //��� ����, ����� ������ �������� ������� ������� � �����������, ���������� ����, ����� �� ���� Iter ����� ���� ��������� �������� ++ != � *(�������������) 
		callback(*begin);
}

//�������� ��� �������� �� std::vector � �� �������
void my_for_each_test() {
	std::vector<double> vec = { 1.1,2.2,3.3,-1.1,-2.2,-3.3 };
	char arr[6] = "Hello";

	my_for_each(vec.begin(), vec.end(), print<double>);
	std::cout << std::endl;
	my_for_each(arr, arr + 5, print<char>);
	std::cout << std::endl;
}

//��������� �� ����������� ��� my_for_each ���������� �� ��� ����� �����������
//��������� ��������� ����������� �������� *

class AsteriskOverload {
	int i;
public:
	AsteriskOverload(int i): i(i) { }

	int operator*() const { //���� � ������� ������� ��� ���������, �� ��� �������� �������������, ���� ���� - ���������
		return i;
	}
};

void asterisk_operator_test() {
	AsteriskOverload asl(7);
	//std::cout << asl << std::endl;//��� ������ ������ ������� �� �����...
	std::cout << *asl << std::endl; //� ������������� �����, �.�. ��� ���������� �������� ���������� ����� �����
}

//�����������, �� ����� ����� ���� ����� � ����������� �� min �� max � �������� ����� ���������� my_for_each
//�� �� ����� �������� std::my_for_each(min,max,print<int>); �.�. transform ����� �������� ��������� �������� �������������
/*void naive_my_for_each_test() {
	my_for_each(-10, 0, print<int>);
}*/
//�����, ������� ���������� �������� �����

//�������� ����� Counter ��� ���� ����
class Counter {
	int const start;
	int current;
	
public:
	Counter(int start) : start(start), current(start) { }

	Counter& operator++() {
		++current;
		return *this;
	}

	int operator*() {
		return current;
	}

	bool operator==(Counter const &oth) {
		return oth.current == current;
	}

	bool operator!=(Counter const &oth) {
		return !(oth.current == current);
	}
};

void counter_my_for_each_test() {
	my_for_each(Counter(-10), Counter(0), print<int>);
}


int main() {
	if (false) my_for_each_test();
	if (false) asterisk_operator_test();
	if (false) counter_my_for_each_test();

	return 0;
}
