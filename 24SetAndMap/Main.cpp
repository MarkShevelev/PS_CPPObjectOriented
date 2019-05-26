#include <iostream>
#include <string>

//Бинарные деревья можно эффективно использовать для поиска элементов

//Если стоит задача создания множества для того, чтобы проверять в нём наличие элемента, то для этого можно использовать стандартный контейнер set

//задача, выбрать уникальные элементы из двух векторов и сложить в третий
#include <vector>
#include <set>   //сортированное множество

template <typename T>
std::vector<T> unique_elements(std::vector<T> const &lha, std::vector<T> const &rha) {
	std::set<T> unique_set; //set хранит только уникальные элементы, повторное включение игнорируется
	for (auto &element : lha)
		unique_set.insert(element); //insert - добавляет элемен в множество
	for (auto &element : rha)
		unique_set.insert(element);
	return { unique_set.begin(),unique_set.end() }; //конструируем вектор из двух итераторов
}

void unique_elements_test() {
	std::vector<std::string> big_cats = { "Lion","Tiger","Leopard","Panther","Jaguar" };
	std::vector<std::string> animals = { "Wolf","Lion","Tiger","Mouse","Horse" };
	std::vector <std::string> unique_animals = unique_elements(big_cats, animals);
	for (auto &element : unique_animals)
		std::cout << element << ' ';
	std::cout << std::endl;
}

//Задание: написать программу, которая запрашивает у пользователя логин и пароль.
//Если пользователь с таким логином не существует, то программа регистрирует нового пользователя и пишет сообщение об успешной регистрации
//Если пользователь с таким логином уже есть в системе, то программа проверяет пароль.
//Если пароль неверный, то выдаётся сообщение о неверной паре логин/пароль, если пароль верный - выдаётся приветствие

struct User { //попытаемся определить структуру User и использовать её в set
	std::string login, password;
	User(std::string const &login, std::string const &password): login(login), password(password) { }
};

//данный код не компилируется!
/*void user_login_test() {
	std::set<User> users;

	bool proceed = true;
	while (proceed) {
		std::string login, password;
		std::cin >> login;
		if ("exit" == login) break;
		std::cin >> password;

		users.emplace(login, password); //при попытке добавить элемент в множество возникает ошибка, связанная с отсутствием оператора сравнения <
	}

	for (auto &user : users)
		std::cout << user.login << " : " << user.password << std::endl;
}*/

struct SortedUser { //для новой структуры определим необходимые операции
	std::string login, password;
	SortedUser(std::string const &login, std::string const &password) : login(login), password(password) { }
};
//Наши пользователи уникальны по логину, потому и сравнение будем вести по логину
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

//хотя подобный код можно было создать и с использованием вектора, но с исполльзованием set она значительно эффективнее!

void sorteduser_login_search_test() {
	std::set<SortedUser> users;

	bool proceed = true;
	while (proceed) {
		std::string login, password;
		std::cin >> login;
		if ("exit" == login) break;
		std::cin >> password;

		if (0 == users.count({ login,password })) { //метод count подсчитывает кол-во вхождений элемента, равного заданному
			users.emplace(login, password);
			std::cout << "New user added!" << std::endl;
		}
		else {
			auto it = users.find({ login,password }); //метод find ищет итератор (положение) элемента, равного заданному
			if (password == it->password) //итератор ведёт себя, как указатель, перегруженнный оператор -> позволяет обратиться к данным структуры без лишних операций разыменования
				std::cout << "Welcome back, " << it->login << "!" << std::endl;
			else
				std::cout << "Wrong password!" << std::endl;
		}
	}

	for (auto &user : users)
		std::cout << user.login << " : " << user.password << std::endl;
}

//в предыдущем примере нам пришлось сделать некоторое количество избыточных действий
//i) при поиске мы писали код .count({login,password}) и .find({login,password})
//этот необходим, так как поиск и подсчёт требуют совпадающих по типу объектов, в то время, как на самом деле нам было бы достаточно только строки login
//ii) из-за того, что мы включили в set всю структуру SortedUser, нам пришлось перегрузить операторы == и <, хотя по существу они просто перевызывали эти операции у строки login

//чтобы избежать этой проблемы разделим задачу на "ключ" - login и "значение" - User
//с этим эффективно справится шаблон map
#include <map>
void user_login_map_test() {
	std::map<std::string, User> users; //map имеет два параметра: первый - тип ключа, второй - тип значения

	bool proceed = true;
	while (proceed) {
		std::string login, password;
		std::cin >> login;
		if ("exit" == login) break;
		std::cin >> password;

		if (0 == users.count(login)) { //ключом является строка, нет необходимости создавать временный объект User
			users.insert(std::make_pair(login, User(login, password))); //метод срабатывает успешно, хотя Users не иммет операторов < или ==
			//map производить упорядочивание только для ключей, но не для значений
			//для вставки в map необходимо создать пару ключ-значение
			std::cout << "New user added!" << std::endl;
		}
		else {
			auto it = users.find(login);
			if (password == it->second.password) //по итератору мы получаем не само значение, а пару <ключ, значение>
				std::cout << "Welcome back, " << it->second.login << "!" << std::endl;
			else
				std::cout << "Wrong password!" << std::endl;
		}
	}

	for (auto &pair : users)
		std::cout << pair.second.login << " : " << pair.second.password << std::endl;
}

//Задача: на каждую дату, которая представлена годом, месяцем и днём в месяце, сохранить список дел
//ADD 2017-01-23 take my dog for a walk //добавить дело "take my dog for a walk" на 2017-01-23
//ADD 2017-01-23 visit a doctor //добавить дело "visit a doctor" на 2017-01-23
//ADD 2016-05-09 spare time
//Find 2017-01-23 //найти все дела за 2017-01-23
//take my dog for a walk
//visit a doctor
//Find 2017-05-09  //найти все дела за 2017-05-09
//No entries  //не найдено дел
//EXIT //выход из программы

//Ключом является дата
struct Date {
	int year, month, day;
};

std::istream& operator>>(std::istream &is, Date &d) { //считываем дату из потока
	char delim;
	return is >> d.year >> delim >> d.month >> delim >> d.day;
}

#include <iomanip> //setfill setw
std::ostream& operator<<(std::ostream &os, Date const &d) { //сохраняем дату
	return os << std::setfill("0") << std::setw(4) << d.year << '-' << std::setw(2) << d.month << '-' << std::setw(2) << d.day;
}

//т.к. Date - это ключ, то для него следует перегрузить оператор <
//воспользуемся тюплем
#include <tuple>
bool operator<(Date const &lha, Date const &rha) {
	return std::tie(lha.year, lha.month, lha.day) < std::tie(rha.year, rha.month, rha.day);
}

void date_entry_test() {
	std::map<Date, std::set<std::string>> date_entries; //Date - ключ, набор уникальных дел - значение

	bool proceed = true;
	while (proceed) {
		std::string command;
		std::cin >> command;

		if ("EXIT" == command) { proceed = false; continue; }
		if ("ADD" == command) {
			Date key; std::string entry;
			std::cin >> key;
			std::getline(std::cin, entry);
			date_entries[key].insert(entry); //оператор [] создаст элемент, если его ещё нет, и даст ссылку на существующий, если он есть
		}
		if ("FIND" == command) { //реализовать самостоятельно!
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