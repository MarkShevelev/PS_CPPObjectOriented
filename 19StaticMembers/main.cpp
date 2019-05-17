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

//��� � ������� ������, ����������� ������ ����� ���� private
//��������, ��� ����� ���� ����������, ����� �������������� ����������� ������
class CountResource {
public:
	CountResource() : local_reference(make_resource()) { ++resource_counter; }
	CountResource(CountResource const &oth) : local_reference(oth.local_reference) { ++resource_counter; }
	~CountResource() {
		--resource_counter; if (0 == resource_counter) { delete resource; resource = nullptr; }
	}

	int GetResource() const { return local_reference; }
	int& GetResource() { return local_reference; }

private:
	int &local_reference;

	static int *resource;
	static int& make_resource() { if (nullptr == resource) resource = new (std::nothrow) int(5); return *resource; }

public: //��������� ������� public, ����� �������� �����������
	static size_t resource_counter;
};

int *CountResource::resource = nullptr;
size_t CountResource::resource_counter = 0;

void shared_resource_test() {
	std::cout << "No objects: " << CountResource::resource_counter << std::endl;
	{
		CountResource resA;
		std::cout << "After one ojbect created: " << CountResource::resource_counter << std::endl;
	}
	std::cout << "After the ojbect has been destroyed: " << CountResource::resource_counter << std::endl;

	{
		CountResource resA, resB, resC;
		std::cout << "Check resources: " << resA.GetResource() << " " << resB.GetResource() << " " << resC.GetResource() << std::endl;
		std::cout << "Tree objects created: " << CountResource::resource_counter << std::endl;
		{
			CountResource resD;
			std::cout << "Another one object: " << resD.GetResource() << " count = " << CountResource::resource_counter << std::endl;
		}
		std::cout << "After one object has been destroyed: " << CountResource::resource_counter << std::endl;
	}
	std::cout << "All objects destroyed: " << CountResource::resource_counter << std::endl;
}

int main() {
	if (false) test_static_intersect();
	if (false) construct_counter_test();
	if (false) shared_resource_test();
}