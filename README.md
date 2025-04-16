
# 📘 Project: Find Horcrux - A Harry Potter Text Adventure Game

## 🎮 Project Overview
**Find Horcrux** is a console-based text adventure game designed as a C++ Data Structures project. It immerses the player in the world of Harry Potter, where the goal is to collect magical items like the Elder Wand and Horcrux, and defeat Voldemort.

---

## 🧠 Data Structures Used

### 1. Stack (📚 Room History)
- **Purpose**: Stores the history of rooms the player has visited.
- **Use Case**: Helps the player go "back" to the previous room using LIFO (Last In, First Out).

### 2. Queue (📜 Task List)
- **Purpose**: Manages tasks to be completed in order (e.g., find wand → get horcrux → defeat Voldemort).
- **Use Case**: Enforces task sequence using FIFO (First In, First Out).

### 3. Linked List (🧳 Inventory)
- **Purpose**: Dynamic storage for magical items the player collects.
- **Use Case**: Allows adding and checking for items (e.g., check if player has Elder Wand).

---

## 🗺️ Game Flow

- Starts at **Gryffindor Common Room**
- Player uses commands:
  - `move [location]` to explore
  - `back` to revisit previous location
  - `help` for instructions
  - `exit` to quit
- The goal is to collect:
  - **Elder Wand** (from Dumbledore’s Office)
  - **Horcrux** (from Forbidden Forest)
  - **Final Battle** in Chamber of Secrets

---

## 💡 How to Compile and Run

```bash
g++ horcrux.cpp -o horcrux
./horcrux
```

---

## 🔚 Conclusion

This project is a perfect demonstration of how basic data structures (Stack, Queue, Linked List) can be used to build a fun and functional adventure game in C++.
