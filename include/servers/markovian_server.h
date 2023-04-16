#ifndef __QUEUE_MARKOVIAN_SERVER
#define __QUEUE_MARKOVIAN_SERVER

#include <server.h>

using namespace omnetpp;

class MarkovianServer: public Server{
private:
public:
    MarkovianServer(): Server(){};
    virtual void initialize(void) override;
    virtual void scheduleNext(void) override;
};

Define_Module(MarkovianServer);

#endif
