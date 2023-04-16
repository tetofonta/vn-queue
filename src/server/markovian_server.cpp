#include <servers/markovian_server.h>

using namespace omnetpp;

void MarkovianServer::initialize(){
    Server::initialize();
}

void MarkovianServer::scheduleNext(){
    scheduleAfter(par("scheduleInterval").doubleValue(), new cMessage());
}
