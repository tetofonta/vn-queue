#ifndef __QUEUE_MARKOVIAN_GENERATOR
#define __QUEUE_MARKOVIAN_GENERATOR

#include <generator.h>

using namespace omnetpp;

class MarkovianGenerator: public Generator{
private:
public:
    virtual void initialize(void) override;
    virtual void scheduleNext(void) override;
};

Define_Module(MarkovianGenerator);

#endif
