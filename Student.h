#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#pragma region Default Funtion

struct HocSinh
{
	char maSo[30], hoTen[30];
	double diemToan, diemLy, diemHoa;
};

struct  Node
{
	HocSinh info;
	Node *next;
};

struct List
{
	Node *head, *tail;
};

void NhapHocSinh(HocSinh &);
void XuatHocSinh(HocSinh);

Node *createNode(HocSinh);

void iNit(List &);

bool isEmpty(List l);

void addHead(List &, HocSinh);

void addTail(List &, HocSinh);

void print(List);
void freeList(List &);

#pragma endregion

void ThemTheoThuTu(List &, HocSinh);
void themSaoChuoiXuatHien(List &, HocSinh, char *);
void docFile(ifstream &, List &);
double diemTrungBinh(HocSinh);
char *timHangNhat(List);
HocSinh thongTinHocSinhHang1(List);
void GhiFile(ofstream &, List);

double TimHocSinhDtbThapNhat(List &);

void xoaHocSinhCoDtbX(List &, double );
void xoaHocSinhVoiMSHSChoTruoc(List &, char *);
void capNhatThongTinHocSinh(List ,char *);


void XoaCuoiThemDau(List &);

int menu();

void AppList();