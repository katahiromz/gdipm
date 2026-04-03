// main.c --- gdi plus minus
// Author: katahiromz
// License: MIT

#include <windows.h>
#include <stdio.h>
#include <wchar.h>
#include "gdipm.h"

void version(void)
{
    puts("gdipm version 1.2");
}

void usage(void)
{
    puts("Usage: gdipm input_image output_image");
}

int wmain(int argc, wchar_t **wargv)
{
    wchar_t *input;
    wchar_t *output;
    void *gdipm;
    GpStatus status;
    HBITMAP hBitmap;
#ifndef GDIPM_NO_DPI
    float x_dpi, y_dpi;
#endif

    if (argc != 3)
    {
        usage();
        return 1;
    }

    input = wargv[1];
    output = wargv[2];

    status = gdipm_init_ex(&gdipm);
    if (status != Ok)
    {
        printf("FAILED: %d\n", status);
        return 1;
    }

    status = GenericError;
#ifdef GDIPM_NO_DPI
    hBitmap = gdipm_load_pic(gdipm, input);
    if (hBitmap)
    {
        if (gdipm_save_pic(gdipm, output, hBitmap))
        {
            status = Ok;
        }
        DeleteObject(hBitmap);
    }
#else
    hBitmap = gdipm_load_pic(gdipm, input, &x_dpi, &y_dpi);
    if (hBitmap)
    {
        if (gdipm_save_pic(gdipm, output, hBitmap, x_dpi, y_dpi))
        {
            status = Ok;
            printf("x_dpi: %f, y_dpi: %f\n", x_dpi, y_dpi);
        }
        DeleteObject(hBitmap);
    }
#endif

    gdipm_exit_ex(gdipm);

    if (status != Ok)
    {
        printf("FAILED: %d\n", status);
        return 1;
    }

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
