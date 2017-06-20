class Customer {
public:
    Customer(){}
    Customer(string name) {
        this->name = name;
        nextDeptNum = 0;
    }

    string getName() {
        return name;
    }
    void doShopping(Department* department) {
        department->acceptVisitor(name);
    }
    void incrementNextDeptNum() {
        if (nextDeptNum < 2) {
            this->nextDeptNum = nextDeptNum + 1;

        }
        else {
            nextDeptNum = 0;
        }
    }
    int getNextDeptNum() {
        return nextDeptNum++;
    }
private:
    string name;
    volatile int nextDeptNum;
};