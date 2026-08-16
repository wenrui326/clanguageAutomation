#include <windows.h>

int main(void)
{
    HDC hdc = GetDC(NULL);
    if (hdc) {
        for (int y = 0; y < 300; ++y)
            for (int x = 0; x < 300; ++x)
                SetPixel(hdc, x, y, RGB(255, 0, 0));
    }
	ReleaseDC(NULL, hdc);

    MessageBoxW(NULL,
                L"已绘制 20x20 红块。查看桌面后点确定退出。",
                L"提示",
                MB_OK);
    return 0;
}