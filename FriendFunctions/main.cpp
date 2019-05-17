#include <iostream>
#include <algorithm>

//ƒружественные функции - это функции, которым разрешЄн доступ к внутренним данным объекта

class Segment {
public:
	Segment(int begin, int end): begin(begin), end(end) { }

	bool contains(int point) const { return point >= begin && point <= end;	}
	int length() { return begin >= end ? 0 : (end - begin); }
	//объ€вл€ем функцию intersect дружественной с помощью ключевого слова friend
	friend Segment intercect(Segment const &lha, Segment const &rha);

private:
	int begin, end;
};

//данна€ функци€ свободно может получить доступ к внутренним данным объектов класса Segment
Segment intercect(Segment const &lha, Segment const &rha) {
	return Segment(std::max(lha.begin, rha.begin), std::min(lha.end, rha.end));
}

void intersect_test() {
	Segment a(-1, 3);
	Segment b(2, 4);
	std::cout << a.length() << " " << b.length() << " " << intercect(a, b).length() << std::endl;
}

int main() {
	if (false) intersect_test();

	return 0;
}