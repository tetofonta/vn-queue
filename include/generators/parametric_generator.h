#ifndef __QUEUE_PARAMETRIC_GENERATOR
#define __QUEUE_PARAMETRIC_GENERATOR

#include <generator.h>

using namespace omnetpp;

class ParametricGenerator: public Generator{
public:
    virtual void scheduleNext(void) override;
};

Define_Module(ParametricGenerator);

#endif
