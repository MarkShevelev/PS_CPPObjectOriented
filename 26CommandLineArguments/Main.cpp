#include <iostream>
#include <string>

//Функция main может принимать при запуске программы аргументы, которые сообщаются через командную строку
//аргументы функции main - это всегда строки, наборы символов, они вводятся при вызове программы
//каждый набор символов без пробелов - это один аргумент
//аргументы разделены пробелами
/*int main(
	int argc //количество аргументов
	, char **argv //значения аргументов
) {
	if (0 < argc) std::cout << argv[0] << std::endl; //аргумент с индексом 0 - это путь, по которому запущена программа
	for (int i = 1; i < argc; ++i)
		std::cout << i << ": " << argv[i] << std::endl;

	return 0;
}*/

/*int main(int argc, char **argv) {
	if (3 >= argc) { std::cout << "Not enough arguments!" << std::endl; return 0; }
	std::string operation, lha, rha;
	operation = argv[1];
	lha = argv[2];
	rha = argv[3];

	int i_lha = std::stoi(lha), i_rha = std::stoi(rha);
	if ("sum" == operation) {
		std::cout << (i_lha + i_rha) << std::endl;
	} else if ("sub" == operation) {
		std::cout << (i_lha - i_rha) << std::endl;
	} else {
		std::cout << "Unknown command!" << std::endl;
	}
	
	return 0;
}*/
