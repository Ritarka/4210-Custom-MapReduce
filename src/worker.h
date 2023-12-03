#pragma once

#include <mr_task_factory.h>
#include "mr_tasks.h"
#include <chrono>
#include <thread>

#include <grpcpp/grpcpp.h>
#include <grpc/support/log.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>


#include "masterworker.pb.h"
#include "masterworker.grpc.pb.h"


using grpc::Server;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerBuilder;
using grpc::ServerCompletionQueue;
using grpc::ServerContext;
using grpc::Status;
using masterworker::IntermediateFile;
using masterworker::MapTaskCompleted;
using masterworker::MapTaskRequest;
using masterworker::MasterWorker;
using masterworker::ReduceTaskCompleted;
using masterworker::ReduceTaskRequest;
using namespace std;


class GreeterServiceImpl final : public MasterWorker::Service {
public:
	explicit GreeterServiceImpl(bool simulateTimeout = false, bool simulateFailure = false, int simulateDelay = 0);

    	Status AssignMapTask(ServerContext* context, const MapTaskRequest* request,
                         MapTaskCompleted* reply) override;

    	Status AssignReduceTask(ServerContext* context, const ReduceTaskRequest* request,
                            ReduceTaskCompleted* reply) override;
private:
	bool simulate_timeout_;
	bool simulate_failure_;
	int simulate_delay_;
	void simulateScenarios();
};

GreeterServiceImpl::GreeterServiceImpl(bool simulateTimeout, bool simulateFailure, int simulateDelay)
    : simulate_timeout_(simulateTimeout), simulate_failure_(simulateFailure), simulate_delay_(simulateDelay) {}

Status GreeterServiceImpl::AssignMapTask(ServerContext* context, const MapTaskRequest* request,
                                         MapTaskCompleted* reply) {
    simulateScenarios();  // Simulate different scenarios

    // Check for simulated timeout
    if (simulate_timeout_) {
        return Status(grpc::DEADLINE_EXCEEDED, "Simulated timeout in task processing.");
    }

    reply->set_task_id(request->task_id());
    std::cout << "Worker received MapTask " << request->task_id() << std::endl;

    // Add intermediate file
    for (int i = 0; i < request->num_reduces(); ++i) {
        IntermediateFile* intermediate_file = reply->add_intermediate_files();
        intermediate_file->set_file_name("intermediate" + std::to_string(i) + ".txt");
    }

    std::cout << "Got Map Task" << std::endl;
    return Status::OK;
}
Status GreeterServiceImpl::AssignReduceTask(ServerContext* context, const ReduceTaskRequest* request,
                                            ReduceTaskCompleted* reply) {
    simulateScenarios();  // Simulate different scenarios

    // Check for simulated timeout
    if (simulate_timeout_) {
        return Status(grpc::DEADLINE_EXCEEDED, "Simulated timeout in task processing.");
    }

    reply->set_task_id(request->task_id());
    std::cout << "Worker received ReduceTask " << request->task_id() << std::endl;

    // Add the output file
    reply->mutable_output_file()->set_file_name("output" + std::to_string(request->task_id()) + ".txt");

    std::cout << "Got Reduce Task" << std::endl;
    return Status::OK;
}
void GreeterServiceImpl::simulateScenarios() {
    if (simulate_failure_) {
        std::cerr << "Simulated failure in task processing." << std::endl;
        exit(1);  // Simulate a failure by exiting the worker process
    } else if (simulate_delay_ > 0) {
        std::this_thread::sleep_for(std::chrono::seconds(simulate_delay_));  // Simulate a delay in task processing
    } else {
        std::cout << "Worker is ready to process tasks." << std::endl;
    }
}
  //Status AssignMapTask(ServerContext* context, const MapTaskRequest* request,
                       //MapTaskCompleted* reply) override {
     //std::string prefix("Hello again ");
     //reply->set_message(prefix + request->name());
     //reply->set_task_id(request->task_id());
     //std::cout << "Worker received MapTask" << request->task_id() << std::endl;
	// Add intermediate file
    // for (int i = 0; i < request->num_reduces(); ++i)
     //{
	//IntermediateFile *intermediate_file = reply->add_intermediate_files();
	//intermediate_file->set_file_name("intermediate" + std::to_string(i) + ".txt");
     //}
	//cout << "Got Map Task" << endl;
    //return Status::OK;
  //}

  //Status AssignReduceTask(ServerContext* context, const ReduceTaskRequest* request,
                       //ReduceTaskCompleted* reply) override {
     //reply->set_task_id(request->task_id());
     //std::cout << "Worker received ReduceTask" << request->task_id() << std::endl;
	// add the output file
     //reply->mutable_output_file()->set_file_name("output" + std::to_string(request->task_id()) + ".txt");
	//cout << "Got Reduce Task" << endl;
    //return Status::OK;
  //}



  //Status SayHello(ServerContext* context, const HelloRequest* request,
                  //HelloReply* reply) override {
		//std::string prefix("Hello ");
		//reply->set_message(prefix + request->name());
		//return Status::OK;
	//}

  //Status SayHelloAgain(ServerContext* context, const HelloRequest* request,
                      // HelloReply* reply) override {
    //std::string prefix("Hello again ");
    //reply->set_message(prefix + request->name());
    //return Status::OK;
  //}
  
  
//};




/* CS6210_TASK: Handle all the task a Worker is supposed to do.
	This is a big task for this project, will test your understanding of map reduce */
class Worker {

	public:
		/* DON'T change the function signature of this constructor */
		Worker(std::string ip_addr_port);

		/* DON'T change this function's signature */
		bool run();

	private:
		/* NOW you can add below, data members and member functions as per the need of your implementation*/
		//std::unique_ptr<ServerCompletionQueue> cq_;
		std::string ip_port;

};


/* CS6210_TASK: ip_addr_port is the only information you get when started.
	You can populate your other class data members here if you want */
Worker::Worker(std::string ip_addr_port) {
	ip_port = ip_addr_port;
	GreeterServiceImpl service;

	
	ServerBuilder builder;

	builder.AddListeningPort(ip_addr_port, grpc::InsecureServerCredentials());
	builder.RegisterService(&service);

	std::unique_ptr<Server> server(builder.BuildAndStart());
	std::cout << "Server listening on " << ip_addr_port << std::endl;

	server->Wait();
}

extern std::shared_ptr<BaseMapper> get_mapper_from_task_factory(const std::string& user_id);
extern std::shared_ptr<BaseReducer> get_reducer_from_task_factory(const std::string& user_id);

/* CS6210_TASK: Here you go. once this function is called your woker's job is to keep looking for new tasks 
	from Master, complete when given one and again keep looking for the next one.
	Note that you have the access to BaseMapper's member BaseMapperInternal impl_ and 
	BaseReduer's member BaseReducerInternal impl_ directly, 
	so you can manipulate them however you want when running map/reduce tasks*/
bool Worker::run() {
	GreeterServiceImpl service(true, false, 10);
	//ServerBuilder builder;
	//builder.AddListeningPort(ip_port, grpc::InsecureServiceCredentials());
	//builder.RegisterService(&service);
	
	//cq_ = builder.AddCompletionQueue();
	
	//std::unique_ptr<Server> server(builder.BuildAndStart());
	//std::cout << "Server listening on " << ip_port << std::endl;
	
	//service.RequestAssignMapTask(cq_.get(), &cq_, server.get());
	//service.RequestAssignReduceTask(cq_.get(), &cq_, server.get());
	
	//void* tag;
	//bool ok;
	
	//while(true){
		//cq_->Next(&tag, &ok);
		//if(ok){
			//if(tag == (void*)1 || tag == (void*)2) {
				//do nothing
			//}
		//} else {
			//std::cerr << "Error in completion queue processing." << std::endl;
		//}
	//}
	
	return true;

}


	// /*  Below 5 lines are just examples of how you will call map and reduce
	// 	Remove them once you start writing your own logic */ 
	// std::cout << "worker.run(), I'm not ready yet" <<std::endl;
	// auto mapper = get_mapper_from_task_factory("cs6210");
	// mapper->map("I m just a 'dummy', a \"dummy line\"");
	// auto reducer = get_reducer_from_task_factory("cs6210");
	// reducer->reduce("dummy", std::vector<std::string>({"1", "1"}));
