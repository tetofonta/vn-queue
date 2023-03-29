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

simple MarkovianGenerator{
    parameters:
 	   @signal[user_arrival](type="unsigned long");
 	   @statistic[user_sent](title="User sent"; source="user_arrival"; record=vector,stats; interpolationmode=none);
 	   	
 	   double distribution_mean;
 	gates:
 	   output gate;
}

simple Server{ 	   
    parameters:
        @signal[user_lost](type="unsigned long");
        @signal[user_processed](type="process_result_m");
        @signal[user_queued](type="unsigned long");
        @signal[user_unqueued](type="unsigned long");
        
        
        int queue_depth;
        double serve_time;
 	gates:
 	   input ingress;
}


network MM1FIFO {
    submodules:
        gen: MarkovianGenerator;
        srv: Server;
    connections:
        gen.gate --> srv.ingress;
}