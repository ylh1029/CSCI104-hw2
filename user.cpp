#include "user.h"
using namespace std;

User::User() : name_("unknown"), balance_(0.0), type_(1), cart_()
{

}
User::User(std::string name, double balance, int type) :
    name_(name), balance_(balance), type_(type), cart_()
{

}

User::~User()
{

}


std::string User::getName() const
{
    return name_;
}

double User::getBalance() const
{
    return balance_;
}

void User::deductAmount(double amt)
{
    balance_ -= amt;
}

void User::dump(std::ostream& os)
{
    os << name_ << " "  << balance_ << " " << type_ << endl;
}

void User::addToCart(std::vector<Product*> add){
    typename std::vector<Product*>::iterator it = add.begin();
    for(; it != add.end(); ++it){
        cart_.push_back(*it);
    }
}

void User::addToCart(Product* add){
    cart_.push_back(add);
}

void User::viewCart() const{
    typename std::vector<Product*>::const_iterator it = cart_.begin();
    int cnt = 1;
    for(; it != cart_.end(); ++it){
        std::cout << "Item " << cnt++ << std::endl;
        std::cout << (*it) -> displayString() << std::endl;
    }
}

void User::checkOutCart(){
    typename std::vector<Product*>::iterator it = cart_.begin();
    std::vector<Product*> newList;

    for(; it != cart_.end(); ++it){
        if((*it) -> getQty() > 0 && balance_ >= (*it) -> getPrice()){
            (*it) -> subtractQty(1);
            deductAmount((*it) -> getPrice());
        }

        else{
            newList.push_back(*it);
        }
    }

    cart_ = newList;
}