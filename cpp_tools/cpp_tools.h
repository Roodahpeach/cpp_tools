#pragma once

#include <fstream>
#include <iostream>
#include <Windows.h>
#include <string>
#include <time.h>

#include <vector>
#include <algorithm>
#include <numeric>

#include <mutex> 
#include <wchar.h>

using namespace std;

class cpp_tools {
private:
#pragma region Private_Variable
	//�α� ��� 
	string log_file_name;
	string log_string;
	ofstream logfile_ofstream;
	mutex log_mutex;
	int log_loglevel;

	//timer ���
	vector<__int64> Tick_Array_Start;
	vector<__int64> Tick_Array_End;
	__int64 TicksPerSec;
	__int64 Program_Init_Time;
	
	//INI ���
	mutex INI_mutex;
	wstring INI_FileLocation;
	wstring INI_FileName;
	wstring INI_FileFullLocation;
	
#pragma endregion

#pragma region Private_Functions
	//�α� �Լ� 
	bool Log_Start(string log_file_name = "Log");
	bool Log_End();
	string FuncLog_GetLogLevelString(int LogLevel);

	//timer ���
	bool Stopwatch_Start();
	bool Stopwatch_End();
	bool Stopwatch_GetQPF(__int64* QPFTicksPerSec);
	__int64 Stopwatch_GetQPCTick(void);
	float Stopwatch_GetProgramElapseTime(int time_unit);

	//INI ���
	wstring GetExePath();
#pragma endregion

	
public:
#pragma region Public_Variable
	typedef enum {
		enum_TimeUnit_sec,
		enum_TimeUnit_millisec
	}enum_TimeUnit;

	typedef enum {
		enum_LogLevel_FATAL,
		enum_LogLevel_ERROR,
		enum_LogLevel_WARNING,
		enum_LogLevel_INFO,
		enum_LogLevel_DEBUG,
	}enum_LogLevel;

	//INI ���
	const wchar_t* INI_No_Result = L"No Result";
#pragma endregion

#pragma region Public_Functions
	//���� �Լ�
	bool Init_cpptools(string log_file_name = "Log", wstring Ini_File_Name = L"Setting");
	bool End_cpptools();

	//�α� �Լ� 
	bool Log_Add(string str);
	bool Log_Add_ElapseTime(int time_unit = enum_TimeUnit_sec);
	bool Log_Add_Quick(string str, int time_unit = enum_TimeUnit_sec);
	bool Log_Add_Stopwatch(int index, int time_unit = enum_TimeUnit_millisec);
	bool Log_Endline();
	
	//�α� �Լ�2
	
	bool FuncLog_Init();
	bool FuncLog_Add(const char * __func, const char* __filename, int __line, int LogLevel = enum_LogLevel_INFO, string msg = "");
	bool FuncLog_SetLogLevel(int LogLevel = enum_LogLevel_INFO);

	//timer ���
	bool Stopwatch_Check_Startpoint();
	bool Stopwatch_Check_Startpoint(int checkpoint_index);
	bool Stopwatch_Check_Endpoint();
	bool Stopwatch_Check_Endpoint(int checkpoint_index);
	float Stopwatch_GetTime(int checkpoint_index, int time_unit = enum_TimeUnit_millisec);
	float Stopwatch_GetAverageTime(int time_unit = enum_TimeUnit_millisec);
	int Stopwatch_Length();
	bool Stopwatch_Reset();

	//��¥, �ð� ������
	string Date_GetDateNTime();
	string Date_GetDateNTime_ForFileName();
	string Date_GetTime();

	//INI ���
	wstring INIReadString(wstring strAppName, wstring strKeyName);
	wstring INIReadString(wstring strAppName, wstring strKeyName, wstring strFilePath);
	void INIWriteString(wstring strAppName, wstring strKeyName, wstring strValue);
	void INIWriteString(wstring strAppName, wstring strKeyName, wstring strValue, wstring strFilePath);
#pragma endregion
};
