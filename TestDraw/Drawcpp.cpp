
//Program:
//		This is a graphics frame
//History:
//		2015/12/18		leiyahui/zhouzhiyuan	First release
#include <windows.h>
#include "resource.h"
#include <math.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void paintStraightLine(float x1, float y1, float x2, float y2, HDC hdc, int xianxing, int wide);		//��ֱ��
void paintCircle(float x0, float y0, float r, HDC hdc);		//��Բ

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
	float ibeginX, ibeginY, iendX, iendY, ilineWidth;		//ֱ��
	float ir, icircleX, icircleY;		//Բ
	int index=-1;		//���ߵ�����
	switch (message)
	{
	case WM_CREATE:
		hwndComboBox = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWN | CBS_HASSTRINGS,
			680, 170, 100,100, hwnd, (HMENU)ID_COMBOBOX, (HINSTANCE)GetWindowLong(hwnd, GWLP_HINSTANCE), NULL);			//�����༭��
		SendMessage(hwndComboBox, CB_ADDSTRING, 0, (LPARAM)TEXT("ʵ��"));
		SendMessage(hwndComboBox, CB_ADDSTRING, 0, (LPARAM)TEXT("����"));
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON1:		//ֱ��
			//��ȡ�༭����ı�
			
			/*GetDlgItemText(hwnd, IDC_RICHEDIT21, (LPTSTR)beginX, 10);
			GetDlgItemText(hwnd, IDC_RICHEDIT22, (LPTSTR)beginY, 10);
			GetDlgItemText(hwnd, IDC_RICHEDIT23, (LPTSTR)endX, 10);
			GetDlgItemText(hwnd, IDC_RICHEDIT24, (LPTSTR)endY, 10);
			GetDlgItemText(hwnd, IDC_RICHEDIT25, (LPTSTR)lineWidth, 10);*/
			
			//��ȡ������Ͽ���ı�
			
			//����ȡ���ı�ת��������
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
				MessageBoxW(hwnd, TEXT("�뽫ֱ�ߵĲ�������"), NULL, MB_OK);
				break;
			}
			
			dc = GetDC(hwndEdit);
			paintStraightLine(ibeginX, ibeginY, iendX, iendY, dc, index, ilineWidth);		//��ֻ��Ҫ���Լ�дֱ�ߵĻ�ͼ�����ӵ��������ȥ����������ibeginX(���X),ibegin(���Y��,iendX(�յ�X),iendY(�յ�Y),index(������ʵ�߻�������,0��ʵ�ߣ�1������), dc(��ͼ���),ilineWidth(�߿�) ����ĺ�������demo���������ļ���ͷ��ʵ�����ļ��������Բο��Ž��и��ģ�
			ReleaseDC(hwndEdit,dc);
			break;
		case IDC_BUTTON2:		//Բ
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
				MessageBox(hwnd, TEXT("�뽫Բ�Ĳ�������"), NULL, MB_OK);
				break;
			}
			hwndEdit = GetDlgItem(hwnd, IDC_EDIT1);
			dc = GetDC(hwndEdit);
			paintCircle(icircleX, icircleY, ir, dc);				//��ֻ��Ҫ���Լ�д��Բ�Ļ�ͼ�����ӵ��������ȥ�ĸ�������icircleX(Բ��X),icircle(Բ��Y),ir(�뾶),dc(��ͼ���),����ĺ�������demo���������ļ���ͷ��ʵ�����ļ��������Բο��Ž��и���
			ReleaseDC(hwndEdit, dc);
			break;
		case IDC_BUTTON3:		//����
			hwndEdit = GetDlgItem(hwnd, IDC_EDIT1);
			InvalidateRect(hwndEdit,NULL, false);
			break;
		case IDC_BUTTON4:		//�˳�
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
void paintStraightLine(float x1, float y1, float x2, float y2, HDC hdc, int xianxing, int wide)		//ֱ�߻�ͼ����,��Щ������bug����Ҫ���¸���
{
	float  x, y, dx, dy, d;
	int i = 1;
	x = x1; y = y1; //��ʼ��x��y��
	dx = x2 - x1; dy = y2 - y1;
	d = 2 * dy - dx;
	if (xianxing == 0)  //0��ʾʵ��
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
	else			//�����ʾ����
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
			if (x == x1 + 10 * i)	//��x������һ�ε��׸�xʱi++
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
				if (x == x1 + 10 * i)	//��x������һ�ε��׸�xʱi++
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