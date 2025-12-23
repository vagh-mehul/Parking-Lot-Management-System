# 🚗 Parking Lot Management System (C++)

A **console-based Parking Lot Management System** implemented in **C++ using Object-Oriented Programming (OOP)** concepts.\
The project is optimized for **performance** using `unordered_set` for free slot tracking and supports a **waiting queue** so vehicles automatically enter when slots become free.



---

## ✨ Features

- Supports **Car** and **Bike** parking
- **Dynamic slot configuration** (user inputs number of car & bike slots)
- Each parking slot has a **unique slot ID**
- **O(1) slot allocation & release** using `unordered_set`
- **Waiting queue** for cars and bikes when slots are full
- Automatic parking of waiting vehicle when a slot is freed
- Parking **ticket generation** with entry time
- **Fee calculation** based on parking duration
- Real-time parking status display

---

## 🏗️ Design Overview

### Core Classes

- **Vehicle (abstract)**\
  Base class for all vehicles

- **Car, Bike**\
  Derived classes implementing vehicle type

- **ParkingSlot**\
  Represents a single parking slot with ID, type, and occupancy

- **Ticket**\
  Stores parking details (slot ID, vehicle number, entry time)

- **ParkingLot**\
  Core class managing slots, tickets, waiting queues, and parking logic

---

## ⚙️ Data Structures Used

| Purpose         | Data Structure                  | Reason            |
| --------------- | ------------------------------- | ----------------- |
| Free car slots  | `unordered_set<int>`            | O(1) insert/erase |
| Free bike slots | `unordered_set<int>`            | O(1) insert/erase |
| Waiting cars    | `queue<Vehicle*>`               | FIFO order        |
| Waiting bikes   | `queue<Vehicle*>`               | FIFO order        |
| Active tickets  | `unordered_map<string, Ticket>` | Fast lookup       |

---

## ⏱️ Time Complexity

| Operation                | Complexity |
| ------------------------ | ---------- |
| Park vehicle             | **O(1)**   |
| Remove vehicle           | **O(1)**   |
| Find free slot           | **O(1)**   |
| Waiting queue operations | **O(1)**   |

---

## 🧪 Sample Flow

```
Enter number of Car slots: 30
Enter number of Bike slots: 3

1. Park Car
2. Park Bike
3. Remove Vehicle
4. Display Status
5. Exit
```

- If all car slots are full, extra cars go into **waiting queue**
- When a car exits, the **next waiting car is parked automatically**

---

## 🧠 OOP Concepts Demonstrated

- **Abstraction** → `Vehicle` abstract base class
- **Inheritance** → `Car`, `Bike`
- **Polymorphism** → `Vehicle*` calling overridden methods
- **Encapsulation** → private data members

##

---



