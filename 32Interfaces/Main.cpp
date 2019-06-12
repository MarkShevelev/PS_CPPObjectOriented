#include <iostream>
#include <string>

//Рассмотрим следующую задачу: написать программу с коммандным интерфейсом
//комманда exit - выход из программы
//комманды add mul и sub - запрашивают пару чисел и выводят сумму, произведение или разность, соответственно
//комманда div запрашивет два числа и либо печатает целую часть от деления, либо сообщает, что производится деление на ноль

//ранее мы бы решали эту задачу так:

void arithmetic() {
	bool proceed = true;
	while (proceed) {
		std::string command;
		std::cin >> command;

		if ("exit" == command) { proceed = false; continue; }
		if ("add" == command) {
			int a, b;
			std::cin >> a >> b;
			std::cout << (a + b) << std::endl;
			continue;
		}

		if ("mul" == command) {
			int a, b;
			std::cin >> a >> b;
			std::cout << (a * b) << std::endl;
			continue;
		}

		if ("sub" == command) {
			int a, b;
			std::cin >> a >> b;
			std::cout << (a - b) << std::endl;
			continue;
		}

		if ("div" == command) {
			int a, b;
			std::cin >> a >> b;
			if (0 == b) { std::cout << "Division by zero!" << std::endl; }
			else { std::cout << (a / b) << std::endl; }
			continue;
		}

		std::cout << "Unknown command" << std::endl;
	};
}

//Понятно, что можно было бы заменить многократные if на поиск в словаре
//Однако не ясно, что именно должно быть элементом словаря
//На каждое слово мы производим какой-то код
//В решении этой задачи нам поможет полиморфизм!

//создадим базовый класс
struct CommandProcess {
	virtual bool process() const { return true; } //метод процесс возвращает нам proceed, флаг продолжения
	//метод виртуальный, потому что мы собираемся дать ему другие реализации в выденных классах
};

struct Exit : CommandProcess {
	bool process() const { return false; } //команда Exit изменяет метод так, что он всегда возвращает false, т.е. прерывает работу мгновенно
};

struct Add : CommandProcess {
	bool process() const {
		int a, b;
		std::cin >> a >> b;
		std::cout << (a + b) << std::endl;
		return true;
	}
};

//реорганизуем основную функцию
#include <map>
void arithmetic_polymorphic() {
	std::map <std::string, CommandProcess*> commands;
	Exit exit;
	Add add;
	commands["exit"] = &exit;
	commands["add"] = &add;

	bool proceed = true;
	while (proceed) {
		std::string command;
		std::cin >> command;

		auto process_it = commands.find(command); //ищем объект с кодом, который необходимо выполнить
		//если не находим, то выполняем код для ошибочной команды
		if (commands.end() == process_it) { std::cout << "Unknown command" << std::endl; continue; }

		//в остальных случаях делегируем работу найденной команде
		proceed = process_it->second->process(); 
	}
}

//Заполнить оставшиеся команды

//Если посмотреть на получившийся код, то становится ясно, что в базовом классе нам нет необходимости содержать никакой реализации, т.к. она никогда не будет использована
//Тем не менее, мы вписали туда совершенно абсурдный код
//Для таких ситуаций в C++ предусмотрен специальный инструмент - чисто виртуальные методы (pure virtual)
//Мы знаем, что виртуальный метод - это указатель на какой-то код, заполнен этот указатель может быть в выведенном классе
//Теоретически мы могли бы просто создать такой указатель и положить в него nullptr
//Именно такая ситуация и называется чисто виртуальной 

struct Figure { //Базовая фигура не имеет никакого конкретного периметра или площади
	virtual double periphery() const = 0; //чисто виртуальная функция
	virtual double area() const = 0; //чисто виртуальная функция
};

class Circle : public Figure {
public:
	Circle(double r) :r(r) { }

	double periphery() const override { return 3.14*r*2.; } //эти методы будут вызваны через указатели
	double area() const override { return 3.14*r*r; }

private:
	double r;
};

class Rectangle : public Figure {
public:
	Rectangle(double w, double h): w(w), h(h) { }

	double periphery() const { return 2 * (w + h); } //эти методы будут вызваны через указатели
	double area() const { return w * h; }

private:
	double w, h;
};

void print_figure(Figure const &fig) {
	std::cout << "periphery = " << fig.periphery() << " and area = " << fig.area() << std::endl;
}

void figure_test() {
	//Figure fig; //ошибка компиляции
	//невозможно создать экземпляр класса с чисто виртуальными функциями, так как потом их нельзя будет вызывать
	
	//Но можно создать ссылки типа Figure на существующие объекты
	Circle cir(1);
	print_figure(cir);

	Rectangle rect(2, 3);
	print_figure(rect);
}

//Классы, все методы которых чисто виртуальные (pure virtual) и открытые (public), а внутренние данные отсутствуют (за исключением, возможно, статических констант), называются "Интерфейсы".

//Работа с интерфейсами вместо простых базовых классов имеет ряд преимуществ
//i) Интерфейсы не нужно конструировать в дочерних классах, т.к. нет внутренних данных
//ii) Интерфейсы всегда определяют методы виртуальными, потому нельзя забыть это сделать
//iii) Интерфейсы показывают, что можно делать с определённым типом данных, супертипом, но не рассказывают о том, как это делать в подтипах, что сильно снижает связанность кода


//Иногда при создании базового класса часть методов мы хотим сделать чисто виртуальными
//Если в классе одновременно с чисто виртуальными методами есть данные или обычные методы, или виртуальные методы с реализацией, то такие классы не называют "Абстрактными"

struct HtmlResponce { //это интерфейс
	virtual std::string header() const = 0; //у каждого ответа есть заголовок
	virtual std::string body() const = 0; //у каждого ответ есть тело
};

struct GoodPage : HtmlResponce { //абстрактный класс
	std::string header() const override final { return "HTTP/1.1 200 OK"; } //у всех страниц, которые успешно получены общий заголовок, его можно вынести в базовый класс для всех хороший страниц
	//а вот тело ответа может быть разным
};

struct MainPage : GoodPage {
	std::string body() const override { return "Main page"; } //даём реализацию чисто виртуальному методу
};

//Абстрактный класс обязательно должен иметь по крайней мере один чисто виртуальный метод, иначе это уже не абстрактный, а самый обычный класс
//Так как в абстрактном классе есть чисто виртуальный метод, то объекты абстрактного класса нельзя создать

int main() {
	if (false) arithmetic();
	if (false) arithmetic_polymorphic();
	if (false) figure_test();

	return 0;
}