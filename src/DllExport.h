#ifndef _DLL_EXPORT_H_
#define _DLL_EXPORT_H_
#if (defined NDEBUG)
#define WNDLIB_USEDLL 0
#else
#define WNDLIB_USEDLL 1
#endif

#ifdef WNDLIB_EXPORT
#undef WNDLIB_EXPORT
#endif

#if WNDLIB_USEDLL
#ifdef _WNDLIB
#define WNDLIB_EXPORT __declspec(dllexport)
#else
#define WNDLIB_EXPORT __declspec(dllimport)
#endif
#else
#define WNDLIB_EXPORT
#endif

#ifdef _MSC_VER
#pragma warning(disable: 4251)
#endif

#endif
