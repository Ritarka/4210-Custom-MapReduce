#pragma once

#include <atomic>
#include <queue>
#include <iostream>
#include "mapreduce_spec.h"
#include "file_shard.h"

#include <grpcpp/grpcpp.h>
#include <grpc/support/log.h>

#include "masterworker.pb.h"
#include "masterworker.grpc.pb.h"



using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using grpc::CompletionQueue;

using masterworker::MasterWorker;
using masterworker::HelloReply;
using masterworker::HelloRequest;
using masterworker::MapTask;
using masterworker::ReduceTask;
using masterworker::TaskCompletion;
using masterworker::TaskType;
//using masterworker::FileShard;


class GreeterClient {
 public:
  GreeterClient(std::shared_ptr<Channel> channel)
      : stub_(MasterWorker::NewStub(channel)), completion_queue_() {}

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  //std::string SayHello(const std::string& user) {
    // Data we are sending to the server.
    //HelloRequest request;
    //request.set_name(user);

    // Container for the data we expect from the server.
    //HelloReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    //ClientContext context;

    // The actual RPC.
    //Status status = stub_->SayHello(&context, request, &reply);

    // Act upon its status.
    //if (status.ok()) {
      //return reply.message();
    //} else {
      //std::cout << status.error_code() << ": " << status.error_message()
               // << std::endl;
      //return "RPC failed";
    //}
  //}
  void AssignMapTask(const MapTask& request, TaskCompletion* response);
  void AssignReduceTask(const ReduceTask& request, TaskCompletion* response);

  CompletionQueue completion_queue_;

 private:
  std::unique_ptr<MasterWorker::Stub> stub_;
};
//Implementation of AssignMapTask
void GreeterClient::AssignMapTask(const MapTask& request, TaskCompletion* response) {
	ClientContext context;
	Status status;
	
	//Create the rpc object
	std::unique_ptr<grpc::ClientAsyncResponseReader<TaskCompletion>> rpc(
		stub_->PrepareAsyncAssignMapTask(&context, request, &completion_queue_));
	//Start the async call
	rpc->StartCall();
	
	//Finish the async call and wait for the response
	rpc->Finish(response, &status, (void*)1); //tag for map
}

//Implementation of AssignReduceTask
void GreeterClient::AssignReduceTask(const ReduceTask& request, TaskCompletion* response){
	ClientContext context;
	Status status;
	
	
	//Create the rpc object
	std::unique_ptr<grpc::ClientAsyncResponseReader<TaskCompletion>> rpc(
		stub_->PrepareAsyncAssignReduceTask(&context, request, &completion_queue_));
	//Start the async call
	rpc->StartCall();
	//Finish the async call and wait for the response
	rpc->Finish(response, &status, (void*)2); // 2 is the tag for reduce
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
		
		std::queue<int> available_workers;
		//Track availablity of the worker
		std::vector<bool> worker_states;
		//save input file file paths for intermediate data
		std::vector<std::string> intermediateFilePaths;
		int intermediate_index;
		
		GreeterClient greeter;
		
		//atomic counters for number of map and reduce workers
		std::atomic<int> remain_map_tasks;
		std::atomic<int> remain_reduce_tasks;
		
		//Do we need this
		// CompletionQueue completion_queue_;
		
		//Helper methods
		void assignMapTasks();
		void assignReduceTasks();
		void handleTaskCompletion();
		void waitForMapTasks();
		void waitForReduceTasks();
		
};


/* CS6210_TASK: This is all the information your master will get from the framework.
	You can populate your other class data members here if you want */
Master::Master(const MapReduceSpec& mr_spec, const std::vector<FileShard>& file_shards):
	spec(mr_spec),
	shards(file_shards),

	maps(file_shards.size()),
	reduces(spec.num_out_files),
	remain_map_tasks(maps),
	remain_reduce_tasks(reduces),
	intermediate_index(0),
	//setup connections to worker threads
	greeter(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials())){
	//std::string user("world");
	//std::string reply = greeter.SayHello(user);
	//std::cout << "Greeter received: " << reply << std::endl;	
	
	//Initialize available workers with indices
	for(int i = 0; i < spec.workers; ++i){
		available_workers.push(i);
		worker_states.push_back(true);
		intermediateFilePaths.push_back(""); //does this work?
	}
}

//Helper methods implementation
void Master::assignMapTasks(){
	for(int i = 0; i < maps; ++i){
		//get the available worker index
		int worker_index = available_workers.front();
		available_workers.pop();
		
		//Create a MapTask
		MapTask mapTask;
		//populate the fields of MapTask
		//unique id
		mapTask.set_taskid(i);
		//MAP type
		mapTask.set_tasktype(TaskType::MAP);
		//create and set an intermediate file path - look into this
		//new file: intermediate_worker_index_taskID.txt
		std::string intermediateFilePath = "intermediate_" + std::to_string(worker_index) + "_" + std::to_string(i) + ".txt";
		mapTask.set_filepath(intermediateFilePath);
		intermediateFilePaths[i] = intermediateFilePath;
		//set the file shard information based on the shards vector - CHECK THIS
		for(const MiniShard& mini: shards[i].shards){
			masterworker::MiniShard* miniShard = mapTask.mutable_fileshard()->add_shards();
			miniShard->set_file_name(mini.file_name);
			miniShard->set_start_offset(mini.start_offset);
			miniShard->set_end_offset(mini.end_offset);
		}
		
		//TaskCompletion object to hold reponse
		TaskCompletion response;
		
		//assign map task to worker async
		greeter.AssignMapTask(mapTask, &response);
		void* tag;
		bool ok = false;
		greeter.completion_queue_.Next(&tag, &ok);
		
		if(ok && tag && tag == (void*)1) { //Check if the tag is correct
			worker_states[worker_index] = false;
			handleTaskCompletion();
		} else {
			std::cerr << "Error in cq processing." << std::endl;
		}
	}
}

void Master::assignReduceTasks() {
	for(int i = 0; i< reduces; ++i){
		int worker_index = available_workers.front();
		available_workers.pop();
		
		//create and populate reduce task
		ReduceTask reduceTask;
		reduceTask.set_taskid(i);
		reduceTask.set_tasktype(TaskType::REDUCE);
		//set the output file
		std::string outputFilePath = "output_" + std::to_string(worker_index) + "_" + std::to_string(i) + ".txt";
		reduceTask.set_outputfilepath(outputFilePath);
		//Now assign the set of intermediate files to reducer worker - check bounds
		for(int j = 0; j < maps/reduces && intermediate_index < maps; ++j) {
			reduceTask.add_inputfilepath(intermediateFilePaths[intermediate_index]);
			++intermediate_index;
		}
		
		//task complete object
		TaskCompletion response;
		
		greeter.AssignReduceTask(reduceTask, &response);
		void* tag;
		bool ok = false;
		greeter.completion_queue_.Next(&tag, &ok);
		
		if(ok && tag && tag == (void*)2) { //Check if the tag is correct
			//int receiver_index = static_cast<int>(tag);
			worker_states[worker_index] = false;
			handleTaskCompletion();
			
		} else {
			std::cerr << "Error in cq processing." << std::endl;
		}
	}
}

void Master::handleTaskCompletion() {
	TaskCompletion response;
	
	//extract worker index
	int worker_index = response.taskid();
	if(response.tasktype() == TaskType::MAP){	
		--remain_map_tasks;
	} else if (response.tasktype() == TaskType::REDUCE){
		--remain_reduce_tasks;
	}
	
	//make the worker as available
	available_workers.push(worker_index);
	worker_states[worker_index] = true;
}

void Master::waitForMapTasks() {
	while(remain_map_tasks > 0){
		handleTaskCompletion();
	}
}
void Master::waitForReduceTasks() {
	while(remain_reduce_tasks > 0){
		handleTaskCompletion();
	}
}
			
		
		
		
		


/* CS6210_TASK: Here you go. once this function is called you will complete whole map reduce task and return true if succeeded */
bool Master::run() {

	// first run the map tasks
	assignMapTasks();
	waitForMapTasks();
	// then the reduce functions
	assignReduceTasks();
	waitForReduceTasks();

	return true;
}
