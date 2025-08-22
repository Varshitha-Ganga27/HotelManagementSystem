# HotelManagementSystem
Overview

This project is a console-based Hotel Management System implemented in C++, demonstrating Object-Oriented Programming (OOP) concepts and file handling.
It allows an admin to manage hotel room bookings, view customer details, calculate bills, and handle checkouts.

Features

Admin Login (Password Protected)

Room Booking with Availability Check

View All Customers (Persistent Storage using File Handling)

Billing System (Auto Calculation of Total Rent)

Customer Checkout (Removes Record from File)

Menu-Driven Console Interface

OOP Concepts Used

Inheritance – Person → Customer

Polymorphism – Overriding display() method

Encapsulation – Using private data members with public methods

File Handling – Store and retrieve customer data (customers.txt)

Tech Stack

Language: C++

Concepts: OOP (Classes, Inheritance, Polymorphism), File Handling, STL (vector, string)

Compiler: GCC (MinGW), Turbo C++, MSVC

How to Run

Clone/Download the repository.

Open terminal/command prompt in the project folder.

Compile the code:

g++ hotel.cpp -o hotel


Run the program:

./hotel


Login as Admin (Default Password: admin123)

Use menu options to book rooms, view customers, or checkout customers.

File Structure
.
├── hotel.cpp         # Main source code
├── customers.txt     # Stores customer data (auto-created)
└── README.md         # Project Documentation

Future Enhancements

Add GUI using Qt for better user experience.

Integrate Database (MySQL/SQLite) for large-scale use.

Add Colorful Console UI with ASCII art.
