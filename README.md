# Code WalkThrough
## masterworker.proto
This file contains the grpc communication specifics. We have a service MasterWorker, that has two rpc calls AssignMapTask, which takes in a MapTaskRequest object/message and return a MapTaskCompleted objects and AssignReduceTask, which takes in a ReduceTaskRequest obejct and returns a ReduceTaskCompleted object.
As for the objects, we a FileShard object, which has an array of MiniShards. And our main messages are MapTaskRequest, which contains information that the master want to send to a worker, like task_id, FileShard object, etc.. Then we have MapTaskCompleted message, which would be the message that's sent from worker to master for map tasks. And we have similar messages for reduce tasks that facilitates communication between master and worker files.
## master.h
Out master acts as an asynchronous client for the gRPC communication. It is using messages from our masterworker.proto file and grpc async client communication. We have a GreeterClient class, for which we used grpc helloworld async_client_2.cc. It has two functions AssignMapTask(request and promise), which prepares to make the async call to the worker, and handles the responses
## worker.h
The worker acts as a server for the grpc communication. The master will either call it's map or reduce functionality based on the need. While a lot of information is given to the server, since the results of map and reduce are stored in files, only a very small amount of infor is sent back to the master.
## mr_tasks.h
## file_shard.h
Given a group of files, here we attempt to convert them all into M (number of mappers) shards. Each shard consists of several minshards, where each minishard contains the file name, start position and end position. We calculate M by finding the total size of all files and divind hat my the max shard size. Rounded up of course. We then go through the input dataset and sharded them accordingly.
## mapreduce_spec.h
This class is fairly simple in reading and validating the input config file. Given that requirements for the config.ini file was not given, we only did the most rudimentary validation.