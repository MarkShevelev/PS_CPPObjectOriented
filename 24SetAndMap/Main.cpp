#include <iostream>
#include <string>

//�������� ������� ����� ���������� ������������ ��� ������ ���������

//���� ����� ������ �������� ��������� ��� ����, ����� ��������� � �� ������� ��������, �� ��� ����� ����� ������������ ����������� ��������� set

//������, ������� ���������� �������� �� ���� �������� � ������� � ������
#include <vector>
#include <set>   //������������� ���������

template <typename T>
std::vector<T> unique_elements(std::vector<T> const &lha, std::vector<T> const &rha) {
	std::set<T> unique_set; //set ������ ������ ���������� ��������, ��������� ��������� ������������
	for (auto &element : lha)
		unique_set.insert(element); //insert - ��������� ������ � ���������
	for (auto &element : rha)
		unique_set.insert(element);
	return { unique_set.begin(),unique_set.end() }; //������������ ������ �� ���� ����������
}

void unique_elements_test() {
	std::vector<std::string> big_cats = { "Lion","Tiger","Leopard","Panther","Jaguar" };
	std::vector<std::string> animals = { "Wolf","Lion","Tiger","Mouse","Horse" };
	std::vector <std::string> unique_animals = unique_elements(big_cats, animals);
	for (auto &element : unique_animals)
		std::cout << element << ' ';
	std::cout << std::endl;
}

//�������: �������� ���������, ������� ����������� � ������������ ����� � ������.
//���� ������������ � ����� ������� �� ����������, �� ��������� ������������ ������ ������������ � ����� ��������� �� �������� �����������
//���� ������������ � ����� ������� ��� ���� � �������, �� ��������� ��������� ������.
//���� ������ ��������, �� ������� ��������� � �������� ���� �����/������, ���� ������ ������ - ������� �����������

struct User { //���������� ���������� ��������� User � ������������ � � set
	std::string login, password;
	User(std::string const &login, std::string const &password): login(login), password(password) { }
};

//������ ��� �� �������������!
/*void user_login_test() {
	std::set<User> users;

	bool proceed = true;
	while (proceed) {
		std::string login, password;
		std::cin >> login;
		if ("exit" == login) break;
		std::cin >> password;

		users.emplace(login, password); //��� ������� �������� ������� � ��������� ��������� ������, ��������� � ����������� ��������� ��������� <
	}

	for (auto &user : users)
		std::cout << user.login << " : " << user.password << std::endl;
}*/

struct SortedUser { //��� ����� ��������� ��������� ����������� ��������
	std::string login, password;
	SortedUser(std::string const &login, std::string const &password) : login(login), password(password) { }
};
//���� ������������ ��������� �� ������, ������ � ��������� ����� ����� �� ������
bool operator<(SortedUser const &lha, SortedUser const &rha) {
	return lha.login < rha.login;
}

bool operator==(SortedUser const &lha, SortedUser const &rha) {
	return lha.login == rha.login;
}

void sorteduser_login_test() {
	std::set<SortedUser> users;

	bool proceed = true;
		while (proceed) {
			std::string login, password;
			std::cin >> login;
			if ("exit" == login) break;
			std::cin >> password;

			users.emplace(login, password);
		}

	for (auto &user : users)
		std::cout << user.login << " : " << user.password << std::endl;
}

//���� �������� ��� ����� ���� ������� � � �������������� �������, �� � ��������������� set ��� ����������� �����������!

void sorteduser_login_search_test() {
	std::set<SortedUser> users;

	bool proceed = true;
	while (proceed) {
		std::string login, password;
		std::cin >> login;
		if ("exit" == login) break;
		std::cin >> password;

		if (0 == users.count({ login,password })) { //����� count ������������ ���-�� ��������� ��������, ������� ���������
			users.emplace(login, password);
			std::cout << "New user added!" << std::endl;
		}
		else {
			auto it = users.find({ login,password }); //����� find ���� �������� (���������) ��������, ������� ���������
			if (password == it->password) //�������� ���� ����, ��� ���������, �������������� �������� -> ��������� ���������� � ������ ��������� ��� ������ �������� �������������
				std::cout << "Welcome back, " << it->login << "!" << std::endl;
			else
				std::cout << "Wrong password!" << std::endl;
		}
	}

	for (auto &user : users)
		std::cout << user.login << " : " << user.password << std::endl;
}

//� ���������� ������� ��� �������� ������� ��������� ���������� ���������� ��������
//i) ��� ������ �� ������ ��� .count({login,password}) � .find({login,password})
//���� ���������, ��� ��� ����� � ������� ������� ����������� �� ���� ��������, � �� �����, ��� �� ����� ���� ��� ���� �� ���������� ������ ������ login
//ii) ��-�� ����, ��� �� �������� � set ��� ��������� SortedUser, ��� �������� ����������� ��������� == � <, ���� �� �������� ��� ������ ������������ ��� �������� � ������ login

//����� �������� ���� �������� �������� ������ �� "����" - login � "��������" - User
//� ���� ���������� ��������� ������ map
#include <map>
void user_login_map_test() {
	std::map<std::string, User> users; //map ����� ��� ���������: ������ - ��� �����, ������ - ��� ��������

	bool proceed = true;
	while (proceed) {
		std::string login, password;
		std::cin >> login;
		if ("exit" == login) break;
		std::cin >> password;

		if (0 == users.count(login)) { //������ �������� ������, ��� ������������� ��������� ��������� ������ User
			users.insert(std::make_pair(login, User(login, password))); //����� ����������� �������, ���� Users �� ����� ���������� < ��� ==
			//map ����������� �������������� ������ ��� ������, �� �� ��� ��������
			//��� ������� � map ���������� ������� ���� ����-��������
			std::cout << "New user added!" << std::endl;
		}
		else {
			auto it = users.find(login);
			if (password == it->second.password) //�� ��������� �� �������� �� ���� ��������, � ���� <����, ��������>
				std::cout << "Welcome back, " << it->second.login << "!" << std::endl;
			else
				std::cout << "Wrong password!" << std::endl;
		}
	}

	for (auto &pair : users)
		std::cout << pair.second.login << " : " << pair.second.password << std::endl;
}

//������: �� ������ ����, ������� ������������ �����, ������� � ��� � ������, ��������� ������ ���
//ADD 2017-01-23 take my dog for a walk //�������� ���� "take my dog for a walk" �� 2017-01-23
//ADD 2017-01-23 visit a doctor //�������� ���� "visit a doctor" �� 2017-01-23
//ADD 2016-05-09 spare time
//Find 2017-01-23 //����� ��� ���� �� 2017-01-23
//take my dog for a walk
//visit a doctor
//Find 2017-05-09  //����� ��� ���� �� 2017-05-09
//No entries  //�� ������� ���
//EXIT //����� �� ���������

//������ �������� ����
struct Date {
	int year, month, day;
};

std::istream& operator>>(std::istream &is, Date &d) { //��������� ���� �� ������
	char delim;
	return is >> d.year >> delim >> d.month >> delim >> d.day;
}

#include <iomanip> //setfill setw
std::ostream& operator<<(std::ostream &os, Date const &d) { //��������� ����
	return os << std::setfill("0") << std::setw(4) << d.year << '-' << std::setw(2) << d.month << '-' << std::setw(2) << d.day;
}

//�.�. Date - ��� ����, �� ��� ���� ������� ����������� �������� <
//������������� ������
#include <tuple>
bool operator<(Date const &lha, Date const &rha) {
	return std::tie(lha.year, lha.month, lha.day) < std::tie(rha.year, rha.month, rha.day);
}

void date_entry_test() {
	std::map<Date, std::set<std::string>> date_entries; //Date - ����, ����� ���������� ��� - ��������

	bool proceed = true;
	while (proceed) {
		std::string command;
		std::cin >> command;

		if ("EXIT" == command) { proceed = false; continue; }
		if ("ADD" == command) {
			Date key; std::string entry;
			std::cin >> key;
			std::getline(std::cin, entry);
			date_entries[key].insert(entry); //�������� [] ������� �������, ���� ��� ��� ���, � ���� ������ �� ������������, ���� �� ����
		}
		if ("FIND" == command) { //����������� ��������������!
			for (auto &pair : date_entries) {
				Date date = pair.first;
				for (auto &entry : pair.second)
					std::cout << date << " " << entry << std::endl;
			}
		}
	}
}

int main() {
	if (false) unique_elements_test();
	if (false) sorteduser_login_test();
	if (false) sorteduser_login_search_test();
	if (false) user_login_map_test();
	if (false) date_entry_test();

	return 0;
}