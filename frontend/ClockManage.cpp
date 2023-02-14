#include "pch.h"
#include "ClockManage.h"


void CClockManage::start() {
    File file;
    file.GetClocksFromFile(m_lstClockAll);
    m_nLimitNum = m_lstClockAll.size();
}

void CClockManage::GetNowTime()
{
    time(&m_tCurrentTime);
    localtime_s(&m_srtCurrentTime, &m_tCurrentTime);
    UpdateMPqClockWait();
}

void CClockManage::ClockRing()
{
    if (!m_lstClockTrigger.empty()&&m_bMusicFlag)
    {
        RingClock();
    }
}

void CClockManage::Record()
{
    /*待触发队列闹钟，出队列，进入触发状态列表*/
    while (!m_pqClockWait.empty() && (m_pqClockWait.top().GetMTBeginTime() <= m_tCurrentTime && m_tCurrentTime < m_pqClockWait.top().GetMTBeginTime() + 60))
    {
        CClockOfToday clockOfToday(m_pqClockWait.top());
        clockOfToday.SetMBTrigger(true);
        m_lstClockTrigger.push_back(clockOfToday);
        m_pqClockWait.pop();
        m_bMusicFlag = true;
        m_bFlagShow = true;
    }
    /*延迟触发队列闹钟，出队列，进入触发状态列表*/
    while (!m_pqClockDelay.empty() && (m_pqClockDelay.top().GetMTBeginTime() <= m_tCurrentTime && m_tCurrentTime < m_pqClockDelay.top().GetMTBeginTime() + 60))
    {
        CClockOfToday clockOfToday(m_pqClockDelay.top());
        clockOfToday.SetMBTrigger(true);
        m_lstClockTrigger.push_back(clockOfToday);
        m_pqClockDelay.pop();
        m_bMusicFlag = true;
        m_bFlagShow = true;
    }
    /*将触发闹列表列优先级最高闹钟响铃状态置为真，其余闹钟为假*/
    if (!m_lstClockTrigger.empty())
    {
        list<CClockOfToday>::iterator it;
        for (it = m_lstClockTrigger.begin(); it != m_lstClockTrigger.end(); it++)
        {
            it->SetMBRing(false);
        }
        m_lstClockTrigger.back().SetMBRing(true);
    }

    /*记录日志，闹钟确认延时，维护延时队列*/
    for (list<CClockOfToday>::iterator it = m_lstClockTrigger.begin(); it != m_lstClockTrigger.end(); it++)
    {
        time_t end;
        int t = it->GetMSrtClock().GetMSDuration() * 60;
        end = it->GetMTBeginTime() + t;
        if (end < m_tCurrentTime || !it->IsMBTrigger())
        {
            CClockOfToday clockOfToday(*it);
            if (clockOfToday.GetMSCount() < 3)
            {
                Delay(clockOfToday);
                m_pqClockDelay.push(clockOfToday);
            }
            else
            {
                Confirm(clockOfToday);
            }
            m_lstClockTrigger.erase(it);
            break;
        }
    }
}

CClockManage::CClockManage()
{

}

list<CClock>& CClockManage::GetMLstClockAll()
{
    return m_lstClockAll;
}

void CClockManage::SetMLstClockAll(const list<CClock>& mLstClockAll)
{
    m_lstClockAll = mLstClockAll;
}

priority_queue<CClockOfToday, std::vector<CClockOfToday>, _CMP_CLOCK_WAIT>& CClockManage::GetMPqClockWait() {
    return m_pqClockWait;
}

priority_queue<CClockOfToday, std::vector<CClockOfToday>, _CMP_CLOCK_WAIT>& CClockManage::GetMPqClockDelay()
{
    return m_pqClockDelay;
}

list<CClockOfToday>& CClockManage::GetMLstClockTrigger()
{
    return m_lstClockTrigger;
}

void CClockManage::UpdateMPqClockWait()
{
    std::lock_guard<std::mutex> mtxLocker(m_mutexPqWait);
    while (!m_pqClockWait.empty())
    {
        m_pqClockWait.pop();
    }
    time_t t;
    tm tm;
    time(&t);
    localtime_s(&tm, &t);
    list<CClock>::iterator it;
    //维护今日等待响铃队列
    for (it = m_lstClockAll.begin(); it != m_lstClockAll.end(); it++)
    {
        //闹钟开关标志
        if (it->IsMBFlag())
        {
            switch (it->GetMELoopType())
            {
            case single:
            {
                CClockOfToday clockOfToday(*it);
                if (clockOfToday.GetMTBeginTime() >= t)
                {
                    m_pqClockWait.push(clockOfToday);
                }
                break;
            }
            case hourCycle:
            {
                CClockOfToday clockOfToday(*it);
                if (clockOfToday.GetMTBeginTime() >= t)
                {
                    m_pqClockWait.push(clockOfToday);
                }
                break;
            }
            case dayCycle:
            {
                CClockOfToday clockOfToday(*it);
                if (clockOfToday.GetMTBeginTime() >= t)
                {
                    m_pqClockWait.push(clockOfToday);
                }
                break;
            }
            case weekCycle:
            {
                if (it->GetMEszWeek()[tm.tm_wday])
                {
                    CClockOfToday clockOfToday(*it);
                    if (clockOfToday.GetMTBeginTime() >= t)
                    {
                        m_pqClockWait.push(clockOfToday);
                    }
                }
                break;
            }
            case monthCycle:
            {
                if (it->GetMSDay() == tm.tm_mday)
                {
                    CClockOfToday clockOfToday(*it);
                    if (clockOfToday.GetMTBeginTime() >= t)
                    {
                        m_pqClockWait.push(clockOfToday);
                    }
                }
                break;
            }
            default:
                break;
            }
        }
    }
}

int CClockManage::GetMNLimitNum() const
{
    return m_nLimitNum;
}


eRULE CClockManage::GetMESelectRule() const
{
    return m_eSelectRule;
}

void CClockManage::SetMESelectRule(eRULE mESelectRule)
{
    m_eSelectRule = mESelectRule;
}

int CClockManage::GetMNLimitNum()
{
    m_nLimitNum = m_lstClockAll.size();
    return m_nLimitNum;
}

int CClockManage::ClockExit(int clockID)
{
    int flag = 0;
    list<CClock>::iterator it;
    for (it = m_lstClockAll.begin(); it != m_lstClockAll.end(); it++)
    {
        if (it->GetMNClockId() == clockID)
        {
            flag = 1;
        }
    }
    return flag;
}

int CClockManage::AddClock(CClock& clock)
{
    int flag = 0;
    if (m_nLimitNum < 256)
    {
        list<CClock>::iterator it;
        for (it = m_lstClockAll.begin(); it != m_lstClockAll.end(); it++)
        {
            if (clock.GetMNClockId() == it->GetMNClockId())
            {
                return flag;
            }
        }
        m_lstClockAll.push_back(clock);
        File file;
        file.AddClockToFile(clock);
        m_nLimitNum++;
        flag = 1;
    }
    else
    {
        cout << "Too much clocks!" << endl;
    }
    return flag;
}

int CClockManage::DeleteClock(int clockID)
{
    int flag = 0;
    for (list<CClock>::iterator it = m_lstClockAll.begin(); it != m_lstClockAll.end(); it++)
    {
        if (it->GetMNClockId() == clockID)
        {
            flag = 1;
            m_lstClockAll.erase(it);
            break;
        }
    }
    priority_queue<CClockOfToday, std::vector<CClockOfToday>, _CMP_CLOCK_WAIT> tempClockDelay;
    while (!m_pqClockDelay.empty())
    {
        CClockOfToday clockOfToday(m_pqClockDelay.top());
        list<CClock>::iterator it;
        for (it = m_lstClockAll.begin(); it != m_lstClockAll.end(); it++)
        {
            if (it->GetMNClockId() == clockOfToday.GetMSrtClock().GetMNClockId())
            {
                tempClockDelay.push(clockOfToday);
                break;
            }
        }
        m_pqClockDelay.pop();
    }
    m_pqClockDelay = tempClockDelay;
    File file;
    file.DeleteClockFromFile(clockID);
    return flag;
}

int CClockManage::UpdateClock(int clockID, char chszClockName[], eLOOP_TYPE eLoopType, short sMin, short sHour, short sDay, bool eszWeek[], short sDuration, eMUSIC_TYPE eMusicType)
{
    int flag = 0;
    for (list<CClock>::iterator it = m_lstClockAll.begin(); it != m_lstClockAll.end(); it++) {
        if (it->GetMNClockId() == clockID)
        {
            it->SetMBFlag(true);
            it->SetMchszClockName(chszClockName);
            it->SetMELoopType(eLoopType);
            it->SetMSMin(sMin);
            it->SetMSHour(sHour);
            it->SetMSDay(sDay);
            it->SetMEszWeek(eszWeek);
            it->SetMSDuration(sDuration);
            it->SetMEMusicType(eMusicType);
            it->SetMTCreateOrChangeTime(m_tCurrentTime);
            switch (it->GetMELoopType()) {
            case single:
                it->ClockDay(sMin, sHour);
                break;
            case hourCycle:
                it->ClockHour(sMin);
                break;
            case dayCycle:
                it->ClockDay(sMin, sHour);
                break;
            case weekCycle:
            {
                it->ClockWeek(sMin, sHour, eszWeek);
                int sum = 0;
                bool* temp = it->GetMEszWeek();
                for (int i = 0; i < 7; i++) {
                    sum += *(temp + i);
                }
                if (7 == sum)
                {
                    it->SetMELoopType(dayCycle);
                    it->ClockDay(sMin, sHour);
                }
                break;
            }
            case monthCycle:
                it->ClockMonth(sMin, sHour, sDay);
                break;
            default:
                break;
            }
            flag = 1;
            break;
        }

    }
    priority_queue<CClockOfToday, std::vector<CClockOfToday>, _CMP_CLOCK_WAIT> tempClockDelay;
    while (!m_pqClockDelay.empty())
    {
        CClockOfToday clockOfToday(m_pqClockDelay.top());
        if (clockID != clockOfToday.GetMSrtClock().GetMNClockId())
        {
            tempClockDelay.push(clockOfToday);
        }
        m_pqClockDelay.pop();
    }
    m_pqClockDelay = tempClockDelay;
    File file;
    file.UpdateClockToFile(m_lstClockAll);
    return flag;
}


void CClockManage::ShowClockAll()
{
    list<CClock>::iterator it;
    cout << "ClockID" << " " << "ClockName" << " " << "LoopType" << " " << "TargetTime" << endl;
    for (it = m_lstClockAll.begin(); it != m_lstClockAll.end(); it++)
    {
        cout << it->GetMNClockId() << " " << it->GetMChszClockName() << "     " << short(it->GetMELoopType()) << "   " << it->GetMSDay()
            << " " << it->GetMSHour() << " " << it->GetMSMin() << endl;
    }
}

void CClockManage::ShowRecord()
{
    list<_RECORD>::iterator it;
    File file;
    list<_RECORD> records;
    file.GetRecordsFromFile(records);
    for (it = records.begin(); it != records.end(); it++)
    {
        cout << it->chszClockName << ":" << it->bOperate << ":" << it->tRecordTime << endl;
    }
}

CClock& CClockManage::GetClockByID(const int clockID)
{
    list<CClock>::iterator it;
    for (it = m_lstClockAll.begin(); it != m_lstClockAll.end(); it++)
    {
        if (it->GetMNClockId() == clockID)
        {
            return *it;
        }
    }
    return *it;
}

void CClockManage::SortByRule()
{
    list<CClock>::iterator it;
    switch (m_eSelectRule)
    {
    case byFlag:
    {
        priority_queue<CClock, std::vector<CClock>, _CMP_CLOCK_SORT_BY_FLAG> pqClocksByFlag;
        for (it = m_lstClockAll.begin(); it != m_lstClockAll.end(); it++) {
            pqClocksByFlag.push(*it);
        }
        m_lstClockAll.clear();
        while (!pqClocksByFlag.empty()) {
            m_lstClockAll.push_back(pqClocksByFlag.top());
            pqClocksByFlag.pop();
        }
        break;
    }
    case byID:
    {
        priority_queue<CClock, std::vector<CClock>, _CMP_CLOCK_SORT_BY_ID> pqClocksByID;
        for (it = m_lstClockAll.begin(); it != m_lstClockAll.end(); it++) {
            pqClocksByID.push(*it);
        }
        m_lstClockAll.clear();
        while (!pqClocksByID.empty()) {
            m_lstClockAll.push_back(pqClocksByID.top());
            pqClocksByID.pop();
        }
        break;
    }
    case byName:
    {
        priority_queue<CClock, std::vector<CClock>, _CMP_CLOCK_SORT_BY_NAME> pqClocksByName;
        for (it = m_lstClockAll.begin(); it != m_lstClockAll.end(); it++)
        {
            pqClocksByName.push(*it);
        }
        m_lstClockAll.clear();
        while (!pqClocksByName.empty())
        {
            m_lstClockAll.push_back(pqClocksByName.top());
            pqClocksByName.pop();
        }
        break;
    }
    default:
    {
        priority_queue<CClock, std::vector<CClock>, _CMP_CLOCK_SORT_BY_FLAG> pqClocksByFlag;
        for (it = m_lstClockAll.begin(); it != m_lstClockAll.end(); it++) {
            pqClocksByFlag.push(*it);
        }
        m_lstClockAll.clear();
        while (!pqClocksByFlag.empty()) {
            m_lstClockAll.push_back(pqClocksByFlag.top());
            pqClocksByFlag.pop();
        }
        break;
    }
    }
}

void CClockManage::RingClock()
{
    string str;
    eMUSIC_TYPE eMusicType = m_lstClockTrigger.back().GetMSrtClock().GetMEMusicType();
    switch (eMusicType)
    {
    case dida:
    {
        str = "dida.wav";
        break;
    }
    case kuaimen:
    {
        str = "kuaimen.wav";
        break;
    }
    case zhuanhuan:
    {
        str = "chang.wav";
        break;
    }
    default:
        break;
    }
    int nlen = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str.c_str(), -1, NULL, 0);
    wchar_t* wname = new wchar_t[nlen];
    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str.c_str(), -1, wname, nlen);
    PlaySound(wname, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    m_bMusicFlag = false;
}

int CClockManage::UserConfirm()
{
    int flag = 0;
    if (!m_lstClockTrigger.empty())
    {
        m_lstClockTrigger.back().SetMSCount(3);
        m_lstClockTrigger.back().SetMBTrigger(false);
        flag = 1;
    }
    return flag;
}

int CClockManage::UserDelay(short sTime)
{
    int flag = 0;
    if (!m_lstClockTrigger.empty())
    {
        if (m_lstClockTrigger.back().GetMSCount() < 3)
        {
            m_lstClockTrigger.back().SetMSDelay(sTime);
            m_lstClockTrigger.back().SetMBTrigger(false);
            flag = 1;
        }
        else
        {
            m_lstClockTrigger.back().SetMBTrigger(false);
            flag = 2;
        }
    }
    return flag;
}

int CClockManage::OpenClock(int clockID)
{
    int flag = 0;
    list<CClock>::iterator it;
    for (it = m_lstClockAll.begin(); it != m_lstClockAll.end(); it++)
    {
        if (clockID == it->GetMNClockId())
        {
            if (it->IsMBFlag())
            {
                flag = 1;
            }
            else
            {
                it->SetMBFlag(true);
                flag = 1;
            }
        }
    }
    File file;
    file.UpdateClockToFile(m_lstClockAll);
    return flag;
}

int CClockManage::CloseClock(int clockID)
{
    int flag = 0;
    list<CClock>::iterator it;
    for (it = m_lstClockAll.begin(); it != m_lstClockAll.end(); it++)
    {
        if (clockID == it->GetMNClockId())
        {
            if (it->IsMBFlag())
            {
                it->SetMBFlag(false);
                flag = 1;
            }
            else
            {
                flag = 1;
            }
        }
    }
    priority_queue<CClockOfToday, std::vector<CClockOfToday>, _CMP_CLOCK_WAIT> tempClockDelay;
    while (!m_pqClockDelay.empty())
    {
        CClockOfToday clockOfToday(m_pqClockDelay.top());
        if (clockID != clockOfToday.GetMSrtClock().GetMNClockId())
        {
            tempClockDelay.push(clockOfToday);
        }
        m_pqClockDelay.pop();
    }
    m_pqClockDelay = tempClockDelay;
    File file;
    file.UpdateClockToFile(m_lstClockAll);
    return flag;
}

void CClockManage::Delay(CClockOfToday& clockOfToday)
{
    clockOfToday.SetMSCount((short)(clockOfToday.GetMSCount() + 1));
    int temp = clockOfToday.GetMSDelay() * 60;
    clockOfToday.SetMTBeginTime(clockOfToday.GetMTBeginTime() + temp);
    clockOfToday.SetMBTrigger(false);
    if (clockOfToday.IsMBRing())
    {
        clockOfToday.SetMBRing(false);
        PlaySound(NULL, NULL, NULL);
        m_bMusicFlag = true;
    }
    auto* pRecord = new _RECORD;
    time_t t;
    time(&t);
    pRecord->tRecordTime = t;
    if (strlen(clockOfToday.GetMSrtClock().GetMChszClockName()) < 18)
    {
        for (int i = 0; i < strlen(clockOfToday.GetMSrtClock().GetMChszClockName()); i++)
        {
            pRecord->chszClockName[i] = clockOfToday.GetMSrtClock().GetMChszClockName()[i];
        }
        for (int i = strlen(clockOfToday.GetMSrtClock().GetMChszClockName()); i < 18; i++)
        {
            pRecord->chszClockName[i] = '\0';
        }
    }
    pRecord->nRecordID = (int)t;
    pRecord->nClockID = clockOfToday.GetMSrtClock().GetMNClockId();
    pRecord->nRsv = 0;
    pRecord->bOperate = false;
    pRecord->chRsv = ' ';
    File file;
    file.AddRecordToFile(*pRecord);
    delete pRecord;
}

void CClockManage::Confirm(CClockOfToday& clockOfToday)
{
    auto* pRecord = new _RECORD;
    time_t t;
    time(&t);
    pRecord->tRecordTime = t;
    clockOfToday.SetMBTrigger(false);
    if (clockOfToday.IsMBRing())
    {
        clockOfToday.SetMBRing(false);
        PlaySound(NULL, NULL, NULL);
        m_bMusicFlag = true;
    }

    if (clockOfToday.GetMSrtClock().GetMELoopType() == single)
    {

        list<CClock>::iterator it;
        for (it = m_lstClockAll.begin(); it != m_lstClockAll.end(); it++)
        {
            if (it->GetMNClockId() == clockOfToday.GetMSrtClock().GetMNClockId())
            {
                it->SetMBFlag(false);
                break;
            }
        }
        File file;
        file.UpdateClockToFile(m_lstClockAll);
    }

    if (strlen(clockOfToday.GetMSrtClock().GetMChszClockName()) < 18)
    {
        for (int i = 0; i < strlen(clockOfToday.GetMSrtClock().GetMChszClockName()); i++)
        {
            pRecord->chszClockName[i] = clockOfToday.GetMSrtClock().GetMChszClockName()[i];
        }
        for (int i = strlen(clockOfToday.GetMSrtClock().GetMChszClockName()); i <= 18; i++)
        {
            pRecord->chszClockName[i] = '\0';
        }
    }
    pRecord->nRecordID = (int)t;
    pRecord->nClockID = clockOfToday.GetMSrtClock().GetMNClockId();
    pRecord->nRsv = 0;
    pRecord->bOperate = true;
    pRecord->chRsv = ' ';
    File file;
    file.AddRecordToFile(*pRecord);
    delete pRecord;
}
