#include <generators/markovian_generatior.h>

using namespace omnetpp;

void MarkovianGenerator::initialize(){
    Generator::initialize();
}

void MarkovianGenerator::scheduleNext(){
    scheduleAfter(par("scheduleInterval").doubleValue(), new cMessage());
}
