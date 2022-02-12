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

int main() {
	Example_Stopwatch1();
	return 0;
}