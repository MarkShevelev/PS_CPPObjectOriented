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
	cin >> min >> max;
	vector<int> numbers(20);
	generate(numbers.begin(), numbers.end(), RandomInRange(min, max));
	for_each(numbers.begin(), numbers.end(), print<int>);
	cout << endl;

	sort(numbers.begin(), numbers.end());
	for_each(numbers.begin(), numbers.end(), print<int>);
	cout << endl;
}

//Однако описанный подход по-прежнему неудобен, т.к. приходится описывать класс RandomInRange, который используется только один раз
//Именно для таких случаев в C++ предусмотрен специальный синтаксис, который позволяет определить объект прямо в том месте, где он используется

void random_in_range_lambda_test() {
	using namespace std;

	
	vector<int> numbers(20);
	{
		int min, max;
		cin >> min >> max;
		default_random_engine engine;
		uniform_int_distribution<int> distribution(min,max);
		generate(numbers.begin(), numbers.end(), 
			[&engine,&distribution] {	return distribution(engine); } //объявление объекта с перегруженным оператором () с помощью лямбда-выражения
		);
	}


	for_each(numbers.begin(), numbers.end(), 
		[](int x) { cout << x << ' '; } //объявление объекта с перегруженным оператором () с помощью лямбда-выражения
	);
	std::cout << std::endl;

	sort(numbers.begin(), numbers.end());
	for_each(numbers.begin(), numbers.end(), 
		[](int x) { cout << x << ' '; } //объявление объекта с перегруженным оператором () с помощью лямбда-выражения
	);
	cout << endl;
}

//лямбда выражения определяются конструкцией, состоящей из трёх пар скобок [](){}
//[ ] - определяют список локальных переменных, которые помещаются во внутренние данные лямбда выражения
//( ) - определяют список аргументов, которые при вызове следует передать в круглые скобки
//{ } - определяет тело оператора ()
//между скобками могут быть дополнительные квалификации
//[] () mutable throw() -> int { }
//mutable позволяет изменить данные в теле, throw() - квалифицирует возможные исключения, -> int - указывает возвращаемый тип
//квалификаторы, включая возвращаемый тип, не являются обязательными

//Рассмотрим различные варианты "захвата" данных

//захват всех данных копированием и по ссылке
//задача подсчитать все числа, удовлетворяющие условию
void capture_by_copy_and_reference() { 
	using namespace std;
	vector<int> numbers = { 1,2,3,-2,-3,0,4 };
	for (auto i : numbers)
		cout << i << ' ';
	cout << endl;

	{//ничего не захватываем для подсчёта положительных чисел
		cout << "count positive is " << count_if(numbers.begin(), numbers.end(), [](int x) { return x > 0; }) << endl;
	}

	{//подсчёт чисел в промежутке, необходимо захватить пару чисел
		int min, max;
		cin >> min >> max;
		//мы можем не указывать явно, какие данные захватываем, а использовать специальный синтаксис [=]
		//при этом будут захвачены копированием все упомянутые переменные
		cout << "count in (" << min << "," << max << ") is " << count_if(numbers.begin(), numbers.end(), [=](int x) { return x > min && x < max; }) << endl;
	}

	{//при захвате по ссылке, мы можем менять данные, которые находятся вне лямбда выражения
		int p = 0;
		//для захвата всех упомянутых переменных используется синтаксис [&]
		for_each(numbers.begin(), numbers.end(), [&](int x) { cout << ++p << ' '; } );
		cout << '\n' << p << endl;
	}
}

//захват this
//в лямбда выражение нельзя захватить внутренние данные объекта, но можно захватить указатель на объект (this)
class CaptureTest final {
public:
	CaptureTest(size_t count_numbers, int min , int max) : numbers(count_numbers), min(min), max(max) {
		int p = 0;
		//p - локальные данные, их можно захватывать синтаксисом [&p]
		std::generate(numbers.begin(), numbers.end(), [&p] { return p++; }); //если входящих данных нет, то можно опустить ()
	}

	void print() const {
		std::for_each(numbers.begin(), numbers.end(), [](int x) { std::cout << x << ' '; }); //глобальные объекты специально захватывать не нужно
		std::cout << std::endl;
	}

	int count_in_range() const {
		//захватить min и max нельзя, т.к. они не являются локальными переменными
		//return count_if(numbers.begin(), numbers.end(), [min,max](int x) { return x > min && x < max; });
		
		//такой синтаксис работает! захвачен указатель на объект
		return count_if(numbers.begin(), numbers.end(), [this](int x) { return x > min && x < max; });
	}

	
private:
	std::vector<int> numbers;
	int const min, max;
};

void this_capture_test() {
	CaptureTest ct(20, -10, 10);
	ct.print();
	std::cout << ct.count_in_range() << std::endl;
}


int main() {
	if (false) random_in_range_class_test();
	if (false) random_in_range_lambda_test();
	if (false) capture_by_copy_and_reference();
	if (false) this_capture_test();

	return 0;
}