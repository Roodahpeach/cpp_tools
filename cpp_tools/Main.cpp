#include "cpp_tools.h"

using namespace std;

int main() { //기능 테스트용 메인
	cpp_tools cp;

	cp.Stopwatch_Check_Startpoint();
	cp.Init_cpptools();
	cp.Stopwatch_Check_Startpoint(3);
	cp.Log_Add("Yeah");
	cp.Log_Add(to_string(123));
	cp.Log_Add("df");
	cp.Log_Endline();
	cp.Log_Add("Yeah12");
	cp.Log_Add(to_string(444));
	cp.Log_Add("ef");
	cp.Log_Endline();
	cp.Stopwatch_Check_Endpoint();
	cp.Stopwatch_Check_Endpoint(3);

	cp.Stopwatch_Check_Startpoint();
	cp.Log_Add(to_string(cp.Stopwatch_GetTime_ms(0)));
	cp.Log_Add(to_string(cp.Stopwatch_GetTime_ms(1)));
	cp.Stopwatch_Check_Endpoint();
	cp.Log_Add(to_string(cp.Stopwatch_GetTime_ms(2)));
	cp.Log_Add(to_string(cp.Stopwatch_GetTime_ms(3)));



	cp.Log_Endline();
	cp.End_cpptools();

	return 0;
}