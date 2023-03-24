#include <generators/markovian_generator.h>
#include <fmt/core.h>

using namespace omnetpp;

void MarkovianGenerator::initialize(){
    this->mean = par("mean");
    EV << fmt::format("Initialized Markov generator with mean {}", this->mean) << endl;
    Generator::initialize();
}

void MarkovianGenerator::scheduleNext(){
    this->scheduleAfter(exponential(this->mean), new cMessage());
}
