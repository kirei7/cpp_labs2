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
    //функция гоняет по кругу числа от 0 до 2, как бы номера отделов - побывали в первом, пошли во второй и т.д.
    void incrementNextDeptNum() {
        if (nextDeptNum < 2) {
            this->nextDeptNum = nextDeptNum + 1;

        }
        else {
            nextDeptNum = 0;
        }
    }
    int getNextDeptNum() {
        return nextDeptNum;
    }
private:
    string name;
    volatile int nextDeptNum;
};