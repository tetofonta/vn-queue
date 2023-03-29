#include <generators/parametric_generator.h>

using namespace omnetpp;

void ParametricGenerator::scheduleNext(){
    scheduleAfter(par("generation_interval"), new cMessage());
}
