#include "book.h"
#include <iostream>
#include <sstream>
#include "util.h"

// Book::Book(){};
Book::~Book(){};

Book::Book(std::string name, double price, int qty, std::string isbn, std::string author):Product("book", name, price, qty){
    isbn_ = isbn;
    author_ = author;
}

std::set<std::string> Book::keywords() const{
    std::set<std::string> rtn = parseStringToWords(name_);
    std::set<std::string> authorKeywords = parseStringToWords(author_);

    typename std::set<std::string>::iterator it = authorKeywords.begin();
    for(; it != authorKeywords.end(); ++it){
        rtn.insert(*it);
    }

    rtn.insert(isbn_);

    return rtn;
}

std::string Book::displayString() const{
    std::stringstream ss1;
    ss1 << name_ << std::endl;
    ss1 << "Author: " << author_ << " ISBN: " << isbn_ << std::endl;
    ss1 << price_ << " " << qty_ << " left." << std::endl;
    return ss1.str();
}

void Book::dump(std::ostream& os) const{
    Product::dump(os);
    os << isbn_ << "\n" << author_ << std::endl;
}