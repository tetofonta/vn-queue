#ifndef __QUEUE_QUEUE_H
#define __QUEUE_QUEUE_H

#include <omnetpp.h>
#include <types/client.h>
#include <queue>
#include <memory>

using namespace omnetpp;
using namespace std;

class Server: public cSimpleModule{
private:
    queue<Client> users_queue;
    long queue_depth = 0;

    simsignal_t user_lost_count;
    simsignal_t user_processed_count;
    simsignal_t users_in_system;
    simsignal_t user_wait_time;
    simsignal_t user_process_time;

    unique_ptr<Client> workingClient = nullptr;

    unsigned long lost_number = 0;
    unsigned long processed_number = 0;

public:
    Server();

    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

    virtual unique_ptr<Client> serveNext();

    virtual void scheduleNext() =0;

};
#endif
