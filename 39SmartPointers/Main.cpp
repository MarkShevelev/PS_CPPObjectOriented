#include <iostream>
#include <string>
#include <vector>

//�� ��� ����������� �� ������� ��������� ��� ������ � ������������ ������
//���� �������� ��� ������� ������������, ��������, ��� �������� ������������, �� �� ��������� ��������� ����� ������� � ������������ ������, � � ���������� ��������� ������ ��������� �������� ����

struct Figure { //��������� ������, ������� ���������� ������� ������ area()
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
	std::vector<Figure*> figures; //������ ��� ���������� �������

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

	for (auto fig : figures) //����������� ��� ��� ����������� ������ !!!
		delete fig;
}

//�� �����, ��� ��� ������� �������, ������� ������� �� ������� ��������� ���������� ����������
//� ���������, ��������� ���� ����� C �� ����� ������������
//������, ����� �� ������ ��� ������� "�������" ����������� �����, ������� �������� ����� ������� ������������ ������

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
	std::vector<MyAutoPtr<Figure>> figures; //������, ���������� ����������� �������, ������� ���� ��������� ������������ ������, ������� �������� � ������������

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

	//������ ��� ������ �� �������� �����������
	/*for (auto fig : figures) 
		delete fig;*/
}


//� ����������� ���������� C++ ���� ����������� ������ unique_ptr, ������� ��������� ������� ����������� ���� MyAutoPtr ������������� ���������� �������, ��� ������ �� ������� ��������� ��� ���������� ����� ��������, ������� �� ��������
#include <memory>
void unique_ptr_test() {
	std::unique_ptr<Rectangle> prtRect(new Rectangle(1., 2.));
	{
		std::unique_ptr<Circle> ptrCir(new Circle(1.));
	}
	//unique_ptr ������������ "��������������"
	std::unique_ptr<Figure> figure;
	{
		std::unique_ptr<Circle> ptrCir(new Circle(2.));
		figure = std::move(ptrCir); //������������ ����������, �� �������� �����������
	}
	std::cout << figure->area() << std::endl;
}

//� ��������� ��������� ����� ���������� ������������� ���� � ��� �� ������ ��������� ����� ������� ��������� - ���������
//��� ����� ������� ������ �� ���� ��������, ���� ��� �����������, � ��� �� ����������

//� ������ ���������� ����� ������� ������ ���������� ����� ����������
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
	std::vector<std::unique_ptr<Figure const>> figures; //��� ������ ����� ������� ��� ������ �������� ����� ������
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

//���� �� �� ����� ���������, �� ����� �� ��� �����
//���� �� �������, ������� ������ ���-�� ���
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
	//�� ����������� ������ ����� ��������� ��������� ��� ������
	std::vector<std::unique_ptr<Figure>> figures;
	{
		CompositeFigureViaSimplePointerAggregation compositeA;
		CompositeFigureViaSimplePointerAggregation compositeB;

		//����������� ��������� ������ ������� � ���������
		figures.emplace_back(new Circle(1.));
		figures.emplace_back(new Rectangle(2., 1.));

		//����� ��������� ����� ������������� ���������
		compositeA.add(figures[0].get());
		compositeA.add(figures[1].get());

		compositeB.add(figures[1].get());
		compositeB.add(figures[0].get());

		//figures.erase(figures.begin());//������� �������� ������ ������, ����� ��������� ��������

		std::cout << compositeA.area() << std::endl;
		std::cout << compositeB.area() << std::endl;
	}
}

//� �++ ���� ����������� ����������, ������� ��������� ������ ��� �������� - shared_ptr
//��� ����������� ���������, ������� ������������ ���������� ����� �������� � ������� ������ ������ � ��� ������, ����� ��� ������� ������

void shared_ptr_test() {
	std::shared_ptr<Figure> circle(new Circle(1.));
	{
		std::shared_ptr<Figure> shared_circle = circle;
		std::cout << shared_circle->area() << std::endl;
	}
	std::cout << circle->area() << std::endl;
	//������ � ����� ����� ����� ������
}

//����� ������������ shared_ptr ��� �������� ���������
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

		compositeA.add(circle_ptr);  //���� ������ ����� ���� ����������������, �� ������� ����� ������, ��� ��������� ������� compositeA
		compositeA.add(rectangle_ptr);
	}
	std::cout << "CompositeA: " << compositeA.area() << std::endl;
}


//��� ������������� shared_ptr �������� ��������, ����� ������ ������� �� ����� �����
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
		m->add(o); o->add(b); b->add(m); //m o b ������ �� ����� �������, �.�. ������� ������ ������� �� ��������� ����
	}
}

//��� ������� �������� ����������� ������ ���������� ����������� ����� ��������� weak_ptr
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

//weak_ptr ����� ���� ����� ������ �� shared_ptr, ����� weak_ptr "�����", ���� shared_ptr "����"
//.expired() ���������� true, ���� ��������� � weak_ptr shared_ptr ��� "����"
//.lock() ��������� �������� shared_ptr, ��� ����� ������������� ������������� ������, ���� �� ��������� � ����

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