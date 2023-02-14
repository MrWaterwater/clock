/************************************************************************************************
描述：文件操作单元
（1）闹钟信息增删查改
（2）日志信息写入、查询
************************************************************************************************/

#ifndef BACKEND_FILE_H
#define BACKEND_FILE_H

#include "Clock.h"
#include "list"
using std::list;
class File {
public:
    void AddClockToFile(const CClock& clock);//增加闹钟接口

    void DeleteClockFromFile(int clockID);//删除闹钟接口

    void UpdateClockToFile(list<CClock>& clocks);//更新闹钟接口

    void AddRecordToFile(const _RECORD& record);//增加日志接口

    void GetClocksFromFile(list<CClock>& clocks);//获取闹钟列表接口

    void GetRecordsFromFile(list<_RECORD>& records);//获取日志列表接口

private:
    bool IsFileExists(std::string& name);//判断文件是否存在

private:
    const char* m_clockFile = "clock.dat";//闹钟文件名

    const char* m_recordFile = "record.dat";//日志文件名
};


#endif //BACKEND_FILE_H
