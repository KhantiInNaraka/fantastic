#include "TimerCaculatElement.h"
#include <sys/time.h>
TimerTaskElement::TimerTaskElement(): basic::PipeElement(false)
{

}

void TimerTaskElement::thread_func()
{
    timerFunc();
    for(int i=0;i<m_vecEventElement.size();i++)
    {
        if((getCurrentUs()-m_vecEventElement[i].startTime)>m_vecEventElement[i].duration)
        {
            timerEventHandleFunc(m_vecEventElement[i].nEvent);
        }
    }
}

long TimerTaskElement::getCurrentUs()
{
    timeval time;
    gettimeofday( &time, nullptr);
    return time.tv_sec * 1000000 + time.tv_usec;
}


void TimerTaskElement::startTimer(int nEvent,long duration)
{
    eventElement tmp;
    tmp.nEvent = nEvent;
    tmp.duration = duration;
    tmp.startTime = getCurrentUs();
    m_vecEventElement.push_back(tmp);
}

void TimerTaskElement::stopTimer(int nEvent)
{
    int nIndex = -1;
    for(int i=0;i<m_vecEventElement.size();i++)
    {
        if(m_vecEventElement[i].nEvent==nEvent)
        {
            nIndex = i;
        }
    }
    if(-1!=nIndex)
    {
        m_vecEventElement.erase(m_vecEventElement.begin()+nIndex);
    }
}
