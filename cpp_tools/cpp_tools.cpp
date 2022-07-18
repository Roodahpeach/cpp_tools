#include "cpp_tools.h"

#pragma region 통합 함수
bool cpp_tools::Init_cpptools(string log_file_name, wstring Ini_File_Name)
{
	TicksPerSec = 0;
	this->Log_Start(log_file_name);
	this->Stopwatch_Start();
	FuncLog_SetLogLevel();

	this->Program_Init_Time = cpp_tools::Stopwatch_GetQPCTick();
	this->INI_FileLocation = GetExePath();
	this->INI_FileName = Ini_File_Name + L".ini";
	this->INI_FileFullLocation = INI_FileLocation + L"\\" + INI_FileName;
	return true;
}

bool cpp_tools::End_cpptools()
{
	this->Log_End();
	this->Stopwatch_End();
	return true;
}
#pragma endregion

#pragma region 로그 기능
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
	if (cpp_tools::logfile_ofstream.good()) {
		Log_Add(to_string(this->Stopwatch_GetProgramElapseTime(time_unit)));

		return true;
	}
	return false;
}

bool cpp_tools::Log_Add_Quick(string str, int time_unit)
{
	if (cpp_tools::logfile_ofstream.good()) {
		log_mutex.lock();
		Log_Add(to_string(this->Stopwatch_GetProgramElapseTime(time_unit)));
		this->Log_Add(str);
		this->Log_Endline();
		log_mutex.unlock();
		return true;
	}
	return false;
}

bool cpp_tools::Log_Add_Stopwatch(int index, int time_unit)
{
	if (cpp_tools::logfile_ofstream.good()) {
		Log_Add(to_string(this->Stopwatch_GetTime(index, time_unit)));

		return true;
	}
	return false;
}

bool cpp_tools::Log_Endline()
{
	if (cpp_tools::logfile_ofstream.good()) {
		if (!this->log_string.empty()) {
			this->log_string.pop_back(); // 쉼표 떼기
			cpp_tools::logfile_ofstream << this->log_string << endl;
			this->log_string.clear();
			return true;
		}
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

string cpp_tools::FuncLog_GetLogLevelString(int LogLevel)
{
	string str_returnvalue;

	switch (LogLevel)
	{
	case enum_LogLevel_DEBUG:		str_returnvalue = "DEBUG"; break;
	case enum_LogLevel_ERROR:		str_returnvalue = "ERROR"; break;
	case enum_LogLevel_FATAL:		str_returnvalue = "FATAL"; break;
	case enum_LogLevel_INFO:		str_returnvalue = "INFO"; break;
	case enum_LogLevel_WARNING:		str_returnvalue = "WARNING"; break;
	default:						str_returnvalue = to_string(LogLevel); break;
	}

	return str_returnvalue;
}

bool cpp_tools::FuncLog_Init()
{
	log_mutex.lock();
	Log_Add("수행 시간(s)");
	Log_Add("함수 이름");
	Log_Add("로그 레벨");
	Log_Add("메시지");
	Log_Add("파일명");
	Log_Add("위치");
	Log_Endline();
	log_mutex.unlock();
	return false;
}

bool cpp_tools::FuncLog_Add(const char * __func, const char* __filename, int __line, int LogLevel, string msg)
{
	string str_FuncName = string(__func);
	string str_FileName = string(__filename);
	string str_LineNum = to_string(__line);

	if (LogLevel <= this->log_loglevel) {
		log_mutex.lock();
		Log_Add_ElapseTime(enum_TimeUnit_sec);
		Log_Add(str_FuncName);
		Log_Add(FuncLog_GetLogLevelString(LogLevel));
		Log_Add(msg);
		Log_Add(str_FileName);
		Log_Add(str_LineNum);
		Log_Endline();
		log_mutex.unlock();
	}
	return false;
}
bool cpp_tools::FuncLog_SetLogLevel(int LogLevel)
{
	this->log_loglevel = LogLevel;
	return false;
}
#pragma endregion

#pragma region 날짜, 시간기능
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

#pragma endregion

#pragma region 타이머 기능
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
		this->Tick_Array_Start.resize(checkpoint_index + 1);
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
	else if (time_unit == this->enum_TimeUnit_millisec) {
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

#pragma endregion

#pragma region INI 기능

wstring cpp_tools::GetExePath()
{
	static TCHAR pBuf[256] = { 0, };
	memset(pBuf, NULL, sizeof(pBuf));
	GetModuleFileName(NULL, pBuf, sizeof(pBuf)); //현재 실행 경로를 가져오는 함수
	wstring strFilePath(pBuf);
	strFilePath = strFilePath.substr(0, strFilePath.rfind(L"\\")); //마지막 EXE부분 떼어내기
	return strFilePath;
}

wstring cpp_tools::INIReadString(wstring strAppName, wstring strKeyName)
{
	return INIReadString(strAppName, strKeyName, this->INI_FileFullLocation);
}

wstring cpp_tools::INIReadString(wstring strAppName, wstring strKeyName, wstring strFilePath)
{
	wchar_t szReturnString[1024] = { 0, };
	memset(szReturnString, NULL, 1024 * 2);
	GetPrivateProfileString(strAppName.c_str(), strKeyName.c_str(), INI_No_Result, szReturnString, 1024, strFilePath.c_str());
	wstring str(szReturnString);
	return str;

	return wstring();
}

void cpp_tools::INIWriteString(wstring strAppName, wstring strKeyName, wstring strValue)
{
	INIWriteString(strAppName, strKeyName, strValue, this->INI_FileFullLocation);
}

void cpp_tools::INIWriteString(wstring strAppName, wstring strKeyName, wstring strValue, wstring strFilePath)
{
	WritePrivateProfileString(strAppName.c_str(), strKeyName.c_str(), strValue.c_str(), strFilePath.c_str());
}
#pragma endregion
