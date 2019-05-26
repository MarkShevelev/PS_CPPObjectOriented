#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <time.h>

int main(void) {
	struct _finddata_t c_file;
	intptr_t hFile;

	// Find first .c file in current directory
	if ((hFile = _findfirst("*.*", &c_file)) == -1L) //ищет первое вхождение и возвращает handler
		printf("No *.c files in current directory!\n");
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
			ctime_s(buffer, _countof(buffer), &c_file.time_write); //
			printf(" %-12s %.24s  %9ld\n",
				c_file.name, buffer, c_file.size);
		} while (_findnext(hFile, &c_file) == 0);
		_findclose(hFile);
	}
}