#include <iostream>
#include <string>

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

int main() {
	if (false) inner_transfer_class_test();

	return 0;
}