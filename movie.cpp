#include "movie.h"
#include <iostream>
#include <sstream>

// Movie::Movie(){}
Movie::~Movie(){}

Movie::Movie(std::string name, double price, int qty, std::string genre, std::string rating):
Product("movie", name, price, qty)
{
    genre_ = genre;
    rating_ = rating;
}

std::set<std::string> Movie::keywords() const{
    std::set<std::string> rtn = parseStringToWords(name_);
    std::set<std::string> genreKeywords = parseStringToWords(genre_);

    typename std::set<std::string>::iterator it = genreKeywords.begin();
    for(; it != genreKeywords.end(); ++it){
        rtn.insert(*it);
    }
    
    return rtn;
}

std::string Movie::displayString() const{
    std::stringstream ss1;
    ss1 << name_ << std::endl;
    ss1 << "Genre: " << genre_ << " Rating: " << rating_ << std::endl;
    ss1 << price_ << " " << qty_ << " left." << std::endl;
    return ss1.str();
}

void Movie:: dump(std::ostream& os) const{
    Product::dump(os);
    os << genre_ << "\n" << rating_ << std::endl;
}