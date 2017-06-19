#include <string>

using namespace std;

class Department {
public:
    Department(){}
    Department(string name) {
        this->name = name;
    }

    string getName() {
        return name;
    }
    void acceptVisitor(string customerName) {
        printf("\nCustomer %s visited %s", customerName, this->getName());
    }
private:
    string name;
};