#include <iostream>
#include <string>
#include <vector>

//Если объекты двух классов каким-либо образом взаимодействуют, то говорят что между ними существует "зависимость" (dependency)
//Зависимость означает, что изменения спецификации одного класса, могут повлиять на спецификацию другого класса

//Пример зависимости
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

//Объекты класса DependentTransfer используют возможности класса Account, вызывают его методы, но не содержат объектов класса Account во внутренних данных, такое взаимодействие называется "зависимостью".
//Обратим внимание, что именно DependentTransfer зависит от Account, т.к. изменение в методах класса Account могут привести к изменениям в методах класса DependentTransfer
//Обратное, очевидно, не является верным


//Более тесные отношения между классами - это ситуации, когда объекты одного класса содержат в качестве полей объекты другого класса. Такая зависимость называется ассоциацией.
//Типичный пример ассоциации - контейнер, содержащий указатели на объекты
//При выполнении определённых дополнительных условий, ассоциация может быть сужена до агрегации и далее до композиции.
//В общем случае при ассоциации объект, содержащий указатель на другой объект, может успешно выполнять свои действия и в отсутствие включаемого объекта
//Например контейнер указателей может содержать в указателе nullptr, но продолжать успешно работать

//Более тесная связь - это агрегация, в этом случае объект класса A никак не может выполнять действий без объекта класса B

//Объекты класса AssociatedTransfer содержат ссылки на объекты класса Account, следовательно объекты класса AssociatedTransfer не могут выполнять своих действий без верных объектов класса Account
//Однако время жизни объектов from и to не контроллируется объектами класса AssociatedTransfer, сслыки на одни и те же объекты могли быть переданы разным объектам класса AssociatedTransfer или объектам других классов, причём если объект класса AssociatedTransfer погибнет, объекты Account продолжат существовать
//Это и есть агрегация
class AssociatedTransfer {
public:
	AssociatedTransfer(int sum_to_transfer, Account &from, Account &to) : sum_to_transfer(sum_to_transfer), from(from), to(to) { }
	void transfer() const { from.withdraw(sum_to_transfer); to.deposit(sum_to_transfer); }
private:
	int sum_to_transfer;
	Account &from, &to;
};

//Агрегация и композиция - это два отношения, которые можно выразить парой часть-целое
//В примере выше Account - это часть AssociatedTransfer
//Однако композиция является более строгим отношением
//При композиции часть зависит от целого и принадлежит только одному объекту, исключительое владение

//В следующем примере класс Employee зависит от класса std::string и входит с ним в отношение композции
class Employee {
public:
	Employee(std::string const &name): name(name) { }

	bool am_i(std::string const &oth) const { return name == oth; }

private:
	std::string const name;
};

//Действительно, Employee зависит от std::string, если изменится поведение оператора ==, то придётся менять и класс Employee
//В сравнении с классов DependentAccount Employee находится в более тесной связи с классом std::string, так как содержит его во внутренних данных, т.е. может в любой момент, не только в методе am_i, обратиться к методам этого класса
//Данные отношения более тесные, чем простая ассоциация, т.к. объекты Employee не могут использоваться без объектов std::string, метод am_i работал бы непредсказуемо
//Так как объекты Employee содержат объекты std::string в качестве значения, а не ссылки, то они, очевидно, владеют им уникально и контроллирую время жизни - как только умрёт объект Employee, он унесёт с собой объект std::string
//Такое отношение мы и называет композицией

//Подумайте, в какое отношение объект PrintableEmployee входит с классом std::ostream&
class PrintableEmployee {
public:
	PrintableEmployee(std::string const &name) : name(name) { }

	bool am_i(std::string const &oth) const { return name == oth; }
	void print(std::ostream &out) const { out << "I am " << name; } //???

private:
	std::string const name;
};

//В какое оношение входит класс PaidEmployee с классом Account?
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

//В какое отношение входит класс Department c классом Employee и с классом Account?
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



