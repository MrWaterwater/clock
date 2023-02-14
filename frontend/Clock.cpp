#include "pch.h"
#include "Clock.h"
CClock::CClock()
{

}

CClock::CClock(char chszClockName[], eLOOP_TYPE eLoopType, short sMin, short sHour, short sDay, bool eszWeek[], short sDuration, eMUSIC_TYPE eMusicType)
{
    time_t t;
    time(&t);
    m_nClockID = t;
    m_tCreateOrChanGetime = t;
    m_bFlag = true;
    SetMchszClockName(chszClockName);
    m_eLoopType = eLoopType;
    m_sDuration = sDuration;
    m_eMusicType = eMusicType;
    switch (m_eLoopType)
    {
    case single:
        ClockDay(sMin, sHour);
        break;
    case hourCycle:
        ClockHour(sMin);
        break;
    case dayCycle:
        ClockDay(sMin, sHour);
        break;
    case weekCycle:
    {
        ClockWeek(sMin, sHour, eszWeek);
        int sum = 0;
        bool* temp = m_eszWeek;
        for (int i = 0; i < 7; i++)
        {
            sum += *(temp + i);
        }
        if (7 == sum)
        {
            m_eLoopType = dayCycle;
            ClockDay(sMin, sHour);
        }
        break;
    }
    case monthCycle:
    {
        ClockMonth(sMin, sHour, sDay);
        break;
    }
    default:
        break;
    }
}

void CClock::ClockHour(short sMin)
{
    m_sMin = sMin;
    m_sHour = 0;
    m_sDay = 0;
    bool week[7] = { 0,0,0,0,0,0,0 };
    SetMEszWeek(week);
}

void CClock::ClockDay(short sMin, short sHour)
{
    m_sMin = sMin;
    m_sHour = sHour;
    m_sDay = 0;
    bool week[7] = { 0,0,0,0,0,0,0 };
    SetMEszWeek(week);
}

void CClock::ClockWeek(short sMin, short sHour, bool bszWeek[])
{
    m_sMin = sMin;
    m_sHour = sHour;
    m_sDay = 0;
    SetMEszWeek(bszWeek);
}

void CClock::ClockMonth(short sMin, short sHour, short sDay)
{
    m_sMin = sMin;
    m_sHour = sHour;
    m_sDay = sDay;
    bool week[7] = { 0,0,0,0,0,0,0 };
    SetMEszWeek(week);
}

eLOOP_TYPE CClock::GetMELoopType() const
{
    return m_eLoopType;
}

bool CClock::GetMBFlag() const
{
    return m_bFlag;
}

eMUSIC_TYPE CClock::GetMEMusicType() const
{
    return m_eMusicType;
}

short CClock::GetMSMin() const
{
    return m_sMin;
}

short CClock::GetMSHour() const
{
    return m_sHour;
}

short CClock::GetMSDay() const
{
    return m_sDay;
}

time_t CClock::GetMTCreateOrChangeTime() const
{
    return m_tCreateOrChanGetime;
}

const char* CClock::GetMChszClockName() const
{
    return m_chszClockName;
}


short CClock::GetMSDuration() const
{
    return m_sDuration;
}

bool CClock::IsMBFlag() const
{
    return m_bFlag;
}

bool* CClock::GetMEszWeek()
{
    return m_eszWeek;
}


int CClock::GetMNClockId() const
{
    return m_nClockID;
}

void CClock::SetMEszWeek(bool eszWeek[])
{
    for (int i = 0; i < 7; i++)
    {
        m_eszWeek[i] = eszWeek[i];
    }
}

void CClock::SetMchszClockName(const char chszClockName[])
{
    if (chszClockName != nullptr)
    {
        if (strlen(chszClockName) <= 18)
        {
            for (int i = 0; i <= strlen(chszClockName); i++)
            {
                m_chszClockName[i] = chszClockName[i];
            }
            for (int i = strlen(chszClockName); i <= 18; i++)
            {
                m_chszClockName[i] = '\0';
            }
        }
        else
        {
            cout << "Clock name length is illegal" << endl;
        }
    }
}


void CClock::SetMSMin(short mSMin) {
    m_sMin = mSMin;
}

void CClock::SetMSHour(short mSHour) {
    m_sHour = mSHour;
}

void CClock::SetMSDay(short mSDay) {
    m_sDay = mSDay;
}

void CClock::SetMSDuration(short mSDuration) {
    m_sDuration = mSDuration;
}

void CClock::SetMBFlag(bool mBFlag) {
    m_bFlag = mBFlag;
}

void CClock::SetMTCreateOrChangeTime(time_t mTCreateOrChanGetime) {
    m_tCreateOrChanGetime = mTCreateOrChanGetime;
}

void CClock::SetMELoopType(eLOOP_TYPE eLoopType) {
    m_eLoopType = eLoopType;
}

void CClock::SetMEMusicType(eMUSIC_TYPE eMusicType)
{
    m_eMusicType = eMusicType;
}
