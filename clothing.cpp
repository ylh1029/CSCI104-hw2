#include "clothing.h"
#include <iostream>
#include <sstream>

// Clothing::Clothing(){}
Clothing::~Clothing(){}

Clothing::Clothing(std::string name, double price, int qty, std::string size, std::string brand):
Product("clothing", name, price, qty)
{
    size_ = size;
    brand_ = brand;
}

std::set<std::string> Clothing::keywords() const{
    std::set<std::string> rtn = parseStringToWords(name_);
    std::set<std::string> brandKeywords = parseStringToWords(brand_);

    typename std::set<std::string>::iterator it = brandKeywords.begin();
    for(; it != brandKeywords.end(); ++it){
        rtn.insert(*it);
    }
    
    return rtn;
}

std::string Clothing::displayString() const{
    std::stringstream ss1;
    ss1 << name_ << std::endl;
    ss1 << "Size: " << size_ << " Brand: " << brand_ << std::endl;
    ss1 << price_ << " " << qty_ << " left." << std::endl;
    return ss1.str();
}

void Clothing:: dump(std::ostream& os) const{
    Product::dump(os);
    os << size_ << "\n" << brand_ << std::endl;
}