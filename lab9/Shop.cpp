#include "Department.cpp"
#include "Customer.cpp"
#include <time.h>
#include <windows.h>
#include <stdio.h>

typedef struct customer_wrapper {
    Customer* customer; //одиночный покупатель который будет делать шоппинг
    Department* departments; //массив магазинов
} customer_wrapper, *pcustomer_wrapper;

const int N = 3; //количество отделов
const int CUSTOMERS_NUM = 10; //количество покупателей


static DWORD WINAPI goShopping(LPVOID lpParam);



class Shop {
public:
    Shop() {
        srand (time(NULL));

        depts[0] = Department("Equipment department");
        depts[1] = Department("Food department");
        depts[2] = Department("Magic department");

    }
    void work() {
        Customer customers[CUSTOMERS_NUM];
        fillWithCustomers(customers);

        HANDLE hThreadArray[CUSTOMERS_NUM];
        DWORD dwThreadIdArray[CUSTOMERS_NUM];
        pcustomer_wrapper customerData[CUSTOMERS_NUM];

        for (int i = 0; i < CUSTOMERS_NUM; ++i) {
            customerData[i] = (pcustomer_wrapper) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(customer_wrapper));
            customerData[i]->departments = depts;
            customerData[i]->customer = &(customers[i]);
            hThreadArray[i] = CreateThread(
                    NULL,                   // default security attributes
                    0,                      // use default stack size
                    goShopping,       // thread function name
                    customerData[i],          // argument to thread function
                    NULL,                      // use default creation flags
                    &dwThreadIdArray[i]);
        }

        WaitForMultipleObjects(CUSTOMERS_NUM, hThreadArray, TRUE, INFINITE);
        for (int i = 0; i < CUSTOMERS_NUM; i++) {
            CloseHandle(hThreadArray[i]);
        }
    }
private:
    Department depts[N];
    void fillWithCustomers(Customer* customers) {
        for (int i = 1; i <= CUSTOMERS_NUM; i++) {
            customers[i-1] = Customer("customer-" + to_string(i));
        }
    }
};

static DWORD WINAPI goShopping(LPVOID lpParam) {
    pcustomer_wrapper customerData;
    customerData = (pcustomer_wrapper) lpParam;
    Customer* customer;
    customer = customerData->customer;
    int deptNumber = customer->getNextDeptNum();
    customer->incrementNextDeptNum();
    printf("\n%s", customerData->departments[deptNumber].getName().c_str());
}