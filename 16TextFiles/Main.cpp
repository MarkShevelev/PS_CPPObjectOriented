#include <iostream> //����� ������ ����� � ������ ostream istream cin cout cerr
#include <fstream>  //������ ��� ������ � ������� ofstream ifstream fstream
#include <string>   //std::getline
#include <vector>
#include <algorithm>

//� �++ ���������� ���� ����������� ������ ������ � �������
//�� ���������� � ������ � ��������� ������� ofstream ifstream � fstream
//ifstream (input file stream) ������������ ��� ����� ������ � ���������, ������ �����
void open_file_read() {
	std::string filename;
	std::cin >> filename;

	std::ifstream in_file(filename); //�������� ������� ���� filename
	if (!in_file.good()) { //���� ��� �������� ����� ��������� ������, �� in_file.good() ����� false
		std::cout << "Can't open file " << filename << std::endl;
		return;
	}

	//������ ����� �� �����, ��� �������� ���������� ������ �� ������������ �����
	std::string word;
	in_file >> word;
	std::cout << word << std::endl; //������� �� ����� ����� �� �����

	//������ ����������� ������ �������� � ����, ��� �� ���������� ����� � ����, ��� � ����������� �����
	std::string next_word;
	in_file >> next_word;
	std::cout << next_word << std::endl;

	in_file.close(); //�������� �����
	//�� ����� ���� ��� ����� ���� ����������� �������������, ������������ ������� in_file
}

//��� ������ � ���� ������������ ����������� ����� ofstream (output file stream)
void open_file_write() {
	std::string filename;
	std::cin >> filename;

	std::ofstream out_file(filename);
	if (!out_file.good()) {
		std::cout << "Can't open file " << filename << std::endl;
		return;
	}
	//����� � ���� �� ��� �� ���������� �� ������ � ����������� �����
	out_file << "Eva" << '\n' << "Alice" << '\n' << "Bob" << std::flush;

	out_file.close(); //������ �������� �� �������� ������������ � ������ ����, ��� ����������� � �����������
}

//�� ��������� ��� ������ ���� ��������� ������������
//��������� �������������� ���� std::ios::app (append) ����� ���������� ���������� � ����, �������� ��, ��� ��� ���� �����
void append_file_test() {
	std::string filename;
	std::cin >> filename;

	{
		std::ofstream out_file(filename);
		if (!out_file) { //����� �� �������� .good() ����, ��� ������ �����/������ ����� ������������� ��������� ���������� � ���� bool
			std::cout << "Can't open file " << filename << std::endl;
			return;
		}
		out_file << "Some sentence" << std::endl;
	} //�� �����, ��� ���������� ������� ����, ��� ������������� �������� .close() ����

	{
		std::ofstream out_file(filename,std::ios::app); //������� ��� ���� �������� - ���� app
		if (!out_file) { 
			std::cout << "Can't open file " << filename << std::endl;
			return;
		}
		out_file << "Another sentence" << std::endl;
	}

	//������ ���������� �����
	{
		std::ifstream in_file(filename);
		if (!in_file) {
			std::cout << "Can't open file " << filename << std::endl;
			return;
		}
		std::string line;
		while (std::getline(in_file, line)) //�� ����� ������������ ������� getline � � ������� ����
			std::cout << line << std::endl;
		//����� ������ ������ �� ����� ����� ����������, ���� ����������
	}
}

//������ �� ���� ����� � ������, �������������� � ��������������� ����
void vector_file_test() {
	std::vector<int> numbers; //�� �� ����� ������� ����� � �����, ������ ����� ��������� �� � ������, �� ��� �������� ����� ������
	std::string filename;
	std::cin >> filename;

	{
		std::ifstream in_file(filename);
		if (!in_file) {
			std::cout << "Error!" << std::endl;
			return;
		}

		do {
			int i;
			in_file >> i;
			if (in_file) //��� ����� ����������� �� ����� ��� ���� ����� �����
				numbers.push_back(i);
		} while (in_file); //��� ������ ������ �� ����� ����� ����������, ���������� ������ �����

		if (!in_file.eof()) {
			std::cout << "Data have not been read till the end of the file!" << std::endl;
			return;
		}
	}

	//������� ����� �� �����
	for (auto num : numbers)
		std::cout << num << ' ';
	std::cout << std::endl;

	//���������
	std::sort(numbers.begin(), numbers.end());
	for (auto num : numbers)
		std::cout << num << ' ';
	std::cout << std::endl;

	{
		std::ofstream out_file(filename);
		if (!out_file) {
			std::cout << "Error" << std::endl;
			return;
		}

		for (auto num : numbers)
			out_file << num << ' ';
		out_file << std::endl;
	}
}

int main() {
	if (false) open_file_read();
	if (false) open_file_write();
	if (false) append_file_test();
	if (false) vector_file_test();

	return 0;
}