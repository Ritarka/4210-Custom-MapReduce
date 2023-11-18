#pragma once

#include <math.h>
#include <vector>
#include <filesystem>
#include "mapreduce_spec.h"

using namespace std;
using namespace std::filesystem;

/* CS6210_TASK: Create your own data structure here, where you can hold information about file splits,
     that your master would use for its own bookkeeping and to convey the tasks to the workers for mapping */

struct MiniShard {
	std::string file_name;
	size_t start_offset;
	size_t end_offset;
};

struct FileShard {
	vector<MiniShard> shards;
};

/* CS6210_TASK: Create fileshards from the list of input files, map_kilobytes etc. using mr_spec you populated  */ 
inline bool shard_files(const MapReduceSpec& spec, std::vector<FileShard>& fileShards) {
	// Calculate the approximate shard size
	int total = 0;
	stringstream ss;
	for (string name : spec.in_files) {
		cout << name << " " << file_size(name) << endl;
		total += std::filesystem::file_size(name);
		ss << ifstream(name).rdbuf();
	}

	cout << "Total size is " << total << endl;
	int shards = ceil((double)total / (spec.map_kb * 1000));
	printf("Shards: %d; spec.map_kp %d\n", shards, spec.map_kb);

	int len_size = ss.str().size() / shards;
	printf("Approx length: %d\n", len_size);

	vector<MiniShard> minis;

	int length = 0;
	int chunk_length = 0;
	int start = 0;
	std::string item;
	for (string name : spec.in_files) {
		ifstream s(name);
		while(getline(s, item, '\n')) {
			// cout << item << endl;
			int size = item.size();
			if (size + length > len_size) { // if we're coming to a point where we need to create a chunk
				struct MiniShard ms;
				ms.file_name = name;
				ms.start_offset = start;

				if ((length + size - len_size) < len_size - length) // pick previous \n
					length += size;

				ms.end_offset = chunk_length + start;
				minis.push_back(ms);

				FileShard fs;
				fs.shards = minis;
				minis.clear();
				fileShards.push_back(fs);

				start = ms.end_offset;
				length = 0;
				chunk_length = 0;
			} else {
				length += size;
				chunk_length += size;
			}
		}
		
		struct MiniShard ms;
		ms.file_name = name;
		ms.start_offset = start;
		ms.end_offset = length + start;
		minis.push_back(ms);
		
		// length = 0;
		chunk_length = 0;
		start = 0;
	}

	for (MiniShard mini : minis) {
		printf("%s: Start: %ld End: %ld Size: %ld\n", mini.file_name.c_str(), mini.start_offset, mini.end_offset,
			mini.end_offset - mini.start_offset);
	}


	// dumbly assign minishards to overall file shards
	// fixe later?
	for (int i = 0; i < fileShards.size(); i++) {
		printf("Shard %d: ", i);
		for (int j = 0; j < fileShards[i].shards.size(); j++)
			printf("(%s %ld) ", fileShards[i].shards[j].file_name.c_str(), 
				fileShards[i].shards[j].end_offset - fileShards[i].shards[j].start_offset);

		printf("\n");
	}

	// int estimate = total / length;
	// cout << estimate << endl;


	return true;
}
