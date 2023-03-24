#include <queue.h>

using namespace omnetpp;

void Queue::initialize(){

    EV << "Initializing Queue..." << endl;

}

void Queue::handleMessage(cMessage * msg){

    EV << "Received message" << endl;

    delete msg;

}
