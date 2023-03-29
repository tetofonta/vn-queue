#include <server.h>
#include <client_arrived/client_arrived_m.h>
#include <process_result/process_result_m.h>
#include <fmt/format.h>

using namespace std;
using namespace omnetpp;

Server::Server(){
    this->users_queue = queue<Client>();
}

void Server::initialize(){
    this->queue_depth = par("queue_depth");
    this->user_lost = registerSignal("user_lost");
    this->user_processed = registerSignal("user_processed");
    this->user_queued = registerSignal("user_queued");
    this->user_unqueued = registerSignal("user_unqueued");
}

void Server::handleMessage(cMessage * msg){
    unique_ptr<cMessage> msg_p(msg);

    if(msg_p->isSelfMessage()){
        unique_ptr<process_result_m> result_message(new process_result_m());

        result_message->setUser_id(this->workingClient->userId());
        result_message->setWait_time(this->workingClient->waitTime());
        result_message->setProcess_time(this->workingClient->processTime());
        emit(this->user_processed, result_message.get());

        this->workingClient = this->serveNext();
    } else {

        unique_ptr<client_arrived_m> client_msg(check_and_cast<client_arrived_m *>(msg_p.release()));
        Client client(client_msg->getUser_id());

        if(this->queue_depth > 0 && this->users_queue.size() >= this->queue_depth){
            EV << fmt::format("Lost user {}", client.userId()) << endl;
            emit(this->user_lost, client.userId());
            return;
        }

        this->users_queue.push(client);

        if(this->workingClient == nullptr){
            this->workingClient = this->serveNext();
        } else {
            EV << fmt::format("Queuing user {} {}/{}", client.userId(), this->users_queue.size(), this->queue_depth) << endl;
            emit(this->user_queued, this->users_queue.size());
        }
    }

}

unique_ptr<Client> Server::serveNext(){
    if(this->users_queue.size() == 0) {
        return nullptr;
    }

    auto c = make_unique<Client>(this->users_queue.front());

    this->users_queue.pop();
    emit(this->user_unqueued, c->userId());
    c->serve();
    EV << fmt::format("Serving user {}", c->userId()) << endl;
    scheduleAfter(par("serve_time"), new cMessage());
    return c;
}
