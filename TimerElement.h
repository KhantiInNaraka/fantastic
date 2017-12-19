#ifndef TIMERELEMENT_H
#define TIMERELEMENT_H
#include <basic/pipe/PipeElement.h>

class TimerElement : public basic::PipeElement
{
public:
    TimerElement(int interval);
    int getInterval() const;
    void setInterval(int value);
    long getCurrentUs();

private:
    int interval;
    double lastUs;
private:
    virtual void thread_func();
    virtual void timerFunc(){}
};

#endif // TIMERELEMENT_H
