#include <iostream>
#include <string>

//������� main ����� ��������� ��� ������� ��������� ���������, ������� ���������� ����� ��������� ������
//��������� ������� main - ��� ������ ������, ������ ��������, ��� �������� ��� ������ ���������
//������ ����� �������� ��� �������� - ��� ���� ��������
//��������� ��������� ���������
/*int main(
	int argc //���������� ����������
	, char **argv //�������� ����������
) {
	if (0 < argc) std::cout << argv[0] << std::endl; //�������� � �������� 0 - ��� ����, �� �������� �������� ���������
	for (int i = 1; i < argc; ++i)
		std::cout << i << ": " << argv[i] << std::endl;

	return 0;
}*/

/*int main(int argc, char **argv) {
	if (3 >= argc) { std::cout << "Not enough arguments!" << std::endl; return 0; }
	std::string operation, lha, rha;
	operation = argv[1];
	lha = argv[2];
	rha = argv[3];

	int i_lha = std::stoi(lha), i_rha = std::stoi(rha);
	if ("sum" == operation) {
		std::cout << (i_lha + i_rha) << std::endl;
	} else if ("sub" == operation) {
		std::cout << (i_lha - i_rha) << std::endl;
	} else {
		std::cout << "Unknown command!" << std::endl;
	}
	
	return 0;
}*/
