#include <iostream>
#include <string>

//��� �������� ������ ���������� ��������
//�� ������� ������������ std::set
//������ std::set �������� ������������ ������������
//i)    � std::set ����� �������� ������ ����� �������, ��� ������� �������� �������, �.�. ������� ���������� ��������� <, ������          ����� �������, ����� ��� ����� O1 � O2 �����������: O1 < O2 => !(O2 < O1) � !(O1 < O2) && !(O2 < O1) => O1 == O2
//ii)   � std::set ������� ����������� � ������, ��������� ������ ���������� ���������� log(N), ��� N - ����� ��������� � ������
//      ��� ���������� K ��������� � std::set ��� ����������� K*log(K) ��������, �.�. ������� ��, ������� ��� ����������

//� ��������� ��������� ��� ����� ���� �����, �������� ���� �� ����� ������ �������� � ��������� ��������
//���� ����� ������ �� ����� ��� �������� ������������� ������ (����������) �������� ���� � ������, �� �������� �� ���������� �� std::set � ������ ����-���� ����� ��������
//������ ����� �������� �������� "���-�������"
//���-������� ������ �������� �� �������� ������������� ������� ������� ������������ ��������, ������� ���������� ����� � ���������� �������������� ������ � �������
//������������� ������� �������� ������������ � ������� ���-�������

//�������� ��������� � ��������� �� �������� ���-������� ������������ �������� std::unordered_set

#include <unordered_set>
void unordered_set_test() {
	using namespace std;
	unordered_set<int> set_of_integers;
	for (int counter = 0; counter != 10; ++counter) {
		int user_input;
		cin >> user_input;
		set_of_integers.insert(user_input);
	}

	for (auto i : set_of_integers)
		cout << i << ' ';
	cout << endl;
}

//� ������� �� std::set std::unordered_set �� ������������� ������� �������� �� ������� ��������� ��� ������
void unordered_set_of_strings() {
	using namespace std;
	unordered_set<string> set_of_strings;
	for (int counter = 0; counter != 5; ++counter) {
		string user_input;
		cin >> user_input;
		set_of_strings.insert(user_input);
	}
	cout << "-----------------------" << endl;
	for (auto i : set_of_strings)
		cout << i << '\n';
	cout << endl;
}

//��� ����, ����� ������������ � std::set ����������� ������, ��� ���� ���������� ����������� �������� <
//��� ����, ����� ������������ � std::unordered_set ���������� ������, ��� ���������� ����������� �������� == � ������� ����������� ���-�������

//������
struct InRagnePredicateHasher;

class InRangePredicate final {
public:
	InRangePredicate(int min, int max): min(min), max(max) { }
	bool operator()(int x) const { return x >= min && x <= max; }

	//������������� �������� ��������� �� ����������
	bool operator==(InRangePredicate const &oth) const { return min == oth.min && max == oth.max; }

	friend std::ostream& operator<<(std::ostream &os, InRangePredicate const &p);
	friend InRagnePredicateHasher;

private:
	int const min, max;
};

std::ostream& operator<<(std::ostream &os, InRangePredicate const &p) {
	return os << "[" << p.min << "," << p.max << "]";
}

//�����, ������� ������������ ����� ������� �����������, ����������� �������� �� ������ �������
struct InRagnePredicateHasher final {
	int operator()(InRangePredicate const &p) const { return p.min << 5 ^ p.max; }
};

void inrangepredicate_unordered_set() {
	using namespace std;
	unordered_set<InRangePredicate, InRagnePredicateHasher> predicate_set;
	for (int counter = 0; counter != 5; ++counter) {
		int user_min, user_max;
		cin >> user_min >> user_max;
		auto done = predicate_set.insert(InRangePredicate(user_min, user_max));
		cout << (done.second ? "Inserted new range: " : "Range already exists: ") << *done.first << endl;
	}

	cout << "-------------------------" << endl;
	for (auto const &p : predicate_set)
		cout << p << '\n';
	cout << endl;
}


int main() {
	if (false) unordered_set_test();
	if (false) unordered_set_of_strings();
	if (false) inrangepredicate_unordered_set();

	return 0;
}