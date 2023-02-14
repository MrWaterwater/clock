#include "pch.h"
#include "ClockOfToday.h"

CClock& CClockOfToday::GetMSrtClock()
{
    return m_srtClock;
}

CClockOfToday::CClockOfToday()
{

}

CClockOfToday::CClockOfToday(const CClock& srtClock)
{
    m_srtClock = srtClock;
    m_bRing = false;
    m_bTrigger = false;
    m_sCount = 0;
    SetMSDelay(10);
    m_chRsv1 = ' ';
    m_chRsv2 = ' ';
    time_t tCurrentTime;
    time_t tSetTime;
    time(&tCurrentTime);
    tSetTime = tCurrentTime;
    tm temp;
    localtime_s(&temp, &tCurrentTime);
    switch (m_srtClock.GetMELoopType())
    {
    case single:
    {
        temp.tm_sec = 0;
        temp.tm_min = GetMSrtClock().GetMSMin();
        temp.tm_hour = GetMSrtClock().GetMSHour();
        tSetTime = mktime(&temp);
        break;
    }
    case hourCycle:
    {
        temp.tm_sec = 0;
        temp.tm_min = GetMSrtClock().GetMSMin();
        tSetTime = mktime(&temp);
        break;
    }
    case dayCycle:
    {
        temp.tm_sec = 0;
        temp.tm_min = GetMSrtClock().GetMSMin();
        temp.tm_hour = GetMSrtClock().GetMSHour();
        tSetTime = mktime(&temp);
        break;
    }
    case weekCycle:
    {
        temp.tm_sec = 0;
        temp.tm_min = GetMSrtClock().GetMSMin();
        temp.tm_hour = GetMSrtClock().GetMSHour();
        tSetTime = mktime(&temp);
        break;
    }
    case monthCycle:
    {
        temp.tm_sec = 0;
        temp.tm_min = GetMSrtClock().GetMSMin();
        temp.tm_hour = GetMSrtClock().GetMSHour();
        temp.tm_mday = GetMSrtClock().GetMSDay();
        tSetTime = mktime(&temp);
        break;
    }
    default:
    {
        break;
    }
    }
    m_tBeginTime = tSetTime;
}

void CClockOfToday::SetMSDelay(short sDelay)
{
    if (sDelay >= 10 && sDelay < 60)
    {
        m_sDelay = sDelay;
    }
    else
    {
        cout << "Illegal delay time!" << endl;
    }
}

time_t CClockOfToday::GetMTBeginTime() const
{
    return m_tBeginTime;
}

bool CClockOfToday::IsMBTrigger() const
{
    return m_bTrigger;
}

void CClockOfToday::SetMBTrigger(bool mBTrigger)
{
    m_bTrigger = mBTrigger;
}

bool CClockOfToday::IsMBRing() const
{
    return m_bRing;
}

void CClockOfToday::SetMBRing(bool mBRing)
{
    m_bRing = mBRing;
}

short CClockOfToday::GetMSCount()
{
    return m_sCount;
}

void CClockOfToday::SetMSCount(short mSCount)
{
    m_sCount = mSCount;
}

short CClockOfToday::GetMSDelay() {
    return m_sDelay;
}

void CClockOfToday::SetMTBeginTime(time_t mTBeginTime)
{
    m_tBeginTime = mTBeginTime;
}