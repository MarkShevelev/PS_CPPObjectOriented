#include <iostream>

//std::vector - это специальный класс, который "инкапсулирует" работу с динамической памятью
//объекты класса std::vector умеют при необходимости занимать необходимую динамическую память
//при копировании, присваивании и удалении объекты самостоятельно управляют памятью, копируют или уничтожают
//класс std::vector определён в заголовочном файле vector

#include <vector> //для использования std::vector
void vector_test() {
	std::vector<int> a; //при объявлении нам необходимо указать в угловых скобках тип данных, который мы будем хранить в векторе
	//вектор использует внутри себя массив, потому может хранить только однотипные объекты

	std::vector<int> b(10); //будет создан вектор из 10 элементов, заполненных значением по умолчанию (для int это 0)

	std::vector<int> c(10, -1);//будет создан вектор из 10 элементов, инициализированных значением -1

	std::cout << "a: ";
	for (int i = 0; i != a.size(); ++i) //каждый объект класса std::vector знает кол-во элементов в нём
		std::cout << a[i] << ' '; //обращение к конкретному элементу можно выполнить через [], как у массива
	std::cout << std::endl;

	std::cout << "b: ";
	for (int i = 0; i != b.size(); ++i)
		std::cout << b[i] << ' '; 
	std::cout << std::endl;

	std::cout << "c: ";
	for (int i = 0; i != c.size(); ++i)
		std::cout << c[i] << ' ';
	std::cout << std::endl;
}

//автоматическое расширение размера ветора
void vector_expand_test() {
	std::vector<int> vec; //пустой вектор, нет ни одного значения
	std::cout << vec.size() << std::endl;
	std::cout << vec.capacity() << '\n' << std::endl;

	vec.push_back(-1); //добавляет в конец массива новое значение: -1
	std::cout << vec.size() << std::endl;
	std::cout << vec.capacity() << std::endl;
	std::cout << "vec[0]: " << vec[0] << '\n' << std::endl;

	vec.push_back(-2);
	std::cout << vec.size() << std::endl;
	std::cout << vec.capacity() << std::endl;
	std::cout << "vec[0]: " << vec[0] << std::endl;
	std::cout << "vec[1]: " << vec[1] << '\n' << std::endl;

	vec.reserve(100); //расширение внутренней памяти
	vec.push_back(-3);
	std::cout << vec.size() << std::endl;
	std::cout << vec.capacity() << std::endl;
	std::cout << "vec[0]: " << vec[0] << std::endl;
	std::cout << "vec[1]: " << vec[1] << std::endl;
	std::cout << "vec[2]: " << vec[2] << '\n' << std::endl;
}

//создание ветора из других типов
#include <string>
void vector_string() {
	std::vector<std::string> strings = { "Hello", "World", "!" };
	std::string answer("Ans: ");

	for (std::string const &s : strings) //это специальный цикл, который позволяет обойти весь вектор, да и любой контейнер
		answer += s;
	
	std::cout << answer << std::endl;

	for (auto ch : answer) //перед знаком : указывается ссылка или копиня на элемент контейнера, а после - сам контейнер
		std::cout << ch << ' ';
	std::cout << std::endl;
}


//если во внутренних данных класса необходимо использовать набор объектов, то std::vector - идеальное решение
//Рассмотрим решение задачи PolygonalLine с использованием std::vector

#include <cmath>
class Point {
	double x, y;
public:
	Point(double x, double y): x(x), y(y) { }

	double distance(Point const &oth) const {
		return hypot(x - oth.x, y - oth.y);
	}
};

class PolygonalLine {
public:
	PolygonalLine(std::vector<Point> const &points) : points(points) { }//инициализируем внутренний вектор параметром функции, все необходимые действия по выделению памяти и копированию данных std::vector берёт на себя
	PolygonalLine() { } //конструктор без параметров автоматически вызывает конструктор без параметров для std::vector

	double full_distance() {
		double fd = 0;
		for (size_t pos = 0; pos != points.size() - 1; ++pos) //вектор сам знает свой размер, нет смысла хранить его отдельно
			fd += points[pos].distance(points[pos + 1]); //мы успешно можем обращаться к элементам std::vector через оператор []
		return fd;
	}

	//~PolygonalLine() { } //нет необходимости писать деструктор! Декструкторы всех внутренних данных будут вызваны автоматически! Деструктор вектора сам освободит динамическую память
	PolygonalLine(PolygonalLine const &src) = default;// как и нет нужны писать конструктор копирования
	PolygonalLine& operator=(PolygonalLine const &src) = default; // или оператор присваивания
	//все эти операции автоматически вызываются и копируют внутренние данные, а вектор реализует в своих перегруженных констукторе и операторе присваивания необходимую логику для работы с динамической памятью
	PolygonalLine(PolygonalLine &&src) = default; //создать перемещение по умолчанию, оно вызовет перемещение внутренних данных
	PolygonalLine& operator=(PolygonalLine &&src) = default; //то же для оператора присваивания

	//операции сложения могут быть просто реализованы с использованием вектора
	PolygonalLine& operator+=(PolygonalLine const &src) {
		points.reserve(points.size() + src.points.size()); //резервируем память
		for (size_t size = points.size(), end = src.points.size(), pos = 0; pos != end; ++pos)
			points[size + pos] = src.points[pos];

		return *this;
	}
	//оператор + может быть легко реализован, если есть += и конструктор копирования
	PolygonalLine operator+(PolygonalLine const &src) const {
		PolygonalLine tmp(*this); //копируем свои данные
		tmp += src;
		return tmp;
	}

private:
	std::vector<Point> points;
};


int main() {
	if (false) vector_test();
	if (false) vector_expand_test();
	if (false) vector_string();

	return 0;
}