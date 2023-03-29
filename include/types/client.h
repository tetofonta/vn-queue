#ifndef __QUEUE_TYPES_CLIENT_H
#define __QUEUE_TYPES_CLIENT_H

#include <omnetpp.h>
#include <bits/unique_ptr.h>
using namespace omnetpp;

class Client{
private:
    unsigned long user_id;
    simtime_t spawn_time;
    simtime_t serve_time = SimTime::ZERO;
public:
    Client(long user_id, simtime_t spawn_time){
        this->user_id = user_id;
        this->spawn_time = spawn_time;
    };
    Client(long userid) : Client(userid, simTime()) {};
    bool hasBeenServed(void){ return this->serve_time != SimTime::ZERO; };

    inline unsigned long userId(void){ return this->user_id; };
    inline simtime_t waitTime(void){ return this->serve_time - this->spawn_time; };
    inline simtime_t processTime(void) { return simTime() - this->serve_time; };
    inline void serve(){ this->serve_time = simTime(); }
};

#endif
