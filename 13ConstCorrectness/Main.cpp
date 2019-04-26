#include <iostream>

//определим простой класс Date 
class Date {
	int year, month, day;
public:
	Date(int year, int month, int day) {
		Date::year = year;
		Date::month = month;
		Date::day = day;
	}

	Date next() {
		int day_next = (day + 1)%31;
		int month_next = (month + (day + 1) / 31) % 12;
		int year_next = year + (month + 1 + (day + 1) / 31) / 12;
		return { year,month,day };
	}

	void print() {
		std::cout << day << "." << month << "." << year;
	}
};

//предположим, что я хочу печатать объект типа Date, в том числе и неизменяемые, но без копирования
void print_date(Date const &d) {
	//d.print(); //ошбика компиляции! Невозможно вызывать метод print
	std::cout << std::endl;
}

class ConstCorrectDate {
	int year, month, day;
public:
	ConstCorrectDate(int year, int month, int day) {
		ConstCorrectDate::year = year;
		ConstCorrectDate::month = month;
		ConstCorrectDate::day = day;
	}

	ConstCorrectDate next() const {
		int day_next = (day + 1) % 31;
		int month_next = (month + (day + 1) / 31) % 12;
		int year_next = year + (month + 1 + (day + 1) / 31) / 12;
		return { year,month,day };
	}

	void print() const { //ключевое слово const в объявлении метода показывает компилятору, что этот метод допустим для вызова на неизменяемых объектах
		std::cout << day << "." << month << "." << year;
	}
};

void print_date(ConstCorrectDate const &d) {
	d.print(); //успешно работает!
	std::cout << std::endl;
}

int main() {
	ConstCorrectDate const d(2019, 4, 20);
	print_date(d);
	print_date(ConstCorrectDate{ 2019,5,1 });

	return 0;
}