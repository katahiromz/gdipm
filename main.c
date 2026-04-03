// main.c --- gdi plus minus
// Author: katahiromz
// License: MIT

#include <windows.h>
#include <stdio.h>
#include <wchar.h>
#include "gdipm.h"

void version(void)
{
    puts("gdipm version 1.6");
}

void usage(void)
{
    puts("Usage: gdipm input_image output_image");
}

void show_info(PBITMAP pbm)
{
    printf("bmWidth: %ld\n", pbm->bmWidth);
    printf("bmHeight: %ld\n", pbm->bmHeight);
    printf("bmBitsPixel: %d\n", pbm->bmBitsPixel);
}

int wmain(int argc, wchar_t **wargv)
{
    wchar_t *input;
    wchar_t *output;
    void *gdipm;
    BOOL result = FALSE;
    HBITMAP hBitmap;
#ifndef GDIPM_NO_DPI
    float x_dpi, y_dpi;
#endif
    const ARGB back_color = MakeARGB(0xFF, 0xFF, 0xFF, 0xFF);

    if (argc != 3)
    {
        usage();
        return 1;
    }

    input = wargv[1];
    output = wargv[2];

    if (gdipm_init_ex(&gdipm) != S_OK)
    {
        printf("FAILED: gdipm_init_ex\n");
        return 1;
    }

#ifdef GDIPM_NO_DPI
    hBitmap = gdipm_load_pic(gdipm, input, back_color);
#else
    hBitmap = gdipm_load_pic(gdipm, input, back_color, &x_dpi, &y_dpi);
#endif

    if (hBitmap)
    {
        BITMAP bm;
        GetObjectW(hBitmap, sizeof(bm), &bm);
        show_info(&bm);

        result = gdipm_save_pic(gdipm, output, hBitmap, x_dpi, y_dpi);
        DeleteObject(hBitmap);
    }

    gdipm_exit_ex(gdipm);

    if (!result)
    {
        puts("FAILED");
        return 1;
    }

#ifndef GDIPM_NO_DPI
    printf("x_dpi: %f, y_dpi: %f\n", x_dpi, y_dpi);
#endif
    puts("Success!");
    return 0;
}

int main(void)
{
    int argc;
    LPWSTR* wargv = CommandLineToArgvW(GetCommandLineW(), &argc);
    int ret = wmain(argc, wargv);
    LocalFree(wargv);
    return ret;
}
