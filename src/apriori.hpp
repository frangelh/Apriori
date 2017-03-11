#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
#ifndef apriori_hpp
#define apriori_hpp
typedef struct{
	std::set<std::string> set;
	double support;
	double conf;
}setsToMine;
class Apriori{
	private:
        double minSupport;
        double conf;
		std::vector<std::set<std::string> > frequentSets;
		std::vector <std::set<std::string> > tranactions;
		std::set <std::string,double>supportSet; 
		std::vector<setsToMine> ruleCandidates;
		std::set<std::string> subSupportSet; 
    public:
        Apriori();
        Apriori(double minSupport,double conf);
		void create();
		void fillWithFile(std::string filename);
		int supportCount(const std::set<std::string> &subItemSet);
		void printTransactions();
		void printResults();
		double getSupport(const std::set<std::string> &subset);
		void doCombinations(const std::set<std::string> &elements,int k,std::vector< std::set<std::string> > &comb);
};
#endif