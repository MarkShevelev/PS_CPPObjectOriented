#include <iostream>
#include <string>

//Для того, чтобы легче выводить данные в потоки (в консоль или в файл) в C++ есть специальный механизм:
//перегрузка операторов ввода/вывода

//Создадим простую структуру
struct SimpleSegment {
	int begin, end;
};

void simple_segment_test() {
	SimpleSegment ss{ 0,10 };
	//std::cout << ss << std::endl; //код не компилируется! компилятор не знает, что именно следует сделать
	//мы можем выводить в консоль данные с использованием декомпозиции
	std::cout << "SimpleSegment ss = (" << ss.begin << "," << ss.end << ")" << std::endl;
}

//если структура достаточно большая и содержит много данных, то постоянно повторять сложный код,
//выводящий на экран отдельные элементы структуры - сложная задача

//можно создать простую функцию, которая печатает данные
void print_simple_segment(SimpleSegment const &ss) {
	std::cout << "(" << ss.begin << "," << ss.end << ")";
}

//мы сможем использовать функцию print_simple_segment, но не сможем использовать преимущества беглого вывода
void print_simple_segment_test() {
	SimpleSegment a{ 0, 1 };
	SimpleSegment b{ 1, 0 };
	std::cout << "SimpleSegment a: "; print_simple_segment(a); std::cout << std::endl;
	std::cout << "SimpleSegment b: "; print_simple_segment(b); std::cout << std::endl;
}

//Чтобы эффективно использовать вывод можно перегрузить оператор <<
//Для этого существует специальный синтаксис
//std::ostream& operator<<(std::ostream&,<ссылка на объект>);

//создадим ещё одну простую структуру и перегрузим оператор вывода
struct OutputSegment {
	int begin, end;
};
//обратите внимание, что используемый тип std::ostream - это общий тип для всех потоков вывода
std::ostream& operator<<(std::ostream &os, OutputSegment const &s) {
	os << "(" << s.begin << "," << s.end << ")";
	return os;
}

//теперь при попытки вызвать операцию вывода с OutputSegment компилятор будет подставлять код функции выше
void output_operator_test() {
	OutputSegment a{ 0,1 };
	OutputSegment b{ 1,0 };
	std::cout << "OutputSegment a: " << a << std::endl << "OutputSegment b: " << b << std::endl;
}

//перегрузить можно и оператор ввода
std::istream& operator>>(std::istream &is, OutputSegment &s) {
	is >> s.begin >> s.end;
	return is;
}

void input_operator_test() {
	OutputSegment a,b;
	std::cin >> a >> b;
	std::cout << "Segment a: " << a << std::endl << "Segment b: " << b << std::endl;
}

//Мы знаем, что в классах принято прятать внутренние данные, например в классе Segment
class Segment {
public:
	Segment(): begin(0), end(0) { }
	Segment(int begin, int end) : begin(begin), end(end) { }

	bool contains(int point) const { return point >= begin && point <= end; }
	int length() { return begin >= end ? 0 : (end - begin); }

private:
	int begin, end;
};

//если мы хотим вывести на экран или считать с консоли данные объекта типа Segment, то нам понадобится способ обратиться к внутренним данным
//разместить оператор внутри класса (создать метод) возможно, но в этом случае мы потеряем привычную семантику 
class IOSegment {
public:
	IOSegment() : begin(0), end(0) { }
	IOSegment(int begin, int end) : begin(begin), end(end) { }

	bool contains(int point) const { return point >= begin && point <= end; }
	int length() { return begin >= end ? 0 : (end - begin); }

	//мы можем объявить оператор дружественным
	friend std::ostream& operator<<(std::ostream &os, IOSegment const &s);
	friend std::istream& operator>>(std::istream &is, IOSegment &s);

private:
	int begin, end;
};

std::ostream& operator<<(std::ostream &os, IOSegment const &s) {
	return os << "(" << s.begin << "," << s.end << ")";
}

std::istream& operator>>(std::istream &is, IOSegment &s) {
	return is >> s.begin >> s.end;
}

void friend_operators_test() {
	IOSegment a, b;
	std::cin >> a >> b;
	std::cout << "Segment a: " << a << std::endl << "Segment b: " << b << std::endl;
}

int main() {
	if (false) simple_segment_test();
	if (false) print_simple_segment_test();
	if (false) output_operator_test();
	if (false) input_operator_test();
	if (false) friend_operators_test();
}