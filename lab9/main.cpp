#include <conio.h>
#include "Shop.cpp"



int main() {
/*

    Shop shop;
    shop.work();
*/

    Customer customer = Customer("customer");
    printf("%d", customer.getNextDeptNum());
    printf("%d", customer.getNextDeptNum());
    printf("%d", customer.getNextDeptNum());

    getch();
    return 0;
}
