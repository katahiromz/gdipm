// gdipm.h --- GDI plus minus
// Author: katahiromz
// License: MIT

#pragma once

#define GDIPM_VERSION MAKELONG(1, 4)

#ifdef __cplusplus
extern "C" {
#endif

typedef LPVOID GpBitmap, GpImage;
typedef DWORD ARGB, Color;
typedef float REAL;

enum
{
    AlphaShift = 24,
    RedShift = 16,
    GreenShift = 8,
    BlueShift = 0
};

static __inline ARGB
MakeARGB(BYTE a, BYTE r, BYTE g, BYTE b)
{
    ARGB a0 = a, r0 = r, g0 = g, b0 = b;
    return (a0 << AlphaShift) | (r0 << RedShift) | (g0 << GreenShift) | (b0 << BlueShift);
}

HRESULT gdipm_init_ex(void **pgdipm);
void gdipm_exit_ex(void *gdipm);

#ifdef GDIPM_NO_DPI
    HBITMAP gdipm_load_pic(void *gdipm, const WCHAR *image_filename);
    BOOL gdipm_save_pic(void *gdipm, const WCHAR *image_filename, HBITMAP hBitmap);
#else
    HBITMAP gdipm_load_pic(void *gdipm, const WCHAR *image_filename, float *x_dpi, float *y_dpi);
    BOOL gdipm_save_pic(void *gdipm, const WCHAR *image_filename, HBITMAP hBitmap, float x_dpi, float y_dpi);
#endif

#ifdef __cplusplus
} // extern "C"
#endif
