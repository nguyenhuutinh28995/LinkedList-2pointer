#include "Student.h"

#pragma region Default Funtion

Node *createNode(HocSinh hs)
{
	Node *p = new Node;
	if(p)
	{
		p ->info = hs;
		p->next = NULL;
	}
	return p;
}

void iNit(List &l)
{
	l.head = l.tail = NULL;
}

void NhapHocSinh(HocSinh &hs)
{
	cout << "\n Nhap vao ma so hoc sinh : ";
	fflush(stdin);
	gets(hs.maSo);

	cout << "\n Nhap vao ho ten hoc sinh : ";
	fflush(stdin);
	gets(hs.hoTen);

	cout << "\nNhap vao diem Toan : ";
	cin >> hs.diemToan;
	cout << "\nNhap vao diem Ly : ";
	cin >> hs.diemLy;
	cout << "\nNhap vao diem Hoa : ";
	cin >> hs.diemHoa ;
}

void XuatHocSinh( HocSinh hs)
{
	cout << "\n Ma So Hoc Sinh : " << hs.maSo
		<< "\n Ho Ten Hoc Sinh : " << hs.hoTen
		<<"\n Diem Toan : " << hs.diemToan
		<<"\n Diem Ly : " << hs.diemLy
		<<"\n Diem Hoa : " << hs.diemHoa;
}

bool isEmpty(List l)
{
	return l.head == NULL;
}

void addHead(List &l, HocSinh hs)
{
	Node *p = createNode(hs);
	if(isEmpty(l))
		l.tail = p;
	else 
		p ->next = l.head;
	l.head = p;
}

void addTail(List &l, HocSinh hs)
{
	Node *p = createNode(hs);
	if(isEmpty(l))
		l.head = p;
	else 
		l.tail ->next = p;
	l.tail = p;
}

void ThemTheoThuTu(List &l, HocSinh hs)
{
	if((l.head == NULL) || (strcmp(hs.maSo,l.head->info.maSo) == -1) )
		addHead(l,hs);
	else if((strcmp(hs.maSo,l.tail->info.maSo) == 1))
		addTail(l, hs);
	else
	{
		for(Node *p = l.head; p != NULL; p = p ->next)
		{
			if((strcmp(hs.maSo,p->info.maSo) == 1) && (strcmp(hs.maSo,p->next->info.maSo) == -1 ))
			{
				Node * k = createNode(hs);
					k ->next = p->next;
					p->next = k;
			}	
		}
	}
}

void print(List l)
{
	if(l.head == NULL)
	{
		cout << "\n Danh Sach Lop Rong !!!";
		return ;
	}
	for(Node *p = l.head; p != NULL; p = p->next)
	{
		cout << "\n-------------Thong Tin Hoc Sinh-------------\n";
		XuatHocSinh(p->info);
	}
}

void freeList(List &l)
{
	Node *p;
	while(l.head != NULL)
	{
		p = l.head;
		l.head = l.head ->next;
		delete p;
	}
	if(l.head == NULL)
		cout << "\nDa Xoa Xong Danh Sach !!";
}

#pragma endregion

void themSaoChuoiXuatHien(List &l, HocSinh hs, char *str)
{
	for(Node *p = l.head; p != NULL; p = p->next)
	{
		if(strstr(p->info.maSo, str))
		{
			NhapHocSinh(hs);
			if(p == l.tail)
				addTail(l,hs);
			else
			{
				Node *k = createNode(hs);
				k ->next = p ->next;
				p->next = k;
				return ;
			}
		}
	}
	cout << "\n khong co chuoi str trong danh sach ";
}

void docFile(ifstream &fileIn, List &l)
{
	fileIn.open("INPUT.txt",ios::in);
	HocSinh hs;
	while (!fileIn.eof())
	{
		fileIn >> hs.maSo;
		fileIn.seekg(2,1);
		fileIn.getline(hs.hoTen,30,'-');
		fileIn >> hs.diemToan >> hs.diemLy >> hs.diemHoa;
		ThemTheoThuTu(l, hs);
	}
	fileIn.close();
}

double diemTrungBinh(HocSinh hs)
{
	return (hs.diemToan + hs.diemLy +hs.diemHoa)/3;
}

char *timHangNhat(List l)
{
	Node *p = l.head;
	char ten[30];
	double max = diemTrungBinh(p->info);
	strcpy(ten,p->info.hoTen);
	double dtb;
	
	for(p = l.head ->next; p != NULL; p = p->next)
	{
		dtb = diemTrungBinh(p->info);
		if(dtb > max)
		{
			max = dtb;
			strcpy(ten,p->info.hoTen);

		}
	}
	return ten;
}

HocSinh thongTinHocSinhHang1(List l)
{
	Node *p = l.head;
	HocSinh hs;
	double max = diemTrungBinh(p->info);
	double dtb;
	for(p = l.head ->next; p != NULL; p = p->next)
	{
		dtb = diemTrungBinh(p->info);
		if(dtb > max)
		{
			max = dtb;
			hs = p->info;
		}
	}
	return hs;
}

void GhiFile(ofstream &fileOut, List l)
{
	fileOut.open("OUTPUT.TXT");
	HocSinh hs;
	hs = thongTinHocSinhHang1(l);
	fileOut << hs.maSo << " -" << hs.hoTen << "- " 
		<< hs.diemToan <<" " << hs.diemLy << " " << hs.diemHoa ;
	fileOut.close();
}

double TimHocSinhDtbThapNhat(List &l)
{
	double min = diemTrungBinh(l.head->info);
	for(Node *p = l.head->next; p != NULL; p  = p->next)
	{
		if(diemTrungBinh(p->info) < min)
			min = diemTrungBinh(p->info);
	}
	return min;
}

void xoaHocSinhCoDtbX(List &l, double x)
{
	Node *truoc = l.head; // Node truoc p;
	for(Node *p = l.head ->next; p != NULL; p = p->next)
	{

		if(x == diemTrungBinh(p->info))
		{

			if(p == l.tail) // x o cuoi danh sach
			{
				truoc ->next = NULL;
				l.tail = truoc;
			}
			else // x o vi tri bat ki
				truoc ->next = p->next;
			delete p;
			p = truoc;
		}
		truoc = p;
	}

	if(x == diemTrungBinh(l.head->info)) // xoa x  khi x = l.head va x == l.head == l.tail
	{
		Node *p = l.head;
		if(x == diemTrungBinh(l.tail ->info))
			l.head = l.tail = NULL;
		else
			l.head = l.head ->next;
		delete p;
	}
}

void xoaHocSinhVoiMSSVChoTruoc(List &l, char *str)
{
	Node *q;
	for(Node *p = l.head; p != NULL; p = p->next)
	{
		if(strcmp(p->info.maSo,str) == 0)
		{
			if(p == l.head)
				l.head = l.head ->next;
			else if(p == l.tail)
			{
				l.tail = q;
				q ->next = NULL;
			}
			else
				q ->next = p->next;
			delete p;
			return;
		}
		q = p;
	}
}

void capNhatThongTinHocSinh(List l,char *str)
{
	for(Node *p = l.head; p != NULL; p = p->next)
	{
		if(strcmp(p->info.maSo,str) == 0)
		{
			cout << "\ncap nhat lai ten hoc sinh : ";
			fflush(stdin);
			gets(p->info.hoTen);
			cout << "\n cap nhat lai diem Toan : ";
			cin >> p->info.diemToan;
			cout << "\n cap nhat lai diem Ly : ";
			cin >> p->info.diemLy;
			cout << "\n cap nhat lai diem Hoa : ";
			cin >> p->info.diemHoa;
			return;

		}
	}

}


void XoaCuoiThemDau(List &l)
{
	HocSinh hs;
	Node *q;
	if(l.head == NULL)
		cout << "\nKhong Co Lam Sao Xoa ";
	else if(l.head == l.tail)
		cout << "\n Danh Sach chi co 1 phan tu khong lam dc chuyen nay ";
	else
	{
		for(Node *p = l.head; p != NULL; p = p->next)
		{
			if(p == l.tail)
			{
				hs = p->info;
				q ->next = NULL;
				l.tail = q;
				delete p;
				addHead(l,hs);
				return;
			}
			q = p;
		}
	}
}

int menu()
{
	cout << "\n\n-------------------Menu-------------------\n\n"
	   	<<"1. Khoi Tao Danh Sach Rong\n"
		<<"2. Kiem tra danh sach \n"
		<<"3. Them vao dau danh sach \n"
		<<"4. Them vao cuoi danh sach \n"
		<<"5. Them phan tu vao theo thu tu \n"
		<<"6. Doc file \n"
		<<"7. Tim Hoc Sinh Xep Hang 1. Chon 1 Xuat ra ten, Chon 2 Xuat ra Tat Ca Thong Tin \n"
		<<"8. Tim Hoc Sinh Xep Hang Thu k \n"
		<<"9. In Danh sach \n"
		<<"10. Them Hoc Sinh Vao Sau Chuoi Con Co Xuat Hien \n"
		<<"11. Lay Hoc Sinh Cuoi Them Vao Dau \n"
		<<"12. Ghi Thong tin hoc sinh nhat lop ra file \n"
		<< "13. Tim Hoc Sinh Co Diem Trung Binh Thap Nhat \n"
		<< "14. Xoa Hoc Sinh Co Diem Trung Binh x  \n"
		<< "15. Xoa Hoc Sinh Voi MSSV x  \n"
		<< "16. Cap Nhat Diem Hoc Sinh Voi MSSV x  \n"
		<<"0.Thoat va huy danh sach \n"
		 << "\n------------------------------------------\n";
	int chon;
	cout <<"\n Nhap vao lua chon : ";
	cin >>chon;
	return chon;
}

void AppList()
{
	List l;
	iNit(l);
	HocSinh hs;
	while(1)
	{
		int chon = menu();
		switch (chon)
		{
		#pragma region case 1- 7

		case 1:
			{
				iNit(l);
				if(l.head == NULL)
					cout << "\nKhoi Tao Danh Sach Thanh Cong ";
				break;
			}
		case 2:
			{
				if(isEmpty(l))
					cout << "\nDanh Sach Rong !!";
				else
					cout << "\nDanh Sach Da co Phan Tu !!";
				break;
			}
		case 3:
			{
				NhapHocSinh(hs);
				addHead(l, hs);
				break;
			}
		case 4:
			{
				NhapHocSinh(hs);
				addTail(l, hs);
				break;
			}
		case 5:
			{
				NhapHocSinh(hs);
				ThemTheoThuTu(l, hs);
				break;
			}
		case 6:
			{
				ifstream fileIn;
				docFile(fileIn, l);
				break;
			}
		case 7:
			{
				cout << "\n Nhap vao lua chon xem thong tin cua ban : ";
				int luachon;
				cin >> luachon;
				if(luachon == 1)
				{
					cout <<"\n Ten Hoc Sinh Hang 1 la :\n";
					char ten[30];
					strcpy(ten,timHangNhat(l));
					cout << ten;
				}
				else if(luachon == 2)
				{
					cout <<"\n Thong Tin Hoc Sinh Hang 1 la  : ";
					XuatHocSinh(thongTinHocSinhHang1(l));
				}
				break;
			}
		#pragma endregion 
		
		#pragma region case 8 - 14
		case 8:
			{

			}
		case 9:
			{
				cout << "\n -----------Danh Sach Hoc Sinh----------- ";
				print(l);
				break;
			}
		case 10 :
			{
				cout << "\n Nhap vao chuoi con can them : ";
				char str[10];
				fflush(stdin);
				gets(str);
				themSaoChuoiXuatHien(l, hs, str);
				break;
			}
		case 11:
			{
				XoaCuoiThemDau(l);
				break;
			}
		case 12:
			{
				ofstream fileOut;
				GhiFile(fileOut,l);
				break;
			}
		case 13:
			{
				cout <<"\n diem trung binh thap nhat la : "
					 << TimHocSinhDtbThapNhat(l);				
				break;
			}
		case 14:
			{
				cout << "\nNhap vao diem ban muon xoa  : ";
				double x;
				cin >> x;
				xoaHocSinhCoDtbX(l, x);
				break;
			}
		#pragma endregion
		case 15:
			{
				cout << "\n Nhap MSHS cua hoc sinh muon xoa : ";
				char str[30];
				fflush(stdin);
				gets(str);
				xoaHocSinhVoiMSSVChoTruoc(l,str);
				break;
			}
		case 16 :
			{
				cout << "\n Nhap MSHS cua hoc sinh muon thay doi thong tin : ";
				char str[30];
				fflush(stdin);
				gets(str);
				capNhatThongTinHocSinh(l, str);
				break;
			}
		case 0:
			{
				freeList(l);
				return;
			}
		default:
			{
					cout << "\nLua Chon khong hop le !!";
					break;
			}
		}
	}
}