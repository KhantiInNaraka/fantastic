#include "PipeElement.h"
using namespace basic;
PipeElement::PipeElement(bool waitCond) :
        running(false), func_cond_mutex(PTHREAD_MUTEX_INITIALIZER),
        func_cond(PTHREAD_COND_INITIALIZER),
        busy(false), waitCond(waitCond), submited(false), thd() {
}

void PipeElement::start() {
	if (running)
		return;
	running = true;
	pthread_create(&thd, nullptr, &thread_thd_func, this);
}

void PipeElement::stop() {
	running = false;
    submit();
}

void PipeElement::wait() {
	pthread_join(thd, nullptr);
}

void PipeElement::submit() {
	submited = true;
	pthread_cond_signal(&func_cond);
}

bool PipeElement::isBusy() {
    return busy;
}

void PipeElement::setWaitCond(bool wait) {
	waitCond = wait;
}

void PipeElement::registerConnector(PipeConnector& connector) {
	connectors.push_back(&connector);
}

void PipeElement::clearConnectors() {
	connectors.clear();
}

void PipeElement::fireConnectors() {
	for (size_t i = 0; i < connectors.size(); ++i) {
		connectors[i]->pipeElementFire();
        connectors[i]->pipeElementFire(this);
        connectors[i]->pipeElementFire(getUserFlag(PIPE_FLAG_FIRE));
	}
}

void PipeElement::setUserFlag(std::string key, int value)
{
    userFlags[key] = value;
}

int PipeElement::getUserFlag(std::string key)
{
    return userFlags[key];
}

bool PipeElement::isRunning() const
{
    return running;
}

void PipeElement::threadInitial() {

}

void PipeElement::threadClosing() {

}

PipeElement::~PipeElement() {
}

void * PipeElement::thread_thd_func(void * arg) {
    PipeElement* element = (PipeElement*) arg;
    pthread_mutex_lock(&element->func_cond_mutex);
	element->threadInitial();
	while (element->running) {
		if (element->waitCond && !element->submited) {
			pthread_cond_wait(&element->func_cond, &element->func_cond_mutex);
            if(!element->running){
                break;
            }
		}
		element->busy = true;
		element->thread_func();
        element->threadFunc();
		element->busy = false;
		element->submited = false;
	}
    element->threadClosing();
    pthread_mutex_unlock(&element->func_cond_mutex);
	return nullptr;
}
