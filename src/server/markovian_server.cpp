#include <servers/markovian_server.h>

using namespace omnetpp;

void MarkovianServer::initialize(){
    this->distributionMean = par("distribution_mean");
    Server::initialize();
}

void MarkovianServer::scheduleNext(){
    scheduleAfter(exponential(this->distributionMean), new cMessage());
}
