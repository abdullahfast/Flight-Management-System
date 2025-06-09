# ✈️ Flight Reservation and Management System

A fully functional, console-based Flight Reservation System implemented in **C++**. This application simulates airline operations, offering features such as flight booking, ticketing, customer management, seat assignment, loyalty discounts, and data persistence via external files.

---

## 📌 Features

- **Customer Management**
  - Add, update, delete, and view customer profiles.
  - Validates date of birth input.

- **Flight Management**
  - Add, update, delete, and view scheduled flights.
  - Supports ticket types and plane association.

- **Reservation System**
  - Reserve and cancel flight seats.
  - Manage waiting lists for full flights.
  - Automatically assigns the next available seat.

- **Ticketing**
  - Generate tickets with unique numbers.
  - Display price, seat number, and applied discounts.

- **Loyalty Offers**
  - Discount logic based on:
    - Total miles traveled
    - Number of flights taken

- **Data Persistence**
  - Load and save data via:
    - `flights.txt`
    - `customers.txt`
    - `planes.txt`
    - `offers.txt`
    - `tickets.txt`
    - `airports.txt`

---

## 🧰 Technologies & Concepts Used

- **Language:** C++
- **Data Structures:**
  - Singly Linked List – for Airports and Planes
  - Doubly Linked List – for Flights
  - Binary Search Tree (BST) – for Customers and Flight Passengers
  - Queue – for managing waiting lists
  - Vectors & Arrays – for Tickets and Offers

- **Standard C++ Libraries:**
  - `<iostream>`, `<fstream>`, `<string>`, `<vector>`, `<queue>`, `<unordered_map>`, `<unordered_set>`, `<algorithm>`, `<iomanip>`, `<limits>`, `<ctime>`

---


