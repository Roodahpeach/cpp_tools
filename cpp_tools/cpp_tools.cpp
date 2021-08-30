#include "cpp_tools.h"

bool cpp_tools::Log_Start(string log_file_name)
{
    cpp_tools::log_file_name = log_file_name + "_" + cpp_tools::Date_GetDateNTime_ForFileName() + ".csv";
    cpp_tools::logfile_ofstream.open(cpp_tools::log_file_name); //Log_시간.csv 저장
    bool result = logfile_ofstream.fail();
    return !result;
}

bool cpp_tools::Log_Add(string str)
{
    this->log_string.append(str);
    this->log_string.append(",");
    return true;
}

bool cpp_tools::Log_Endline()
{
    this->log_string.pop_back(); // 쉼표 떼기
    cpp_tools::logfile_ofstream << this->log_string << endl;
    this->log_string.clear();
    return true;
}

bool cpp_tools::Log_end()
{
    cpp_tools::logfile_ofstream.close();
    return true;
}



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

bool cpp_tools::Stopwatch_Start()
{
    this->_Stopwatch_Length = 0;
    return this->Stopwatch_GetQPF(&this->TicksPerSec);
}

bool cpp_tools::Stopwatch_End()
{
    this->_Stopwatch_Length = 0;
    this->TicksPerSec = 0;
    return true;
}

int cpp_tools::Stopwatch_Length()
{
    return this->_Stopwatch_Length;
}

bool cpp_tools::Stopwatch_Check_Startpoint(int checkpoint_index)
{
    this->Tick_Array_Start[checkpoint_index] = cpp_tools::Stopwatch_GetQPCTick();
    return true;
}

bool cpp_tools::Stopwatch_Check_Endpoint(int checkpoint_index) {
    this->_Stopwatch_Length++;
    this->Tick_Array_End[checkpoint_index] = cpp_tools::Stopwatch_GetQPCTick();
    return true;
}

float cpp_tools::Stopwatch_GetTime_s(int checkpoint_index)
{
    return ((float)(Tick_Array_End[checkpoint_index] - Tick_Array_Start[checkpoint_index]) / this->TicksPerSec);
}

float cpp_tools::Stopwatch_GetTime_ms(int checkpoint_index)
{
    return ((float)(Tick_Array_End[checkpoint_index] - Tick_Array_Start[checkpoint_index]) / this->TicksPerSec) * 1000;
}

//=====================================================================================================

