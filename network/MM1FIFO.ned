//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

simple MarkovianGenerator
{
    parameters:
        @signal[user_arrival](type="unsigned long");

        @statistic[user_arrival](title="User Injected Count"; source="user_arrival"; record=vector,max; interpolationmode=none);


        volatile double scheduleInterval;
    gates:
        output gate;
}

simple MarkovianServer
{
    parameters:
        @signal[user_lost_count](type="unsigned long");
        @signal[user_processed_count](type="unsigned long");
        @signal[users_in_system](type="unsigned long");
        @signal[user_wait_time](type="simtime_t");
        @signal[user_process_time](type="simtime_t");

        @statistic[users_in_system](title="User in system"; source="users_in_system"; record=vector,stats; interpolationmode=none);
        @statistic[users_lost](title="User Lost Count"; source="user_lost_count"; record=vector,max; interpolationmode=none);
        @statistic[user_wait_time](title="Wait Time"; source="user_wait_time"; record=vector,stats; interpolationmode=none);
        @statistic[user_process_time](title="Process Time"; source="user_process_time"; record=vector,stats; interpolationmode=none);

        int queue_depth;
        volatile double scheduleInterval;
    gates:
        input ingress;
}


network MM1FIFO
{
    @display("bgb=282,121");
    submodules:
        gen: MarkovianGenerator {
            @display("p=55,58");
        }
        srv: MarkovianServer {
            @display("p=219,58");
        }
    connections:
        gen.gate --> srv.ingress;
}
