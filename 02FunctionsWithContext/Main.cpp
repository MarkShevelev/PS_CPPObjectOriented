#include <iostream>
#include <algorithm>
#include <cstdlib>

void print_int(int x) {
	std::cout << x << " ";
}

//хотя полиморфные алгоритмы и дают серьёзное преимущество при создании кода,
//существует ряд сложностей при их использовании в классическом процедурном программировании

//рассмотрим задачу о заполнении массива значениями

//заполняем конкретным числом, используя алгоритм std::generate
int zero() {
	return 0;
}

void zerofill_array_test() {
	int arr[10];
	std::generate(arr, arr + 10, zero); //std::generate принимает промежуток адресов и указатель на функцию
	std::for_each(arr, arr + 10, print_int);
	std::cout << std::endl;
}

//мы могли бы заполнять любым числом, если создадим функцию, которая возвращает нужное значение
int unity() {
	return 1;
}

void unityfill_array_test() {
	int arr[10];
	std::generate(arr, arr + 10, unity);
	std::for_each(arr, arr + 10, print_int);
	std::cout << std::endl;
}

//однако мы не можем заполнить произвольным числом массив, точнее таким, которое не известно на этапе компиляции
//следующий код не компилируется
int any_number(int x) {
	return x;
}

void anyfill_array_test() {
	std::cout << "Enter to number to fill: " << std::endl;
	int user_fill;
	std::cin >> user_fill;
	
	int arr[10];

	//???
	//std::generate(arr, arr + 10, any_number); //здесь возникнет ошибка компиляции
	//проблема в том, что std::generate умеет вызывать только функции без параметров
	//если в функцию нужно передать параметр, то std::generate не знает откуда его взять
	//мы не знаем, куда его передать...

	std::for_each(arr, arr + 10, print_int);
	std::cout << std::endl;
}

//мы приходим к противоречивой ситуации:
//функция оперирует данными x, но не должна получать их через параметр
/*
int any_number() {
	return x;
}
*/
//x - данные неизвестного источника, нужно указать, откуда их взять
//в чистом Си единственный способ - глобальная область видимости

int global_x;
int any_number_global() {
	return global_x;
}

void anyfill_global_array_test() {
	std::cout << "Enter to number to fill: " << std::endl;
	int user_fill;
	std::cin >> user_fill;

	int arr[10];
	//устанавливаем глобальный параметр
	global_x = user_fill;
	std::generate(arr, arr + 10, any_number_global); //std::generate вызывает функцию без параметров, а уже функция достаёт значение из глобального пространства
	std::for_each(arr, arr + 10, print_int);
	std::cout << std::endl;
}

//процесс сопоставления данных свободной переменной называют "замыканием"
//функцию, которая получает данные откуда-то ещё, кроме входящих параметров, например, из глобального пространства, называют "функция с окружением" или "функция с контекстом"
//то место, откуда приходят данные в свободные переменные называют "контекстом" или "окружением": локальный контекст, глобальный контекст и т.д.

//работа с полиморфными алгоритмами и контекстом возможна и в языке Си, хотя крайне неудобна

//определим функцию, которая будет при каждом следующем вызове возвращать следующий член арифметической прогрессии
/*
int arithm() {
	int tmp = c;
	c += d;
	return tmp;
}
*/
//эта функция содержит две свободные переменные c и d, текущее значение и разность прогрессии
//определим структуру, которая будет содержать эти данные
struct ArithmContext {
	int c, d;
};

//перепишем функцию так, чтобы она принимала адрес контекста
int arithm(void *address) {//никто не должен знать, как устроен контекст! (Инкапсуляция)
	ArithmContext *context = (ArithmContext*)address;
	int tmp = context->c;
	context->c += context->d;
	return tmp;
}

//создадим свой алгоритм generate, который будет знать, что функция ожидает контекст
//my_generate не знает ничего о контексте generator (Инкапсуляция), но знает где он находится и куда его передать
void my_generate(int *begin, int *end, int(*generator)(void*), void *generator_context) {
	while (begin != end) {
		*begin++ = generator(generator_context);//при вызове функции алгоритм передаёт контекст в generator
	}
}

void generate_with_context_test() {
	std::cout << "Enter the first element of the progression and the difference: " << std::endl;
	int user_a, user_d;
	std::cin >> user_a >> user_d;

	int arr[10];

	//создаём контекст
	ArithmContext context = { user_a,user_d }; //мы знаем, какой контекст нам нужен, а my_generate - нет :)
	my_generate(arr, arr + 10, arithm, &context); //вызываем my_generate с контектом
	std::for_each(arr, arr + 10, print_int);
	std::cout << std::endl;
}

//создание функции генерации случайных чисел в диапазоне
//генерация случайных чисел в заданном диапазоне требует пары свободных переменных
/*
int rand_in_range() {
	return rand()%(max-min+1) + min;
}
*/
//max и min - свободные переменные
//создаём окружение
struct RangeContext {
	int min, max;
};

//функция, ожидающая контекст
int rand_in_range(void *address) {
	RangeContext *context = (RangeContext*)address;
	return rand() % (context->max - context->min + 1) + context->min;
}

void rand_in_range_test() {
	std::cout << "Enter the range min max: " << std::endl;
	int min, max;
	std::cin >> min >> max;

	int arr[10];

	srand(1023);

	//создаём контекст
	RangeContext context = { min, max }; //мы знаем, какой контекст нам нужен, а my_generate - нет :)
	my_generate(arr, arr + 10, rand_in_range, &context); //вызываем my_generate с контектом
	std::for_each(arr, arr + 10, print_int);
	std::cout << std::endl;
}


int main() {
	if (false) zerofill_array_test();
	if (false) unityfill_array_test();
	//if (false) anyfill_array_test(); //эта функция содержит преднамеренную ошибку компиляции!!!
	if (false) anyfill_global_array_test();
	if (false) generate_with_context_test();
	if (false) rand_in_range_test();

	return 0;
}