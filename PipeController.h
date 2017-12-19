#ifndef PIPECONTROLLER_H
#define PIPECONTROLLER_H
#include <vector>
#include <basic/pipe/PipeElement.h>
#include <mutex>

class PipeController
{
public:
    void registerElement(basic::PipeElement& element);
    void start();
    void stop();
    void wait();
private:
    std::mutex pipesMutex;
    std::vector<basic::PipeElement*> pipeElements;
};

#endif // PIPECONTROLLER_H
