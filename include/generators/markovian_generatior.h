#ifndef __QUEUE_PARAMETRIC_GENERATOR
#define __QUEUE_PARAMETRIC_GENERATOR

#include <generator.h>

using namespace omnetpp;

class MarkovianGenerator: public Generator{
private:
    double distributionMean;
public:
    virtual void initialize(void) override;
    virtual void scheduleNext(void) override;
};

Define_Module(MarkovianGenerator);

#endif
