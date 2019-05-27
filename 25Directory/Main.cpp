#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <time.h>

//������������� �������� �� io.h
void io_test() {
	struct _finddata_t c_file; //���������, ���������� ������ � �����
	intptr_t hFile;

	if ((hFile = _findfirst("*", &c_file)) == -1L) //���� ������ ��������� � ���������� handler
		printf("No files with the mask given in current directory!\n");
	else
	{
		printf("Listing of .cpp files\n\n");
		printf("RDO HID SYS ARC  FILE         DATE %25c SIZE\n", ' ');
		printf("--- --- --- ---  ----         ---- %25c ----\n", ' ');
		do {
			char buffer[30];
			printf((c_file.attrib & _A_RDONLY) ? " Y  " : " N  "); //������ ��� ������
			printf((c_file.attrib & _A_HIDDEN) ? " Y  " : " N  "); //�����
			printf((c_file.attrib & _A_SYSTEM) ? " Y  " : " N  "); //���������
			printf((c_file.attrib & _A_ARCH) ? " Y  " : " N  ");   //��������
			ctime_s(buffer, 30, &c_file.time_write);
			printf(" %-12s %.24s  %9ld\n",
				c_file.name, buffer, c_file.size);
		} while (_findnext(hFile, &c_file) == 0);
		_findclose(hFile);
	}
}

//������������� Win32 API
#include <Windows.h>
#include <string.h>
void list_files_and_dirs() {
	char dir[MAX_PATH]; //�����, � ������� ���������� �������� �����, ����� ��� ����������� ��������� ����� (255)
	strcpy(dir, "./*"); //����� ���� ������ � ����������� ������� ����������

	WIN32_FIND_DATAA ffd; //���������, ���������� ������ � �����
	HANDLE hFind = FindFirstFileA(dir, &ffd); //������� ������ ������� ��������� �����

	if (INVALID_HANDLE_VALUE == hFind) { //�������� �� ����������
		printf("Can't open directory: %s\n", dir);
		return;
	}

	do
	{
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			printf("  %32s   <DIR>\n", ffd.cFileName); //���� ����� ����������
		} else {
			LARGE_INTEGER filesize;
			filesize.LowPart = ffd.nFileSizeLow;
			filesize.HighPart = ffd.nFileSizeHigh;
			printf("  %32s   %lld bytes\n", ffd.cFileName, filesize.QuadPart); //������ �����
		}
	} while (FindNextFileA(hFind, &ffd) != 0); //������������ � ���������� ���������, ���� ��� ��������
}

int main() {
	if (false) io_test();
	if (false) list_files_and_dirs();

	return 0;
}