/************************************************************************************************
�������ļ�������Ԫ
��1��������Ϣ��ɾ���
��2����־��Ϣд�롢��ѯ
************************************************************************************************/

#ifndef BACKEND_FILE_H
#define BACKEND_FILE_H

#include "Clock.h"
#include "list"
using std::list;
class File {
public:
    void AddClockToFile(const CClock& clock);//�������ӽӿ�

    void DeleteClockFromFile(int clockID);//ɾ�����ӽӿ�

    void UpdateClockToFile(list<CClock>& clocks);//�������ӽӿ�

    void AddRecordToFile(const _RECORD& record);//������־�ӿ�

    void GetClocksFromFile(list<CClock>& clocks);//��ȡ�����б�ӿ�

    void GetRecordsFromFile(list<_RECORD>& records);//��ȡ��־�б�ӿ�

private:
    bool IsFileExists(std::string& name);//�ж��ļ��Ƿ����

private:
    const char* m_clockFile = "clock.dat";//�����ļ���

    const char* m_recordFile = "record.dat";//��־�ļ���
};


#endif //BACKEND_FILE_H
