#include<iostream>
#include<fstream>
#include "init.h"

using namespace std;

void Writting(BitmapFileHeader header, BitmapInfoHeader infoheader)
{
	printf("%d %d %d %d %d\n", header.bType, header.bSize, header.bReserved1, header.bReserved2, header.bOffsets);
	printf("%d %d %d %d\n", infoheader.biSize, infoheader.bPlanes, infoheader.bBitcount, infoheader.bCompression);
	printf("%d %d %d\n", infoheader.bColorUsed, infoheader.bColorImportant, infoheader.bBitcount);
}

int main()
{
	BitmapFileHeader header;
	BitmapInfoHeader infoheader;
	string s;
	FILE *f = NULL, *g = fopen("out.bmp","wb");
	RGBtriple **pix = NULL;
	ShowIntro();
	system("pause");
	system("cls");
	cout << "Enter FileName : ";
	getline(cin, s);
	f = fopen(s.c_str(), "rb");
	while (f == NULL)
	{
		cout << "#Not found@! Please enter exactly path of FileName : ";
		getline(cin, s);
		cout << endl;
		f = fopen(s.c_str(), "rb");
	}

	ReadFileBMP(f,header,infoheader,pix);
	/*fread(&header, sizeof(BitmapFileHeader), 1, f);
	fread(&infoheader, sizeof(BitmapInfoHeader), 1, f);

	pix = (RGBtriple **)malloc(infoheader.bHeight * sizeof(RGBtriple*));
	for (int i = 0; i < infoheader.bHeight; i++)
		pix[i] = (RGBtriple *)malloc(infoheader.bWidth * sizeof(RGBtriple));*/
	/*int m = infoheader.bHeight, n = infoheader.bWidth;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			fread(&pix[i][j], sizeof(RGBtriple), 1, f);*/

	int m = infoheader.bHeight, n = infoheader.bWidth; resizeConsole(m * 8, n * 8);
	unsigned int key;
	//Vong lap chay chuc nang 
	while (true)
	{
		ShowMenu();
		ShowImgToMenu(pix, m, n);
		key = 0;
		cout << "Moi Ban chon chuc nang : ";
		cin >> key;
		switch (key)
		{
		case 1:
			FlipVertical(pix,m,n);
			break;
		case 2:
			FlipHorizontal(pix, m, n);
			break;
		case 3:
			Flip90toLeft(pix, m, n);
			break;
		case 4:
			Flip90toRight(pix, m, n);
			break;
		case 5:
			BlurImg(pix, m, n);
			break;
		case 6:
			GrayScale(pix, m, n);
			break;
		case 7:
			BlackWhite(pix, m, n);
			break;
		case 8:
			Lightening(pix, m, n);
			break;
		case 9:
			Darkening(pix, m, n);
			break;
		case 10:
			AdjustImage(pix, m, n);
			break;
		case 11:
			InvertColor(pix, m, n);
			break;
		case 12:
			CropImage(pix, m, n);
			break;
		case 13:
			BorderImg(pix, m, n);
			break;
		case 14:
			DubImgHor(pix, m, n);
			break;
		case 15:
			DubImgVer(pix, m, n);
			break;
		case 16:
			ResizeImg(pix, m, n);
			break;
		case 0:
			cout << "Bye bye !! See you again.." << endl;
			Sleep(1000);
			break;
		default:
			cout << "#@Error\n";
			Sleep(1000);
			break;
		}
		if (key == 0)
			break;
	}

	//Luu anh ra file moi.
	infoheader.bHeight = m; infoheader.bWidth = n; 
	header.bSize = infoheader.bHeight * infoheader.bWidth*3 + 54;
	SaveFileBMP(g, header, infoheader, pix);

	//Huy ma tran pixel.
	for (int i = 0; i < m; i++)
		delete[]pix[i];
	delete[]pix;

	fclose(f);
	fclose(g);
	return 0;
}