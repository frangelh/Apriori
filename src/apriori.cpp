#include "apriori.hpp"

Apriori::Apriori(){
	minSupport = 0;
	conf =0;
}

Apriori::Apriori(double minSupport,double conf){
	this->minSupport = minSupport;
	this->conf = conf;
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
		}
		tranactions.push_back(elemens);
		transline++;
	}
}
int Apriori::frequency(const std::set<std::string> &subItemSet){
	int freq= 0 ;
	for(auto &X:tranactions){
		if(std::includes(X.begin(),X.end(),subItemSet.begin(),subItemSet.end())){
			freq++;
		}
	}
	return freq;
}

void Apriori::doCombinations(const std::set<std::string> &elements,int k,std::set<std::string> &comb){
	if(k==1){
		comb = std::set<std::string>(elements);
		return;
	}
	auto getStringWithOffset = [&](std::set<std::string> ele,int offset,int number) -> std::string{
		std::string result = "";
		for(int i=offset; i < offset +number; i++){
			result += *std::next(ele.begin(),i);
		}
		return result;
	};
	int limit = elements.size()-k;
		for(int i =0 ; i<= limit ;i++){
		for(int j=i+1 ; j <= limit+1 ;j++){
			std::string res =  *std::next(elements.begin(),i) + getStringWithOffset(elements,j,k-1);
			comb.insert(res);
		}
	}
}

void Apriori::create(){
	//TODO
}
void Apriori::printResults(){
	std::cout << "Results" << std::endl;
 	for(auto &X:results){
		std::cout << X << std::endl;	
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