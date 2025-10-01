#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include "user.h"
#include "book.h"
#include "clothing.h"
#include "movie.h"
#include "util.h"
#include <map>
#include <vector>

class MyDataStore: public DataStore{
public:
    MyDataStore();
    ~MyDataStore();
    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);
    void print() const;
    User* getUser(std::string name) const;
    bool isValidUser(std::string name) const;

    // Add cart? 
    // Check out cart? 

private: 
    std::map<std::string, std::vector<Product*>> products_;
    std::map<std::string, User*> users_;
    std::set<Product*> product_master;

    std::vector<Product*> toVector(const std::set<Product*>& input);
    std::set<Product*> toSet(const std::vector<Product*>& input);

};

#endif