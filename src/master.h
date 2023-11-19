#pragma once

#include "mapreduce_spec.h"
#include "file_shard.h"

#include <grpcpp/grpcpp.h>
#include <grpc/support/log.h>

#include "workerservice.pb.h"
#include "workerservice.grpc.pb.h"


using grpc::Server;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerBuilder;
using grpc::ServerCompletionQueue;
using grpc::ServerContext;
using grpc::Status;

using WorkerAction::WorkerService;
using WorkerAction::HelloReply;
using WorkerAction::HelloRquest;
using WorkerAction::SayHello;



class GreeterServiceImpl final : public WorkerService::Service {
  Status SayHello(ServerContext* context, const HelloRequest* request,
                  HelloReply* reply) override {
    std::string prefix("Hello ");
    reply->set_message(prefix + request->name());
    return Status::OK;
}

  Status SayHelloAgain(ServerContext* context, const HelloRequest* request,
                       HelloReply* reply) override {
    std::string prefix("Hello again ");
    reply->set_message(prefix + request->name());
    return Status::OK;
  }
};


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
};


/* CS6210_TASK: This is all the information your master will get from the framework.
	You can populate your other class data members here if you want */
Master::Master(const MapReduceSpec& mr_spec, const std::vector<FileShard>& file_shards) {
	spec = mr_spec;
	shards = file_shards;

	maps = file_shards.size();
	reduces = spec.num_out_files;

	//setup connections to worker threads

	
}


/* CS6210_TASK: Here you go. once this function is called you will complete whole map reduce task and return true if succeeded */
bool Master::run() {

	// first run the map tasks

	// then the reduce functions

	return true;
}