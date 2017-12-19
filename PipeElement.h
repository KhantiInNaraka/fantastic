#ifndef PIPEELEMENT_H
#define PIPEELEMENT_H

#include <pthread.h>
#include <basic/timer_counter/Clocktimer.h>
#include <basic/pipe/PipeConnector.h>
#include<vector>
#include <map>
#include <basic/debug/Debug.h>
#include <unistd.h>
#define PIPE_FLAG_FIRE "pipe_flag_fire"
namespace basic {
	class PipeElement {
	public:
        PipeElement(bool waitCond = true);
		virtual ~PipeElement();
		void start();
		void stop();
		void wait();
		void submit();
        bool isBusy();
		void setWaitCond(bool wait);
		void registerConnector(PipeConnector& connector);
		void clearConnectors();
		void fireConnectors();
        void setUserFlag(std::string key, int value);
        int getUserFlag(std::string key);
        bool isRunning() const;

    private:
        std::vector<PipeConnector*> connectors;
		pthread_t thd;
		pthread_cond_t func_cond;
		pthread_mutex_t func_cond_mutex;
		bool running;
		bool busy;
		bool waitCond;
		bool submited;
        std::map<std::string, int> userFlags;
        virtual void thread_func(){} //deprecated
        virtual void threadFunc(){}
		virtual void threadInitial();
		virtual void threadClosing();
		static void* thread_thd_func(void* arg);

	};
}
#endif //PIPEELEMENT_H
