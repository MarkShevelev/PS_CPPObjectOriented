#include <iostream>
#include <string>

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

int main() {
	if (false) inner_transfer_class_test();

	return 0;
}