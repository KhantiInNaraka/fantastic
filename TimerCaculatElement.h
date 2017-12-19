#ifndef TIMERCACULATELEMENT_H
#define TIMERCACULATELEMENT_H

#include <basic/pipe/PipeElement.h>
struct eventElement
{
    int nEvent;
    long startTime;
    long duration;
};
class TimerTaskElement : public basic::PipeElement
{
public:
    TimerTaskElement();
    void startTimer(int nEvent,long duration);
    void stopTimer(int nEvent);
private:
    std::vector<eventElement> m_vecEventElement;
private:
    virtual void timerFunc(){}
    virtual void thread_func();
    virtual void timerEventHandleFunc(int){}
    long getCurrentUs();
};

#endif // TIMERCACULATELEMENT_H
