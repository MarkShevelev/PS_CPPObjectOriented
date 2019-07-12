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

int main() {
	if (false) unordered_set_test();
	if (false) unordered_set_of_strings();

	return 0;
}