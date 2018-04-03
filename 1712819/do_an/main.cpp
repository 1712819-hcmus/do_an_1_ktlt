#include<stdio.h>
#include<conio.h>
# include <io.h> 
#include <fcntl.h> 
#include <string.h> 
#include <stdlib.h> 
#include <wchar.h> 
struct sinhvien {
	wchar_t mssv[11];
	wchar_t name[31];
	wchar_t khoa[31];
	wint_t nam;
	wchar_t birth[15];
	wchar_t hinh[15];
	wchar_t mota[1001];
	wchar_t sothich1[1001];
	wchar_t sothich2[1001];
};
typedef struct sinhvien SV;
void main()
{
	FILE *fp;
	fp = _wfopen(L"do_an_1.csv", L" r, ccs = UTF-8 ");
	if (fp == NULL)
		wprintf(L"mo file that bai");
		while (feof(fp)==NULL)
		{
			wchar_t s= fgetwc(fp);
			wprintf(L"%lc", s);
		}
	fclose(fp);
	_getch();
}