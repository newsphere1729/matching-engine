#include "../include/Order.h"
#include <iostream>

int main() {
    Order o(1, true, 100.5, 10, 123456789);

    std::cout << "Order created: id="
              << o.orderId
              << ", price="
              << o.price
              << "\n";

    return 0;
}