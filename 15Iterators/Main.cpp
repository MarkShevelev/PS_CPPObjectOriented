#include <iostream>
#include <algorithm>
#include <vector>
#include <string>


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

//���������, ������� ������������ � ����������� ���������� ������ ������������� ������� ��� ����� �������

#include <iterator>
class IterCounter {
	int const start;
	int current;

public:
	typedef int       value_type;
	typedef int       difference_type;
	typedef int*      pointer;
	typedef int&      reference;

	typedef std::forward_iterator_tag  iterator_category;

	IterCounter(int start) : start(start), current(start) { }

	IterCounter& operator++() {
		++current;
		return *this;
	}

	IterCounter& operator++(int v) {
		IterCounter tmp(*this);
		++*this;
		return tmp;
	}

	int& operator*() {
		return current;
	}

	int operator*() const {
		return current;
	}

	bool operator==(IterCounter const &oth) {
		return oth.current == current;
	}

	bool operator!=(IterCounter const &oth) {
		return !(oth.current == current);
	}
};

void itercounter_test() {
	std::for_each(Counter(-10), Counter(0), print<int>);
}

//� ��������� ������� �� ��������� ��������� ������������� ����������� �������� ->
//��������, ���� �� �������� � ������� �� �����������

struct Person {
	std::string name, familyname;
	bool operator==(Person const &p) {
		return name == p.name && familyname == p.familyname;
	}
};

void vector_iterator_test() {
	std::vector<Person> persons({ {"Boris","Bolkan"}, {"Dean","Corson"}, {"Liana","Telfer"}, {"Viktor","Fargas"} });
	std::vector<Person>::iterator res = std::find(persons.begin(), persons.end(), Person{ "Liana","Telfer" });
	//�������� find ���������� �������� �� ������ ��� �������
	//������� �� ����� ������
	std::cout << (*res).name << " " << (*res).familyname << std::endl; //��� ���������, �� �� �� ������ ������������ ��������� �������� ->
	std::cout << res->name << " " << res->familyname << std::endl; //������� ��������, ��� -> ����������� � ���� std::vector<Person>::iterator, ������� ����� �� ������ ���� ����������
}

int main() {
	if (false) my_for_each_test();
	if (false) asterisk_operator_test();
	if (false) counter_my_for_each_test();
	if (false) itercounter_test();
	if (false) vector_iterator_test();

	return 0;
}
