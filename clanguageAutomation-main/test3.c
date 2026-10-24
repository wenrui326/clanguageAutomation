#include <windows.h>
#include <stdio.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    POINT pt;
    int lastX = -1, lastY = -1;
    int lastR = -1, lastG = -1, lastB = -1;

    printf("实时鼠标坐标与颜色追踪程序\n");
    printf("按 Ctrl+C 退出程序\n\n");
    printf("刷新期:0.1s\n");

    while (1) {
        // 获取鼠标位置
        GetCursorPos(&pt);

        // 获取屏幕DC并读取像素颜色
        HDC hdc = GetDC(NULL);
        COLORREF color = GetPixel(hdc, pt.x, pt.y);
        ReleaseDC(NULL, hdc);

        int r = GetRValue(color);
        int g = GetGValue(color);
        int b = GetBValue(color);

        // 只在坐标或颜色变化时更新显示
        if (pt.x != lastX || pt.y != lastY || r != lastR || g != lastG || b != lastB) {
            if (color == CLR_INVALID) {
                printf("\r当前坐标: (%4d, %4d)  颜色: 无效      ", pt.x, pt.y);
            } else {
                printf("\r当前坐标: (%4d, %4d)  颜色: R=%3d G=%3d B=%3d", pt.x, pt.y, r, g, b);
            }
            fflush(stdout);//刷新缓冲区，删掉不影响，但影响与其他代码兼容性

            lastX = pt.x;
            lastY = pt.y;
            lastR = r;
            lastG = g;
            lastB = b;
        }

        // 短暂休眠，减少CPU占用
        Sleep(100);
    }
    return 0;
}