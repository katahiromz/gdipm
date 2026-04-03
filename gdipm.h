// gdipm.h --- GDI plus minus
// Author: katahiromz
// License: MIT

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef enum GpStatus
{
    Ok = 0,
    GenericError = 1,
    InvalidParameter = 2,
    OutOfMemory = 3,
    ObjectBusy = 4,
    InsufficientBuffer = 5,
    NotImplemented = 6,
    Win32Error = 7,
    WrongState = 8,
    Aborted = 9,
    FileNotFound = 10,
    ValueOverflow = 11,
    AccessDenied = 12,
    UnknownImageFormat = 13,
    FontFamilyNotFound = 14,
    FontStyleNotFound = 15,
    NotTrueTypeFont = 16,
    UnsupportedGdiplusVersion = 17,
    GdiplusNotInitialized = 18,
    PropertyNotFound = 19,
    PropertyNotSupported = 20,
    ProfileNotFound = 21
} GpStatus;

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

GpStatus gdipm_init_ex(void **pgdipm);
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
