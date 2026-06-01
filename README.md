# 🚚 Event Logistics Management System

A **C++ console application** that models a transportation network and finds the optimal (shortest) delivery route between cities using **Graph Theory** and the **BFS (Breadth-First Search)** algorithm. Cities are represented as vertices and routes (road or air) as edges.

---

## 📌 Features

- Models a transportation network with cities connected by **road and air routes**
- Finds the **shortest path** from the source city to the destination using BFS
- Supports **multiple air routes** between non-adjacent cities (distance > 6 stops apart)
- Calculates **total delivery time** in days and hours
- Validates whether delivery can be completed within a **user-defined deadline**
- Handles **multiple test cases** in a single run
- Includes **robust input validation** to prevent invalid or malformed entries
- Colorized terminal output for better readability

---

## 🛠️ Technologies Used

- **Language:** C++
- **Data Structures:** Adjacency List (Linked List), Custom Queue
- **Algorithm:** Breadth-First Search (BFS)
- **Concepts:** Graph Theory, Dynamic Memory Management

---

## 🚀 Getting Started

### Prerequisites

- A C++ compiler (e.g., `g++`, MSVC, or Clang)

### Compilation

```bash
g++ project.cpp -o logistics
```

### Run

```bash
./logistics
```

---

## 🎮 How to Use

1. **Enter the number of test cases** you want to run.
2. For each test case:
   - Enter the **number of stops** (cities) in the network.
   - Enter the **number of air routes** to add.
   - For each air route, enter the **source and destination city** (space-separated). Air routes are only added if the cities are more than 6 stops apart.
   - Enter the **maximum allowed delivery time** as `days hours` (e.g., `3 12` = 3 days and 12 hours).
3. The program will:
   - Display the full **graph of connections** (road and air)
   - Print the **shortest path** to the destination
   - Show the **estimated delivery time**
   - Indicate whether the deadline **can or cannot** be met ✅ / ❌

---

## 📊 Route Time Rules

| Route Type | Condition         | Time Cost |
|------------|-------------------|-----------|
| Road       | Adjacent cities   | 4 hours   |
| Air        | Distance > 6 stops| 24 hours  |

---

## 🧩 Project Structure

```
project.cpp
├── struct node          → Graph vertex / queue node
├── struct Queue         → Custom linked-list queue (push, pop, peek)
├── reverse_queue()      → Reverses queue recursively (for path display)
├── struct Graph
│   ├── Graph()          → Constructor; builds road-connected city chain
│   ├── add_edge()       → Adds road or air route between cities
│   ├── shortest_path()  → BFS traversal to find shortest path
│   ├── print()          → Displays adjacency list with route types
│   └── output()         → Calculates and displays delivery time & result
├── convert()            → Parses space-separated string input to integers
├── valid_input()        → Validates user input for numbers and format
├── case_solve()         → Handles one full test case
└── main()               → Entry point; loops over test cases
```

---

## 💡 Example

```
Enter number of Test cases = 1
Test case 1
Enter number of stops : 10
Enter number of routes by air : 1
1 9
Enter the max days and hours for delivery : 2 0

#####################################################################################
###                      GRAPH OF LINKS BETWEEN STOPS                            ###
###                         ( BY ROAD AND BY AIR )                               ###
#####################################################################################

   1 -> 2 (road) , 9 (air)
   2 -> 3 (road)
   ...
  10 (DESTINATION)

The Shortest Path to reach the destination is :
1 -> 9 -> 10 ->

The equipment will be delivered in : 1 days and 4 hours

Congrats, the delivery CAN be made within the assigned time of 2 days and 0 hours.
```

---

## ⚠️ Input Constraints

- Number of stops must be **greater than 0**
- Air route source and destination must be **different cities** within the valid range
- Air routes are **ignored** if the two cities are 6 or fewer stops apart
- Max delivery time: hours must be between **0 and 23**

---

## 👤 Author

**sohaib0075**  
[GitHub Profile](https://github.com/sohaib0075)

---

## 📄 License

This project is open source and available under the [MIT License](LICENSE).
