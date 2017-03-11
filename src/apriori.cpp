#include "apriori.hpp"

Apriori::Apriori(){
	minSupport = 0;
	conf = 0;
}

Apriori::Apriori(double minSupport,double conf){
	this->minSupport = minSupport;
	this->conf = conf;
}
double Apriori::getSupport(const std::set<std::string> &subset){
	return(double)supportCount(subset)/tranactions.size();
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
int Apriori::supportCount(const std::set<std::string> &subItemSet){
	int freq= 0 ;
	for(auto &X:tranactions){
		if(std::includes(X.begin(),X.end(),subItemSet.begin(),subItemSet.end())){
			freq++;
		}
	}
	return freq;
}

void Apriori::doCombinations(const std::set<std::string> &elements,int k,std::vector< std::set<std::string> > &comb){
	if(k==1){
		comb.push_back(elements);
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
void print(std::set<std::string> set){
	for(auto &X:set){
		std::cout << X << " ";
	}
	std::cout << std::endl;
}
void Apriori::create(){
	for(int i=1; i <= subSupportSet.size();i++){
		std::vector<std::set<std::string> >comb;
		doCombinations(subSupportSet,i,comb);
		for(auto &X:comb){
			if(getSupport(X) >= minSupport){
				frequentSets.push_back(X);
			}
		}
	}
}
void Apriori::printResults(){
	std::cout << "Requent Sets [" << frequentSets.size() << "]" << std::endl;
 	for(auto &X:frequentSets){
		 for(auto &Y:X){
			std::cout << Y << " ";	
		 }
		 std::cout << " with support " << std::to_string(getSupport(X)) << std::endl;
	}
}
void Apriori::printTransactions(){
	std::cout << "Transactions" << std::endl;
	for(auto &X:tranactions){
		for(auto &Y:X){
			std::cout << Y << " ";
		}
		std::cout << std::endl;
	}
}