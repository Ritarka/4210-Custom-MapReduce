#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
//string stream for breaking the words

/* CS6210_TASK Implement this data structureas per your implementation.
		You will need this when your worker is running the map task*/
struct BaseMapperInternal {

		/* DON'T change this function's signature */
		BaseMapperInternal();

		/* DON'T change this function's signature */
		void emit(const std::string& key, const std::string& val);

		/* NOW you can add below, data members and member functions as per the need of your implementation*/
		//for mapper, write the intermediate pairs to an intermediate file than can be passed to the reduce function
		void writeInterToFile(const std::string& filePath);
		//have our intermediate pairs
		std::vector<std::pair<std::string, std::string>> intermediatePairs;
};


/* CS6210_TASK Implement this function */
inline BaseMapperInternal::BaseMapperInternal() {
//leave the constructor empty?

}


/* CS6210_TASK Implement this function */
inline void BaseMapperInternal::emit(const std::string& key, const std::string& val) {
	std::cout << "Dummy emit by BaseMapperInternal: " << key << ", " << val << std::endl;
	//create a key, value pair and push it into the int pair vector
	intermediatePairs.emplace_back(key, val);
}
inline void BaseMapperInternal::writeInterToFile(const std:: string& filePath){
	std::ofstream intermediateFile(filePath);
	if(intermediateFile.is_open()) {
		for (const auto& pair : intermediatePairs) {
			//write each pair in the file
			intermediateFile << pair.first << " " << pair.second << "\n";
		}
		intermediateFile.close();
	} else {
		std::cerr <<"Error: unable to open the file for writing intermediate data\n";
	}
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
		void writeOutputToFile(const std::string& filePath);
		//vector of pairs for final output
		std::vector<std::pair<std::string, std::string>> finalPairs;
};


/* CS6210_TASK Implement this function */
inline BaseReducerInternal::BaseReducerInternal() {
//leaving the constructor empty for now?

}


/* CS6210_TASK Implement this function */
inline void BaseReducerInternal::emit(const std::string& key, const std::string& val) {
	std::cout << "Dummy emit by BaseReducerInternal: " << key << ", " << val << std::endl;
	finalPairs.emplace_back(key, val);
}
//implementation of writeOutputToFile()
inline void BaseReducerInternal::writeOutputToFile(const std:: string& filePath){
	std::ofstream outputFile(filePath);
	if(outputFile.is_open()){
		for(const auto& pair: finalPairs){
			outputFile << pair.first << " " << pair.second << "\n";
		}
		outputFile.close();
	} else {
		std::cerr << "Error: Unable to open file for writing final output\n";
	}
}
