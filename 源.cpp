/**********************************************
文件名称：main.cpp
文件描述：实现简单PS
编译环境：VS2008-VS2017  VC6.0
最后修改：
<2017年12月31日>  <创建工程>
**********************************************/
//像素：图像的最小单位，有单一的颜色纯在
#include<graphics.h>
#include<conio.h>

VOID InitPS();
VOID MaSaiKe(IMAGE*pimg, int tilesize, int startx, int starty);
VOID DiPian(IMAGE*pimg);
//VOID HuiDu();
VOID Gray(IMAGE*pimg);

IMAGE img;

int main()
{
	InitPS();
	TCHAR s[] = _T("选择图片q或w和进行的处理a,b,c:");
	TCHAR d[] = _T("a.马赛克");
	TCHAR f[] = _T("b.底片效果");
	TCHAR g[] = _T("c.灰度效果");
	TCHAR h[] = _T("d.");
	setbkmode(0);
	settextcolor(BLUE);
	outtextxy(200, 150, s);
	outtextxy(250, 200, d);
	outtextxy(250, 250, f);
	outtextxy(250, 300, g);
	outtextxy(250, 350, h);

	switch (_getch())
	{
	case 'a':
	case 'A':
		MaSaiKe(&img, 10, 0, 0);
		break;
	case 'b':
	case 'B':
		DiPian(&img);
		break;
	case 'c':
	case 'C':
		Gray(&img);
		break;
	case 'd':
	case 'D':

		break;

	}
	putimage(0, 0, &img);
	getch();
	return 0;
}

VOID InitPS()
{
	initgraph(640, 480);
	loadimage(&img, L"一天.jpg", 640, 480);
	putimage(0, 0, &img);
}


//马赛克  pimg:图片地址 
//tilesize：小方块的尺寸
//starx，starty：起始坐标
VOID MaSaiKe(IMAGE*pimg, int tilesize, int startx, int starty)
{
	int width = pimg->getwidth();
	int height = pimg->getheight();

	int redsum, greensum, bluesum;

	int count;//每一个小方块中的像素数量
	int color;//每一个像素的颜色
	int x, y, tx, ty;

	DWORD*PMem = GetImageBuffer(pimg);//获取指向显存的指针

	startx = (startx%tilesize == 0 ? 0 : startx%tilesize - tilesize);//0,0
	starty = (starty%tilesize == 0 ? 0 : starty%tilesize - tilesize);

	for (y = starty; y < height; y += tilesize)
	{
		for (x = startx; x < width; x += tilesize)
		{
			redsum = greensum = bluesum = count = 0;
			for (ty = min(y + tilesize, height) - 1; ty >= max(y, 0); ty--)
			{
				for (tx = min(x + tilesize, width) - 1; tx >= max(x, 0); tx--)
				{
					color = PMem[ty*width + tx];
					redsum += GetRValue(color);
					greensum += GetGValue(color);
					bluesum += GetBValue(color);
					count++;
				}
			}
			redsum /= count;
			greensum /= count;
			bluesum /= count;
			bluesum /= count;
			color = RGB(redsum, greensum, bluesum);


			for (ty = min(y + tilesize, height) - 1; ty >= max(y, 0); ty--)
			{
				for (tx = min(x + tilesize, width) - 1; tx >= max(x, 0); tx--)
				{
					PMem[ty*width + tx] = color;
				}
			}
		}
	}

	_getch();
}

VOID DiPian(IMAGE*pimg)
{
	DWORD *pMem = GetImageBuffer(pimg);
	for (int i = pimg->getwidth()*pimg->getheight() - 1; i >= 0; i--)
	{
		pMem[i] = (~pMem[i]) & 0x00FFFFFF;
	}
}



/*
Gray=R*0.299+G*0.587+B*0.114
Gray=(R*299+G*587+B*114)/1000
*/
VOID Gray(IMAGE*pimg)
{
	DWORD *pMem = GetImageBuffer(pimg);
	COLORREF c;
	for (int i = pimg->getwidth()*pimg->getheight() - 1; i >= 0; i--)
	{
		c = pMem[i];
		//pMem[i] = (GetRValue(c) * 0.299 + GetGValue(c) * 0.587 + GetBValue(c) * 0.114);
		pMem[i] = (GetRValue(c) * 30 + GetGValue(c) * 59 + GetBValue(c) * 11 + 50) / 100;
	}
}
