#include <string>
#include "shops.cpp"

class Husband {
public:
    /*this method sets the list of items to be purchased & resets all result variables*/
    void acceptList(std::vector<string> itemsToBuy) {
        this->itemsToBuy = itemsToBuy;

        std::vector<Product> emptyTotalItems;
        totalItems= emptyTotalItems;
        std::vector<Product> emptyBought;
        bought = emptyBought;
        sum = 0;
    }
    void doShopping() {
        totalItems;
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < shops[i]->getListOfItems().size(); j++)
                totalItems.push_back(shops[i]->getListOfItems()[j]);

        for (int i = 0; i < itemsToBuy.size(); i++)
            for (int j = 0; j < totalItems.size(); j++)
                if (itemsToBuy[i].compare(totalItems[j].name) == 0) //if names are equal
                    bought.push_back(totalItems[j]);
        sum = 0;
        for (int i = 0; i < bought.size(); i++)
            sum += bought[i].price;
    }

    std::vector<Product> getResultTotalItems() {
        return totalItems;
    }
    std::vector<Product> getResultBought() {
        return bought;
    }
    int getResultSum() {
        return sum;
    }

    static Husband* getInstance()
    {
        static Husband* instance;
        if(!instance)
            instance = new Husband;
        return instance;
    }
    Husband(Husband const&) = delete;
    Husband& operator= (Husband const&) = delete;

private:
    Husband(){
        shops[0] = new EquipmentShop;
        shops[1] = new ProductsShop;
    }
    Shop* shops[2];

    std::vector<string> itemsToBuy;
    std::vector<Product> totalItems;
    std::vector<Product> bought;
    int sum;
};