# Railway-_Reservation_System
A C++ Railway Reservation System demonstrating OOP concepts like classes, inheritance, polymorphism, encapsulation, abstraction, exception handling, STL vectors, dynamic objects, and file handling for train search, ticket booking, cancellation, and management.
# 🚆 Railway Reservation System

A **console-based Railway Reservation System** developed using **C++ and Object-Oriented Programming (OOP)** concepts. The system provides basic railway reservation features such as train searching, ticket booking, ticket cancellation, boarding station changes, and ticket file storage.

## 📌 Features

* 🚆 Display all available trains
* 🔍 Search trains by source and destination
* 🎫 Book tickets
* 👤 Store passenger details
* 💺 Select coach class and seat type
* 🧾 Generate PNR and e-ticket details
* ❌ Cancel tickets and calculate refunds
* 📍 Change boarding station
* 🛠️ Display train facilities
* 💾 Save and read tickets using file handling
* ⚠️ Handle invalid inputs using exception handling

##  OOP Concepts Used

This project demonstrates the following C++ concepts:

* Classes and Objects
* Encapsulation
* Abstraction
* Inheritance
* Function Overloading
* Function Overriding
* Runtime Polymorphism
* Abstract Classes
* Pure Virtual Functions
* Constructors and Destructors
* Friend Functions
* Operator Overloading
* Array of Objects
* Dynamic Object Creation
* References and Pass-by-Reference
* Exception Handling
* STL `vector`

## 🏗️ Classes

| Class       | Purpose                                 |
| ----------- | --------------------------------------- |
| `Coach`     | Abstract base class for coach types     |
| `Sleeper`   | Implements Sleeper coach                |
| `AC3Tier`   | Implements AC 3 Tier coach              |
| `AC2Tier`   | Implements AC 2 Tier coach              |
| `Person`    | Abstract base class for person details  |
| `Passenger` | Stores passenger information            |
| `Train`     | Manages train details, routes and seats |
| `Ticket`    | Manages reservation and ticket details  |

##  Technologies Used

* **Language:** C++
* **Programming Paradigm:** Object-Oriented Programming
* **STL:** `vector`
* **File Handling:** `fstream`
* **Input/Output:** `iostream`



## 📋 Main Menu

The application provides the following options:


1. Show all trains
2. Search trains (route wise)
3. Book ticket
4. View ticket
5. Cancel ticket
6. Change boarding station
7. Train facilities
8. Show tickets saved in file
9. Exit


💾##  File Handling

Booked ticket information is stored in a `tickets.txt` file using C++ file handling. The system can also read and display previously saved tickets.

## 🎯 Project Objective

The objective of this project is to implement a practical railway reservation system while demonstrating important **C++ OOP concepts** such as inheritance, abstraction, polymorphism, encapsulation, constructors, friend functions, exception handling, dynamic objects, STL vectors, and file handling.

## 👨‍💻 Author

**Raj Choudhary**

---

