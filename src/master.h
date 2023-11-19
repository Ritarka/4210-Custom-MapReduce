#pragma once

#include "mapreduce_spec.h"
#include "file_shard.h"

#include <grpcpp/grpcpp.h>
#include <grpc/support/log.h>

#include "workerservice.pb.h"
#include "workerservice.grpc.pb.h"


using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using WorkerAction::WorkerService;
using WorkerAction::HelloReply;
using WorkerAction::HelloRequest;


class GreeterClient {
 public:
  GreeterClient(std::shared_ptr<Channel> channel)
      : stub_(WorkerService::NewStub(channel)) {}

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  std::string SayHello(const std::string& user) {
    // Data we are sending to the server.
    HelloRequest request;
    request.set_name(user);

    // Container for the data we expect from the server.
    HelloReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->SayHello(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      return reply.message();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

 private:
  std::unique_ptr<WorkerService::Stub> stub_;
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
	GreeterClient greeter(
		grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
	std::string user("world");
	std::string reply = greeter.SayHello(user);
	std::cout << "Greeter received: " << reply << std::endl;	
}


/* CS6210_TASK: Here you go. once this function is called you will complete whole map reduce task and return true if succeeded */
bool Master::run() {

	// first run the map tasks

	// then the reduce functions

	return true;
}