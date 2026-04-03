// gdipm.h --- GDI plus minus
// Author: katahiromz
// License: MIT

#pragma once

#define GDIPM_VERSION MAKELONG(1, 5)

#ifdef __cplusplus
extern "C" {
#endif

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
