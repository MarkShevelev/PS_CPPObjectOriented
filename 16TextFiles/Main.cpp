#include <iostream> //общие потоки ввода и вывода ostream istream cin cout cerr
#include <fstream>  //потоки для работы с файлами ofstream ifstream fstream
#include <string>   //std::getline
#include <vector>
#include <algorithm>

//в С++ существует свой стандартный способ работы с файлами
//он выражается в работе с объектами классов ofstream ifstream и fstream
//ifstream (input file stream) используется для ввода данных в программу, чтения файла
void open_file_read() {
	std::string filename;
	std::cin >> filename;

	std::ifstream in_file(filename); //пытается открыть файл filename
	if (!in_file.good()) { //если при открытии файла произошла ошибка, то in_file.good() вернёт false
		std::cout << "Can't open file " << filename << std::endl;
		return;
	}

	//прочтём слово из файла, это делается аналогично чтению из стандартного ввода
	std::string word;
	in_file >> word;
	std::cout << word << std::endl; //выводим на экран слово из файла

	//каждое последующее чтение проводит к тому, что мы обращаемся далее в файл, как и стандартном вводе
	std::string next_word;
	in_file >> next_word;
	std::cout << next_word << std::endl;

	in_file.close(); //закрытие файла
	//на самом деле оно может быть произведено автоматически, деструктором объекта in_file
}

//для записи в файл используется специальный класс ofstream (output file stream)
void open_file_write() {
	std::string filename;
	std::cin >> filename;

	std::ofstream out_file(filename);
	if (!out_file.good()) {
		std::cout << "Can't open file " << filename << std::endl;
		return;
	}
	//вывод в файл ни чем не отличается от вывода в стандартный поток
	out_file << "Eva" << '\n' << "Alice" << '\n' << "Bob" << std::flush;

	out_file.close(); //данная операция не является обезательной к вызову явно, она совершается в деструкторе
}

//по умолчанию при записи файл полностью пересоздаётся
//используя дополнительный флаг std::ios::app (append) можно дописывать информацию в файл, оставляя ту, что уже есть целой
void append_file_test() {
	std::string filename;
	std::cin >> filename;

	{
		std::ofstream out_file(filename);
		if (!out_file) { //можно не вызывать .good() явно, все классы ввода/вывода имеют перегруженные операторы привидения к типу bool
			std::cout << "Can't open file " << filename << std::endl;
			return;
		}
		out_file << "Some sentence" << std::endl;
	} //мы знаем, что деструктор закроет файл, нет необходимости вызывать .close() явно

	{
		std::ofstream out_file(filename,std::ios::app); //добавим ещё один параметр - флаг app
		if (!out_file) { 
			std::cout << "Can't open file " << filename << std::endl;
			return;
		}
		out_file << "Another sentence" << std::endl;
	}

	//прочтём содержимое файла
	{
		std::ifstream in_file(filename);
		if (!in_file) {
			std::cout << "Can't open file " << filename << std::endl;
			return;
		}
		std::string line;
		while (std::getline(in_file, line)) //мы можем использовать функцию getline и с файлами тоже
			std::cout << line << std::endl;
		//когда чтение строки из файла будет невозможно, файл закончился
	}
}

//читаем из файл числа в вектор, перезаписываем в отсортированном виде
void vector_file_test() {
	std::vector<int> numbers; //мы не знаем сколько чисел в файле, потому будем добавлять их в вектор, он сам увеличит объём памяти
	std::string filename;
	std::cin >> filename;

	{
		std::ifstream in_file(filename);
		if (!in_file) {
			std::cout << "Error!" << std::endl;
			return;
		}

		do {
			int i;
			in_file >> i;
			if (in_file) //нам может встретиться не число или даже конец файла
				numbers.push_back(i);
		} while (in_file); //как только читать из файла стало невозможно, прекращаем работу цикла

		if (!in_file.eof()) {
			std::cout << "Data have not been read till the end of the file!" << std::endl;
			return;
		}
	}

	//выведем числа на экран
	for (auto num : numbers)
		std::cout << num << ' ';
	std::cout << std::endl;

	//сортируем
	std::sort(numbers.begin(), numbers.end());
	for (auto num : numbers)
		std::cout << num << ' ';
	std::cout << std::endl;

	{
		std::ofstream out_file(filename);
		if (!out_file) {
			std::cout << "Error" << std::endl;
			return;
		}

		for (auto num : numbers)
			out_file << num << ' ';
		out_file << std::endl;
	}
}

int main() {
	if (false) open_file_read();
	if (false) open_file_write();
	if (false) append_file_test();
	if (false) vector_file_test();

	return 0;
}