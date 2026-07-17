#include "../include/OrderBook.h"

int main() {
    OrderBook book;

    book.addOrder(Order(1, true, 100.5, 10, 1));
    book.addOrder(Order(2, true, 101.0, 5, 2));
    book.addOrder(Order(3, false, 102.0, 8, 3));
    book.addOrder(Order(4, false, 103.5, 4, 4));

    book.printBook();

    return 0;
}