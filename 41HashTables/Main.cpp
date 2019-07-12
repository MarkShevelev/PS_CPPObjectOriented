#include <iostream>
#include <string>

//Для создания набора уникальных значений
//Мы успешно использовали std::set
//Однако std::set обладает определёнными недостатками
//i)    в std::set можно помещать только такие объекты, для которых определён порядок, т.е. требует перегрузки оператора <, причём          таким образом, чтобы для любых O1 и O2 выполнялось: O1 < O2 => !(O2 < O1) и !(O1 < O2) && !(O2 < O1) => O1 == O2
//ii)   в std::set объекты добавляются в дерево, сложность такого добавления составляет log(N), где N - число элементов в дереве
//      для добавления K элементов в std::set нам потребуется K*log(K) действий, т.е. столько же, сколько при сортировке

//В некоторых ситуациях это может быть важно, например если мы хотим искаль элементы в диапазоне значений
//Если такой задачи не стоит или элементы принципиально сложно (невозможно) сравнить друг с другом, то хотелось бы отказаться от std::set в пользу чего-либо более быстрого
//Именно таким решением является "хеш-таблица"
//хеш-таблица хранит элементы по принципу сопоставления каждому объекту определённого значения, которое называется хешем и однозначно идентифицирует ячейку в таблице
//сопоставление объекту значения производится с помощью хеш-функции

//хранение элементов в множестве по принципу хеш-таблицы представлено шаблоном std::unordered_set

#include <unordered_set>
void unordered_set_test() {
	using namespace std;
	unordered_set<int> set_of_integers;
	for (int counter = 0; counter != 10; ++counter) {
		int user_input;
		cin >> user_input;
		set_of_integers.insert(user_input);
	}

	for (auto i : set_of_integers)
		cout << i << ' ';
	cout << endl;
}

//в отличие от std::set std::unordered_set не предоставляет никакой гарантии на порядок элементов при обходе
void unordered_set_of_strings() {
	using namespace std;
	unordered_set<string> set_of_strings;
	for (int counter = 0; counter != 5; ++counter) {
		string user_input;
		cin >> user_input;
		set_of_strings.insert(user_input);
	}
	cout << "-----------------------" << endl;
	for (auto i : set_of_strings)
		cout << i << '\n';
	cout << endl;
}

//для того, чтобы использовать в std::set собственные классы, нам было необходимо перегружать оператор <
//для того, чтобы использовать в std::unordered_set собственые классы, нам необходимо перегружать оператор == и создать специальную хеш-функцию

//пример
struct InRagnePredicateHasher;

class InRangePredicate final {
public:
	InRangePredicate(int min, int max): min(min), max(max) { }
	bool operator()(int x) const { return x >= min && x <= max; }

	//перегруженный оператор сравнения на совпадение
	bool operator==(InRangePredicate const &oth) const { return min == oth.min && max == oth.max; }

	friend std::ostream& operator<<(std::ostream &os, InRangePredicate const &p);
	friend InRagnePredicateHasher;

private:
	int const min, max;
};

std::ostream& operator<<(std::ostream &os, InRangePredicate const &p) {
	return os << "[" << p.min << "," << p.max << "]";
}

//класс, который представляет собой процесс хеширования, определения значения по данным объекта
struct InRagnePredicateHasher final {
	int operator()(InRangePredicate const &p) const { return p.min << 5 ^ p.max; }
};

void inrangepredicate_unordered_set() {
	using namespace std;
	unordered_set<InRangePredicate, InRagnePredicateHasher> predicate_set;
	for (int counter = 0; counter != 5; ++counter) {
		int user_min, user_max;
		cin >> user_min >> user_max;
		auto done = predicate_set.insert(InRangePredicate(user_min, user_max));
		cout << (done.second ? "Inserted new range: " : "Range already exists: ") << *done.first << endl;
	}

	cout << "-------------------------" << endl;
	for (auto const &p : predicate_set)
		cout << p << '\n';
	cout << endl;
}


int main() {
	if (false) unordered_set_test();
	if (false) unordered_set_of_strings();
	if (false) inrangepredicate_unordered_set();

	return 0;
}