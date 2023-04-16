#include <server.h>
#include <client_arrived/client_arrived_m.h>
#include <fmt/format.h>

using namespace std;
using namespace omnetpp;

Server::Server(){
    this->users_queue = queue<Client>();
}

void Server::initialize(){
    this->queue_depth = par("queue_depth");
    this->user_lost_count = registerSignal("user_lost_count");
    this->user_processed_count = registerSignal("user_processed_count");
    this->users_in_system = registerSignal("users_in_system");
    this->user_process_time = registerSignal("user_process_time");
    this->user_wait_time = registerSignal("user_wait_time");
}

void Server::handleMessage(cMessage * msg){
    unique_ptr<cMessage> msg_p(msg);

    if(msg_p->isSelfMessage()){

        emit(this->user_processed_count, ++this->processed_number);
        emit(this->user_wait_time, this->workingClient->waitTime());
        emit(this->user_process_time, this->workingClient->processTime());
        EV << fmt::format("Finished serving user {}", this->workingClient->userId());

        this->workingClient = this->serveNext();
    } else {
        unique_ptr<client_arrived_m> client_msg(check_and_cast<client_arrived_m *>(msg_p.release()));
        Client client(client_msg->getUser_id());

        if(this->workingClient == nullptr){
            this->users_queue.push(client);
            this->workingClient = this->serveNext();
        } else {
            if(this->queue_depth > 0 && this->users_queue.size() >= this->queue_depth){
                EV << fmt::format("Lost user {}", client.userId()) << endl;
                emit(this->user_lost_count, ++this->lost_number);
                emit(this->users_in_system, this->users_queue.size() + 1);
                return;
            } else {
                this->users_queue.push(client);
                EV << fmt::format("Queuing user {} {}/{}", client.userId(), this->users_queue.size(), this->queue_depth) << endl;
                emit(this->users_in_system, this->users_queue.size() + 1); //server is busy and user has been queued
            }
        }
    }

}

unique_ptr<Client> Server::serveNext(){
    emit(this->users_in_system, this->users_queue.size()); //the server has finished working on someone, considering that if a user would be popped it would still be in the system we can send the actual queue length

    if(this->users_queue.size() == 0) {
        return nullptr;
    }

    auto c = make_unique<Client>(this->users_queue.front());

    this->users_queue.pop();
    c->serve();
    EV << fmt::format("Serving user {}", c->userId()) << endl;
    this->scheduleNext();
    return c;
}
