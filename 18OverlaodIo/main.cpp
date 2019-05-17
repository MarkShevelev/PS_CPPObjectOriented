#include <iostream>
#include <string>

//��� ����, ����� ����� �������� ������ � ������ (� ������� ��� � ����) � C++ ���� ����������� ��������:
//���������� ���������� �����/������

//�������� ������� ���������
struct SimpleSegment {
	int begin, end;
};

void simple_segment_test() {
	SimpleSegment ss{ 0,10 };
	//std::cout << ss << std::endl; //��� �� �������������! ���������� �� �����, ��� ������ ������� �������
	//�� ����� �������� � ������� ������ � �������������� ������������
	std::cout << "SimpleSegment ss = (" << ss.begin << "," << ss.end << ")" << std::endl;
}

//���� ��������� ���������� ������� � �������� ����� ������, �� ��������� ��������� ������� ���,
//��������� �� ����� ��������� �������� ��������� - ������� ������

//����� ������� ������� �������, ������� �������� ������
void print_simple_segment(SimpleSegment const &ss) {
	std::cout << "(" << ss.begin << "," << ss.end << ")";
}

//�� ������ ������������ ������� print_simple_segment, �� �� ������ ������������ ������������ ������� ������
void print_simple_segment_test() {
	SimpleSegment a{ 0, 1 };
	SimpleSegment b{ 1, 0 };
	std::cout << "SimpleSegment a: "; print_simple_segment(a); std::cout << std::endl;
	std::cout << "SimpleSegment b: "; print_simple_segment(b); std::cout << std::endl;
}

//����� ���������� ������������ ����� ����� ����������� �������� <<
//��� ����� ���������� ����������� ���������
//std::ostream& operator<<(std::ostream&,<������ �� ������>);

//�������� ��� ���� ������� ��������� � ���������� �������� ������
struct OutputSegment {
	int begin, end;
};
//�������� ��������, ��� ������������ ��� std::ostream - ��� ����� ��� ��� ���� ������� ������
std::ostream& operator<<(std::ostream &os, OutputSegment const &s) {
	os << "(" << s.begin << "," << s.end << ")";
	return os;
}

//������ ��� ������� ������� �������� ������ � OutputSegment ���������� ����� ����������� ��� ������� ����
void output_operator_test() {
	OutputSegment a{ 0,1 };
	OutputSegment b{ 1,0 };
	std::cout << "OutputSegment a: " << a << std::endl << "OutputSegment b: " << b << std::endl;
}

//����������� ����� � �������� �����
std::istream& operator>>(std::istream &is, OutputSegment &s) {
	is >> s.begin >> s.end;
	return is;
}

void input_operator_test() {
	OutputSegment a,b;
	std::cin >> a >> b;
	std::cout << "Segment a: " << a << std::endl << "Segment b: " << b << std::endl;
}

//�� �����, ��� � ������� ������� ������� ���������� ������, �������� � ������ Segment
class Segment {
public:
	Segment(): begin(0), end(0) { }
	Segment(int begin, int end) : begin(begin), end(end) { }

	bool contains(int point) const { return point >= begin && point <= end; }
	int length() { return begin >= end ? 0 : (end - begin); }

private:
	int begin, end;
};

//���� �� ����� ������� �� ����� ��� ������� � ������� ������ ������� ���� Segment, �� ��� ����������� ������ ���������� � ���������� ������
//���������� �������� ������ ������ (������� �����) ��������, �� � ���� ������ �� �������� ��������� ��������� 
class IOSegment {
public:
	IOSegment() : begin(0), end(0) { }
	IOSegment(int begin, int end) : begin(begin), end(end) { }

	bool contains(int point) const { return point >= begin && point <= end; }
	int length() { return begin >= end ? 0 : (end - begin); }

	//�� ����� �������� �������� �������������
	friend std::ostream& operator<<(std::ostream &os, IOSegment const &s);
	friend std::istream& operator>>(std::istream &is, IOSegment &s);

private:
	int begin, end;
};

std::ostream& operator<<(std::ostream &os, IOSegment const &s) {
	return os << "(" << s.begin << "," << s.end << ")";
}

std::istream& operator>>(std::istream &is, IOSegment &s) {
	return is >> s.begin >> s.end;
}

void friend_operators_test() {
	IOSegment a, b;
	std::cin >> a >> b;
	std::cout << "Segment a: " << a << std::endl << "Segment b: " << b << std::endl;
}

int main() {
	if (false) simple_segment_test();
	if (false) print_simple_segment_test();
	if (false) output_operator_test();
	if (false) input_operator_test();
	if (false) friend_operators_test();
}