/************************************************************************************************
描述：闹钟操作单元
（1）提供闹钟增删查改、排序、延迟、确认等接口
（2）调用文件操作单元接口，实现闹钟信息持久化
（3）提供多线程，分别控制当前时间、闹钟触发、用户操作、日志记录操作
************************************************************************************************/
#ifndef BACKEND_CLOCKMANAGE_H
#define BACKEND_CLOCKMANAGE_H
#include "ClockOfToday.h"
#include <thread>
#include "list"
#include "queue"
#include "vector"
#include "File.h"
#include <mutex>
using std::list;
using std::priority_queue;
using std::thread;
using std::cin;

struct _CMP_CLOCK_WAIT {
    bool operator()(CClockOfToday a, CClockOfToday b) {
        if (a.GetMTBeginTime() == b.GetMTBeginTime()) {
            return a.GetMSrtClock().GetMTCreateOrChangeTime() > b.GetMSrtClock().GetMTCreateOrChangeTime();
        }
        else {
            return a.GetMTBeginTime() > b.GetMTBeginTime();
        }
    }
};

struct _CMP_CLOCK_SORT_BY_NAME {
    bool operator()(CClock a, CClock b) {
        if (strcmp(a.GetMChszClockName(), b.GetMChszClockName()) == 0) {
            return a.GetMNClockId() > b.GetMNClockId();
        }
        else
        {
            return strcmp(a.GetMChszClockName(), b.GetMChszClockName()) > 0;
        }
    }
};

struct _CMP_CLOCK_SORT_BY_ID {
    bool operator()(CClock a, CClock b) {
        return a.GetMNClockId() > b.GetMNClockId();
    }
};

struct _CMP_CLOCK_SORT_BY_FLAG {
    bool operator()(CClock a, CClock b) {
        if (a.IsMBFlag() == b.IsMBFlag())
        {
            return a.GetMNClockId() > b.GetMNClockId();
        }
        else
        {
            if (a.IsMBFlag() && !b.IsMBFlag())
            {
                return true;
            }
            if (!a.IsMBFlag() && b.IsMBFlag())
            {
                return false;
            }
        }
    }
};
class CClockManage {

public:
    ~CClockManage(){}
    CClockManage(const CClockManage& clockManage) = delete;
    CClockManage& operator=(const CClockManage& clockManage) = delete;
    static CClockManage& GetClockManageInstance(){
        static CClockManage instance;
        return instance;
    }
private:
    CClockManage();

public:
    bool m_bFlagShow = true;

    std::mutex m_mutexPqWait;

    time_t m_tCurrentTime;

    tm m_srtCurrentTime;

    void GetNowTime();

    void ClockRing();

    void Record();

    void start();

    int AddClock(CClock& clock);

    int DeleteClock(int clockID);

    int UpdateClock(int clockID, char chszClockName[], eLOOP_TYPE eLoopType, short sMin, short sHour, short sDay,
        bool eszWeek[], short sDuration, eMUSIC_TYPE eMusicType);

    void ShowClockAll();

    void ShowRecord();

    void SortByRule();

    void RingClock();

    int UserConfirm();

    int UserDelay(short sTime);

    int OpenClock(int clockID);
    
    int CloseClock(int clockID);

    void Delay(CClockOfToday& clockOfToday);

    void Confirm(CClockOfToday& clockOfToday);

    CClock& GetClockByID(int clockID);

    list<CClock>& GetMLstClockAll();

    void SetMLstClockAll(const list<CClock>& mLstClockAll);

    priority_queue<CClockOfToday, std::vector<CClockOfToday>, _CMP_CLOCK_WAIT>& GetMPqClockWait();

    priority_queue<CClockOfToday, std::vector<CClockOfToday>, _CMP_CLOCK_WAIT>& GetMPqClockDelay();

    list<CClockOfToday>& GetMLstClockTrigger();

    void UpdateMPqClockWait();

    int GetMNLimitNum() const;

    eRULE GetMESelectRule() const;

    void SetMESelectRule(eRULE mESelectRule);

    int GetMNLimitNum();

    int ClockExit(int clockID);

private:

    bool m_bMusicFlag = true;

    list<CClock> m_lstClockAll;

    priority_queue<CClockOfToday, std::vector<CClockOfToday>, _CMP_CLOCK_WAIT> m_pqClockWait;

    priority_queue<CClockOfToday, std::vector<CClockOfToday>, _CMP_CLOCK_WAIT> m_pqClockDelay;

    list<CClockOfToday> m_lstClockTrigger;

    int m_nLimitNum;

    eRULE m_eSelectRule;
};


#endif //BACKEND_CLOCKMANAGE_H
