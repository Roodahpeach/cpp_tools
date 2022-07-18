#include "cpp_tools.h"

using namespace std;

/// <summary>
/// Log_Add_Quick 사용법에 대한 예제
/// </summary>
void Example_Log_Add_Quick() { 
	cpp_tools cp;
	cp.Init_cpptools("Example_Log_Add_Quick Log"); //cpptools 시작

	cp.Log_Add_Quick("로깅 시작됨.", cp.enum_TimeUnit_sec);
	cout << "apfhadpfahd";
	cp.Log_Add_Quick("Cout 수행", cp.enum_TimeUnit_sec);
	int x = 10 + 10;
	cp.Log_Add_Quick("쓸데없는 연산 수행", cp.enum_TimeUnit_sec);
	cp.Log_Add_Quick("로깅 종료함", cp.enum_TimeUnit_sec);
	cp.End_cpptools();//cpptools 끝
}

void Example_Stopwatch1() {
	cpp_tools cp;
	cp.Init_cpptools("Example_Stopwatch1 Log"); //cpptools 시작

	const int Function_TimeCheck_Index = 0;

	cp.Stopwatch_Check_Startpoint(Function_TimeCheck_Index);
	Sleep(100);
	cp.Stopwatch_Check_Endpoint(Function_TimeCheck_Index);

	cp.Log_Add("Sleep(100)의 수행시간 체크 - ");
	cp.Log_Add_Stopwatch(Function_TimeCheck_Index, cp.enum_TimeUnit_millisec);
	cp.Log_Endline();

	cp.End_cpptools();
}

void Example_INI_File() {
	cpp_tools cp;
	cp.Init_cpptools();

	cp.INIWriteString(L"Test Settings", L"Testvalue", L"1");

	wstring temp = cp.INIReadString(L"Test Settings", L"Testvalue");
	wcout << temp;
	cp.End_cpptools();
}

void Example_FuncLog() {
	cpp_tools cp;

	cp.Init_cpptools();

	cp.FuncLog_Init();
	cp.FuncLog_Add(__FUNCTION__, __FILE__, __LINE__, cp.enum_LogLevel_INFO, "시발");
	cp.FuncLog_Add(__FUNCTION__, __FILE__, __LINE__, cp.enum_LogLevel_INFO, "시발");

}

int main() {
	Example_FuncLog();

	return 0;
}