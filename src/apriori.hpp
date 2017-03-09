#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <set>
#include <algorithm>
#ifndef apriori_hpp
#define apriori_hpp
class Apriori{
	private:
        double minSupport;
        double conf;
		std::vector<std::string> results;
		std::vector < std::set<std::string> > tranactions;
		std::set <std::string,double>supportSet; 
    public:
        Apriori();
        Apriori(double minSupport,double conf);
		void create();
		void fillWithFile(std::string filename);
		int frequency(const std::set<std::string> &subItemSet);
		void printTransactions();
		void printResults();
		void doCombinations(const std::set<std::string> &elements,int k,std::set<std::string> &comb);

};
#endif