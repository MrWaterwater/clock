/************************************************************************************************
描述：闹钟信息单元
（1）构造闹钟对象
（2）对外提供接口访问闹钟对象信息
************************************************************************************************/
#ifndef BACKEND_CLOCK_H
#define BACKEND_CLOCK_H

#include "cstring"
#include "MyData.h"
#include "fstream"
#include <iostream>
using std::cout;
using std::endl;

class CClock {
public:
    CClock();

    CClock(char chszClockName[], eLOOP_TYPE eLoopType, short sMin, short sHour, short sDay,
        bool eszWeek[], short sDuration, eMUSIC_TYPE eMusicType);

    void ClockHour(short sMin);

    void ClockDay(short sMin, short sHour);

    void ClockWeek(short sMin, short sHour, bool bszWeek[]);

    void ClockMonth(short sMin, short sHour, short sDay);

    eLOOP_TYPE GetMELoopType() const;

    bool GetMBFlag() const;

    eMUSIC_TYPE GetMEMusicType() const;

    short GetMSMin() const;

    short GetMSHour() const;

    short GetMSDay() const;

    time_t GetMTCreateOrChangeTime() const;

    const char* GetMChszClockName() const;

    short GetMSDuration() const;

    bool IsMBFlag() const;

    bool* GetMEszWeek();

    int GetMNClockId() const;

    void SetMEszWeek(bool eszWeek[]);

    void SetMchszClockName(const char chszClockName[]);

    void SetMSMin(short mSMin);

    void SetMSHour(short mSHour);

    void SetMSDay(short mSDay);

    void SetMSDuration(short mSDuration);

    void SetMBFlag(bool mBFlag);

    void SetMTCreateOrChangeTime(time_t mTCreateOrChanGetime);

    void SetMELoopType(eLOOP_TYPE eLoopType);

    void SetMEMusicType(eMUSIC_TYPE eMusicType);

private:
    char m_chszClockName[18];

    short m_sMin;

    short m_sHour;

    short m_sDay;

    bool m_bFlag;

    bool m_eszWeek[7];

    time_t m_tCreateOrChanGetime;

    short m_sDuration;

    eMUSIC_TYPE m_eMusicType;

    eLOOP_TYPE m_eLoopType;

    int m_nClockID;
};


#endif //BACKEND_CLOCK_H
