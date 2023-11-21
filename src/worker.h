#pragma once

#include <mr_task_factory.h>
#include "mr_tasks.h"

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

using masterworker::MasterWorker;
using masterworker::MapTask;
using masterworker::ReduceTask;
using masterworker::TaskCompletion;
using masterworker::HelloReply;
using masterworker::HelloRequest;

using namespace std;


class GreeterServiceImpl final : public MasterWorker::Service {

  Status AssignMapTask(ServerContext* context, const MapTask* request,
                       TaskCompletion* reply) override {
     //std::string prefix("Hello again ");
     //reply->set_message(prefix + request->name());
     reply->set_taskid(request->taskid());
     reply->set_tasktype(request->tasktype());
	cout << "Got Map Task" << endl;
    return Status::OK;
  }

  Status AssignReduceTask(ServerContext* context, const ReduceTask* request,
                       TaskCompletion* reply) override {
     reply->set_taskid(request->taskid());
     reply->set_tasktype(request->tasktype());
	cout << "Got Reduce Task" << endl;
    return Status::OK;
  }



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
  
  
};




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
	//GreeterServiceImpl service;
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
