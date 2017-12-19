#include "PipeController.h"

void PipeController::registerElement(basic::PipeElement &element)
{
    pipeElements.push_back(&element);
}

void PipeController::start()
{

    for(auto iter:pipeElements){
        basic::PipeElement* element = iter;
        element->start();
    }
}

void PipeController::stop()
{
    for(auto iter:pipeElements){
        basic::PipeElement* element =iter;
        element->stop();
    }
}

void PipeController::wait()
{
    for(auto iter:pipeElements){
        basic::PipeElement* element =iter;
        element->wait();
    }
}
