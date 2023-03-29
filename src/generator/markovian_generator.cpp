#include <generators/markovian_generatior.h>

using namespace omnetpp;

void MarkovianGenerator::initialize(){
    this->distributionMean = par("distribution_mean");
    Generator::initialize();
}

void MarkovianGenerator::scheduleNext(){
    scheduleAfter(exponential(this->distributionMean), new cMessage());
}
