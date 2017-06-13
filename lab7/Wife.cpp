#include <vector>
#include <string>
#include <iostream>

#include "Husband.cpp"

class Wife {
public:
    Wife() {
        /*get singleton instance*/
        husband = Husband::getInstance();

        /*initialize vector of 'to buy' items*/
        purchases.push_back("Sony");
        purchases.push_back("Bread");
        purchases.push_back("Lenovo");
        purchases.push_back("Onion");
    }
    void makeOrder() {
        /*make order*/
        husband->acceptList(purchases);
        husband->doShopping();

        /*display results*/
        std::vector<Product> resultTotal = husband->getResultTotalItems();
        std::cout<<"Total items:"<<std::endl;
        for (int i = 0; i < resultTotal.size(); ++i) {
            std::cout<<resultTotal[i].name<<" - "<<resultTotal[i].price<<std::endl;
        }
        std::vector<Product> resultBought = husband->getResultBought();
        std::cout<<endl<<"Bought:"<<std::endl;
        for (int i = 0; i < resultBought.size(); ++i) {
            std::cout<<resultBought[i].name<<" - "<<resultBought[i].price<<std::endl;
        }
        std::cout<<"Total price = "<<husband->getResultSum()<<std::endl;
    }


private:
    std::vector<std::string> purchases;
    Husband* husband;
};