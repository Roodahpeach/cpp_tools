#pragma once


#ifdef CREATEDLL_EXPORTS
#define MYMATH_DECLSPEC __declspec(dllexport)
#else
#define CPP_TOOLS_DECLSPEC __declspec(dllimport)
#endif

extern "C" CPP_TOOLS_DECLSPEC double Sum(double a, double b);
extern "C" CPP_TOOLS_DECLSPEC double Sub(double a, double b);
extern "C" CPP_TOOLS_DECLSPEC double Mul(double a, double b);
extern "C" CPP_TOOLS_DECLSPEC double Div(double a, double b);