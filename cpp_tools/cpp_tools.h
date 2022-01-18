#pragma once

#include <fstream>
#include <iostream>
#include <Windows.h>
#include <string>
#include <time.h>

#include <vector>


using namespace std;

class cpp_tools {
private:
	//�α� ��� 
	string log_file_name;
	string log_string;
	ofstream logfile_ofstream;

	//timer ���
	vector<__int64> Tick_Array_Start;
	vector<__int64> Tick_Array_End;
	__int64 TicksPerSec;

	bool Stopwatch_GetQPF(__int64* QPFTicksPerSec);
	__int64 Stopwatch_GetQPCTick(void);
public:
	//���� �Լ�
	bool Init_cpptools(string log_file_name = "Log");
	bool End_cpptools();

	//�α� �Լ� 
	bool Log_Start(string log_file_name = "Log");
	bool Log_Add(string str);
	bool Log_Endline();
	bool Log_End();

	//timer ���
	bool Stopwatch_Start();
	bool Stopwatch_Check_Startpoint();
	bool Stopwatch_Check_Startpoint(int checkpoint_index);
	bool Stopwatch_Check_Endpoint();
	bool Stopwatch_Check_Endpoint(int checkpoint_index);
	float Stopwatch_GetTime_s(int checkpoint_index);
	float Stopwatch_GetTime_ms(int checkpoint_index);
	bool Stopwatch_End();
	int Stopwatch_Length();

	//��¥, �ð� ������
	string Date_GetDateNTime();
	string Date_GetDateNTime_ForFileName();
	string Date_GetTime();
};
