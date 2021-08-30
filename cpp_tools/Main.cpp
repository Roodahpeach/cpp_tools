#include "cpp_tools.h"

using namespace std;

int main() { //기능 테스트용 메인
	cpp_tools cp;

	cp.Log_Start();

	cp.Log_Add("Yeah");
	cp.Log_Add(to_string(123));
	cp.Log_Add("df");
	cp.Log_Endline();
	cp.Log_Add("Yeah12");
	cp.Log_Add(to_string(444));
	cp.Log_Add("ef");
	cp.Log_Endline();
	cp.Log_end();

	return 0;
}