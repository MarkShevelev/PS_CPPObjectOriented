#include <iostream>
#include <string>
#include <vector>

//���� ������� ���� ������� �����-���� ������� ���������������, �� ������� ��� ����� ���� ���������� "�����������" (dependency)
//����������� ��������, ��� ��������� ������������ ������ ������, ����� �������� �� ������������ ������� ������

//������ �����������
class Account {
public:
	Account(int amount): amount(amount) { }
	void deposit(int some) { amount += some; }
	void withdraw(int some) { amount -= some; }
	int check() const { return amount; }
private:
	int amount;
};

class DependentTransfer {
public:
	DependentTransfer(int sum_to_transfer): sum_to_transfer(sum_to_transfer) { }
	void transfer(Account &from, Account &to) const { from.withdraw(sum_to_transfer); to.deposit(sum_to_transfer); }
private:
	int sum_to_transfer;
};

//������� ������ DependentTransfer ���������� ����������� ������ Account, �������� ��� ������, �� �� �������� �������� ������ Account �� ���������� ������, ����� �������������� ���������� "������������".
//������� ��������, ��� ������ DependentTransfer ������� �� Account, �.�. ��������� � ������� ������ Account ����� �������� � ���������� � ������� ������ DependentTransfer
//��������, ��������, �� �������� ������


//����� ������ ��������� ����� �������� - ��� ��������, ����� ������� ������ ������ �������� � �������� ����� ������� ������� ������. ����� ����������� ���������� �����������.
//�������� ������ ���������� - ���������, ���������� ��������� �� �������
//��� ���������� ����������� �������������� �������, ���������� ����� ���� ������ �� ��������� � ����� �� ����������.
//� ����� ������ ��� ���������� ������, ���������� ��������� �� ������ ������, ����� ������� ��������� ���� �������� � � ���������� ����������� �������
//�������� ��������� ���������� ����� ��������� � ��������� nullptr, �� ���������� ������� ��������

//����� ������ ����� - ��� ���������, � ���� ������ ������ ������ A ����� �� ����� ��������� �������� ��� ������� ������ B

//������� ������ AssociatedTransfer �������� ������ �� ������� ������ Account, ������������� ������� ������ AssociatedTransfer �� ����� ��������� ����� �������� ��� ������ �������� ������ Account
//������ ����� ����� �������� from � to �� ��������������� ��������� ������ AssociatedTransfer, ������ �� ���� � �� �� ������� ����� ���� �������� ������ �������� ������ AssociatedTransfer ��� �������� ������ �������, ������ ���� ������ ������ AssociatedTransfer ��������, ������� Account ��������� ������������
//��� � ���� ���������
class AssociatedTransfer {
public:
	AssociatedTransfer(int sum_to_transfer, Account &from, Account &to) : sum_to_transfer(sum_to_transfer), from(from), to(to) { }
	void transfer() const { from.withdraw(sum_to_transfer); to.deposit(sum_to_transfer); }
private:
	int sum_to_transfer;
	Account &from, &to;
};

//��������� � ���������� - ��� ��� ���������, ������� ����� �������� ����� �����-�����
//� ������� ���� Account - ��� ����� AssociatedTransfer
//������ ���������� �������� ����� ������� ����������
//��� ���������� ����� ������� �� ������ � ����������� ������ ������ �������, ������������� ��������

//� ��������� ������� ����� Employee ������� �� ������ std::string � ������ � ��� � ��������� ���������
class Employee {
public:
	Employee(std::string const &name): name(name) { }

	bool am_i(std::string const &oth) const { return name == oth; }

private:
	std::string const name;
};

//�������������, Employee ������� �� std::string, ���� ��������� ��������� ��������� ==, �� ������� ������ � ����� Employee
//� ��������� � ������� DependentAccount Employee ��������� � ����� ������ ����� � ������� std::string, ��� ��� �������� ��� �� ���������� ������, �.�. ����� � ����� ������, �� ������ � ������ am_i, ���������� � ������� ����� ������
//������ ��������� ����� ������, ��� ������� ����������, �.�. ������� Employee �� ����� �������������� ��� �������� std::string, ����� am_i ������� �� ��������������
//��� ��� ������� Employee �������� ������� std::string � �������� ��������, � �� ������, �� ���, ��������, ������� �� ��������� � ������������ ����� ����� - ��� ������ ���� ������ Employee, �� ����� � ����� ������ std::string
//����� ��������� �� � �������� �����������

//���������, � ����� ��������� ������ PrintableEmployee ������ � ������� std::ostream&
class PrintableEmployee {
public:
	PrintableEmployee(std::string const &name) : name(name) { }

	bool am_i(std::string const &oth) const { return name == oth; }
	void print(std::ostream &out) const { out << "I am " << name; } //???

private:
	std::string const name;
};

//� ����� �������� ������ ����� PaidEmployee � ������� Account?
class PaidEmployee {
public:
	PaidEmployee(std::string const &name) : name(name), account(0) { }

	bool am_i(std::string const &oth) const { return name == oth; }
	void print(std::ostream &out) const { out << name << " paid " << account.check(); }

	void salary_inflow(int amount) { account.deposit(amount); }
	void salary_penalty(int amount) { account.withdraw(amount); }

private:
	std::string const name;
	Account account;
};

//� ����� ��������� ������ ����� Department c ������� Employee � � ������� Account?
class Department {
public:
	Department(std::string const &name): name(name) { }

	void salary_month(int amount) const {
		for (auto emplolyee_ptr : employees)
			emplolyee_ptr->salary_inflow(amount);
	}

private:
	std::string const name;
	std::vector<PaidEmployee*> employees;
};



