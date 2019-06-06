#include <iostream>
#include <string>
#include <vector>

//Вложенный класс (inner class или nested class) - это класс, определённый внутри другого класса
//Вложенный класс имеет доступ к внутренним данным окружающего класса, обратное неверно
//Вложенный класс может иметь различный доступ: private, public или protected
//При обращении к вложенному классу следует указывать пространство окружающего класса 

//Пример
class Account {
private: //обратите внимание, вложенный класс может быть private, т.е. само определение класса недоступно извне, например все его статические функции или конструкторы
	class Transfer {
	public:
		Transfer(int sum_to_transfer, Account &from, Account &to): sum_to_transfer(sum_to_transfer), from(from), to(to) { }
		//обратите внимание, что вложенный класс Transfer имеет доступ к private данным окружающего класса
		void commit() { from.amount -= sum_to_transfer; to.amount += sum_to_transfer; }
	private:
		int sum_to_transfer;
		Account &from, &to;
	};

public:
	Account(): Account(0) { }
	Account(int amount) : amount(amount) { }

	Transfer open_transfer_to(int sum, Account &to) {
		return Transfer(sum, *this, to);
	}

	int check() const { return amount; }

private:
	int amount;
};

void inner_transfer_class_test() {
	Account acc1(100), acc2(100);
	//Account::Transfer transfer; //явное использование имени недоступно
	auto transfer12 = acc1.open_transfer_to(10,acc2); //это разрешено, нет явного использования имени
	std::cout << "Acc1: " << acc1.check() << '\n' << "Acc2: " << acc2.check() << std::endl;

	transfer12.commit(); //хотя определение недоступно, но методы открыты, так что если объект создан, то можно вызвать его public методы

	std::cout << "Acc1: " << acc1.check() << '\n' << "Acc2: " << acc2.check() << std::endl;
}

//Одно из ходовых применений вложенных классов - это прокси
//Рассмотрим следующую задачу: есть список контактов, необходимо обеспечить доступ к этим контактам вне зависимости от увеличения количества контаков в векторе

//!!!Неверное решение!!!
class Contacts {
public:
	Contacts& add(std::string const &contact) { contacts.push_back(contact); return *this; }
	std::string get_contact(size_t id) const { return contacts[id]; } //здесь всё хорошо, изменение копии не страшно

	std::string& get_contact(size_t id) { return contacts[id]; } //здесь всё плохо! Вызов push_back погубит ссылку

private:
	std::vector<std::string> contacts;
};

class ProxContacts {
private:
	class proxy_contact {
	public:
		proxy_contact(ProxContacts &contacts, size_t id): contacts(contacts), id(id) { }
		proxy_contact& operator=(std::string const &str) { contacts.contacts[id] = str; return *this; }
		operator std::string() { return contacts.contacts[id]; } //неявное преобразование для прозрачной работы

	private:
		ProxContacts &contacts;
		size_t id;
	};

public:
	Contacts& add(std::string const &contact) { contacts.push_back(contact); }
	std::string get_contact(size_t id) const { return contacts[id]; }

	proxy_contact get_contact(size_t id) { return proxy_contact(*this, id); } //мы возвращаем объект, который запоминает индекс контакта и через индекс предоставляет доступ

private:
	std::vector<std::string> contacts;
};

void proxy_contact_test() {
	Contacts book;
	book.add("First contact");
	book.add("Second contact");
	auto first_contact = book.get_contact(0);
	book.add("Third contact");
	auto third_contact = book.get_contact(2);

	third_contact = first_contact; //всё выглядит так, словоно это и есть строка
	std::cout << first_contact << " : " << third_contact << std::endl; //всё благодаря неявному преобразованию
}

int main() {
	if (false) inner_transfer_class_test();
	if (false) proxy_contact_test();

	return 0;
}