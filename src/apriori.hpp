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
	double conf;
}MinedRule;
class Apriori{
	private:
        int minSupport;
        double minconf;
		std::vector <std::set<std::string> > frequentSets;
		std::vector <std::set<std::string> > tranactions;
		std::vector<MinedRule> rulesMined;
		std::set<std::string> subSupportSet; 
		void mineRules();
		void createFrequentSets();
    public:
        Apriori();
        Apriori(int minSupport,double minconf);
		void fillWithFile(std::string filename);
		void execute();
		int getSupportCount(const std::set<std::string> &subItemSet);
		double getSupport(const std::set<std::string> &subset);
		double getConfidence(const std::set<std::string> &SetS,const std::set<std::string> &SetSMinsI);
		void doCombinations(const std::set<std::string> &elements,const int &k,std::vector< std::set<std::string> > &comb);
		void printTransactions();
		void printFrequentSets();
		void printRulesMined();
};
#endif