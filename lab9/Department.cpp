#include <string>

using namespace std;

class Department {
public:
    Department(){}
    //принимаем как аргумент название отдела
    Department(string name) {
        this->name = name;
    }

    //функция для доступа к названию отдела
    string getName() {
        return name;
    }
    //функция которая принимает посетителя
    void acceptVisitor(string customerName) {
        printf("\nCustomer %s visited %s", customerName.c_str(), this->getName().c_str());
    }
private:
    string name;
};