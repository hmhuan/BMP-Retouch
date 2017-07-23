#include "init.h"

HANDLE wHnd = GetStdHandle(STD_OUTPUT_HANDLE), rHnd = GetStdHandle(STD_INPUT_HANDLE);
// Nhom ham do hoa Handle
void GotoXY(int x, int y)
{
	COORD Pos_Of_Cur = { x,y };
	SetConsoleCursorPosition(wHnd, Pos_Of_Cur);
}
void SetColor(int color)
{
	CONSOLE_SCREEN_BUFFER_INFO Scr_Buff_Info;
	GetConsoleScreenBufferInfo(wHnd, &Scr_Buff_Info);
	int wAttributes = Scr_Buff_Info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;
	SetConsoleTextAttribute(wHnd, wAttributes);
}
void SetForeGoundColor(int color)
{
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(wHnd, &screen_buffer_info);
	int wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	color <<= 4;
	wAttributes &= 0xff0f;
	wAttributes |= color;

	SetConsoleTextAttribute(wHnd, wAttributes);
}
void ShowCur(bool CursorVisibility)
{
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(wHnd, &cursor);
}
void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}
void cls()
{
	COORD Position;
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(wHnd, Position);
}

//Ham lam tron RGB
unsigned char truncate(float value)
{
	if (value < 0) return 0;
	if (value > 255) return 255;
	return (unsigned char)value;
}

// Nhom ham xu ly trong main

//Nhom Ham nhap xuat file
void ReadFileBMP(FILE *f, BitmapFileHeader &h, BitmapInfoHeader &info, RGBtriple **&p)
{
	fread(&h, sizeof(BitmapFileHeader), 1, f);
	fread(&info, sizeof(BitmapInfoHeader), 1, f);

	int m = info.bHeight, n = info.bWidth;
	p = new RGBtriple*[m];
	for (int i = 0; i < m; i++)
		p[i] = new RGBtriple[n];

	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			fread(&p[i][j], sizeof(RGBtriple), 1, f);
}

void SaveFileBMP(FILE *g, BitmapFileHeader h, BitmapInfoHeader info, RGBtriple **p)
{

	unsigned char temp = 0;
	fwrite(&h, sizeof(BitmapFileHeader), 1, g);
	fwrite(&info, sizeof(BitmapInfoHeader), 1, g);
	int m = info.bHeight, n = info.bWidth;
	int padding = (4 - (n * 3 % 4)) % 4;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			fwrite(&p[i][j], sizeof(RGBtriple), 1, g);
		for (int i = 0; i < padding; i++)
			fwrite(&temp, sizeof(unsigned char), 1, g);
	}	
}

//Ham show thong tin dau PM
void ShowIntro()
{
	ShowCur(false);
	char c = 201;
	cout << c;
	for (int i = 0; i < 100; i++)
	{
		Sleep(10);
		cout << (char)205;
	}
	Sleep(25);
	cout <<(char)187<< endl;
	Sleep(100);
	cout << (char)186 << "			        --TRUONG DAI HOC KHOA HOC TU NHIEN TP.HCM--			     " << (char)186 << endl;
	Sleep(100);
	cout << (char)186 << "				    DO AN GIUA KI MON THUC HANH KTLT				     " << (char)186<< endl;
	Sleep(100);
	cout << (char)186 << "			     Phan mem chinh sua anh Bitmap - Bitmap Editor			     "<<(char)186<<endl;
	Sleep(100);
	cout << (char)186 << "					Lop 16CTT32 - Nhom HTH 					     " << (char)186 << endl;
	Sleep(100);
	cout << (char)186 << "												     " << (char)186 << endl;
	Sleep(100);
	cout << (char)186 << "Danh sach thanh vien nhom :									     " << (char)186 << endl;
	Sleep(100);
	cout << (char)186 << "	1. Huynh Hoang Huy - 1612861 (Leader)							     " << (char)186 << endl;
	Sleep(100);
	cout << (char)186 << "	2. Tran Dang Nhat Tan - 1612889 (Dev 1)							     " << (char)186 << endl;
	Sleep(100);
	cout << (char)186 << "	3. Huynh Minh Huan - 1612858 (Dev 2)							     " << (char)186 << endl;
	Sleep(100);
	cout << (char)186 << "												     " << (char)186 << endl;
	Sleep(100);
	cout << (char)186 << "									Product built by HTH-Team    " << (char)186 << endl;
	Sleep(100);
	cout << (char)200;
	for (int i = 0; i < 100; i++)
	{
		Sleep(10);
		cout << (char)205;
	}
	cout << (char)188 << endl;
	ShowCur(true);
}

//Ham SHow Menu chuc nang
void ShowMenu()
{
	system("cls");
	cout << "--------------------------MENU--------------------------\n";
	cout << "	1. Lat anh theo chieu doc (Flip 180)"<< endl;
	cout << "	2. Lat anh theo chieu ngang (Flip 270)" << endl;
	cout << "	3. Lat anh 90 do sang trai (Flip 90L)" << endl;
	cout << "	4. Lat anh 90 do sang phai (Flip 90R)" << endl;
	cout << "	5. Lam mo anh (Blur Image)" << endl;
	cout << "	6. Chuyen thanh anh xam (GrayScale)" << endl;
	cout << "	7. Chuyen thanh anh trang den (Black-White)" << endl;
	cout << "	8. Tang do sang cho anh (Lighter)"<<endl;
	cout << "	9. Giam do sang cho anh (Darker)" << endl;
	cout << "	10. Tang/Giam do tuong phan (adjust)" << endl;
	cout << "	11. Chuyen mau anh thanh am ban (invert)" << endl;
	cout << "	12. Cat anh (Crop Image)" << endl;
	cout << "	13. Vien khung anh (Border Image)" << endl;
	cout << "	14. Nhan ban anh theo chieu ngang (Dublicate Image horizontal)" << endl;
	cout << "	15. Nhan ban anh theo chieu doc (Dublicate Image vertical)" << endl;
	cout << "	16. Thay doi kich thuoc anh (Resize Image)" << endl;
	cout << "	0. Thoat chuong trinh" << endl;
	cout << "--------------------------------------------------------\n";
}

// Ham Show Anh trong menu chuc nang
void ShowImgToMenu(RGBtriple **p, int m, int n)
{
	HWND myconsole = GetConsoleWindow();
	HDC mydc = GetDC(myconsole);
	for (int i = 0; i<m; i++)
		for (int j = 0; j < n; j++)
		{
			COLORREF COLOR_1 = RGB(p[i][j].B, p[i][j].G, p[i][j].R);
			SetPixel(mydc, j + 20, m - 1 - i + 400, COLOR_1);
		}
	ReleaseDC(myconsole, mydc);
}

//Show Old - new image
void ShowImgToConsole(RGBtriple **p, RGBtriple **q, int m, int n)
{
	system("cls");
	HWND myconsole = GetConsoleWindow();
	HDC mydc = GetDC(myconsole);
	for (int i = 0; i<m; i++)
		for (int j = 0; j < n; j++)
		{
			COLORREF COLOR_1 = RGB(p[i][j].B, p[i][j].G, p[i][j].R);
			COLORREF COLOR_2 = RGB(q[i][j].B, q[i][j].G, q[i][j].R);
			SetPixel(mydc, j + 20, m - 1 - i + 100, COLOR_1);
			SetPixel(mydc, j + n + 50, m - 1 - i + 100, COLOR_2);
		}
	ReleaseDC(myconsole, mydc);
}
//Show Image flip 90
void ShowImgFlip90(RGBtriple **p, RGBtriple **q, int m, int n)
{
	system("cls");
	HWND myconsole = GetConsoleWindow();
	HDC mydc = GetDC(myconsole);
	for (int i = 0; i<m; i++)
		for (int j = 0; j < n; j++)
		{
			COLORREF COLOR_1 = RGB(p[i][j].B, p[i][j].G, p[i][j].R);
			COLORREF COLOR_2 = RGB(q[j][i].B, q[j][i].G, q[j][i].R);
			SetPixel(mydc, j + 20, m - 1 - i + 100, COLOR_1);
			SetPixel(mydc, i + n + 50, m - 1 - j + 100, COLOR_2);
		}
	ReleaseDC(myconsole, mydc);
}
//show Crop image
void ShowCropImg(RGBtriple **p, RGBtriple **q, int m, int n, int m1, int n1)
{
	system("cls");
	HWND myconsole = GetConsoleWindow();
	HDC mydc = GetDC(myconsole);
	for (int i = 0; i<m; i++)
		for (int j = 0; j < n; j++)
		{
			COLORREF COLOR_1 = RGB(p[i][j].B, p[i][j].G, p[i][j].R);
			SetPixel(mydc, j + 20, m - 1 - i + 75, COLOR_1);
			if (i < m1 && j < n1)
			{
				COLORREF COLOR_2 = RGB(q[m1-1-i][j].B, q[m1-1-i][j].G, q[m1-1-i][j].R);
				SetPixel(mydc, n + j + 50, m - 1 - i + 75, COLOR_2);
			}
		}
	ReleaseDC(myconsole, mydc);
}
//show dub image
void ShowDubImg(RGBtriple **p, RGBtriple **q, int m, int n, int m1, int n1)
{
	system("cls");
	HWND myconsole = GetConsoleWindow();
	HDC mydc = GetDC(myconsole);
	for (int i = 0; i<m1; i++)
		for (int j = 0; j < n1; j++)
		{

			if (i < m && j < n)
			{
				COLORREF COLOR_1 = RGB(p[i][j].B, p[i][j].G, p[i][j].R);
				SetPixel(mydc, j + 20, m - 1 - i + 75, COLOR_1);
			}
			COLORREF COLOR_2 = RGB(q[i][j].B, q[i][j].G, q[i][j].R);
			SetPixel(mydc, j + n + 50, m - 1 - i + 75, COLOR_2);
		}
	ReleaseDC(myconsole, mydc);
}

//Nhom ham cac chuc nang cua PM

//1.
void FlipVertical(RGBtriple **p, int m, int n)
{
	char key;
	RGBtriple **q = NULL;
	/*q = (RGBtriple **)malloc(m * sizeof(RGBtriple *));
	for (int i = 0; i < m; i++)
	q[i] = (RGBtriple *)malloc(n * sizeof(RGBtriple));*/
	q = new RGBtriple*[m];
	for (int i = 0; i < m; i++)
		q[i] = new RGBtriple[n];
	for (int i = 0; i< m; i++)
		for (int j = 0; j<n; j++)
			q[m - 1 - i][j] = p[i][j];
	ShowImgToConsole(p, q, m, n);

	cout << "Do you want to save ? (Y/N) : ";
	rewind(stdin);
	cin >> key;
	if (key == 'Y' || key == 'y')
	{
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				p[i][j] = q[i][j];
	}
	for (int i = 0; i < m; i++)
		delete[]q[i];
	delete[]q;
	q = NULL;
}
//2.
void FlipHorizontal(RGBtriple **p, int m, int n)
{
	char key;
	RGBtriple **q = NULL;
	/*q = (RGBtriple **)malloc(m * sizeof(RGBtriple *));
	for (int i = 0; i < m; i++)
	q[i] = (RGBtriple *)malloc(n * sizeof(RGBtriple));*/
	q = new RGBtriple*[m];
	for (int i = 0; i < m; i++)
		q[i] = new RGBtriple[n];
	for (int i = 0; i < m; i++)
		for (int j = n - 1; j >= 0; j--)
			q[i][n - 1 - j] = p[i][j];

	ShowImgToConsole(p, q, m, n);

	cout << "Do you want to save ? (Y/N) : ";
	rewind(stdin);
	cin >> key;
	if (key == 'Y' || key == 'y')
	{
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				p[i][j] = q[i][j];
	}
	for (int i = 0; i < m; i++)
		delete[]q[i];
	delete[]q;
	q = NULL;
}
//3.
void Flip90toLeft(RGBtriple **&p, int &m, int &n)
{
	char key;
	int m1 = n;
	RGBtriple **q = NULL;
	/*q = (RGBtriple **)malloc(n * sizeof(RGBtriple *));
	for (int i = 0; i < n; i++)
	q[i] = (RGBtriple *)malloc(m * sizeof(RGBtriple));*/
	q = new RGBtriple*[n];
	for (int i = 0; i < n; i++)
		q[i] = new RGBtriple[m];
	for (int j = 0; j < n; j++)
		for (int i = m - 1; i >= 0; i--)
			q[j][m - 1 - i] = p[i][j];
	ShowImgFlip90(p, q, m, n);

	cout << "Do you want to save ? (Y/N) : ";
	rewind(stdin);
	cin >> key;
	if (key == 'Y' || key == 'y')
	{
		for (int i = 0; i < m; i++)
			delete[]p[i];
		delete[]p;
		int temp = m; m = n; n = temp;
		/*p = new RGBtriple*[m];
		for (int i = 0; i < n; i++)
		p[i] = new RGBtriple[n];*/
		p = (RGBtriple **)malloc(m * sizeof(RGBtriple *));
		for (int i = 0; i < m; i++)
			p[i] = (RGBtriple *)malloc(n * sizeof(RGBtriple));

		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				p[i][j] = q[i][j];
	}
	for (int i = 0; i < m1; i++)
		delete[]q[i];
	delete[]q;
	q = NULL;
}
//4.
void Flip90toRight(RGBtriple **&p, int &m, int &n)
{
	char key;
	int m1 = n;
	RGBtriple **q = NULL;
	/*q = (RGBtriple **)malloc(n * sizeof(RGBtriple *));
	for (int i = 0; i < n; i++)
	q[i] = (RGBtriple *)malloc(m * sizeof(RGBtriple));*/
	q = new RGBtriple*[n];
	for (int i = 0; i < n; i++)
		q[i] = new RGBtriple[m];
	for (int j = n - 1; j >= 0; j--)
		for (int i = 0; i<m; i++)
			q[n - 1 - j][i] = p[i][j];
	ShowImgFlip90(p, q, m, n);

	cout << "Do you want to save ? (Y/N) : ";
	rewind(stdin);
	cin >> key;
	if (key == 'Y' || key == 'y')
	{
		for (int i = 0; i < m; i++)
			delete[]p[i];
		delete[]p;

		int temp = m; m = n; n = temp;
		/*p = new RGBtriple*[m];
		for (int i = 0; i < n; i++)
		p[i] = new RGBtriple[n];*/
		p = (RGBtriple **)malloc(m * sizeof(RGBtriple *));
		for (int i = 0; i < m; i++)
			p[i] = (RGBtriple *)malloc(n * sizeof(RGBtriple));

		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				p[i][j] = q[i][j];
	}
	for (int i = 0; i < m1; i++)
		delete[]q[i];
	delete[]q;
	q = NULL;
}
//5.
void BlurImg(RGBtriple **&p, int m, int n)
{
	char key;
	RGBtriple **q;
	q = (RGBtriple **)malloc(m * sizeof(RGBtriple *));
	for (int i = 0; i < m; i++)
		q[i] = (RGBtriple *)malloc(n * sizeof(RGBtriple));

	for (int i = 1; i<m - 1; i++)
		for (int j = 1; j < n - 1; j++)
		{
			q[i][j].R = (p[i][j].R + p[i - 1][j - 1].R +
				p[i - 1][j].R + p[i - 1][j + 1].R + p[i][j + 1].R +
				p[i + 1][j + 1].R + p[i + 1][j].R + p[i + 1][j - 1].R + p[i][j - 1].R) / 9;
			q[i][j].G = (p[i][j].G + p[i - 1][j - 1].G +
				p[i - 1][j].G + p[i - 1][j + 1].G + p[i][j + 1].G +
				p[i + 1][j + 1].G + p[i + 1][j].G + p[i + 1][j - 1].G + p[i][j - 1].G) / 9;
			q[i][j].B = (p[i][j].R + p[i - 1][j - 1].B +
				p[i - 1][j].B + p[i - 1][j + 1].B + p[i][j + 1].B +
				p[i + 1][j + 1].B + p[i + 1][j].B + p[i + 1][j - 1].B + p[i][j - 1].B) / 9;
		}
	ShowImgToConsole(p, q, m, n);
	cout << "Do you want to save ? (Y/N) : ";
	rewind(stdin);
	cin >> key;
	if (key == 'Y' || key == 'y')
	{
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				p[i][j] = q[i][j];
	}

	for (int i = 0; i < m; i++)
		delete[]q[i];
	delete[]q;
	q = NULL;
}
//6.
void GrayScale(RGBtriple **&p, int m, int n)
{
	RGBtriple **q = NULL;
	unsigned char _val;
	bool IsSave = false;
	char key;
	/*q = (RGBtriple **)malloc(m * sizeof(RGBtriple*));
	for (int i = 0; i < m; i++)
		q[i] = (RGBtriple *)malloc(n * sizeof(RGBtriple));*/
	q = new RGBtriple*[m];
	for (int i = 0; i < m; i++)
		q[i] = new RGBtriple[n];
	for (int i = 0; i < m; i++)
		for (int j = 0; j<n; j++)
		{
			_val = (p[i][j].R * 0.2126 + p[i][j].G *0.7152 + p[i][j].B*0.0722);
			q[i][j].R = q[i][j].G = q[i][j].B = _val;
		}
	ShowImgToConsole(p,q,m,n);
	cout << "Do you want to save ? (Y/N) : ";
	rewind(stdin);
	cin >> key;
	if (key == 'Y' || key == 'y')
	{
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				p[i][j] = q[i][j];
	}

	for (int i = 0; i < m; i++)
		delete[]q[i];
	delete[]q;
	q = NULL;
}
//7.
void BlackWhite(RGBtriple **p, int m, int n)
{
	unsigned char _val;
	char key;
	RGBtriple **q = NULL;
	/*q = (RGBtriple **)malloc(m * sizeof(RGBtriple *));
	for (int i = 0; i < m; i++)
		q[i] = (RGBtriple *)malloc(n * sizeof(RGBtriple));*/
	q = new RGBtriple*[m];
	for (int i = 0; i < m; i++)
		q[i] = new RGBtriple[n];
	for (int i = 0; i<m; i++)
		for (int j = 0; j < n; j++)
		{
			_val = p[i][j].R * 0.2126 + p[i][j].G *0.7152 + p[i][j].B*0.0722;
			if (_val >= 127)
			{
				q[i][j].R = q[i][j].G = q[i][j].B = 255;
			}
			else
			{
				q[i][j].R = q[i][j].G = q[i][j].B = 0;
			}
		}
	ShowImgToConsole(p, q, m, n);

	cout << "Do you want to save ? (Y/N) : ";
	rewind(stdin);
	cin >> key;
	if (key == 'Y' || key == 'y')
	{
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				p[i][j] = q[i][j];
	}

	for (int i = 0; i < m; i++)
		delete[]q[i];
	delete[]q;
	q = NULL;
}
//8.
void Lightening(RGBtriple **&p, int m, int n)
{
	char key;
	RGBtriple **q = NULL;
	int x;
	float del;
	system("cls");
	cout << "Nhap phan tram tang (10 -> 100) : ";
	cin >> x;
	del = (float)x / 100;
	/*q = (RGBtriple **)malloc(m * sizeof(RGBtriple*));
	for (int i = 0; i < m; i++)
	q[i] = (RGBtriple *)malloc(n * sizeof(RGBtriple));*/
	q = new RGBtriple*[m];
	for (int i = 0; i < m; i++)
		q[i] = new RGBtriple[n];
	for (int i = 0; i<m; i++)
		for (int j = 0; j < n; j++)
		{
			q[i][j].R = (p[i][j].R*(1 - del) / 255 + del) * 255;
			q[i][j].G = (p[i][j].G*(1 - del) / 255 + del) * 255;
			q[i][j].B = (p[i][j].B*(1 - del) / 255 + del) * 255;
		}

	ShowImgToConsole(p, q, m, n);
	cout << "Do you want to save ? (Y/N) : ";
	rewind(stdin);
	cin >> key;
	if (key == 'Y' || key == 'y')
	{
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				p[i][j] = q[i][j];
	}

	for (int i = 0; i < m; i++)
		delete[]q[i];
	delete[]q;
	q = NULL;
}
//9.
void Darkening(RGBtriple **&p, int m, int n)
{
	char key;
	int x;
	float del;
	system("cls");
	cout << "Nhap phan tram giam (10 -> 100) : ";
	cin >> x;
	del = (float)x / 100;
	RGBtriple **q = NULL;
	/*q = (RGBtriple **)malloc(m * sizeof(RGBtriple*));
	for (int i = 0; i < m; i++)
	q[i] = (RGBtriple *)malloc(n * sizeof(RGBtriple));*/
	q = new RGBtriple*[m];
	for (int i = 0; i < m; i++)
		q[i] = new RGBtriple[n];
	for (int i = 0; i<m; i++)
		for (int j = 0; j < n; j++)
		{
			q[i][j].R = (p[i][j].R * (1 - del) / 255) * 255;
			q[i][j].G = (p[i][j].G * (1 - del) / 255) * 255;
			q[i][j].B = (p[i][j].B * (1 - del) / 255) * 255;
		}

	ShowImgToConsole(p, q, m, n);
	cout << "Do you want to save ? (Y/N) : ";
	rewind(stdin);
	cin >> key;
	if (key == 'Y' || key == 'y')
	{
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				p[i][j] = q[i][j];
	}

	for (int i = 0; i < m; i++)
		delete[]q[i];
	delete[]q;
	q = NULL;
}
//10.
void AdjustImage(RGBtriple **p, int m, int n)
{
	char key;
	RGBtriple **q = NULL;
	int contrast;
	system("cls");
	q = new RGBtriple*[m];
	for (int i = 0; i < m; i++)
		q[i] = new RGBtriple[n];

	cout << "Nhap ti le tuong phan contrast (-255 -> 259) : ";
	cin >> contrast;
	float factor = (float)259 * (contrast + 255) / (255 * (259 - contrast));

	for (int i = 0; i<m; i++)
		for (int j = 0; j < n; j++)
		{
			q[i][j].R = truncate((float)(factor * ((float)p[i][j].R - 128) + 128));
			q[i][j].G = truncate((float)(factor * ((float)p[i][j].G - 128) + 128));
			q[i][j].B = truncate((float)(factor * ((float)p[i][j].B - 128) + 128));
		}
	ShowImgToConsole(p, q, m, n);
	cout << factor << endl;
	cout << "Do you want to save ? (Y/N) : ";
	rewind(stdin);
	cin >> key;
	if (key == 'Y' || key == 'y')
	{
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				p[i][j] = q[i][j];
	}

	for (int i = 0; i < m; i++)
		delete[]q[i];
	delete[]q;
	q = NULL;
}
//11.
void InvertColor(RGBtriple **&p, int m, int n)
{
	char key;
	RGBtriple **q = NULL;
	/*q = (RGBtriple **)malloc(m * sizeof(RGBtriple*));
	for (int i = 0; i < m; i++)
		q[i] = (RGBtriple *)malloc(n * sizeof(RGBtriple));*/
	q = new RGBtriple*[m];
	for (int i = 0; i < m; i++)
		q[i] = new RGBtriple[n];
	for (int i = 0; i<m; i++)
		for (int j = 0; j < n; j++)
		{
			q[i][j].R = 255 - p[i][j].R;
			q[i][j].G = 255 - p[i][j].G;
			q[i][j].B = 255 - p[i][j].B;
		}

	ShowImgToConsole(p, q, m, n);
	cout << "Do you want to save ? (Y/N) : ";
	rewind(stdin);
	cin >> key;
	if (key == 'Y' || key == 'y')
	{
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				p[i][j] = q[i][j];
	}
	for (int i = 0; i < m; i++)
		delete[]q[i];
	delete[]q;
	q = NULL;
}
//12.
void CropImage(RGBtriple **&p, int &m, int &n)
{
	system("cls");
	RGBtriple **q = NULL;
	char key;
	cout << m << " " << n << endl;
	int x, y, u, v;
	cout << "Nhap toa do o trai tren va o phai duoi : \n";
	cout << "x1 y1 = ";
	cin >> x >> y; 
	cout << "x2 y2 = ";
	cin >> u >> v;
	while (x < 0 || y < 0 || u <= x || u>m || v <= y || v>n)
	{
		cout << "Vui long nhap (0 <= x1 < x2 <= " << m << ", " << " 0 <= y1 < y2 <= "<< n << ") : ";
		cin >> x >> y >> u >> v;
	}
	int m1 = 0, n1 = 0;
	for (int i = x; i < u; i++)
		m1++;
	for (int i = y; i < v; i++)
		n1++;
	q = (RGBtriple**)malloc(m1 * sizeof(RGBtriple *));
	for (int i = 0; i < m1; i++)
		q[i] = (RGBtriple *)malloc(n1 * sizeof(RGBtriple));
	for (int i = x; i < u; i++)
		for (int j = y; j < v; j++)
			q[i - x][j - y] = p[m-1-i][j];
	ShowCropImg(p, q, m, n, m1, n1);
	cout << "Do you want to save ? (Y/N) : ";
	rewind(stdin);
	cin >> key;
	if (key == 'Y' || key == 'y')
	{
		for (int i = 0; i < m; i++)
			delete[]p[i];
		delete[]p;

		m = m1; n = n1;
		p = (RGBtriple **)malloc(m * sizeof(RGBtriple *));
		for (int i = 0; i < m; i++)
			p[i] = (RGBtriple *)malloc(n * sizeof(RGBtriple));

		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				p[i][j] = q[m-1-i][j];
	}
	for (int i = 0; i < m1; i++)
		delete[]q[i];
	delete[]q;
}
//13.
void BorderImg(RGBtriple **&p, int &m, int &n)
{
	float R, G, B;
	char key;
	system("cls");
	cout << "Nhap R G B : ";
	cin >> B >> G >> R;
	R = truncate(R);
	B = truncate(B);
	G = truncate(G);
	RGBtriple **q = NULL;
	q = (RGBtriple **)malloc(m * sizeof(RGBtriple *));
	for (int i = 0; i < m; i++)
		q[i] = (RGBtriple *)malloc(n * sizeof(RGBtriple));
	for (int j = 0; j < n; j++)
	{
		q[0][j] = q[m - 1][j] = { (unsigned char)R, (unsigned char)G, (unsigned char)B };
		q[1][j] = q[m - 2][j] = { (unsigned char)R, (unsigned char)G, (unsigned char)B };
		q[2][j] = q[m - 3][j] = { (unsigned char)R, (unsigned char)G, (unsigned char)B };
	}
	for (int i = 2; i < m; i++)
	{
		q[i][0] = q[i][n - 1] = { (unsigned char)R, (unsigned char)G, (unsigned char)B };
		q[i][1] = q[i][n - 2] = { (unsigned char)R, (unsigned char)G, (unsigned char)B };
		q[i][2] = q[i][n - 3] = { (unsigned char)R, (unsigned char)G, (unsigned char)B };
	}
	for (int i = 3; i < m - 3; i++)
		for (int j = 3; j < n - 3; j++)
			q[i][j] = p[i][j];
	ShowImgToConsole(p, q, m, n);
	cout << "Do you want to save ? (Y/N) : ";
	rewind(stdin);
	cin >> key;
	if (key == 'Y' || key == 'y')
	{
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				p[i][j] = q[i][j];
	}
	for (int i = 0; i < m; i++)
		delete[]q[i];
	delete[]q;
}
//14.
void DubImgHor(RGBtriple **&p, int &m, int &n)
{

	char key;
	int m1 = m, n1 = n * 2;
	RGBtriple **q = NULL;
	q = (RGBtriple **)malloc(m1 * sizeof(RGBtriple *));
	for (int i = 0; i < m1; i++)
		q[i] = (RGBtriple *)malloc(n1 * sizeof(RGBtriple));
	for (int i = 0; i<m; i++)
		for (int j = 0; j < n; j++)
		{
			q[i][j] = q[i][j + n] = p[i][j];
		}
	ShowDubImg(p, q, m, n, m1, n1);
	cout << "Do you want to save ? (Y/N) : ";
	rewind(stdin);
	cin >> key;
	if (key == 'Y' || key == 'y')
	{
		for (int i = 0; i < m; i++)
			delete[]p[i];
		delete[]p;

		m = m1; n = n1;
		p = (RGBtriple **)malloc(m * sizeof(RGBtriple *));
		for (int i = 0; i < m; i++)
			p[i] = (RGBtriple *)malloc(n * sizeof(RGBtriple));

		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				p[i][j] = q[i][j];
	}
	for (int i = 0; i < m1; i++)
		delete[]q[i];
	delete[]q;
	q = NULL;
}
//15.
void DubImgVer(RGBtriple **&p, int &m, int &n)
{
	char key;
	int m1 = m * 2, n1 = n;
	RGBtriple **q = NULL;
	q = (RGBtriple **)malloc(m1 * sizeof(RGBtriple *));
	for (int i = 0; i < m1; i++)
		q[i] = (RGBtriple *)malloc(n1 * sizeof(RGBtriple));
	for (int i = 0; i<m; i++)
		for (int j = 0; j < n; j++)
		{
			q[i][j] = q[i + m][j] = p[i][j];
		}
	ShowDubImg(p, q, m, n, m1, n1);
	cout << "Do you want to save ? (Y/N) : ";
	rewind(stdin);
	cin >> key;
	if (key == 'Y' || key == 'y')
	{
		for (int i = 0; i < m; i++)
			delete[]p[i];
		delete[]p;

		m = m1; n = n1;
		p = (RGBtriple **)malloc(m * sizeof(RGBtriple *));
		for (int i = 0; i < m; i++)
			p[i] = (RGBtriple *)malloc(n * sizeof(RGBtriple));

		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				p[i][j] = q[i][j];
	}
	for (int i = 0; i < m1; i++)
		delete[]q[i];
	delete[]q;
	q = NULL;
}
//16.
void ResizeImg(RGBtriple **&p, int &m, int &n)
{
	RGBtriple **q = NULL;
	int k;
	char key;
	system("cls");
	cout << "Nhap ti le (x N) : ";
	cin >> k;
	int m1 = m * k, n1 = n * k;
	q = (RGBtriple**)malloc(m1 * sizeof(RGBtriple *));
	for (int i = 0; i < m1; i++)
		q[i] = (RGBtriple *)malloc(n1 * sizeof(RGBtriple));
	int u, v;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
		{
			u = i*k; v = j*k;
			/*for (int k1 = 0; k1 < k; k1++)
				q[u][v + k1] = q[u + k1][v]=q[u+k1][v+k1] = p[i][j];*/
			for (int k1 = u; k1 < u + k; k1++)
				for (int k2 = v; k2 < v + k; k2++)
					q[k1][k2] = p[i][j];
		}
	ShowDubImg(p, q, m, n, m1, n1);

	cout << "Do you want to save ? (Y/N) : ";
	rewind(stdin);
	cin >> key;
	if (key == 'Y' || key == 'y')
	{
		for (int i = 0; i < m; i++)
			delete[]p[i];
		delete[]p;

		m = m1; n = n1;
		p = (RGBtriple **)malloc(m * sizeof(RGBtriple *));
		for (int i = 0; i < m; i++)
			p[i] = (RGBtriple *)malloc(n * sizeof(RGBtriple));

		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				p[i][j] = q[i][j];
	}
	for (int i = 0; i < m1; i++)
		delete[]q[i];
	delete[]q;
	q = NULL;
}







