
//Program:
//		This is a graphics frame
//History:
//		2015/12/18		leiyahui/zhouzhiyuan	First release
#include <windows.h>
#include "resource.h"
#include <math.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void paintStraightLine(float x1, float y1, float x2, float y2, HDC hdc, int xianxing, int wide);		//画直线
void paintCircle(float x0, float y0, float r, HDC hdc);		//画圆

#define ID_COMBOBOX 1
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("DrawDialog");
	HWND         hwnd;
	HWND		 hwndComboBox;
	MSG          msg;
	WNDCLASS     wndclass;
	DWORD error;
	char temp[10];
	int i;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = DLGWINDOWEXTRA;    // Note!
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, szAppName);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"),
			szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateDialog(hInstance, szAppName, 0, NULL);
	

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}



LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC dc;
	static HWND hwndComboBox;
	static HWND hwndEdit;
	float ibeginX, ibeginY, iendX, iendY, ilineWidth;		//直线
	float ir, icircleX, icircleY;		//圆
	int index=-1;		//画线的种类
	switch (message)
	{
	case WM_CREATE:
		hwndComboBox = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWN | CBS_HASSTRINGS,
			680, 170, 100,100, hwnd, (HMENU)ID_COMBOBOX, (HINSTANCE)GetWindowLong(hwnd, GWLP_HINSTANCE), NULL);			//创建编辑框
		SendMessage(hwndComboBox, CB_ADDSTRING, 0, (LPARAM)TEXT("实线"));
		SendMessage(hwndComboBox, CB_ADDSTRING, 0, (LPARAM)TEXT("虚线"));
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON1:		//直线
			//获取编辑框的文本
			
			/*GetDlgItemText(hwnd, IDC_RICHEDIT21, (LPTSTR)beginX, 10);
			GetDlgItemText(hwnd, IDC_RICHEDIT22, (LPTSTR)beginY, 10);
			GetDlgItemText(hwnd, IDC_RICHEDIT23, (LPTSTR)endX, 10);
			GetDlgItemText(hwnd, IDC_RICHEDIT24, (LPTSTR)endY, 10);
			GetDlgItemText(hwnd, IDC_RICHEDIT25, (LPTSTR)lineWidth, 10);*/
			
			//获取下拉组合框的文本
			
			//将获取的文本转化问数字
			/*ibeginX = atof((char*)beginX);
			ibeginY = atof((char*)beginY);
			iendX = atof((char*)endX);
			iendY = atof((char*)endY);
			ilineWidth = atof((char*)lineWidth);*/
			ibeginX = GetDlgItemInt(hwnd, IDC_RICHEDIT21, NULL, false);
			ibeginY = GetDlgItemInt(hwnd, IDC_RICHEDIT22, NULL, false);
			iendX = GetDlgItemInt(hwnd, IDC_RICHEDIT23, NULL, false);
			iendY = GetDlgItemInt(hwnd, IDC_RICHEDIT24, NULL, false);
			ilineWidth = GetDlgItemInt(hwnd, IDC_RICHEDIT25, NULL, false);
			index = SendMessage(hwndComboBox, CB_GETCURSEL, 0, 0);
			hwndEdit=GetDlgItem(hwnd, IDC_EDIT1);
			if (ilineWidth==0||index==-1)
			{
				MessageBoxW(hwnd, TEXT("请将直线的参数填满"), NULL, MB_OK);
				break;
			}
			
			dc = GetDC(hwndEdit);
			paintStraightLine(ibeginX, ibeginY, iendX, iendY, dc, index, ilineWidth);		//你只需要把自己写直线的绘图函数加到这里，传进去六个参数，ibeginX(起点X),ibegin(起点Y）,iendX(终点X),iendY(终点Y),index(标明是实线还是虚线,0是实线，1是虚线), dc(绘图句柄),ilineWidth(线宽) 具体的函数调用demo的声明在文件开头，实现在文件最后，你可以参考着进行更改，
			ReleaseDC(hwndEdit,dc);
			break;
		case IDC_BUTTON2:		//圆
			/*GetDlgItemText(hwnd, IDC_RICHEDIT26, (LPWSTR)r, 10);
			GetDlgItemText(hwnd, IDC_RICHEDIT27, (LPWSTR)circleX, 10);
			GetDlgItemText(hwnd, IDC_RICHEDIT28, (LPWSTR)circleY, 10);*/
			/*ir = atof(r);
			icircleX = atof(circleX);
			icircleY = atof(circleY);*/
			icircleY = GetDlgItemInt(hwnd, IDC_RICHEDIT26, NULL, false);
			icircleX = GetDlgItemInt(hwnd, IDC_RICHEDIT27, NULL, false);
			ir = GetDlgItemInt(hwnd, IDC_RICHEDIT28, NULL, false);
			if (ir == 0 )
			{
				MessageBox(hwnd, TEXT("请将圆的参数填满"), NULL, MB_OK);
				break;
			}
			hwndEdit = GetDlgItem(hwnd, IDC_EDIT1);
			dc = GetDC(hwndEdit);
			paintCircle(icircleX, icircleY, ir, dc);				//你只需要把自己写的圆的绘图函数加到这里，传进去四个参数，icircleX(圆心X),icircle(圆心Y),ir(半径),dc(绘图句柄),具体的函数调用demo的声明在文件开头，实现在文件最后，你可以参考着进行更改
			ReleaseDC(hwndEdit, dc);
			break;
		case IDC_BUTTON3:		//清屏
			hwndEdit = GetDlgItem(hwnd, IDC_EDIT1);
			InvalidateRect(hwndEdit,NULL, false);
			break;
		case IDC_BUTTON4:		//退出
			PostQuitMessage(0);
			return 0;
		}
		break;
	case WM_DESTROY:	
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
void paintStraightLine(float x1, float y1, float x2, float y2, HDC hdc, int xianxing, int wide)		//直线绘图函数,这些函数有bug，需要重新更改
{
	float  x, y, dx, dy, d;
	int i = 1;
	x = x1; y = y1; //初始化x，y点
	dx = x2 - x1; dy = y2 - y1;
	d = 2 * dy - dx;
	if (xianxing == 0)  //0表示实线
	{
		while (x<x2)
		{
			if (d >= 0)
			{
				x = x + 1;  y = y + 1; d = d - 2 * (dx - dy);
				SetPixel(hdc, x, y, RGB(255, 0, 0));
			}
			else
			{
				x = x + 1;
				y = y;
				d = d + 2 * dy;
				SetPixel(hdc, x, y, RGB(255, 0, 0));
			}
		}
	}
	else			//否则表示虚线
	{
		while (x<x2)
		{
			if (i%2)
			{
				if (d >= 0)
				{
					x = x + 1;  y = y + 1; d = d - 2 * (dx - dy);
					SetPixel(hdc, x, y, RGB(255, 0, 0));
				}
				else
				{
					x = x + 1;
					y = y;
					d = d + 2 * dy;
					SetPixel(hdc, x, y, RGB(255, 0, 0));
				}
			if (x == x1 + 10 * i)	//当x等于下一段的首个x时i++
					i++;
			}
			else
			{
				if (d >= 0)
				{
					x = x + 1;  y = y + 1; d = d - 2 * (dx - dy);
				}
				else
				{
					x = x + 1;
					y = y;
					d = d + 2 * dy;
				}
				if (x == x1 + 10 * i)	//当x等于下一段的首个x时i++
					i++;

			}

		}
	}
		
}



void paintCircle(float x0, float y0, float r,HDC hdc)
{
	float x, y, f, dU, dD;
	x = x0; y = y0 + r;
	dU = (x + 1 - x0)*(x + 1 - x0) + (y - y0)*(y - y0) - r*r;
	dD = (x + 1 - x0)*(x + 1 - x0) + (y - 1 - y0)*(y - 1 - y0) - r*r;
	f = fabs(dU) - fabs(dD);
	while (x - x0<y - y0)
		if (f >= 0)
		{
			x = x + 1; y = y - 1;
			dU = (x + 1 - x0)*(x + 1 - x0) + (y - y0)*(y - y0) - r*r;
			dD = (x + 1 - x0)*(x + 1 - x0) + (y - 1 - y0)*(y - 1 - y0) - r*r;
			f = fabs(dU) - fabs(dD);

			SetPixel(hdc,x, y, RGB(255, 0, 0));
			SetPixel(hdc,y + x0 - y0, x + y0 - x0, RGB(255, 0, 0));
			SetPixel(hdc,2 * x0 - x, y, RGB(255, 0, 0));
			SetPixel(hdc,x0 - y + y0, x + y0 - x0, RGB(255, 0, 0));
			SetPixel(hdc,x, 2 * y0 - y, RGB(255, 0, 0));
			SetPixel(hdc,y + x0 - y0, y0 - x + x0, RGB(255, 0, 0));
			SetPixel(hdc,2 * x0 - x, 2 * y0 - y, RGB(255, 0, 0));
			SetPixel(hdc,x0 + y0 - y, y0 - x + x0, RGB(255, 0, 0));
		}
		else
		{
			x = x + 1; y = y;
			dU = (x + 1 - x0)*(x + 1 - x0) + (y - y0)*(y - y0) - r*r;
			dD = (x + 1 - x0)*(x + 1 - x0) + (y - 1 - y0)*(y - 1 - y0) - r*r;
			f = fabs(dU) - fabs(dD);

			SetPixel(hdc,x, y, RGB(255, 0, 0));
			SetPixel(hdc,y + x0 - y0, x + y0 - x0, RGB(255, 0, 0));
			SetPixel(hdc,2 * x0 - x, y, RGB(255, 0, 0));
			SetPixel(hdc,x0 - y + y0, x + y0 - x0, RGB(255, 0, 0));
			SetPixel(hdc,x, 2 * y0 - y, RGB(255, 0, 0));
			SetPixel(hdc,y + x0 - y0, y0 - x + x0, RGB(255, 0, 0));
			SetPixel(hdc,2 * x0 - x, 2 * y0 - y, RGB(255, 0, 0));
			SetPixel(hdc,x0 + y0 - y, y0 - x + x0, RGB(255, 0, 0));
		}

}