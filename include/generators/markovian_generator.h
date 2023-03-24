#ifndef __QUEUE_MARKOVIAN_GENERATOR
#define __QUEUE_MARKOVIAN_GENERATOR

#include <generator.h>

using namespace omnetpp;

class MarkovianGenerator: public Generator{
private:
    double mean;
public:
    virtual void scheduleNext(void) override;
    virtual void initialize() override;
};

Define_Module(MarkovianGenerator);

#endif
