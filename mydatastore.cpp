#include "mydatastore.h"

MyDataStore::MyDataStore(){}

MyDataStore::~MyDataStore(){
    typename std::map<std::string, User*>::iterator it = users_.begin();

    for(; it != users_.end(); ++it){
        delete it->second;
    }

    typename std::set<Product*>::iterator ite = product_master.begin();
    for(; ite != product_master.end(); ++ite){
        delete *ite;
    }   
}

void MyDataStore::addProduct(Product* p){
    product_master.insert(p);
    std::set<std::string> keywords = p -> keywords();

    typename std::set<std::string>::iterator it = keywords.begin();
    for(; it != keywords.end(); ++it){
        if(products_.find(*it) == products_.end()){
            std::vector<Product*> second;
            second.push_back(p);
            products_[*it] = second;
        }

        else{
            products_.find(*it) -> second.push_back(p);
        }
    }
}

void MyDataStore::addUser(User* u){
    users_[u->getName()] = u;
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
    typename std::vector<std::string>::iterator it = terms.begin();
    std::set<Product*> rtn;

    if(products_.find(*it) != products_.end()){
        rtn = toSet(products_.find(*it) -> second);
    }

    for(it = it+1; it != terms.end(); ++it){
        if(products_.find(*it) != products_.end()){
            std::set<Product*> temp =  toSet(products_.find(*it) -> second);
            if(type){
                //OR search
                rtn = setUnion(rtn, temp);
            }

            else{
                //AND search 
                rtn = setIntersection(rtn, temp);
            }
        }
    }

    return toVector(rtn);
}

void MyDataStore::dump(std::ostream& ofile){
    typename std::set<Product*>::iterator it = product_master.begin();
    ofile << "<products>" << std::endl;
    for(; it != product_master.end(); ++it){
      (*it) -> dump(ofile);
    }
    ofile << "</products>" << std::endl;
    ofile << "<users>" << std::endl;
    typename std::map<std::string, User*>::iterator ite = users_.begin();
    for(; ite != users_.end(); ++ite){
      ite -> second -> dump(ofile);
    }
    ofile << "</users>" << std::endl;
}

std::vector<Product*> MyDataStore::toVector(const std::set<Product*>& input){
    std::vector<Product*> rtn;

    typename std::set<Product*>::iterator it = input.begin();
    for(; it != input.end(); ++it){
        rtn.push_back(*it);
    }

    return rtn;
}

std::set<Product*> MyDataStore::toSet(const std::vector<Product*>& input){
    std::set<Product*> rtn;

    typename std::vector<Product*>::const_iterator it = input.begin();
    for(; it != input.end(); ++it){
        rtn.insert(*it);
    }

    return rtn;
}

void MyDataStore::print() const{
    typename std::map<std::string, std::vector<Product*>>::const_iterator it = products_.begin();
    std::cout << "Printing out stored products: " << std::endl;
    for(; it != products_.end(); ++it){
        std::vector<Product*> currVector = it -> second;
        std::cout << "Keyword: " << it -> first << std::endl;
        typename std::vector<Product*>::iterator iterate = currVector.begin();
        for(; iterate != currVector.end(); ++iterate){
            std::cout << (*iterate) ->getName() << std::endl;
        }
    }

    std::cout << "Printing out stored users: " << std::endl;
    typename std::map<std::string, User*>::const_iterator ite = users_.begin();
    for(; ite != users_.end(); ++ite){
        std::cout << ite -> first << std::endl;
    }
}

User* MyDataStore::getUser(std::string name) const{
    //Check if the variable name is valid??
    User* rtn;
    if(users_.find(name) != users_.end()){
        rtn = users_.find(name) -> second;
    }

    return rtn;
}

bool MyDataStore::isValidUser(std::string name) const{
    return users_.find(name) != users_.end();
}