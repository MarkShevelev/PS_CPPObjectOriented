#include <iostream>
#include <string>

//работа со строками языка Си очень сложна и требует крайней аккуратности
//во многом из-за того, что требует работы с памятью вручную
//С++ решает эту проблему за счёт ООП и деструкторов
void construct_string() {
	std::string s1; //пустая строка
	std::string s2('a', 10); //строка длиной 10, заполненная символом 'a'
	std::string s3("Hello World!"); //создание строки С++ из массива символов, завершаемого нулём
	std::string s4(s3); //копия строки s3

	//каждое создание строки требует динамической памяти,
	//при выходе строки из области видимости память будет освобождена деструктором

	//строки устроены таким образом, что могут быть выведены на экран через оператор вывода
	std::cout << "s1: " << s1 << "\ns2: " << s2 << "\ns3: " << s3 << "\ns4: " << s4 << std::endl;

	//как и массивы символов, строки можно заполнять с клавиатуры
	std::string in;
	std::cin >> in;
	std::cout << "in: " << in;

	//метод get объекта std::cin позволяет читать данные в массив-буфер
	char buff[100];
	std::cin.get(buff, 100, '\n');//прочесть не более 99 символов до '\n' (перевода строки)

	//функция std::getline читает данные в стандартную строку std::string
	std::string in2;
	std::getline(std::cin, in2, '\n'); //чтение данных в стандартную строку
	//количество необходимой памяти определяется автоматически
}

//доступ к элементам строки, символам
void accessing_string() {
	std::string s("Hello String!");

	//доступ к элементам строки осуществляется методами at и []
	for (std::string::size_type pos = 0; pos != s.size(); ++pos)
		std::cout << s[pos] << "  " << s.at(pos) << std::endl;
	//разница между [] и .at состоит в том, что .at производит проверку выхода за пределы массива данных

	//есть возможность получить доступ к первому и последнему символам
	std::cout << s.front() << "<...>" << s.back() << std::endl;

	//при необходимости можно получить доступ к массиву внутренних данных
	//s.data()[1] = 'h';//С++ 17
	std::cout << s.c_str() << std::endl;
}

//строки можно сравнивать на точное совпадение между собой
void compare_string() {
	std::string s1("Abba");
	std::string s2("Bbba");

	std::cout << std::boolalpha << (s1 == s2) << " " << (s1 > s2) << " " << (s1 < s2) << std::endl;

	//можно использовать метод compare, который ведёт сяебя идентично функции strcmp из языка Си
	std::string user_input;
	std::cin >> user_input;
	if (0 == user_input.compare(s1))
		std::cout << "Yes" << std::endl;
	else
		std::cout << "No" << std::endl;
}

//строки можно модифицировать
void modification_string() {
	std::string a, b;
	std::cin >> a >> b;

	//строки можно соединять вместе и использованием оператора +, который создаёт новую строку
	std::string sum = a + b;
	std::cout << "a+b: " << sum << std::endl;

	//можно добавлять данные к уже существующей строке
	std::string c;
	std::cin >> c;
	c += a;
	std::cout << "c + a: " << c << std::endl;
	c.append(b);
	std::cout << "c + a + b: " << c << std::endl;

	//к строке можно добавлять отдельные символы в конец
	std::cout << a << " ";
	a.push_back('#');
	std::cout << a << " ";

	//и извлекать последний символ
	a.pop_back();
	std::cout << a << std::endl;

	//вставка строк в середину
	a.insert(2, b);
	std::cout << "a insert b: " << a << std::endl;
}

//replace
void replace_string() {
	std::string str = "Hello World!";
	str.replace(6, 5, "Replace");
	std::cout << str << std::endl;
}

//substring
void substring_string() {
	std::string str = "Hello World!";
	std::cout << str.substr(6) << std::endl;
	std::cout << str.substr(0, 5) << std::endl;
}

int main() {
	if (false) construct_string();
	if (false) accessing_string();
	if (false) compare_string();
	if (false) modification_string();
	if (false) replace_string();
	if (false) substring_string();

	return 0;
}