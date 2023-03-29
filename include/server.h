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
    simsignal_t user_lost;
    simsignal_t user_processed;
    simsignal_t user_queued;
    simsignal_t user_unqueued;

    unique_ptr<Client> workingClient = nullptr;
public:
    Server();

    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

    unique_ptr<Client> serveNext();

};

Define_Module(Server);

#endif
