#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

/* CS6210_TASK: Create your data structure here for storing spec from the config file */
struct MapReduceSpec {
	int workers;
	std::vector<std::string> ips;
	std::vector<std::string> in_files;
	std::string out_dir;
	int num_out_files;
	int map_kb;
	std::string id;
};


/* CS6210_TASK: Populate MapReduceSpec data structure with the specification from the config file */
inline bool read_mr_spec_from_config_file(const std::string& config_filename, MapReduceSpec& mr_spec) {
	ifstream config(config_filename);
	string line;
	while (getline(config, line)) {
		int pos = line.find_first_of("=");
		string head = line.substr(0, pos);
		string tail = line.substr(pos+1);
		cout << head << " " << tail << endl;
		if (head == "n_workers") {
			mr_spec.workers = stoi(tail);

		} else if (head == "worker_ipaddr_ports") {
			std::stringstream ss(tail);
			std::string item;

			while (getline(ss, item, ',')) {
				mr_spec.ips.push_back(item);
				// cout << item << endl;
			}

		} else if (head == "input_files") {
			std::stringstream ss(tail);
			std::string item;

			while (getline(ss, item, ',')) {
				mr_spec.in_files.push_back(item);
				// cout << item << endl;
			}


		} else if (head == "output_dir") {
			mr_spec.out_dir = tail;
		} else if (head == "n_output_files") {
			mr_spec.num_out_files = stoi(tail);
		} else if (head == "map_kilobytes") {
			mr_spec.map_kb = stoi(tail);
		} else if (head == "user_id") {
			mr_spec.id = tail;
		}
	}
	return true;
}


/* CS6210_TASK: validate the specification read from the config file */
inline bool validate_mr_spec(const MapReduceSpec& spec) {
	if (spec.workers != spec.ips.size()) return false; // 1 ip for each worker
	for (string path : spec.ips) {
		if (!ifstream(path).good()) return false; // if input file path does not exist, return false
	}
	return true;
}
