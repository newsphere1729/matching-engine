#include "../include/OrderBook.h"

int main() {
    OrderBook book;

    book.addOrder(Order(1, true, 100.5, 10, 1));    // Resting buy
    book.addOrder(Order(2, false, 100.5, 6, 2));    // Matches 6
    book.printBook();

    book.addOrder(Order(3, false, 99.0, 10, 3));    // Matches remaining 4
    book.printBook();

    return 0;
}