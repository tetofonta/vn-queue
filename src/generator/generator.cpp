#include <generator.h>
#include <client_arrived/client_arrived_m.h>
#include <memory>

using namespace std;
using namespace omnetpp;

void Generator::initialize(){

    EV << "Initializing Generator..." << endl;
    this->user_id = 0;
    this->user_arrival_signal = registerSignal("user_arrival");

    this->scheduleNext();
}

void Generator::handleMessage(cMessage * msg){
    unique_ptr<cMessage> msg_p(msg);
    if(msg->isSelfMessage()){
        auto client_message = new client_arrived_m();
        client_message->setUser_id(this->user_id);
        send(client_message, "gate");
        this->emit(this->user_arrival_signal, this->user_id++);
        this->scheduleNext();
    }
}


