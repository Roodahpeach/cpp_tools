#include "cpp_tools.h"

//=====================================================================================================

bool cpp_tools::Init_cpptools(string log_file_name)
{
	TicksPerSec = 0;
	this->Log_Start(log_file_name);
	this->Stopwatch_Start();

	this->Program_Init_Time = cpp_tools::Stopwatch_GetQPCTick();
	return true;
}

bool cpp_tools::End_cpptools()
{
	this->Log_End();
	this->Stopwatch_End();
	return true;
}

//=====================================================================================================

bool cpp_tools::Log_Start(string log_file_name)
{
	cpp_tools::log_file_name = log_file_name + "_" + cpp_tools::Date_GetDateNTime_ForFileName() + ".csv";
	cpp_tools::logfile_ofstream.open(cpp_tools::log_file_name); //Log_시간.csv 저장
	bool result = logfile_ofstream.fail();
	return !result;
}

bool cpp_tools::Log_Add(string str)
{
	if (cpp_tools::logfile_ofstream.good()) {
		this->log_string.append(str);
		this->log_string.append(",");
		return true;
	}
	return false;
}

bool cpp_tools::Log_Add_ElapseTime(int time_unit) {
	Log_Add(to_string(this->Stopwatch_GetProgramElapseTime(time_unit)));
	
	return true;
}

bool cpp_tools::Log_Add_Quick(string str, int time_unit)
{
	Log_Add(to_string(this->Stopwatch_GetProgramElapseTime(time_unit)));
	this->Log_Add(str);
	this->Log_Endline();
	return true;
}

bool cpp_tools::Log_Add_Stopwatch(int index, int time_unit)
{
	Log_Add(to_string(this->Stopwatch_GetTime(index, time_unit)));

	return true;
}

bool cpp_tools::Log_Endline()
{
	if (cpp_tools::logfile_ofstream.good()) {
		this->log_string.pop_back(); // 쉼표 떼기
		cpp_tools::logfile_ofstream << this->log_string << endl;
		this->log_string.clear();
		return true;
	}
	return false;
}

bool cpp_tools::Log_End()
{
	if (this->logfile_ofstream.is_open()) {
		cpp_tools::logfile_ofstream.close();
		return true;
	}
	return false;
}

//=====================================================================================================

string cpp_tools::Date_GetDateNTime()
{
	struct tm curr_tm;
	time_t curr_time = time(nullptr);

	localtime_s(&curr_tm, &curr_time);

	int curr_month = curr_tm.tm_mon + 1;
	int curr_day = curr_tm.tm_mday;
	int curr_hour = curr_tm.tm_hour;
	int curr_minute = curr_tm.tm_min;
	int curr_second = curr_tm.tm_sec;

	string out_str;

	out_str += to_string(curr_month);
	out_str += "/";
	out_str += to_string(curr_day);
	out_str += " - ";
	out_str += to_string(curr_hour);
	out_str += ":";
	out_str += to_string(curr_minute);
	out_str += ":";
	out_str += to_string(curr_second);

	return out_str;
}

string cpp_tools::Date_GetDateNTime_ForFileName()
{
	struct tm curr_tm;
	time_t curr_time = time(nullptr);

	localtime_s(&curr_tm, &curr_time);

	int curr_month = curr_tm.tm_mon + 1;
	int curr_day = curr_tm.tm_mday;
	int curr_hour = curr_tm.tm_hour;
	int curr_minute = curr_tm.tm_min;
	int curr_second = curr_tm.tm_sec;

	string out_str;

	out_str += to_string(curr_month);
	out_str += "월";
	out_str += to_string(curr_day);
	out_str += "일-";
	out_str += to_string(curr_hour);
	out_str += "시";
	out_str += to_string(curr_minute);
	out_str += "분";
	out_str += to_string(curr_second);
	out_str += "초";

	return out_str;

	return string();
}

string cpp_tools::Date_GetTime()
{
	struct tm curr_tm;
	time_t curr_time = time(nullptr);

	localtime_s(&curr_tm, &curr_time);

	int curr_hour = curr_tm.tm_hour;
	int curr_minute = curr_tm.tm_min;
	int curr_second = curr_tm.tm_sec;

	string out_str;

	out_str += to_string(curr_hour);
	out_str += ":";
	out_str += to_string(curr_minute);
	out_str += ":";
	out_str += to_string(curr_second);

	return out_str;
}

//=====================================================================================================


bool cpp_tools::Stopwatch_GetQPF(__int64* QPFTicksPerSec)
{
	LARGE_INTEGER li;

	if (QueryPerformanceFrequency(&li) == false)
	{
		return false;
	}

	*QPFTicksPerSec = static_cast<__int64>(li.QuadPart);

	return true;
}

__int64 cpp_tools::Stopwatch_GetQPCTick(void)
{
	LARGE_INTEGER li;

	QueryPerformanceCounter(&li);

	return static_cast<__int64>(li.QuadPart);
}

float cpp_tools::Stopwatch_GetProgramElapseTime(int time_unit)
{

	if (time_unit == this->enum_TimeUnit_sec) {
		return ((float)(Stopwatch_GetQPCTick() - this->Program_Init_Time) / this->TicksPerSec);
	}
	else if (time_unit == this->enum_TimeUnit_millisec) {
		return ((float)(Stopwatch_GetQPCTick() - this->Program_Init_Time) / this->TicksPerSec) * 1000;

	}
	return 0.0f;
}

bool cpp_tools::Stopwatch_Start()
{
	return this->Stopwatch_GetQPF(&this->TicksPerSec);
}

bool cpp_tools::Stopwatch_End()
{
	this->TicksPerSec = 0;
	this->Tick_Array_Start.clear();
	this->Tick_Array_End.clear();
	return true;
}

int cpp_tools::Stopwatch_Length()
{
	return min(this->Tick_Array_End.size(), this->Tick_Array_Start.size());
}

bool cpp_tools::Stopwatch_Reset()
{
	this->Tick_Array_Start.clear();
	this->Tick_Array_End.clear();
	return true;
}


bool cpp_tools::Stopwatch_Check_Startpoint()
{
	this->Tick_Array_Start.push_back(cpp_tools::Stopwatch_GetQPCTick());
	return true;
}

bool cpp_tools::Stopwatch_Check_Startpoint(int checkpoint_index)
{
	if (checkpoint_index >= this->Stopwatch_Length()) {
		this->Tick_Array_Start.resize(checkpoint_index+1);
	}
	this->Tick_Array_Start[checkpoint_index] = cpp_tools::Stopwatch_GetQPCTick();

	return true;
}

bool cpp_tools::Stopwatch_Check_Endpoint() {

	this->Tick_Array_End.push_back(cpp_tools::Stopwatch_GetQPCTick());
	return true;
}

bool cpp_tools::Stopwatch_Check_Endpoint(int checkpoint_index) {
	if (checkpoint_index >= this->Stopwatch_Length()) {
		this->Tick_Array_End.resize(checkpoint_index + 1);
	}
	this->Tick_Array_End[checkpoint_index] = cpp_tools::Stopwatch_GetQPCTick();
	return true;
}

float cpp_tools::Stopwatch_GetTime(int checkpoint_index, int time_unit)
{
	if (checkpoint_index >= this->Stopwatch_Length()) {
		return -1;
	}


	if (time_unit == this->enum_TimeUnit_sec) {
		return ((float)(Tick_Array_End[checkpoint_index] - Tick_Array_Start[checkpoint_index]) / this->TicksPerSec);
	}
	else if (time_unit == this->enum_TimeUnit_millisec){
		return ((float)(Tick_Array_End[checkpoint_index] - Tick_Array_Start[checkpoint_index]) / this->TicksPerSec) * 1000;
		
	}
	
	return 0.0f;
}

float cpp_tools::Stopwatch_GetAverageTime(int time_unit)
{
	int time_offset = enum_TimeUnit_millisec == 1 ? 1000 : 1;
	vector<float> sum;

	for (int i = 0; i < Tick_Array_End.size(); i++) {
		sum.push_back(((float)(Tick_Array_End[i] - Tick_Array_Start[i]) / this->TicksPerSec) * time_offset);
	}
	
	return accumulate(sum.begin(), sum.end(), 0.0f) / sum.size();;
}

//=====================================================================================================

