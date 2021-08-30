#pragma once

#include <fstream>
#include <iostream>
#include <Windows.h>
#include <string>
#include <time.h>


using namespace std;

static class cpp_tools {
private:
	//로그 기능 
	string log_file_name;
	string log_string;
	ofstream logfile_ofstream;

	//timer 기능
	__int64 Tick_Array_Start[100];
	__int64 Tick_Array_End[100];
	__int64 TicksPerSec;
	int _Stopwatch_Length;

	bool Stopwatch_GetQPF(__int64* QPFTicksPerSec);
	__int64 Stopwatch_GetQPCTick(void);
public:
	//로그 함수 
	bool Log_Start(string log_file_name = "Log");
	bool Log_Add(string str);
	bool Log_Endline();
	bool Log_end();

	//timer 기능
	bool Stopwatch_Start();
	bool Stopwatch_Check_Startpoint(int checkpoint_index);
	bool Stopwatch_Check_Endpoint(int checkpoint_index);
	float Stopwatch_GetTime_s(int checkpoint_index);
	float Stopwatch_GetTime_ms(int checkpoint_index);
	bool Stopwatch_End();
	int Stopwatch_Length();

	//날짜, 시간 얻어오기
	string Date_GetDateNTime();
	string Date_GetDateNTime_ForFileName();
	string Date_GetTime();
};
