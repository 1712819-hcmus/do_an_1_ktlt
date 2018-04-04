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
	int nam;
	wchar_t birth[15];
	wchar_t hinh[15];
	wchar_t mota[1001];
	wchar_t sothich1[1001];
	wchar_t sothich2[1001];
};
typedef struct sinhvien SV;
wchar_t* doc_1_tt(wchar_t *s,FILE* fp)
{
	int i = 0;
	wchar_t c='c';
	while (c!= ',')
	{
		c =fgetwc(fp);
		s[i]= c;
		i++;
	}
	s[i-1] = L'\0';
	return s;
}
void doc_1_sv(FILE* fp, SV& x)
{
	doc_1_tt(x.mssv, fp);
	doc_1_tt(x.name, fp);
	doc_1_tt(x.khoa, fp);
	fwscanf(fp, L"%d", &x.nam);
	fflush(fp);
	wchar_t ch = fgetwc(fp);
	doc_1_tt(x.birth, fp);
	doc_1_tt(x.hinh, fp);
	doc_1_tt(x.mota, fp);
	doc_1_tt(x.sothich1, fp);
	fgetws(x.sothich2, 1001, fp);
}
void main()
{
	_setmode(_fileno(stdout), _O_U16TEXT); 
	_setmode(_fileno(stdin), _O_U16TEXT); 
	FILE *fp;
	fp = _wfopen(L"do_an_ktlt.csv", L" r, ccs = UTF-8");
	if (fp == NULL)
		wprintf(L"mo file that bai");
	SV a;
	doc_1_sv(fp, a);
	wprintf(L"%ls", a.mssv);
	wprintf(L"%ls", a.name);
	wprintf(L"%ls", a.khoa);
	wprintf(L"%d", a.nam);
	wprintf(L"%ls", a.birth);
	wprintf(L"%ls", a.hinh);
	wprintf(L"%ls", a.mota);
	wprintf(L"%ls", a.sothich1);
	wprintf(L"%ls", a.sothich2);
	fclose(fp);
	_getch();
}