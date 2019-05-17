#include <iostream>
#include <algorithm>

//����������� ����� ������ - ��� ������ � �������, ������� ����� ������������ ������� ������, �� �� ����������� �������, �.�. ������ ������ �� ���������� ���������� � �������

//���������� ��������� ������� ������ Segment
class Segment {
public:
	//�� �������� ������� intersect c �������������� ��������� ����� static
	//����� ������� �� ������� �������� ����� ��� �������, ��� ���������� ��� ������� ���������� �������
	static Segment intersect(Segment const &lha, Segment const &rha);

public:
	Segment() : begin(0), end(0) { }
	Segment(int begin, int end) : begin(begin), end(end) { }

	bool contains(int point) const { return point >= begin && point <= end; }
	int length() { return begin >= end ? 0 : (end - begin); }
private:
	int begin, end;
};

//��� ���������� ������� intersect �� ������ �������, ��� ��� ������� ����������� ������ Segment ����� �������� ::
Segment Segment::intersect(Segment const &lha, Segment const &rha) {
	//�������� ��������, ��� �� ����� ���������� �� ���������� ������ ��������, ���� �� ��������� ������� �������������
	//��� ������� � ���, ��� ������� ����������� ������
	return Segment(std::max(lha.begin, rha.begin), std::min(lha.end, rha.end));
}

void test_static_intersect() {
	Segment a{ -1,3 }, b{ 2,4 };
	Segment c = Segment::intersect(a, b);
	std::cout << a.length() << " " << b.length() << " " << c.length() << std::endl;
}

//������������ ����� ���� �� ������ �������, �� � ������
class CountCounstruct {
public:
	static unsigned construct_counter;
	//� ������������ ������������� �������
	//������� �� �������� � ����������� �������, �� ���� ����, ��� ���������� ����������
	CountCounstruct(unsigned idx) : idx(idx) { ++construct_counter; }

private:
	unsigned idx;
};

unsigned CountCounstruct::construct_counter = 0; //� ����������� ���������� ������ ���� ��������� ������������� � ����� .cpp �����

void construct_counter_test() {
	{
		CountCounstruct a(0), b(1), c(2);
		//��� ��������� � ����������� ���������� ������� ������� �����
		std::cout << CountCounstruct::construct_counter << std::endl;
	}

	{
		CountCounstruct a(0), b(1), c(2);
		std::cout << CountCounstruct::construct_counter << std::endl;
	}
}

int main() {
	if (false) test_static_intersect();
	if (false) construct_counter_test();
}