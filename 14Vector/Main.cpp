#include <iostream>

//std::vector - ��� ����������� �����, ������� "�������������" ������ � ������������ �������
//������� ������ std::vector ����� ��� ������������� �������� ����������� ������������ ������
//��� �����������, ������������ � �������� ������� �������������� ��������� �������, �������� ��� ����������
//����� std::vector �������� � ������������ ����� vector

#include <vector> //��� ������������� std::vector
void vector_test() {
	std::vector<int> a; //��� ���������� ��� ���������� ������� � ������� ������� ��� ������, ������� �� ����� ������� � �������
	//������ ���������� ������ ���� ������, ������ ����� ������� ������ ���������� �������

	std::vector<int> b(10); //����� ������ ������ �� 10 ���������, ����������� ��������� �� ��������� (��� int ��� 0)

	std::vector<int> c(10, -1);//����� ������ ������ �� 10 ���������, ������������������ ��������� -1

	std::cout << "a: ";
	for (int i = 0; i != a.size(); ++i) //������ ������ ������ std::vector ����� ���-�� ��������� � ��
		std::cout << a[i] << ' '; //��������� � ����������� �������� ����� ��������� ����� [], ��� � �������
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

//�������������� ���������� ������� ������
void vector_expand_test() {
	std::vector<int> vec; //������ ������, ��� �� ������ ��������
	std::cout << vec.size() << std::endl;
	std::cout << vec.capacity() << '\n' << std::endl;

	vec.push_back(-1); //��������� � ����� ������� ����� ��������: -1
	std::cout << vec.size() << std::endl;
	std::cout << vec.capacity() << std::endl;
	std::cout << "vec[0]: " << vec[0] << '\n' << std::endl;

	vec.push_back(-2);
	std::cout << vec.size() << std::endl;
	std::cout << vec.capacity() << std::endl;
	std::cout << "vec[0]: " << vec[0] << std::endl;
	std::cout << "vec[1]: " << vec[1] << '\n' << std::endl;

	vec.reserve(100); //���������� ���������� ������
	vec.push_back(-3);
	std::cout << vec.size() << std::endl;
	std::cout << vec.capacity() << std::endl;
	std::cout << "vec[0]: " << vec[0] << std::endl;
	std::cout << "vec[1]: " << vec[1] << std::endl;
	std::cout << "vec[2]: " << vec[2] << '\n' << std::endl;
}

//�������� ������ �� ������ �����
#include <string>
void vector_string() {
	std::vector<std::string> strings = { "Hello", "World", "!" };
	std::string answer("Ans: ");

	for (std::string const &s : strings) //��� ����������� ����, ������� ��������� ������ ���� ������, �� � ����� ���������
		answer += s;
	
	std::cout << answer << std::endl;

	for (auto ch : answer) //����� ������ : ����������� ������ ��� ������ �� ������� ����������, � ����� - ��� ���������
		std::cout << ch << ' ';
	std::cout << std::endl;
}


//���� �� ���������� ������ ������ ���������� ������������ ����� ��������, �� std::vector - ��������� �������
//���������� ������� ������ PolygonalLine � �������������� std::vector

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
	PolygonalLine(std::vector<Point> const &points) : points(points) { }//�������������� ���������� ������ ���������� �������, ��� ����������� �������� �� ��������� ������ � ����������� ������ std::vector ���� �� ����
	PolygonalLine() { } //����������� ��� ���������� ������������� �������� ����������� ��� ���������� ��� std::vector

	double full_distance() {
		double fd = 0;
		for (size_t pos = 0; pos != points.size() - 1; ++pos) //������ ��� ����� ���� ������, ��� ������ ������� ��� ��������
			fd += points[pos].distance(points[pos + 1]); //�� ������� ����� ���������� � ��������� std::vector ����� �������� []
		return fd;
	}

	//~PolygonalLine() { } //��� ������������� ������ ����������! ������������ ���� ���������� ������ ����� ������� �������������! ���������� ������� ��� ��������� ������������ ������
	PolygonalLine(PolygonalLine const &src) = default;// ��� � ��� ����� ������ ����������� �����������
	PolygonalLine& operator=(PolygonalLine const &src) = default; // ��� �������� ������������
	//��� ��� �������� ������������� ���������� � �������� ���������� ������, � ������ ��������� � ����� ������������� ����������� � ��������� ������������ ����������� ������ ��� ������ � ������������ �������
	PolygonalLine(PolygonalLine &&src) = default; //������� ����������� �� ���������, ��� ������� ����������� ���������� ������
	PolygonalLine& operator=(PolygonalLine &&src) = default; //�� �� ��� ��������� ������������

	//�������� �������� ����� ���� ������ ����������� � �������������� �������
	PolygonalLine& operator+=(PolygonalLine const &src) {
		points.reserve(points.size() + src.points.size()); //����������� ������
		for (size_t size = points.size(), end = src.points.size(), pos = 0; pos != end; ++pos)
			points[size + pos] = src.points[pos];

		return *this;
	}
	//�������� + ����� ���� ����� ����������, ���� ���� += � ����������� �����������
	PolygonalLine operator+(PolygonalLine const &src) const {
		PolygonalLine tmp(*this); //�������� ���� ������
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