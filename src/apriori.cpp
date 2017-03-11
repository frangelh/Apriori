#include "apriori.hpp"

void printSet(std::set<std::string> set){
	for(auto &X:set){
		std::cout << X << " ";
	}
}

Apriori::Apriori(){
	minSupport = 0;
	minconf = 0;
}

Apriori::Apriori(int minSupport,double minconf){
	this->minSupport = minSupport;
	this->minconf = minconf;
}

void Apriori::mineRules(){
	for(auto &frequentSet:frequentSets){
		for(int i =1 ;i < frequentSet.size();i++){
			std::vector <std::set<std::string>> combination;
			doCombinations(frequentSet,i,combination);
			for(auto currentSet:combination){
				double confidence = getConfidence(frequentSet,currentSet);
				if(confidence >= minconf){
					MinedRule minedRule;
					minedRule.set = currentSet;
					minedRule.conf = confidence;
					std::set <std::string> diff;
					std::set_difference(frequentSet.begin(), frequentSet.end(), currentSet.begin(), currentSet.end(), std::inserter(diff, diff.begin()));
					minedRule.recomendedSet = diff;
					rulesMined.push_back(minedRule);
				} 
			}
		}
	}
}

void Apriori::execute(){
	createFrequentSets();
	mineRules();
}

double Apriori::getSupport(const std::set<std::string> &subset){
	return(double)getSupportCount(subset)/tranactions.size();
}
double Apriori::getConfidence(const std::set<std::string> &SetS,const std::set<std::string> &SetSMinsI){
	return (double)getSupportCount(SetS)/getSupportCount(SetSMinsI);
}

void Apriori::fillWithFile(std::string filename){
	std::ifstream file(filename.c_str());
	std::string buffLine;
	int transline=0;
	while(std::getline(file,buffLine)){
		std::stringstream ss(buffLine);
		std::set<std::string> elemens;
		std::string ele;
		while(std::getline(ss,ele,',')){
			elemens.insert(ele);
			subSupportSet.insert(ele);
		}
		tranactions.push_back(elemens);
		transline++;
	}
}
int Apriori::getSupportCount(const std::set<std::string> &subItemSet){
	int freq= 0 ;
	for(auto &X:tranactions){
		if(std::includes(X.begin(),X.end(),subItemSet.begin(),subItemSet.end())){
			freq++;
		}
	}
	return freq;
}

void Apriori::doCombinations(const std::set<std::string> &elements,const int &k,std::vector< std::set<std::string> > &comb){
	if (k > elements.size()){
		return;
	}
	else if(k==1){
		for(auto &element:elements) comb.push_back(std::set<std::string>{element});
		return;
	}
	auto getWithOffset = [&](std::set<std::string> ele,int offset,int number) -> std::set<std::string>{
		std::set<std::string> set;
		for(int i=offset; i < offset +number; i++){
			set.insert(*std::next(ele.begin(),i));
		}
		return set;
	};
	int limit = elements.size()-k;
		for(int i =0 ; i<= limit ;i++){
		for(int j=i+1 ; j <= limit+1 ;j++){
			std::set<std::string> combination;
			combination.insert(*std::next(elements.begin(),i));
			for(auto&X:getWithOffset(elements,j,k-1)){
				combination.insert(X);
			}
			comb.push_back(combination);
		}
	}
}

void Apriori::createFrequentSets(){
	std::vector<std::set<std::string> > currentInterationSet;
	std::set<std::string> currentSubset(subSupportSet);
	for(int i=1 ; i <= subSupportSet.size() ; i++){
		frequentSets.clear();
		std::vector<std::set<std::string> >comb;
		doCombinations(currentSubset,i,comb);
		for(int j = 0; j < comb.size();j++){
			if(getSupportCount(comb[j]) >= minSupport){
				frequentSets.push_back(comb[j]);
			}
		}
		if(frequentSets.size() == 0){
			break;
		}
		else{
			currentSubset.clear();
			for(auto &FreqSet:frequentSets){
				currentSubset.insert(FreqSet.begin(),FreqSet.end());
			}
			currentInterationSet = frequentSets;
		}
	}
	frequentSets = currentInterationSet;
}
void Apriori::printFrequentSets(){
	std::cout << "Frequent Sets [" << frequentSets.size() << "]" << std::endl;
	int i=1;
 	for(auto &X:frequentSets){
		std::cout << "["<< i++ << "] ";
		 for(auto &Y:X){
			std::cout << Y << " ";	
		 }
		 std::cout << " with support " << std::to_string(getSupportCount(X)) << std::endl;
	}
}
void Apriori::printRulesMined(){
	std::cout << "Rules [" << rulesMined.size() << "]" << std::endl;
	int i=1;
	for(auto &ruleMined:rulesMined){
		std::cout << "["<< i++ << "] ";
		printSet(ruleMined.set);
		std::cout << " -> " ; 
		printSet(ruleMined.recomendedSet);
		std::cout << " congf: " << ruleMined.conf << std::endl;
	}
}

void Apriori::printTransactions(){
	int i=1;
	std::cout << "Transactions [" << tranactions.size() << "]" << std::endl;
	for(auto &X:tranactions){
		std::cout << "["<< i++ << "] ";
		for(auto &Y:X){
			std::cout << Y << " ";
		}
		std::cout << std::endl;
	}
}