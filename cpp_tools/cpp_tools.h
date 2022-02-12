#pragma once

#include <fstream>
#include <iostream>
#include <Windows.h>
#include <string>
#include <time.h>

#include <vector>
#include <algorithm>
#include <numeric>


using namespace std;

class cpp_tools {
private:
	
	//로그 기능 
	string log_file_name;
	string log_string;
	ofstream logfile_ofstream;

	//timer 기능
	vector<__int64> Tick_Array_Start;
	vector<__int64> Tick_Array_End;
	__int64 TicksPerSec;

	__int64 Program_Init_Time;

	//=====================================================================================================

	//로그 함수 
	bool Log_Start(string log_file_name = "Log");
	bool Log_End();

	//timer 기능
	bool Stopwatch_Start();
	bool Stopwatch_End();
	bool Stopwatch_GetQPF(__int64* QPFTicksPerSec);
	__int64 Stopwatch_GetQPCTick(void);
	float Stopwatch_GetProgramElapseTime(int time_unit);
public:

	typedef enum {
		enum_TimeUnit_sec,
		enum_TimeUnit_millisec
	}enum_TimeUnit;

	//=====================================================================================================

	//통합 함수
	bool Init_cpptools(string log_file_name = "Log");
	bool End_cpptools();

	//로그 함수 
	bool Log_Add(string str);
	bool Log_Add_Quick(string str, int time_unit = enum_TimeUnit_sec);
	bool Log_Add_Stopwatch(int index, int time_unit = enum_TimeUnit_millisec);
	bool Log_Endline();
		
	//timer 기능
	bool Stopwatch_Check_Startpoint();
	bool Stopwatch_Check_Startpoint(int checkpoint_index);
	bool Stopwatch_Check_Endpoint();
	bool Stopwatch_Check_Endpoint(int checkpoint_index);
	float Stopwatch_GetTime(int checkpoint_index, int time_unit = enum_TimeUnit_millisec);
	float Stopwatch_GetAverageTime(int time_unit = enum_TimeUnit_millisec);
	int Stopwatch_Length();
	bool Stopwatch_Reset();

	//날짜, 시간 얻어오기
	string Date_GetDateNTime();
	string Date_GetDateNTime_ForFileName();
	string Date_GetTime();
};
