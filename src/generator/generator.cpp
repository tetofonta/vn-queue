#include <generator.h>

using namespace omnetpp;

void Generator::initialize(){

    EV << "Initializing Generator..." << endl;
    this->user_id = 0;
    this->user_arrival_signal = registerSignal("user_arrival");

    this->scheduleNext();
}

void Generator::handleMessage(cMessage * msg){

    if(msg->isSelfMessage()){
        send(new cMessage(""), "gate");
        this->emit(this->user_arrival_signal, this->user_id++);
        delete msg;

        this->scheduleNext();
    }

}

