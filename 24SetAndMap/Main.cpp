#include <iostream>
#include <string>

//Бинарные деревья можно эффективно использовать для поиска элементов

//Если стоит задача создания множества для того, чтобы проверять в нём наличие элемента, то для этого можно использовать стандартный контейнер set

//задача, выбрать уникальные элементы из двух векторов и сложить в третий
#include <vector>
#include <set>   //сортированное множество

template <typename T>
std::vector<T> unique_elements(std::vector<T> const &lha, std::vector<T> const &rha) {
	std::set<T> unique_set; //set хранит только уникальные элементы, повторное включение игнорируется
	for (auto &element : lha)
		unique_set.insert(element); //insert - добавляет элемен в множество
	for (auto &element : rha)
		unique_set.insert(element);
	return { unique_set.begin(),unique_set.end() }; //конструируем вектор из двух итераторов
}

void unique_elements_test() {
	std::vector<std::string> big_cats = { "Lion","Tiger","Leopard","Panther","Jaguar" };
	std::vector<std::string> animals = { "Wolf","Lion","Tiger","Mouse","Horse" };
	std::vector <std::string> unique_animals = unique_elements(big_cats, animals);
	for (auto &element : unique_animals)
		std::cout << element << ' ';
	std::cout << std::endl;
}

int main() {
	if (false) unique_elements_test();

	return 0;
}