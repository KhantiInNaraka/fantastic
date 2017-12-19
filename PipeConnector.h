#ifndef PIPECONNECTOR_H
#define PIPECONNECTOR_H

#include <functional>
#include <string>
using namespace std;
#define PIPECONNECTOR(cls,SrcE,DesE) \
    class cls : public basic::PipeConnector{\
    public:\
        cls(SrcE& srcElement, DesE& desElement){\
            this->desElement = &desElement;\
            this->srcElement = &srcElement;\
            srcElement.registerConnector(*this);\
        }\
		~cls(){}\
    private:\
        SrcE* srcElement;\
        DesE* desElement;\
        virtual void pipeElementFire();\
    }\

#define PIPECONNECTORCALLBACK(cls,SrcE,DesE) \
    class cls : public basic::PipeConnector{\
    public:\
        cls(SrcE& srcElement, DesE& desElement, std::function<void(SrcE*,DesE*)>){\
            this->desElement = &desElement;\
            this->srcElement = &srcElement;\
            srcElement.registerConnector(*this);\
        }\
		~cls(){}\
    private:\
        SrcE* srcElement;\
        DesE* desElement;\
        std::function<void(SrcE,DesE)> func;\
        virtual void pipeElementFire(){func(srcElement,desElement);}\
    }\

#define PIPECONNECTORIMPL(cls,SrcE,DesE) \
    class cls : public basic::PipeConnector{\
    public:\
        cls(SrcE& srcElement, DesE& desElement){\
            this->desElement = &desElement;\
            this->srcElement = &srcElement;\
            srcElement.registerConnector(*this);\
        }\
        ~cls()= default;\
    private:\
        SrcE* srcElement;\
        DesE* desElement;\
        virtual void pipeElementFire()

namespace basic {

	class PipeConnector {
    public:
        //flag: set PipeElement userFlag with PIPE_FLAG_FIRE
        //see @PipeElement::fireConnectors
        virtual void pipeElementFire(void* sender){}
        virtual void pipeElementFire(int flag){}
        virtual void pipeElementFire(){}
	};
}

#endif //PIPECONNECTOR_H
