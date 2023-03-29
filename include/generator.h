#ifndef __QUEUE_GENERATOR_H
#define __QUEUE_GENERATOR_H

#include <omnetpp.h>

using namespace omnetpp;

class Generator : public cSimpleModule {
private:
    unsigned long user_id;
    simsignal_t user_arrival_signal;

public:
    virtual void scheduleNext() =0;

    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

};

#endif
