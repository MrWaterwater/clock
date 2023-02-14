#include "pch.h"
#include "File.h"
/*********************************************************************************
*�������ӵ������ļ�
* [in]const CClock& clock ��������
*********************************************************************************/
void File::AddClockToFile(const CClock& clock)
{
    std::ofstream  fout(m_clockFile, std::ios_base::app | std::ios_base::binary);
    fout.write((char*)&clock, sizeof(clock));
    fout.close();
}

/*********************************************************************************
*������־����־�ļ�
* [in]const CClock& record ��־����
*********************************************************************************/
void File::AddRecordToFile(const _RECORD& record)
{
    std::string str = m_recordFile;
    if (IsFileExists(str))
    {
        std::ofstream  fout(m_recordFile, std::ios_base::app | std::ios_base::binary);
        fout.write((char*)&record, sizeof(record));
        fout.close();
    }
    else
    {
        std::ofstream  fout(m_recordFile, std::ios_base::out | std::ios_base::binary);
        _RECORD_FILE_HEADER header;
        time_t timeTemp;
        tm t;
        time(&timeTemp);
        localtime_s(&t, &timeTemp);
        header.tCreateTime = t;
        fout.write((char*)&header, sizeof(header));
        fout.write((char*)&record, sizeof(record));
        fout.close();
    }
}

/*********************************************************************************
*�������ļ���ȡ�����б�
* [in]list<CClock>& clocks �����б�����
*********************************************************************************/
void File::GetClocksFromFile(list<CClock>& clocks)
{
    if (!clocks.empty())
    {
        clocks.clear();
    }
    std::string str = m_clockFile;
    if (IsFileExists(str))
    {
        std::ifstream fin;
        fin.open(m_clockFile, std::ios_base::in | std::ios_base::binary);
        if (fin.is_open())
        {
            std::cout << "read clocks from file!" << std::endl;
        }
        CClock t;
        _CLOCK_FILE_HEADER header;
        fin.read((char*)&header, sizeof(header));
        while (fin.read((char*)&t, sizeof(t)))
        {
            clocks.push_back(t);
        }
        fin.close();
    }
    else
    {
        std::ofstream  fout(m_clockFile, std::ios_base::out | std::ios_base::binary);
        _CLOCK_FILE_HEADER header;
        time_t timeTemp;
        tm t;
        time(&timeTemp);
        localtime_s(&t, &timeTemp);
        header.tCreateTime = t;
        fout.write((char*)&header, sizeof(header));
        fout.close();
    }
}

bool File::IsFileExists(std::string& name)
{
    std::ifstream f(name.c_str());
    return f.good();
}

/*********************************************************************************
*�������ļ�ɾ������
* [in]const int clockID ����ID
*********************************************************************************/
void File::DeleteClockFromFile(const int clockID)
{
    CClock clock;
    list<CClock> clocks;
    GetClocksFromFile(clocks);
    list<CClock>::iterator it;
    for (it = clocks.begin(); it != clocks.end(); it++)
    {
        if (it->GetMNClockId() == clockID)
        {
            clocks.erase(it);
            break;
        }
    }
    std::ifstream fin;
    fin.open(m_clockFile, std::ios_base::in | std::ios_base::binary);
    _CLOCK_FILE_HEADER header;
    fin.read((char*)&header, sizeof(header));
    fin.close();

    std::ofstream  fout(m_clockFile, std::ios_base::out | std::ios_base::binary);
    fout.write((char*)&header, sizeof(header));

    for (it = clocks.begin(); it != clocks.end(); it++)
    {
        clock = *it;
        fout.write((char*)&clock, sizeof(clock));
    }
    fout.close();
}

/*********************************************************************************
*����������Ϣ�ļ�
* [in]list<CClock>& clocks �����б�����
*********************************************************************************/
void File::UpdateClockToFile(list<CClock>& clocks)
{
    CClock clock;
    list<CClock>::iterator it;
    std::ifstream fin;
    fin.open(m_clockFile, std::ios_base::in | std::ios_base::binary);
    _CLOCK_FILE_HEADER header;
    fin.read((char*)&header, sizeof(header));
    fin.close();

    std::ofstream  fout(m_clockFile, std::ios_base::out | std::ios_base::binary);
    fout.write((char*)&header, sizeof(header));
    for (it = clocks.begin(); it != clocks.end(); it++)
    {
        clock = *it;
        fout.write((char*)&clock, sizeof(clock));
    }
    fout.close();
}
/*********************************************************************************
*����־�ļ���ȡ��־�б�
* [in]list<_RECORD>& records ��־�б�����
*********************************************************************************/
void File::GetRecordsFromFile(list<_RECORD>& records)
{
    if (!records.empty())
    {
        records.clear();
    }
    std::string str = m_recordFile;
    if (IsFileExists(str))
    {
        std::ifstream fin;
        fin.open(m_recordFile, std::ios_base::in | std::ios_base::binary);
        _RECORD record{};
        _RECORD_FILE_HEADER header;
        fin.read((char*)&header, sizeof(header));
        while (fin.read((char*)&record, sizeof(record)))
        {
            records.push_back(record);
        }
        fin.close();
    }
    else
    {
        std::ofstream  fout(m_recordFile, std::ios_base::out | std::ios_base::binary);
        _RECORD_FILE_HEADER header;
        time_t timeTemp;
        tm t;
        time(&timeTemp);
        localtime_s(&t, &timeTemp);
        header.tCreateTime = t;
        fout.write((char*)&header, sizeof(header));
        fout.close();
    }

}
