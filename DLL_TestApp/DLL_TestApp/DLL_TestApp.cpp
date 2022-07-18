// DLL_TestApp.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

#include <windows.h>
#include <stdio.h>

#define __DLL_FILE_FULL_PATH__ "DLL_cpp_tools.DLL"

static HINSTANCE g_hCmmLibrary = NULL;

using namespace std;
typedef struct {
	const char* name;
	FARPROC* ptr;
}LIB_FUNCT;

extern bool (_stdcall *ecGn_LoadDevices) (int* ErrCode);

static LIB_FUNCT g_ecSdkFunc[] = {
		{"ecGn_LoadDevice",			(FARPROC*)&ecGn_LoadDevices}
};
bool ecDll_Load(void)
{
	LIB_FUNCT* f;

	if ((g_hCmmLibrary = LoadLibraryA(__DLL_FILE_FULL_PATH__)) == NULL)
		return FALSE;

	f = &g_ecSdkFunc[0];
	while (f->ptr != NULL)
	{
		*(f->ptr) = GetProcAddress((HMODULE)g_hCmmLibrary, f->name);
		if (*(f->ptr) == NULL) {
			//printf("Failed to load \"%s\" Function\n", f->name);
		}
		f++;
	}

	return TRUE;
}

int main()
{
    HMODULE m_handle = LoadLibraryA(__DLL_FILE_FULL_PATH__);

    if (m_handle == NULL) {
        cout << "Hell\n";
    }
    else {
        cout << "Hello World!\n";
    }

    

}
