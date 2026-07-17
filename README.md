# Matching Engine

A C++ implementation of a limit order book matching engine, simulating price-time priority order matching like a stock exchange.

## What it does
Accepts buy/sell limit orders and matches them against the order book using **price-time priority** — the same core rule real exchanges use to decide which orders trade first.

## Features
- Price-time priority matching (best price first, then earliest order at that price)
- Partial fills (an order can be matched across multiple counter-orders)
- Order cancellation with O(log n) lookup via an auxiliary index
- Live order book view with aggregated quantity per price level

## How matching works
When a new order arrives:
1. It's checked against the opposite side of the book (a buy checks sell orders, and vice versa)
2. If the price crosses (buy price ≥ best sell price, or sell price ≤ best buy price), a trade executes
3. Matching continues until the order is fully filled or no more crossing orders exist
4. Any unfilled quantity rests in the book as a new order

## Design decisions
- **`std::map` instead of a heap** for price levels: a heap gives O(log n) access to the best price only, but doesn't support efficient cancellation at arbitrary price levels. `std::map` (red-black tree) gives O(log n) insert/delete at any price level while still giving O(1) access to the best price via `.begin()`.
- **`std::queue` per price level** preserves FIFO time priority among orders at the same price.
- **`unordered_map<orderId, {price, side}>`** as an auxiliary index: enables O(1) lookup of any order's location, avoiding a full book scan on cancellation.
- **Tradeoff/future improvement**: cancellation currently rebuilds the queue at a price level (O(k), k = orders at that price). A doubly linked list per price level would make cancellation O(1) — a reasonable next step for a production-grade version.

## Build & run
```bash
g++ src/main.cpp src/OrderBook.cpp -o engine
./engine
```

## Example output
## Future improvements
- Support market orders (execute immediately at best available price)
- Read order batches from a CSV file for realistic simulation
- Multithreaded order submission for concurrent trading simulation
- Unit test suite covering match/partial-match/cancel scenarios

## Status
🚧 Actively being developed — see commit history for progress.