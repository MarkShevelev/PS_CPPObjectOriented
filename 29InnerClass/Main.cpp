#include <iostream>
#include <string>
#include <vector>

//��������� ����� (inner class ��� nested class) - ��� �����, ����������� ������ ������� ������
//��������� ����� ����� ������ � ���������� ������ ����������� ������, �������� �������
//��������� ����� ����� ����� ��������� ������: private, public ��� protected
//��� ��������� � ���������� ������ ������� ��������� ������������ ����������� ������ 

//������
class Account {
private: //�������� ��������, ��������� ����� ����� ���� private, �.�. ���� ����������� ������ ���������� �����, �������� ��� ��� ����������� ������� ��� ������������
	class Transfer {
	public:
		Transfer(int sum_to_transfer, Account &from, Account &to): sum_to_transfer(sum_to_transfer), from(from), to(to) { }
		//�������� ��������, ��� ��������� ����� Transfer ����� ������ � private ������ ����������� ������
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
	//Account::Transfer transfer; //����� ������������� ����� ����������
	auto transfer12 = acc1.open_transfer_to(10,acc2); //��� ���������, ��� ������ ������������� �����
	std::cout << "Acc1: " << acc1.check() << '\n' << "Acc2: " << acc2.check() << std::endl;

	transfer12.commit(); //���� ����������� ����������, �� ������ �������, ��� ��� ���� ������ ������, �� ����� ������� ��� public ������

	std::cout << "Acc1: " << acc1.check() << '\n' << "Acc2: " << acc2.check() << std::endl;
}

//���� �� ������� ���������� ��������� ������� - ��� ������
//���������� ��������� ������: ���� ������ ���������, ���������� ���������� ������ � ���� ��������� ��� ����������� �� ���������� ���������� �������� � �������

//!!!�������� �������!!!
class Contacts {
public:
	Contacts& add(std::string const &contact) { contacts.push_back(contact); return *this; }
	std::string get_contact(size_t id) const { return contacts[id]; } //����� �� ������, ��������� ����� �� �������

	std::string& get_contact(size_t id) { return contacts[id]; } //����� �� �����! ����� push_back ������� ������

private:
	std::vector<std::string> contacts;
};

class ProxContacts {
private:
	class proxy_contact {
	public:
		proxy_contact(ProxContacts &contacts, size_t id): contacts(contacts), id(id) { }
		proxy_contact& operator=(std::string const &str) { contacts.contacts[id] = str; return *this; }
		operator std::string() { return contacts.contacts[id]; } //������� �������������� ��� ���������� ������

	private:
		ProxContacts &contacts;
		size_t id;
	};

public:
	Contacts& add(std::string const &contact) { contacts.push_back(contact); }
	std::string get_contact(size_t id) const { return contacts[id]; }

	proxy_contact get_contact(size_t id) { return proxy_contact(*this, id); } //�� ���������� ������, ������� ���������� ������ �������� � ����� ������ ������������� ������

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

	third_contact = first_contact; //�� �������� ���, ������� ��� � ���� ������
	std::cout << first_contact << " : " << third_contact << std::endl; //�� ��������� �������� ��������������
}

int main() {
	if (false) inner_transfer_class_test();
	if (false) proxy_contact_test();

	return 0;
}