#pragma once

#include <vector>
#include "mapreduce_spec.h"


/* CS6210_TASK: Create your own data structure here, where you can hold information about file splits,
     that your master would use for its own bookkeeping and to convey the tasks to the workers for mapping */
struct FileShard {
	std::string file_name;
	size_t start_offset;
	size_t end_offset;
};


/* CS6210_TASK: Create fileshards from the list of input files, map_kilobytes etc. using mr_spec you populated  */ 
inline bool shard_files(const MapReduceSpec& mr_spec, std::vector<FileShard>& fileShards) {
	// Calculate the approximate shard size
	
	return true;
}
