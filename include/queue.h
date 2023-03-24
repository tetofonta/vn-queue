#ifndef __QUEUE_QUEUE_H
#define __QUEUE_QUEUE_H

#include <omnetpp.h>

using namespace omnetpp;

class Queue: public cSimpleModule{
public:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Queue);

#endif
