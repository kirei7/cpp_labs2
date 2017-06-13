#include <vector>
#include "Product.cpp"

using namespace std;

class Shop {
public:
    virtual vector<Product> getListOfItems() {
        return products;
    }

protected:
    std::vector<Product> products;
};

class ProductsShop : public Shop {
public:
    ProductsShop() {
        products.push_back(Product{"Sausage", 80});
        products.push_back(Product{"Butter", 70});
        products.push_back(Product{"Milk", 300});
        products.push_back(Product{"Potato", 40});
        products.push_back(Product{"Bread", 110});
    }
};

class EquipmentShop : public Shop {
public:
    EquipmentShop() {
        products.push_back(Product{"Sony", 100});
        products.push_back(Product{"Samsung", 80});
        products.push_back(Product{"Sharp", 70});
        products.push_back(Product{"Apple", 300});
        products.push_back(Product{"Aser", 40});
    }
};