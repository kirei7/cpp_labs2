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
const DWORD mutexFree = 4294967295;

static DWORD WINAPI goShopping(LPVOID lpParam);

class Shop {
public:
    Shop() {
        // три отдела в магазине
        depts[0] = Department("Equipment department");
        depts[1] = Department("Food department");
        depts[2] = Department("Magic department");
    }

    void work() {
        Customer customers[CUSTOMERS_NUM]; //создаем массив с покупателями
        fillWithCustomers(customers); // и заполняем его

        // дальше как обычно переменные для потоков
        HANDLE hThreadArray[CUSTOMERS_NUM]; //массив с указателями на потоки
        DWORD dwThreadIdArray[CUSTOMERS_NUM]; //массив с айдишками потоков
        pcustomer_wrapper customerData[CUSTOMERS_NUM]; //массив аргументов которые нужно будет передать в функцию которая будет исполняться в отдельном потоке

        for (int i = 0; i < CUSTOMERS_NUM; ++i) {
            //заполняем массив структур аргументов
            customerData[i] = (pcustomer_wrapper) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(customer_wrapper));
            customerData[i]->departments = depts;
            customerData[i]->customer = &(customers[i]);
            //создаем потоки
            hThreadArray[i] = CreateThread(
                    NULL,                   // default security attributes
                    0,                      // use default stack size
                    goShopping,       // thread function name
                    customerData[i],          // передаем аргумент в виде структуры в функцию
                    NULL,                      // use default creation flags
                    &dwThreadIdArray[i]);
        }

        //ждем пока все созданные потоки выполнятся
        WaitForMultipleObjects(CUSTOMERS_NUM, hThreadArray, TRUE, INFINITE);
        //закрываем указатели на потоки
        for (int i = 0; i < CUSTOMERS_NUM; i++) {
            CloseHandle(hThreadArray[i]);
        }
    }
private:
    //массив с отделами магазина
    Department depts[N];

    //вспомогательная функция которая заполняет массив покупателей покупателями
    //если что то можно удалить  -" + to_string(i) чтобы не было видно что покупатели идут подряд
    void fillWithCustomers(Customer* customers) {
        for (int i = 1; i <= CUSTOMERS_NUM; i++) {
            customers[i-1] = Customer("customer-" + to_string(i));
        }
    }
};

//функция которая выполняется в потоке
static DWORD WINAPI goShopping(LPVOID lpParam) {
    //вытягиваем из структуры аргументов собственно аргументы
    pcustomer_wrapper customerData;
    customerData = (pcustomer_wrapper) lpParam;
    Customer* customer;
    customer = customerData->customer;
    //просто 3000 раз заставляем покупателя затариться
    for(int i = 0; i < 3000; i++) {
        //берем отдел в который ему нужно пойти
        int deptNumber = customer->getNextDeptNum();
        //ходим в этот отдел
        customerData->departments[deptNumber].acceptVisitor(customer->getName());
        //после того как походили указываем что в следующий раз нужно посетить следующий отдел
        customer->incrementNextDeptNum();
    }
}