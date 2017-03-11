#include <iostream>
#include "apriori.hpp"
int main(int argc,char** arg){
    std::string filename = "entrada";
	int supportCount = 2;
	double conf = 0.6;
    if(argc > 1) filename = std::string(arg[1]);
    if(argc > 2) supportCount = atoi(arg[2]);
    if(argc > 3) conf = atof(arg[3]);
    Apriori apriori(supportCount,conf);
	apriori.fillWithFile(filename);
    apriori.execute();
    //print Results
	apriori.printTransactions();
    apriori.printFrequentSets();
    apriori.printRulesMined();
}