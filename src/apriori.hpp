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
	std::set<std::string> recomendedSet;
	double support;
	double conf;
}MinedSets;
class Apriori{
	private:
        int minSupport;
        double conf;
		std::vector <std::set<std::string> > frequentSets;
		std::vector <std::set<std::string> > tranactions;
		std::vector<MinedSets> rulesMined;
		std::set<std::string> subSupportSet; 
    public:
        Apriori();
        Apriori(int minSupport,double conf);
		void fillWithFile(std::string filename);
		void createFrequentSets();
		int getSupportCount(const std::set<std::string> &subItemSet);
		double getSupport(const std::set<std::string> &subset);
		double getConfidence(const std::set<std::string> &SetS,const std::set<std::string> &SetSMinsI);
		void doCombinations(const std::set<std::string> &elements,const int &k,std::vector< std::set<std::string> > &comb);
		void printTransactions();
		void printResults();
};
#endif