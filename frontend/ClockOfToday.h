/************************************************************************************************
描述：当日闹钟信息单元
（1）构造当日闹钟对象
（2）对外提供接口访问当日闹钟对象信息
************************************************************************************************/

#ifndef BACKEND_CLOCKOFTODAY_H
#define BACKEND_CLOCKOFTODAY_H

#include "Clock.h"
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
using std::string;
class CClockOfToday {
public:
    CClockOfToday();

    explicit CClockOfToday(const CClock& srtClock);

    CClock& GetMSrtClock();

    void SetMSDelay(short sDelay);

    time_t GetMTBeginTime() const;

    void SetMTBeginTime(time_t mTBeginTime);

    bool IsMBTrigger() const;

    void SetMBTrigger(bool mBTrigger);

    bool IsMBRing() const;

    void SetMBRing(bool mBRing);

    short GetMSCount();

    void SetMSCount(short mSCount);

    short GetMSDelay();

private:

    CClock m_srtClock;

    bool m_bTrigger;

    bool m_bRing;

    short m_sCount;

    short m_sDelay;

    char m_chRsv1;

    char m_chRsv2;

    time_t m_tBeginTime;
};


#endif //BACKEND_CLOCKOFTODAY_H
