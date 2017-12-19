#include "TimerElement.h"
#include <sys/time.h>

TimerElement::TimerElement(int interval) :
    PipeElement(false),interval(interval*1000)
{
    long current = getCurrentUs();
    lastUs = current - current%interval;
}

int TimerElement::getInterval() const
{
    return interval;
}

void TimerElement::setInterval(int value)
{
    interval = value;
}

void TimerElement::thread_func()
{
    usleep(1000);
    long current = getCurrentUs();
    if(current-lastUs>interval){
        lastUs = current - current%(interval);
        timerFunc();
    }
}

long TimerElement::getCurrentUs()
{
    timeval time;
    gettimeofday( &time, nullptr);
    return time.tv_sec * 1000000 + time.tv_usec;
}
