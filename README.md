# Code WalkThrough
## masterworker.proto
- This file contains the grpc communication specifics. We have a service MasterWorker, that has two rpc calls AssignMapTask, which takes in a MapTaskRequest object/message and return a MapTaskCompleted objects and AssignReduceTask, which takes in a ReduceTaskRequest obejct and returns a ReduceTaskCompleted object.
- As for the objects, we a FileShard object, which has an array of MiniShards. And our main messages are MapTaskRequest, which contains information that the master want to send to a worker, like taks_id, FileShard object, etc.. 
    - Then we have MapTaskCompleted message, which would be the message that's sent from worker to master for map tasks. And we have similar messages for reduce tasks that facilitates communication between master and worker files.
## master.h
- Our master acts as an asynchronous client for the gRPC communication. It is using messages from our masterworker.proto file and grpc async client communication. 
- We have a GreeterClient class, for which we used grpc helloworld async_client_2.cc. It has two functions AssignMapTask(request and promise), which prepares to make the async call to the worker, and handles the response asynchronously. 
- And then we have AssignReduceTask(request and promise), which prepares the async reduce call to worker and handles the response asynchronously and stores it in a future. 
- In our master class's constructor we initialize members from the information that we get from MapReduce and FileShards. And we have helper functions here- assignMapTask() and assignReduceTask() that helps us create a request packet, handles the retry case in case of slow worker or worker failure. 
- Then the waitForMapTask() us ensure that all the map tasks are done before we begin sending request for the reduce tasks.
### Slow worker and Worker Failure
- To handle these cases, our gRPC calls AssignMapTask and AssignReduceTask returns a number to indicate whether we need to retry a task or not. 
- To handle the slow worker case: We use chrono to set a deadline to the context that we send with the request and if the worker.h(server) returns status of DEADLINE_EXCEEDED, then AssignMap and AssignReduce task methods returns a 0. 
- We use a similar logic to handle worker failure- if the status it receives is not ok or some exception occurs, then it returns a 0 indicating to the helper methods of the Master class that we need to retry that task. 
- And for every retry we use a different worker client to make the call. 
## worker.h
- The worker acts as a server for the grpc communication. - The master will either call its map or reduce functionality based on the need. While a lot of information is given to the server, since the results of map and reduce are stored in files, only a very small amount of info is sent back to the master.
- During the mapping function, we send the worker a file shard along with the user id and the number of reducers. This way M * R intermediate files are made. The user id is used to locate and utilize the user-specific mapper function.
- Before the reducer function, we collect all the intermediate files and assign each reducer a list of files which they will reduce. Each intermediate file follows the patter intermediate_<mapper_id>_<reducer_id>.txt. The reducer will then use the user-specific reducer function to reduce the files.
## mr_tasks.h
- In the BaseMapperInternal constructor, for each worker call to mapper->map(), we create R (number of reduces) files, that stores intermediate data. 
- And inside the emit function, we calculate a index by hash(key) % R. The key/value is then stored into a datastructure index by that index. Finally when the worker has mapped all of its file shards, we then write the key/value pairs into R files.
- In the BaseReducerInternal, for each reducer call, we emit the key, value pair into a data structure.
- At the end of the reduce task of a particular worker, we write the data structure into a file. This file is put into a directory specified by the config file and labelled with the id of the reducer which produced it.
## file_shard.h
- Divides the input files into smaller shards, to help parallelize the mapping phase. 
- Creates MiniShard data structure that hold file_name, start_offset and end_offset.
- the shard_files functions, determines total size of input file, determines the number of shards and divides the files into smaller chunks.
## mapreduce_spec.h
- Creates a MapReduceSpec struct to store configuration specifications of the MapReduce job.
- It reads from the passed in config.ini file, to get value of different parameters like number of workers, worker IP addresses, output directory, etc ..
- It also validates to MapReduceSpec structure, from the specifications read from the config file.

