#include <iostream>
#include "apriori.hpp"
int main(int argc,char** arg){
    std::string filename = "entrada";
	int supportCount = 2;
	double conf = 0;
    if(argc > 1) filename = std::string(arg[1]);
    if(argc > 2) supportCount = atoi(arg[2]);
    if(argc > 3) conf = atof(arg[3]);
    Apriori apriori(supportCount,conf);
	apriori.fillWithFile(filename);
    apriori.createFrequentSets();
	// apriori.printTransactions();
    apriori.printResults();
    // std::set<std::string> val {"1","2","3","4"};
    // std::set<std::string> d;
    // apriori.doCombinations(val,3,d);
    // for(auto &X:d){
    //     std::cout  << X << std::endl;
    // }
}