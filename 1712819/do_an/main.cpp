﻿#include<stdio.h>
#include<conio.h>
# include <io.h> 
#include <fcntl.h> 
#include <string.h> 
#include <stdlib.h> 
#include <wchar.h> 
struct sinhvien {
	wchar_t *mssv;
	wchar_t *name;
	wchar_t *khoa;
	wchar_t *mail;
	wchar_t *birth;
	wchar_t *hinh;
	wchar_t *mota;
	wchar_t *sothich1;
	wchar_t *sothich2;
};
typedef struct sinhvien SV;
int dem_so_kt_chuoi(FILE* fp)
{
	int i = 0;
	int pos = ftell(fp), a = 0;
	wchar_t c;
	c = fgetwc(fp);
	if (c != L'"')// trường hợp : nội dung1, nội dung 2
	{
		a = 0;
		while (c != L',' && c != '\n')
		{
			c = fgetwc(fp);
			i++;
		}
	}
	else// trường hợp: "nội dung 1","nội dung 2"
	{
		a = 1;
		c = fgetwc(fp);
		while (c != L'"' && c != '\n')
		{
			c = fgetwc(fp);
			i++;
		}
	}
	fseek(fp, pos + a, 0);
	return i;
}
wchar_t* doc_1_tt(FILE* fp)
{
	int a = dem_so_kt_chuoi(fp);
	wchar_t *s = (wchar_t*)malloc((a) * sizeof(wchar_t));
	for (int i = 0; i < a; i++)
	{
		s[i] = fgetwc(fp);
	}
	s[a] = L'\0';
	wchar_t c = fgetwc(fp);
	 if (c == L'\0')
	{
		 int pos = ftell(fp);
		 fseek(fp, pos - 1, 0);
	}
	 if (c == L'"')
		 c = fgetwc(fp);
	return s;
}
void doc_1_sv(FILE* fp, SV& x)
{
	x.mssv = doc_1_tt(fp);
	x.name = doc_1_tt(fp);
	x.khoa = doc_1_tt(fp);
	x.mail = doc_1_tt(fp);
	x.birth = doc_1_tt(fp);
	x.hinh = doc_1_tt(fp);
	x.mota = doc_1_tt(fp);
	x.sothich1 = doc_1_tt(fp);
	x.sothich2 = doc_1_tt(fp);
}
int dem_sv(FILE* fp)
{
	wchar_t s[1600];
	int dem = 0;
	while (feof(fp) == NULL) {
		fgetws(s, 1600, fp);
		dem++;
	}
	return dem - 1;
}
SV* doc_mang_sv(FILE* fp,int &n)
{
	n = dem_sv(fp);
	fseek(fp, 0, 0);
	SV* a =(SV*)malloc(n*sizeof(SV));
	for (int i = 0; i < n; i++)
	{
		doc_1_sv(fp, a[i]);
	}
	fclose(fp);
	return  a;
}
void viet_1_sv_html(FILE* fo,sinhvien x)
{
	fwprintf(fo, L"<!DOCTYPE html PUBLIC \" -//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n");
	fwprintf(fo, L"<html xmlns=\"http://www.w3.org/1999/xhtml\">\n");
	fwprintf(fo, L"<head>\n");
	fwprintf(fo, L"<meta http-equiv=\"Content - Type\" content=\"text / html; charset = utf - 8\" />\n");
	fwprintf(fo, L"<link rel=\"stylesheet\" type=\"text/css\" href=\"personal.css\" />\n");
	fwprintf(fo, L"<title>HCMUS - ");
	fwprintf(fo, x.name);//
	fwprintf(fo, L"</title>\n");
	fwprintf(fo, L"</head>\n");
	fwprintf(fo, L"<body>\n");
	fwprintf(fo, L"<div class=\"Layout_container\">\n");
	fwprintf(fo, L"<!-- Begin Layout Banner Region -->\n");
	fwprintf(fo, L"<div class=\"Layout_Banner\" >\n");
	fwprintf(fo, L"<div><img id=\"logo\" src=\"Images/logo.jpg\" height=\"105\" /></div>\n");
	fwprintf(fo, L"<div class=\"Header_Title\">TRƯỜNG ĐẠI HỌC KHOA HỌC TỰ NHIÊN </div>\n");
	fwprintf(fo, L"</div>\n");
	fwprintf(fo, L"<!-- End Layout Banner Region -->\n");
	fwprintf(fo, L"<!-- Begin Layout MainContents Region -->\n");
	fwprintf(fo, L"<div class=\"Layout_MainContents\">\n");
	fwprintf(fo, L"<!-- Begin Below Banner Region -->\n");
	fwprintf(fo, L"<div class=\"Personal_Main_Information\">\n");
	fwprintf(fo, L"<!-- Begin Thông tin cá nhân c?a th?y cô ----------------------------------------------------------------------------------------- -->\n");
	fwprintf(fo, L"<div class=\"Personal_Location\">\n");
	fwprintf(fo, L"<img src=\"Images/LogoFooter.jpg\" width=\"27\" height=\"33\" />\n");
	fwprintf(fo, L"<span class=\"Personal_FullName\">");
	fwprintf(fo, x.name);//
	fwprintf(fo, L" - ");
	fwprintf(fo, x.mssv);//
	fwprintf(fo, L"</span>\n");
	fwprintf(fo, L"<div class=\"Personal_Department\">KHOA CÔNG NGHỆ THÔNG TIN</div>\n");
	fwprintf(fo, L"<br />\n");
	fwprintf(fo, L"<div class=\"Personal_Phone\">\n");
	fwprintf(fo, L"Email: ");
	fwprintf(fo, x.mail);//
	fwprintf(fo, L"\n");
	fwprintf(fo, L"</div>\n");
	fwprintf(fo, L"<br />\n");
	fwprintf(fo, L"<br /> \n");
	fwprintf(fo, L"</div>\n");
	fwprintf(fo, L"<!-- End Thông tin cá nhân c?a th?y cô ----------------------------------------------------------------------------------------- -->\n");
	fwprintf(fo, L"<div class=\"Personal_HinhcanhanKhung\">\n");
	fwprintf(fo, L"<img src=\"Images/");
	fwprintf(fo, x.hinh);//
	fwprintf(fo, L"\" class=\"Personal_Hinhcanhan\" />\n");
	fwprintf(fo, L"</div>\n");
	fwprintf(fo, L"</div>\n");
	fwprintf(fo, L"<!-- End Below Banner Region -->\n");
	fwprintf(fo, L"<!-- Begin MainContents Region -->\n");
	fwprintf(fo, L"<div class=\"MainContain\">\n");
	fwprintf(fo, L"<!-- Begin Top Region -->\n");
	fwprintf(fo, L"<div class=\"MainContain_Top\">\n");
	fwprintf(fo, L"<div class=\"InfoGroup\">Thông tin cá nhân</div>\n");
	fwprintf(fo, L"<div>\n");
	fwprintf(fo, L"<ul class=\"TextInList\">\n");
	fwprintf(fo, L"<li>Họ và tên: ");
	fwprintf(fo, x.name);//
	fwprintf(fo, L"</li>\n");
	fwprintf(fo, L"<li>MSSV: ");
	fwprintf(fo, x.mssv);//
	fwprintf(fo, L"</li>\n");
	fwprintf(fo, L"<li>Sinh viên khoa ");
	fwprintf(fo, x.khoa);//
	fwprintf(fo, L"</li>\n");
	fwprintf(fo, L"<li>Ngày sinh: ");
	fwprintf(fo, x.birth);//
	fwprintf(fo, L"</li>\n");
	fwprintf(fo, L"<li>Email: ");
	fwprintf(fo, x.mail);//
	fwprintf(fo, L"</li>\n");
	fwprintf(fo, L"</ul>\n");
	fwprintf(fo, L"</div>\n");
	fwprintf(fo, L"<div class=\"InfoGroup\">Sở thích</div>\n");
	fwprintf(fo, L"<div>\n");
	fwprintf(fo, L"<ul class=\"TextInList\">\n");
	fwprintf(fo, L"<li>");
	fwprintf(fo, x.sothich1);//
	fwprintf(fo, L"</li>\n");
	fwprintf(fo, L"<li>");
	fwprintf(fo, x.sothich2);//
	fwprintf(fo, L"</li>\n");
	fwprintf(fo, L"</ul>\n");
	fwprintf(fo, L"</div>\n");
	fwprintf(fo, L"<div class=\"InfoGroup\">Mô tả</div>\n");
	fwprintf(fo, L"<div class=\"Description\">\n");
	fwprintf(fo, x.mota);//
	fwprintf(fo, L"</div>\n");
	fwprintf(fo, L"</div>\n");
	fwprintf(fo, L"</div>\n");
	fwprintf(fo, L"</div>\n");
	fwprintf(fo, L"<!-- Begin Layout Footer -->\n");
	fwprintf(fo, L"<div class=\"Layout_Footer\">\n");
	fwprintf(fo, L"<div class=\"divCopyright\">\n");
	fwprintf(fo, L"<br />\n");
	fwprintf(fo, L"<img src=\"Images/LogoFooter_gray.jpg\" width=\"34\" height=\"41\" /><br />\n");
	fwprintf(fo, L"<br />\n");
	fwprintf(fo, L"@2013</br>\n");
	fwprintf(fo, L"Đồ án giữ kỳ</br>\n");
	fwprintf(fo, L"Kỹ thuật lập trình</br>\n");
	fwprintf(fo, L"TH2012/03</br>\n");
	fwprintf(fo, L"MSSV - Tên sinh viên thực hiện</br>\n");
	fwprintf(fo, L"</div>\n");
	fwprintf(fo, L"</div>\n");
	fwprintf(fo, L"<!-- End Layout Footer -->\n");
	fwprintf(fo, L"</div>\n");
	fwprintf(fo, L"</body>\n");
	fwprintf(fo, L"</html>\n");
	fclose(fo);
}
wint_t WSTRLEN(wchar_t *s)
{
	wint_t dem = 0;
	while (s[dem] != L'\0')
	{
		dem++;
	}
	return dem;
}
wchar_t* ten_file(wchar_t *s1)
{
	wint_t a = WSTRLEN(s1);
	wchar_t *s=new wchar_t[a+5];
	for (wint_t i=0; i < a; i++)
	{
		s[i] = s1[i];
	}
	s[a] = L'.';
	s[a+1] =L'h';
	s[a + 2] =L't';
	s[a + 3] = L'm';
	s[a + 4] = L'l';
	s[a + 5] = L'\0';
	return s;
}
void viet_html(int n,sinhvien* a)
{
	for (int i = 0; i < n; i++)
	{
		FILE *fo;
		wchar_t *s = ten_file(a[i].mssv);
		fo = _wfopen(s, L" w, ccs = UTF-8");
		if (fo == NULL)
			wprintf(L"Mo file %ls that bai",s);
		viet_1_sv_html(fo, a[i]);
	}
}
void main()
{
	_setmode(_fileno(stdout), _O_U16TEXT); 
	_setmode(_fileno(stdin), _O_U16TEXT); 
	FILE *fp;
	fp = _wfopen(L"do_an_ktlt.csv", L" r, ccs = UTF-8");
	if (fp == NULL)
		wprintf(L"Mo file csv that bai \n");
	int n;
	SV* a = doc_mang_sv(fp,n);
	viet_html(n, a);
	free(a);
	_getch();
}