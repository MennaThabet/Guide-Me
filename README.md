# Guide Me – Transportation Route Planner

> A budget-conscious travel assistant system using graph algorithms and file-based data storage.

## ✨ Project Overview

"Guide Me" helps users find affordable travel routes between cities. The user enters a source, destination, and budget, and the system displays **all transportation options within budget**, using BFS/DFS to explore the graph.

Includes an **admin panel** to add, update, or delete transportation options and ensures **graph consistency and persistence** through file handling.

## 🔧 Features

- 🚗 Find all valid routes between two cities within a given budget
- 🔁 Traverse the map using **BFS or DFS**
- 🛠️ Update, delete, or add new transportation options (Admin-only)
- 🔍 Check if the graph is **connected** or **complete**
- 💾 Reads from and writes to a file to persist the transportation map

## 🧠 Data Structures Used

- `unordered_map` for city-name to ID mapping
- `vector<vector<pair<int, pair<string, int>>>>` for adjacency list with transport type + cost
- `set<pair<int, vector<string>>>` to store all valid paths sorted by cost
- `vector<vector<bool>>` for completeness checking (adjacency matrix)
- `deque`, `queue`, and `vector` for traversal and state tracking

## 🖼️ Sample Menu Flow

Welcome to Guide Me

To login as a User enter 1, or to login as an Admin enter 2

1. Traverse the graph using BFS or DFS

2. Check if map is connected

3. Check if map is complete

4. Show all valid routes between two cities

5. (Admin) Add, Update, Delete transportation

6. Logout


## 📂 File Structure

- `TransportationMap.txt`: Stores all transportation data
- `main.cpp`: Main application logic
- `Menu()`: Admin/User interface
- `reading_input()`, `write_data()`: File handlers
- `Find_Paths_Between_Cities()`: Core DFS pathfinder

## 🧪 Algorithms Used

- **DFS**: for route exploration and connectivity
- **BFS**: for traversal
- **Custom comparator**: for sorting routes by cost
- **Transformations**: user-friendly name normalization

## 🖥️ How to Run

1. Clone the repo
2. Make sure `TransportationMap.txt` is in the root directory
3. Compile the project:
g++ main.cpp -o guide
./guide
4. Follow console instructions

## 🧠 Learning Outcome

- Practiced using graphs in real-world applications
- Designed flexible input parsing and persistent storage
- Improved file handling, sorting, and user-interface logic
  
