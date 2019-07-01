#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

//Мы уже рассматривали шаблонные функции из заголовка algorithm
//Они позволяют проводить операции с контейнерами C++, используя функции и объекты с перегруженным оператором operator()

//Рассмотрим задачу о заполнении вектора случайными числами в промежутке
int random_in_range(int min, int max) {
	using namespace std;
	std::default_random_engine eng;
	return uniform_int_distribution<int>(min, max)(eng);
}

//Функция random_in_range обладает рядом недостатков
//i) её нельзя использовать в алгоритмах типа generate, которые ожидают функцию, не принимающую параметры
//ii) при многократном использовании функции возникают дополнительные накладные расходы на создание объектов std::default_random_engine и std::uniform_int_distribution

//Мы можем решить эту проблему, используя класс
class RandomInRange final {
public:
	RandomInRange(int min, int max): distribution(min,max) { }
	int operator()() const { return distribution(engine); }

private:
	mutable std::default_random_engine engine;
	std::uniform_int_distribution<int> distribution;
};
//класс позволяет нам "захватить дополнительные данные" в полях объекта и описать только необходимый интерфейс - пустые круглые скобки, что позволяет использовать объекты класса в алгоритме generate
//после создания объекта внутренние данные std::default_random_engin и std::uniform_int_distribution сохраняются и переиспользуются при вызовах оператора круглых скобок, что снижает накладные расходы

//Функция для вывода целых чисел на экран
template<typename T>
void print(T x) { std::cout << x << ' '; }

void random_in_range_class_test() {
	using namespace std;

	int min, max;
	std::cin >> min >> max;
	vector<int> numbers(20);
	generate(numbers.begin(), numbers.end(), RandomInRange(min, max));
	for_each(numbers.begin(), numbers.end(), print<int>);
	std::cout << std::endl;

	sort(numbers.begin(), numbers.end());
	for_each(numbers.begin(), numbers.end(), print<int>);
	std::cout << std::endl;
}

//Однако описанный подход по-прежнему неудобен, т.к. приходится описывать класс RandomInRange, который используется только один раз
//Именно для таких случаев в C++ предусмотрен специальный синтаксис, который позволяет определить объект прямо в том месте, где он используется

void random_in_range_lambda_test() {
	using namespace std;

	
	vector<int> numbers(20);
	{
		int min, max;
		std::cin >> min >> max;
		default_random_engine engine;
		uniform_int_distribution<int> distribution(min,max);
		generate(numbers.begin(), numbers.end(), 
			[&engine,&distribution]() {	return distribution(engine); } //объявление объекта с перегруженным оператором () с помощью лямбда-выражения
		);
	}


	for_each(numbers.begin(), numbers.end(), 
		[](int x) { std::cout << x << ' '; } //объявление объекта с перегруженным оператором () с помощью лямбда-выражения
	);
	std::cout << std::endl;

	sort(numbers.begin(), numbers.end());
	for_each(numbers.begin(), numbers.end(), 
		[](int x) { std::cout << x << ' '; } //объявление объекта с перегруженным оператором () с помощью лямбда-выражения
	);
	std::cout << std::endl;
}

int main() {
	if (false) random_in_range_class_test();
	if (false) random_in_range_lambda_test();

	return 0;
}