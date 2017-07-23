#pragma pack(1)
#include<fstream>
#include<iostream>
#include<Windows.h>
#include<ctime>
#include<cstdlib>
#include <cmath>
#include<string>
#include<malloc.h>
#include<stdio.h>

using namespace std;

struct BitmapFileHeader {
	unsigned short bType;
	unsigned int bSize;
	unsigned short bReserved1;
	unsigned short bReserved2;
	unsigned int bOffsets;
};

struct BitmapInfoHeader {
	unsigned int biSize;
	unsigned int bWidth;
	unsigned int bHeight;
	unsigned short bPlanes;
	unsigned short bBitcount;
	unsigned int bCompression;
	unsigned int bSizeImage;
	unsigned int bXPelsPerMeter;
	unsigned int bYPelsPerMeter;
	unsigned int bColorUsed;
	unsigned int bColorImportant;
};

struct RGBtriple {
	unsigned char R, G, B;
};

//Nhom ham do hoa console
void GotoXY(int x, int y);
void SetColor(int color);
void SetForeGoundColor(int color);
void ShowCur(bool CursorVisibility);
void resizeConsole(int width, int height);
void cls();

void ShowIntro();
void ShowMenu();

unsigned char truncate(float value);

void ReadFileBMP(FILE *f,BitmapFileHeader &h, BitmapInfoHeader &info, RGBtriple **&p);
void SaveFileBMP(FILE *g, BitmapFileHeader h, BitmapInfoHeader info, RGBtriple **p);
//Nhom ham show anh ra console
void ShowImgToMenu(RGBtriple **p, int m, int n);
void ShowDubImg(RGBtriple **p, RGBtriple **q, int m, int n, int m1, int n1);
//Show anh luc xoay 90
void ShowImgFlip90(RGBtriple **p, RGBtriple **q, int m, int n);
//Show anh crop
void ShowCropImg(RGBtriple **p, RGBtriple **q, int m, int n, int m1, int n1);
//Show anh to console
void ShowImgToConsole(RGBtriple **p, RGBtriple **q, int m, int n);

// Nhom ham xu ly anh, tinh chinh anh.

//Anh da sac xam
void GrayScale(RGBtriple **&p, int m, int n);
//ANh den trang
void BlackWhite(RGBtriple **p, int m, int n);
//Lat anh chieu doc
void FlipVertical(RGBtriple **p, int m, int n);
//Lat anh chieu ngang
void FlipHorizontal(RGBtriple **p, int m, int n);
//Lam mo anh
void BlurImg(RGBtriple **&p, int m, int n);
//Chuyen mau am ban
void InvertColor(RGBtriple **&p, int m, int n);
//Lam toi anh
void Darkening(RGBtriple **&p, int m, int n);
//Lam sang anh
void Lightening(RGBtriple **&p, int m, int n);
//Xoay anh 90 do sang trai
void Flip90toLeft(RGBtriple **&p, int &m, int &n);
//Xoay anh 90 so sang phai
void Flip90toRight(RGBtriple **&p, int &m, int &n);
//Cat anh theo toa do
void CropImage(RGBtriple **&p, int &m, int &n);
//Tinh chinh do tuong phan
void AdjustImage(RGBtriple **p, int m, int n);
//Tao vien anh
void BorderImg(RGBtriple **&p, int &m, int &n);
//Nhan ban anh
void DubImgVer(RGBtriple **&p, int &m, int &n);
void DubImgHor(RGBtriple **&p, int &m, int &n);
//resize anh
void ResizeImg(RGBtriple **&p, int &m, int &n);