#pragma once

#include <mr_task_factory.h>
#include "mr_tasks.h"
#include "file_shard.h"
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
using masterworker::Fileshard;
using masterworker::Minishard;
using masterworker::MapTaskCompleted;
using masterworker::MapTaskRequest;
using masterworker::MasterWorker;
using masterworker::ReduceTaskCompleted;
using masterworker::ReduceTaskRequest;
using namespace std;

extern std::shared_ptr<BaseReducer> get_reducer_from_task_factory(const std::string& user_id);
extern std::shared_ptr<BaseMapper> get_mapper_from_task_factory(const std::string& user_id);

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

    reply->set_task_id(request->taskid());
	
	cout << "Got Map Task" << endl;

	FileShard fs;
	const masterworker::Fileshard mfs = request->fileshard();
	for (masterworker::Minishard ms : mfs.shards()) {
		MiniShard m;
		m.end_offset = ms.end_offset();
		m.start_offset = ms.start_offset();
		m.file_name = ms.file_name();
		fs.shards.push_back(m);
	}

	for (int j = 0; j < fs.shards.size(); j++)
		printf("(%s %ld) ", fs.shards[j].file_name.c_str(), 
			fs.shards[j].end_offset - fs.shards[j].start_offset);
	printf("\n");


	// printf("File Path: %s, task type: %d, task id: %d\n",
	// 	request->file_name().c_str(), request->tasktype(), request->taskid());

	cout << request->userid() << endl;
	std::shared_ptr<BaseMapper> mapper = get_mapper_from_task_factory(request->userid());

	string item;
	for (MiniShard ms : fs.shards) {
		ifstream s(ms.file_name);
		int pos = 0;
		while(pos < ms.start_offset && getline(s, item, '\n')) {
			pos += item.size();
		}

		string acc;
		while(pos < ms.end_offset && getline(s, item, '\n')) {
			pos += item.size();
			acc += item;
		}
		// cout << acc << endl;
		mapper->map(acc);
		mapper->emit(acc, nullptr);

        mapper->writeInterToFile(ms.file_name + ".inter");
	}

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

	std::shared_ptr<BaseReducer> reducer = get_reducer_from_task_factory(request->userid());


	const string& user_id = request->userid();
	for (string path : request->inputfilepath()) {
		cout << path << endl;
		ifstream input(path);

		// reducer->reduce(path, std::vector<std::string>({"1", "1"}));
	}

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

/* CS6210_TASK: Here you go. once this function is called your woker's job is to keep looking for new tasks 
	from Master, complete when given one and again keep looking for the next one.
	Note that you have the access to BaseMapper's member BaseMapperInternal impl_ and 
	BaseReduer's member BaseReducerInternal impl_ directly, 
	so you can manipulate them however you want when running map/reduce tasks*/
bool Worker::run() {
	GreeterServiceImpl service(true, false, 10);
	
	return true;

}