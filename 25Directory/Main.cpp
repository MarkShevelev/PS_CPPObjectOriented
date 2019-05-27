#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <time.h>

//использование макросов из io.h
void io_test() {
	struct _finddata_t c_file; //структура, содержащая данные о файле
	intptr_t hFile;

	if ((hFile = _findfirst("*", &c_file)) == -1L) //ищет первое вхождение и возвращает handler
		printf("No files with the mask given in current directory!\n");
	else
	{
		printf("Listing of .cpp files\n\n");
		printf("RDO HID SYS ARC  FILE         DATE %25c SIZE\n", ' ');
		printf("--- --- --- ---  ----         ---- %25c ----\n", ' ');
		do {
			char buffer[30];
			printf((c_file.attrib & _A_RDONLY) ? " Y  " : " N  "); //только для чтения
			printf((c_file.attrib & _A_HIDDEN) ? " Y  " : " N  "); //скрыт
			printf((c_file.attrib & _A_SYSTEM) ? " Y  " : " N  "); //системный
			printf((c_file.attrib & _A_ARCH) ? " Y  " : " N  ");   //архивный
			ctime_s(buffer, 30, &c_file.time_write);
			printf(" %-12s %.24s  %9ld\n",
				c_file.name, buffer, c_file.size);
		} while (_findnext(hFile, &c_file) == 0);
		_findclose(hFile);
	}
}

//Использование Win32 API
#include <Windows.h>
#include <string.h>
void list_files_and_dirs() {
	char dir[MAX_PATH]; //буфер, в который складываем название файла, задаём ему максимально возможную длину (255)
	strcpy(dir, "./*"); //поиск всех файлов и директорийв текущей директории

	WIN32_FIND_DATAA ffd; //структура, содержащая данные о файле
	HANDLE hFind = FindFirstFileA(dir, &ffd); //функция поиска первого вхождения файла

	if (INVALID_HANDLE_VALUE == hFind) { //проверка на успешность
		printf("Can't open directory: %s\n", dir);
		return;
	}

	do
	{
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			printf("  %32s   <DIR>\n", ffd.cFileName); //если видим директорию
		} else {
			LARGE_INTEGER filesize;
			filesize.LowPart = ffd.nFileSizeLow;
			filesize.HighPart = ffd.nFileSizeHigh;
			printf("  %32s   %lld bytes\n", ffd.cFileName, filesize.QuadPart); //размер файла
		}
	} while (FindNextFileA(hFind, &ffd) != 0); //продвигаемся к следующему включению, если это возможно
}

int main() {
	if (false) io_test();
	if (false) list_files_and_dirs();

	return 0;
}