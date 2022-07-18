#include "cpp_tools.h"

using namespace std;

/// <summary>
/// Log_Add_Quick ������ ���� ����
/// </summary>
void Example_Log_Add_Quick() { 
	cpp_tools cp;
	cp.Init_cpptools("Example_Log_Add_Quick Log"); //cpptools ����

	cp.Log_Add_Quick("�α� ���۵�.", cp.enum_TimeUnit_sec);
	cout << "apfhadpfahd";
	cp.Log_Add_Quick("Cout ����", cp.enum_TimeUnit_sec);
	int x = 10 + 10;
	cp.Log_Add_Quick("�������� ���� ����", cp.enum_TimeUnit_sec);
	cp.Log_Add_Quick("�α� ������", cp.enum_TimeUnit_sec);
	cp.End_cpptools();//cpptools ��
}

void Example_Stopwatch1() {
	cpp_tools cp;
	cp.Init_cpptools("Example_Stopwatch1 Log"); //cpptools ����

	const int Function_TimeCheck_Index = 0;

	cp.Stopwatch_Check_Startpoint(Function_TimeCheck_Index);
	Sleep(100);
	cp.Stopwatch_Check_Endpoint(Function_TimeCheck_Index);

	cp.Log_Add("Sleep(100)�� ����ð� üũ - ");
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
	cp.FuncLog_Add(__FUNCTION__, __FILE__, __LINE__, cp.enum_LogLevel_INFO, "�ù�");
	cp.FuncLog_Add(__FUNCTION__, __FILE__, __LINE__, cp.enum_LogLevel_INFO, "�ù�");

}

int main() {
	Example_FuncLog();

	return 0;
}