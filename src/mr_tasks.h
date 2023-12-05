#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "mapreduce_spec.h"

using namespace std;

/* CS6210_TASK Implement this data structureas per your implementation.
		You will need this when your worker is running the map task*/
struct BaseMapperInternal {

		/* DON'T change this function's signature */
		BaseMapperInternal();

		/* DON'T change this function's signature */
		void emit(const std::string& key, const std::string& val);

		/* NOW you can add below, data members and member functions as per the need of your implementation*/
		//for mapper, write the intermediate pairs to an intermediate file than can be passed to the reduce function
		void write_to_file(int);
		int num_reduces;
		std::vector<std::pair<std::string, std::string>> pairs;
};


/* CS6210_TASK Implement this function */
inline BaseMapperInternal::BaseMapperInternal() {

}



/* CS6210_TASK Implement this function */
inline void BaseMapperInternal::emit(const std::string& key, const std::string& val) {
	pairs.push_back(make_pair(key, val));
}
	
inline void BaseMapperInternal::write_to_file(int index) {
	ofstream stream;
	//vector<vector<pair<string, string>>> inter(num_reduces);
	unordered_map<size_t, vector<pair<string, string>>> inter;
	//for (int i = 0; i < num_reduces; i++) {
	hash<string> hasher; //use a single hasher
		for (auto pair : pairs) {
			//hash<string> hasher;
			size_t hash_value = hasher(pair.first);
			size_t index = hash_value % num_reduces;
			inter[index].push_back(pair);
		}
		//stream.close();
	//}


	//added
	// Loop over each entry in the inter and write to file 
    for (const auto& entry : inter) {
        size_t map_index = entry.first;
        const auto& pairs_for_index = entry.second;

        string name = "temp/intermediate_" + to_string(index) + "_" + to_string(map_index);
        stream.open(name, fstream::app);  // Open the file in append mode
        for (const auto& pair : pairs_for_index) {
            stream << pair.first << " " << pair.second << endl;
        }
        stream.close();  // Close the stream after writing to the file
    }

    pairs.clear();  
    // Clear the pairs vector
	//for (int i = 0; i < num_reduces; i++) {
		//string name = "temp/intermediate_" + to_string(index) + "_" + to_string(i);
		//stream.open(name, fstream::app);
		//for (auto pair : inter[i]) {
			//stream << pair.first << " " << pair.second << endl;
		//}
		//stream.close();
	//}
	//pairs.clear();
}

/*-----------------------------------------------------------------------------------------------*/


/* CS6210_TASK Implement this data structureas per your implementation.
		You will need this when your worker is running the reduce task*/
struct BaseReducerInternal {

		/* DON'T change this function's signature */
		BaseReducerInternal();

		/* DON'T change this function's signature */
		void emit(const std::string& key, const std::string& val);

		/* NOW you can add below, data members and member functions as per the need of your implementation*/
		//output file to write the result of the reduce function
		void writeOutputToFile(string out_dir);
		//vector of pairs for final output
		std::vector<std::pair<std::string, std::string>> finalPairs;
};


/* CS6210_TASK Implement this function */
inline BaseReducerInternal::BaseReducerInternal() {
//leaving the constructor empty for now?

}


/* CS6210_TASK Implement this function */
inline void BaseReducerInternal::emit(const std::string& key, const std::string& val) {
	// std::cout << "Dummy emit by BaseReducerInternal: " << key << ", " << val << std::endl;
	finalPairs.emplace_back(key, val);
}
//implementation of writeOutputToFile()
inline void BaseReducerInternal::writeOutputToFile(string path) {
	//added - sorting the finalPair vector
	//std::sort(finalPairs.begin(), finalPairs.end());
	std::ofstream outputFile(path);
	//added for duplicates
	//std::string previousKey;
	for(const auto& pair: finalPairs){
		//if(pair.first != previousKey){
			//outputFile << pair.first << " " << pair.second << "\n";
			outputFile << pair.first << " " << pair.second ;
			//only add new line when pair is not last pair
			if(&pair != &finalPairs.back()){
				outputFile << "\n";
			}
		
	}
	finalPairs.clear();
}
