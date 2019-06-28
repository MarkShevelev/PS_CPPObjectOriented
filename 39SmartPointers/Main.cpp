#include <iostream>
#include <string>
#include <vector>

//Мы уже встречались со сложной ситуацией при работе с полиморфными типами
//Если реальный тип объекта динамический, например, его выбирает пользователь, то мы вынуждены создавать такие объекты в динамической памяти, а в контейнере сохранять только указатели базового типа

struct Figure { //интерфейс фигуры, который определяет наличие метода area()
	virtual double area() const = 0;
	virtual ~Figure() { } 
};

class Circle final: public Figure {
public:
	Circle(double r) : r(r) { }
	double area() const override { return 3.1415*r*r; }
	~Circle() { std::cout << "Circle destroyed" << std::endl; }

private:
	double r;
};

class Rectangle final: public Figure {
public:
	Rectangle(double w, double h): w(w), h(h) { }
	double area() const override { return w * h; }
	~Rectangle() { std::cout << "Rectangle destroyed" << std::endl; }

private:
	double w, h;
};

double full_area(std::vector<Figure*> figures) {
	double area = 0.;
	for (auto fig : figures)
		area += fig->area();
	return area;
}

void polymorphic_choice_test() {
	std::vector<Figure*> figures; //вектор для сохранения адресов

	bool proceed = true;
	do {
		std::string command;
		std::cin >> command;

		if ("exit" == command) { proceed = false; continue; }
		if ("cir" == command) {
			double radius;
			std::cin >> radius;
			figures.push_back(new Circle(radius));
			continue;
		}
		if ("rect" == command) {
			double width, height;
			std::cin >> width >> height;
			figures.push_back(new Rectangle(width, height));
			continue;
		}
		if ("area" == command) { std::cout << full_area(figures) << std::endl; continue; }

		std::cout << "Unknown command!" << std::endl;
	} while (proceed);

	for (auto fig : figures) //необходимый код для возвращения памяти !!!
		delete fig;
}

//Мы знаем, что для каждого объекта, который выходит из области видимости вызывается деструктор
//К сожалению, указатели типа языка C не имеют деструкторов
//Однако, ничто не мешает нам создать "вручную" специальный класс, объекты которого будут удалять динамическую память

#include <algorithm> //swap
template<typename T>
class MyAutoPtr final {
public:
	MyAutoPtr(): MyAutoPtr(nullptr) { }
	MyAutoPtr(T *obj): obj(obj) { }
	~MyAutoPtr() { if (nullptr != obj) delete obj; }
	T& operator*() { return *obj; }
	T const& operator*() const { return *obj; }
	T* operator->() { return obj; }
	T const * operator->() const { return obj; }

	MyAutoPtr(MyAutoPtr const &src) = delete;
	MyAutoPtr& operator=(MyAutoPtr const &src) = delete;

	MyAutoPtr(MyAutoPtr &&src) : obj(src.obj) { src.obj = nullptr; }
	MyAutoPtr& operator=(MyAutoPtr &&src) {
		MyAutoPtr tmp(std::move(src));
		std::swap(obj, tmp.obj);
		return *this;
	}

private:
	T *obj;
};

void myautoptr_test() {
	std::vector<MyAutoPtr<Figure>> figures; //вектор, содержащий специальные объекты, которые сами освободят динамическую память, которую захватят в конструкторе

	bool proceed = true;
	do {
		std::string command;
		std::cin >> command;

		if ("exit" == command) { proceed = false; continue; }
		if ("cir" == command) {
			double radius;
			std::cin >> radius;
			figures.push_back(new Circle(radius));
			continue;
		}
		if ("rect" == command) {
			double width, height;
			std::cin >> width >> height;
			figures.push_back(new Rectangle(width, height));
			continue;
		}
		if ("area" == command) { 
			double area = 0.;
			for (auto &auto_ptr : figures) {
				area += auto_ptr->area();
			}
			std::cout << area << std::endl;
			continue;
		}

		std::cout << "Unknown command!" << std::endl;
	} while (proceed);

	//данный код больше не является необходимым
	/*for (auto fig : figures) 
		delete fig;*/
}


//В стандартной библиотеке C++ есть стандартный шаблон unique_ptr, который позволяет подобно написанному нами MyAutoPtr автоматически уничтожать объекты, при выходе из области видимости или завершении жизни объектов, которые их содержат
#include <memory>
void unique_ptr_test() {
	std::unique_ptr<Rectangle> prtRect(new Rectangle(1., 2.));
	{
		std::unique_ptr<Circle> ptrCir(new Circle(1.));
	}
	//unique_ptr поддерживают "ковариантность"
	std::unique_ptr<Figure> figure;
	{
		std::unique_ptr<Circle> ptrCir(new Circle(2.));
		figure = std::move(ptrCir); //присваивание невозможно, но возможно перемещение
	}
	std::cout << figure->area() << std::endl;
}

//В некоторых ситуациях может возникнуть необходимость один и тот же объект разделять между другими объектами - агрегация
//Где тогда хранить данные об этих объектах, если они полиморфные, и как их уничтожать

//В случае композиции можно создать вектор уникальных умных указателей
class CompositeFigureViaComposition final: public Figure {
public:
	void add(Figure const * fig) { figures.emplace_back(fig); }
	double area() const override {
		double sum = 0;
		for (auto &ptr : figures)
			sum += ptr->area();
		return sum;
	}

private:
	std::vector<std::unique_ptr<Figure const>> figures; //все фигуры будут удалены как только закончит жизнь объект
};

void composite_via_composition_test() {
	{
		Circle cir(1.);
		Rectangle rect(2., 1.);
		std::cout << "Two figures area: " << (cir.area() + rect.area()) << std::endl;
	}

	{
		CompositeFigureViaComposition composite;
		composite.add(new Circle(1.));
		composite.add(new Rectangle(2., 1.));
		std::cout << "Composite area: " << composite.area() << std::endl;
	}
}

//Если же мы хотим агрегацию, то ответ не так прост
//Одно из решений, хранить данные где-то ещё
class CompositeFigureViaSimplePointerAggregation final : public Figure {
public:
	void add(Figure const * fig) { figures.push_back(fig); }
	double area() const override {
		double sum = 0.;
		for (auto ptr : figures)
			sum += ptr->area();
		return sum;
	}

private:
	std::vector<Figure const*> figures;
};

void composite_via_simple_pointer_aggeregation_test() {
	//мы обязательно должны иметь отдельное хранилище для данных
	std::vector<std::unique_ptr<Figure>> figures;
	{
		CompositeFigureViaSimplePointerAggregation compositeA;
		CompositeFigureViaSimplePointerAggregation compositeB;

		//обязательно добавляем фигуру сначала в хранилище
		figures.emplace_back(new Circle(1.));
		figures.emplace_back(new Rectangle(2., 1.));

		//затем разделяем между агрегирующими объектами
		compositeA.add(figures[0].get());
		compositeA.add(figures[1].get());

		compositeB.add(figures[1].get());
		compositeB.add(figures[0].get());

		//figures.erase(figures.begin());//опасная ситуация потери данных, может произойти случайно

		std::cout << compositeA.area() << std::endl;
		std::cout << compositeB.area() << std::endl;
	}
}

//В С++ есть специальный инструмент, который позволяет решить эту проблему - shared_ptr
//это специальный указатель, который подсчитывает количество живых объектов и удаляет память только в том случае, когда все объекты умерли

void shared_ptr_test() {
	std::shared_ptr<Figure> circle(new Circle(1.));
	{
		std::shared_ptr<Figure> shared_circle = circle;
		std::cout << shared_circle->area() << std::endl;
	}
	std::cout << circle->area() << std::endl;
	//только в конце будет удалён объект
}

//Можно использовать shared_ptr для создания агрегации
class CompositeFigureViaSharedPointerAggregation final : public Figure {
public:
	void add(std::shared_ptr<Figure> fig) { figures.push_back(fig); }
	double area() const override {
		double sum = 0.;
		for (auto fig : figures)
			sum += fig->area();
		return sum;
	}

private:
	std::vector<std::shared_ptr<Figure>> figures;
};

void composite_via_shared_pointer_aggeregation_test() {
	CompositeFigureViaSharedPointerAggregation compositeA;
	{
		std::shared_ptr<Figure> circle_ptr(new Circle(1.)), rectangle_ptr(new Rectangle(2.,1.));
		{
			CompositeFigureViaSharedPointerAggregation compositeB;
			compositeB.add(circle_ptr);
			compositeB.add(rectangle_ptr);

			std::cout << "CompositeB: " << compositeB.area() << std::endl;
		}

		compositeA.add(circle_ptr);  //если данную часть кода закомментировать, то объекты умрут раньше, чем выводится площадь compositeA
		compositeA.add(rectangle_ptr);
	}
	std::cout << "CompositeA: " << compositeA.area() << std::endl;
}


//при использовании shared_ptr возможны ситуации, когда объект никогда не будет удалён
class DangerousCircle {
public:
	DangerousCircle(std::string const &name) : name(name) { }
	void add(std::shared_ptr<DangerousCircle> next) { this->next = next; }
	~DangerousCircle() { std::cout << name << " has been destroyed!" << std::endl; }

private:
	std::string name;
	std::shared_ptr<DangerousCircle> next;
};

void dangerous_circle_test() {
	{//line chain is good
		auto m = std::make_shared<DangerousCircle>("Majira"), o = std::make_shared<DangerousCircle>("Odin"), b = std::make_shared<DangerousCircle>("Barks");
		m->add(o); o->add(b);
	}

	{//circle chain is bad
		auto m = std::make_shared<DangerousCircle>("Marks"), o = std::make_shared<DangerousCircle>("Opal"), b = std::make_shared<DangerousCircle>("Bigle");
		m->add(o); o->add(b); b->add(m); //m o b никгда не будут удалены, т.к. счётчик ссылок никогда не достигнет ноля
	}
}

//для разрыва подобных циклических ссылок существует специальный умный указатель weak_ptr
class WeakLink {
public:
	WeakLink(std::string const &name): name(name) { }
	~WeakLink() { std::cout << name << " has been destroyed" << std::endl; }
	void add(std::weak_ptr<WeakLink> link) { this->link = link; }

private:
	std::string name;
	std::weak_ptr<WeakLink> link;
};

void weak_link_test() {
	{//line chain
		auto m = std::make_shared<WeakLink>("Majira"), o = std::make_shared<WeakLink>("Odin"), b = std::make_shared<WeakLink>("Barks");
		m->add(o); o->add(b);
	}

	{//circle chain
		auto m = std::make_shared<WeakLink>("Marks"), o = std::make_shared<WeakLink>("Opal"), b = std::make_shared<WeakLink>("Bigle");
		m->add(o); o->add(b); b->add(m);
	}
}

//weak_ptr может быть легко создан из shared_ptr, такой weak_ptr "знает", если shared_ptr "умер"
//.expired() возвращает true, если связанный с weak_ptr shared_ptr уже "мёртв"
//.lock() позволяет получить shared_ptr, что будет гарантировать существование данных, пока вы работаете с ними

int main() {
	if (false) polymorphic_choice_test();
	if (false) myautoptr_test();
	if (false) unique_ptr_test();
	if (false) composite_via_composition_test();
	if (false) composite_via_simple_pointer_aggeregation_test();
	if (false) shared_ptr_test();
	if (false) composite_via_shared_pointer_aggeregation_test();
	if (false) dangerous_circle_test();
	if (false) weak_link_test();

	return 0;
}