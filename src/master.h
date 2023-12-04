#pragma once


#include <queue>

#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono> //timeout for slow worker and worker failure
#include <future> //to store the asynchronous results
#include <filesystem>
#include "mapreduce_spec.h"
#include "file_shard.h"
//for mkdir
#include <iostream>
#include <stdlib.h>
#include <sys/stat.h>
#include <grpcpp/grpcpp.h>
#include <grpc/support/log.h>

#include "masterworker.pb.h"
#include "masterworker.grpc.pb.h"



using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using grpc::CompletionQueue;
using grpc::ClientAsyncResponseReader;

using masterworker::MasterWorker;
using masterworker::HelloReply;
using masterworker::HelloRequest;
using masterworker::MapTaskRequest;
using masterworker::MapTaskCompleted;
using masterworker::ReduceTaskRequest;
using masterworker::ReduceTaskCompleted;
using masterworker::Fileshard;
using masterworker::Minishard;
using masterworker::IntermediateFile;
using masterworker::OutputFile;

using namespace std;

class GreeterClient {
 public:
  GreeterClient(std::shared_ptr<Channel> channel)
      : stub_(MasterWorker::NewStub(channel)), cq_() {}

 
  int AssignMapTask(const MapTaskRequest& request, promise<MapTaskCompleted>* promise);
  int AssignReduceTask(const ReduceTaskRequest& request, promise<ReduceTaskCompleted>* promise);
  
 

 private:
 // Out of the passed in Channel comes the stub, stored here, our view of the
  // server's exposed services.
  std::unique_ptr<MasterWorker::Stub> stub_;
  // The producer-consumer queue we use to communicate asynchronously with the
  // gRPC runtime.
  CompletionQueue cq_;
};
//Implementation of AssignMapTask
int GreeterClient::AssignMapTask(const MapTaskRequest& request, promise<MapTaskCompleted>* promise) {
	ClientContext context;
	Status status;
	MapTaskCompleted response;
	//5 second deadline for rpc
	auto deadline = std::chrono::system_clock::now() + std::chrono::seconds(180);
	context.set_deadline(deadline);
	
	//future/promise
	//std::promise<MapTaskCompleted> promise;
	//auto promise_ptr = std::make_shared<std::promise<MapTaskCompleted>>();
	//auto future = promise_ptr->get_future();
	
	std::unique_ptr<ClientAsyncResponseReader<MapTaskCompleted>> rpc(
		stub_->PrepareAsyncAssignMapTask(&context, request, &cq_));
	rpc->StartCall();
	//pass in promise as "tag"
	rpc->Finish(&response, &status, (void*)1);
	
	void* got_tag;
	bool ok = false;
	GPR_ASSERT(cq_.Next(&got_tag, &ok));
	
		GPR_ASSERT(ok);
		//std::shared_ptr<std::promise<MapTaskCompleted>> promise_ptr =
        //std::static_pointer_cast<std::promise<MapTaskCompleted>>(got_tag);
		//std::promise<MapTaskCompleted>* promise_ptr = static_cast<std::promise<MapTaskCompleted>*>(got_tag);
		 //auto promise_ptr = static_cast<std::promise<MapTaskCompleted>*>(got_tag);
       		 try {
           		 if (status.ok()) {
                		std::cout << "Master: got map response" << std::endl;
                		promise->set_value(response);
                		return 1; //success
            		} else if (status.error_code() == grpc::DEADLINE_EXCEEDED) {
                		std::cout << "Error: Map task timed out" << std::endl;
                		promise->set_value(MapTaskCompleted());
                		return 0; // retry
            		} else {
                		std::cout << status.error_code() << ": " << status.error_message() << std::endl;
                		promise->set_value(MapTaskCompleted());
                		return 0; //retry
            		}
        	} catch (const std::exception& e) {
            		std::cerr << "Exception while setting promise value: " << e.what() << std::endl;
            		promise->set_value(MapTaskCompleted());
            		return 0; //retry
        	}
        //on success
        //return 1;
        

}

//Implementation of AssignReduceTask
int GreeterClient::AssignReduceTask(const ReduceTaskRequest& request, promise<ReduceTaskCompleted>* promise){
	ClientContext context;
	Status status;
	ReduceTaskCompleted response;
	
	//5 second deadline for rpc
	auto deadline = std::chrono::system_clock::now() + std::chrono::seconds(180);
	context.set_deadline(deadline);
	
	//future/promise
	//std::promise<ReduceTaskCompleted> promise;
	//auto promise_ptr = std::make_shared<std::promise<ReduceTaskCompleted>>();
	//auto future = promise_ptr->get_future();
	
	std::unique_ptr<ClientAsyncResponseReader<ReduceTaskCompleted>> rpc(
		stub_->PrepareAsyncAssignReduceTask(&context, request, &cq_));
	rpc->StartCall();
	rpc->Finish(&response, &status, (void*)1);
	
	void* got_tag;
	bool ok = false;
	GPR_ASSERT(cq_.Next(&got_tag, &ok));
	
		GPR_ASSERT(ok);
		//auto promise_ptr = static_cast<std::promise<ReduceTaskCompleted>*>(got_tag);
       		 try {
           		 if (status.ok()) {
                		std::cout << "Master: got reduce response" << std::endl;
                		promise->set_value(response);
                		return 1; //success
            		} else if (status.error_code() == grpc::DEADLINE_EXCEEDED) {
                		std::cout << "Error: Reduce task timed out" << std::endl;
                		promise->set_value(ReduceTaskCompleted());
                		return 0; //retry
            		} else {
                		std::cout << status.error_code() << ": " << status.error_message() << std::endl;
                		promise->set_value(ReduceTaskCompleted());
                		return 0; //retry
            		}
        	} catch (const std::exception& e) {
            		std::cerr << "Exception while setting promise value: " << e.what() << std::endl;
            		promise->set_value(ReduceTaskCompleted());
            		return 0; //retry
        	}
        
        //return "reduce success";
	
	
	
}


/* CS6210_TASK: Handle all the bookkeeping that Master is supposed to do.
	This is probably the biggest task for this project, will test your understanding of map reduce */
class Master {

	public:
		/* DON'T change the function signature of this constructor */
		Master(const MapReduceSpec&, const std::vector<FileShard>&);

		/* DON'T change this function's signature */
		bool run();

	private:
		/* NOW you can add below, data members and member functions as per the need of your implementation*/
		MapReduceSpec spec;
		std::vector<FileShard> shards;
		int maps;
		int reduces;
		std::string output_dir;
		//std::vector<std::string> worker_ips_;
		//std::vector<std::unique_ptr<GreeterClient>> worker_clients_;
		int map_task_count;
		int reduce_task_count;
		
		//GreeterClient greeter;
		//for all worker ip passed in
		std::vector<std::string> worker_ips_;
    		std::vector<std::unique_ptr<GreeterClient>> worker_clients_;
		
		std::queue<int> available_workers;
		std::vector<bool> map_task_status;
		std::vector<bool> reduce_task_status;
		
		//future vectors for map and reduce tasks
		std::vector<std::future<MapTaskCompleted>> future_map_tasks;
		std::vector<std::future<ReduceTaskCompleted>> future_reduce_tasks;
		
		
    		
    		void initializeWorkerClients();
    		void assignMapTasks();
    		void assignReduceTasks();
    		
    		void waitForMapTask();
    		void waitForReduceTask();
    		void handleMapTaskCompletion();
    		void handleReduceTaskCompletion();
		
		
};


/* CS6210_TASK: This is all the information your master will get from the framework.
	You can populate your other class data members here if you want */
Master::Master(const MapReduceSpec& mr_spec, const std::vector<FileShard>& file_shards):
	spec(mr_spec),
	shards(file_shards),
	maps(file_shards.size()),
	output_dir(spec.out_dir),
	reduces(spec.num_out_files),
	map_task_count(0),
	reduce_task_count(0) {
	//greeter(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials())){
	//Initialize Worker(Greeter) clients
	initializeWorkerClients();
	
}

void Master::initializeWorkerClients(){
	//create worker/greeter client instance for each worker IP
	//CHECK HERE: Make spec.worker workers
	//But make only one grpc channel - maybe localhost:50051- and then use threads??
	for(const std::string& ip: spec.ips){
		worker_ips_.push_back(ip);
		worker_clients_.emplace_back(std::make_unique<GreeterClient>(
			grpc::CreateChannel(ip, grpc::InsecureChannelCredentials())));
	}
	for(int i = 0; i < spec.workers; ++i){
		available_workers.push(i);
	}
	map_task_status.resize(maps, false);
	reduce_task_status.resize(reduces, false);
}
	//ini

//Helper methods implementation
void Master::assignMapTasks(){
	//assign map tasks to available workers
	const char * out_dir = output_dir.c_str();
	std::cout << "assignMaptask worker_clients_ size = " << worker_clients_.size() <<std::endl;
	for(int i = 0; i < maps; ++i){
		int worker_index = (available_workers.front() % worker_clients_.size()); //-1 or not??
		
		std::cout << "assingMapTask: worker_index = " << worker_index << std::endl;
		available_workers.pop();
		MapTaskRequest request;
		request.set_taskid(map_task_count);
		request.set_userid(spec.id);
		for(const MiniShard& mini: shards[i].shards){
			masterworker::Minishard* miniShard = request.mutable_fileshard()->add_shards();
			miniShard->set_file_name(mini.file_name);
			miniShard->set_start_offset(mini.start_offset);
			miniShard->set_end_offset(mini.end_offset);
		}

		request.set_num_reduces(reduces);
		//make the call
		
		//std::cout << "worker calling AssignMapTask with worker ip" <<worker_ips_[worker_index] <<std::endl;
		promise<MapTaskCompleted> promise;
		future<MapTaskCompleted> future = promise.get_future();
		// std::cout<< "calling mkdir" << std::endl;
		// mkdir(out_dir, 0777);
		int result = worker_clients_[worker_index]->AssignMapTask(request, &promise);
		std::cout << "map result = " << result << std::endl;
		std::future<MapTaskCompleted> temp_future;
		while(result == 0){
			//retry logic
			//use worker_index = (worker_index + 1) % worker_clients_.size(); -> make the call again
			//create new promise
			std::promise<MapTaskCompleted> retry_promise;
			std::future<MapTaskCompleted> retry_future = retry_promise.get_future();
			worker_index = (worker_index + 1)%worker_clients_.size();
			std::cout << "worker calling AssignMapTask with DIFF workerIP" <<worker_ips_[worker_index] <<std::endl;
			//call again with a different worker-client
			result  = worker_clients_[worker_index]->AssignMapTask(request, &retry_promise);
			temp_future = (result == 1) ? std::move(retry_future) : std::move(future);
			
		}
		
		//success
		future_map_tasks.push_back(move(temp_future));
		++map_task_count;
			
		//future_map_tasks.push_back(move(future));
		//worker_clients_[worker_index]->AssignMapTask(request).get();
		
		//greeter.AssignMapTask(request);
		//if(worker_clients_[worker_index]){
			//std::cout << "worker calling AssignMapTask," << std::endl;
			//worker_clients_[worker_index]->AssignMapTask(request);
		//} else {
			//std::cout << "Error: Attempting to use null unique_ptr" << std::endl;
		//}
		

		//++map_task_count;
	}
}

void Master::assignReduceTasks() {
	std::cout << "INSIDE assignReduceTask" << std::endl;
	vector<vector<string>> paths(spec.num_out_files);
	std::string path = "temp/";
	//added error checks with files and paths
	if(!std::filesystem::exists(path) || !std::filesystem::is_directory(path)){
		std::cout << "Error: temp/ doesn't exists" <<std::endl;
	}
	try {
        for (const auto &entry : std::filesystem::directory_iterator(path)) {
            string name = entry.path();

            // Ensure the file name is not empty
            if (name.empty()) {
                std::cerr << "Error: Empty file name encountered." << std::endl;
                continue;  // Skip this entry
            }

            // Extract the file number using a safer method
            size_t lastUnderscore = name.find_last_of('_');
            if (lastUnderscore == std::string::npos) {
                std::cerr << "Error: File name does not contain an underscore." << std::endl;
                continue;  // Skip this entry
            }

            // Extract the file number and convert it to an integer
            std::string num = name.substr(lastUnderscore + 1);
            int index;
            try {
                index = std::stoi(num);
            } catch (const std::invalid_argument &ex) {
                std::cerr << "Error: Invalid file number format." << std::endl;
                continue;  // Skip this entry
            }

            // Ensure the index is within bounds
            if (index < 0 || index >= spec.num_out_files) {
                std::cerr << "Error: Invalid file number." << std::endl;
                continue;  // Skip this entry
            }

            // Push the valid file path into the vector
            paths[index].push_back(name);
        }
    } catch (const std::filesystem::filesystem_error &ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return;
    }

	
	
	
    //for (const auto & entry : std::filesystem::directory_iterator(path)) {
		//string name = entry.path();
		//string num = name.substr(name.find_last_of("_") + 1);
		//int index = stoi(num);
		//paths[index].push_back(name);
	//}


	
	std::cout << "assignMaptask worker_clients_ size = " << worker_clients_.size() <<std::endl;
	for(int i = 0; i < reduces; ++i){

		int worker_index = (available_workers.front() % worker_clients_.size()); //-1 or not??
		std::cout << "assingReduceTask: worker_index = " << worker_index << std::endl;

		available_workers.pop();
		ReduceTaskRequest request;
		request.set_task_id(reduce_task_count);
		request.set_userid(spec.id);
		request.set_output_file(spec.out_dir + "/" + to_string(i) + ".txt");
		for (string path : paths[i])
			request.add_inputfilepath(path);
		
		
		std::cout << "worker calling assignReduceTask with worker ip" << worker_ips_[worker_index] <<std::endl;
		
		promise<ReduceTaskCompleted> promise;
		future<ReduceTaskCompleted> future = promise.get_future();
		int result = worker_clients_[worker_index]->AssignReduceTask(request, &promise);
		std::cout <<"reduce result = " << result << std::endl;
		std::future<ReduceTaskCompleted> temp_future;
		while(result == 0) {
		//retry logic
			//create new promise
			std::promise<ReduceTaskCompleted> retry_promise;
			std::future<ReduceTaskCompleted> retry_future = retry_promise.get_future();
			worker_index = (worker_index + 1) % worker_clients_.size();
			std::cout << "worker calling AssignReduceTask with DIFF workerIP" <<worker_ips_[worker_index] <<std::endl;
			result = worker_clients_[worker_index]->AssignReduceTask(request, &retry_promise);
			temp_future = (result == 1)? std::move(retry_future) : std::move(future);
			
		}
		future_reduce_tasks.push_back(std::move(temp_future));
		


		++reduce_task_count;
		//call wait before or after ++ count
	}
		
}

void Master::handleMapTaskCompletion() {
	
	for(int i = 0; i < maps; i++) {
		map_task_status[i] = true;
		available_workers.push(i);
	}
}

void Master::handleReduceTaskCompletion() {
	
	for(int i = 0; i < reduces; i++) {
		reduce_task_status[i] = true;
		available_workers.push(i);
	}
}


void Master::waitForMapTask() {
	std::cout << "future_map_tasks size = " << future_map_tasks.size() << std::endl;
	for(int i = 0; i < maps; ++i) {
		auto& future = future_map_tasks[i];
		if(future.valid()){
			try {
                    		future.get();  // Wait for each map task future to be ready
                	} catch (const std::exception& e) {
                    		std::cerr << "Exception in waitForMapTaskCompletion: " << e.what() << std::endl;
                    		//would this work??
                    		//return;
                	}
		}
		std::cout << "future not valid" << std::endl;
	}
    	std::cout << "calling handle map"<<std::endl;
    	handleMapTaskCompletion();
    	std::cout << "leaving waitForMapTask()"<<std::endl;

}
void Master::waitForReduceTask() {
	
    	std::cout << "future_reduce_tasks size = " << future_reduce_tasks.size() << std::endl;
    	for(int i= 0;i < reduces; ++i) {
    		auto& future = future_reduce_tasks[i];
    		if(future.valid()){
    			try {
                    		future.get();  // Wait for each reduce task future to be ready
                	} catch (const std::exception& e) {
                    		std::cerr << "Exception in waitForReduceTaskCompletion: " << e.what() << std::endl;
                	}
    		}
    		std::cout << "future not valid" << std::endl;
    	}
    	std::cout << "calling handle reduce"<<std::endl;
    	handleReduceTaskCompletion();
	std::cout << "leaving waitForReduceTask()"<<std::endl;
}



/* CS6210_TASK: Here you go. once this function is called you will complete whole map reduce task and return true if succeeded */
bool Master::run() {

	// first run the map tasks
	std::cout << "Calling assignMapTask" <<std::endl;

	std::filesystem::create_directory("temp");

	assignMapTasks();

	std::cout << "calling waitForMapTask() " << std::endl;
	waitForMapTask();
	// then the reduce functions
	std::cout << "Calling assignReduceTask" <<std::endl;

	std::filesystem::create_directory(spec.out_dir);
	std::cout << "After create directory" << std::endl;
	assignReduceTasks();
	
	waitForReduceTask();

	return true;
}
