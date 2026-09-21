Genius Book Management System

A console-based C++ Bookshop Management System designed to manage books, buyers, sellers, shopping carts, and sales through a simple menu-driven interface.

Overview

The Genius Book Management System provides separate access for Guest, Buyer, and Seller users. The application uses Object-Oriented Programming concepts, C++ functions, file handling, and text-file data storage to manage book records and purchase information.

The project is designed as a practical C++ application that demonstrates how a small bookshop can manage its catalog and customer purchasing workflow without a database.

Main Features

Guest Mode

Browse available books without purchasing.

View books by category.

View latest added books.

View company details.

Seller-only operations are protected behind login.

Buyer Mode

View available books by category.

Search books by Book ID.

Search books by complete Book Name.

Add books to the shopping cart.

View cart contents.

Remove books from the cart.

Enter purchase quantities.

Calculate the total purchase amount.

Confirm or cancel a purchase.

Store completed sales records.

Seller Mode

View available book details.

Add new books.

Update existing book details.

Delete books.

View company details.

Manage and view sales records.

Review total sales information.

Book Categories

The system includes categories for:

Martin Wickramasinghe

J.K. Rowling

Gunadasa Amarasekara

Ediriweera Sarachchandra

T.B. Ilangaratne

Educational Books

Children Books

Latest Books

Technologies Used

C++

Object-Oriented Programming (OOP) concepts

Functions and modular programming

File Handling (fstream)

String processing (string)

Text-file based data storage

Console-based user interface

Project Structure

BOOKSHOP-C++/
│
├── FIP.cpp
├── availablebook.txt
├── addbook.txt
├── cart.txt
├── sales.txt
├── newcart.txt
├── newdeatails.txt
├── GeniusBookshop_Code_Explanation_and_Test_Cases.docx
└── .gitignore

Data Files

File

Purpose

availablebook.txt

Stores the main available book catalog.

addbook.txt

Stores books added by the seller.

cart.txt

Stores books currently selected by the buyer.

sales.txt

Stores completed purchase and sales information.

newcart.txt

Supporting cart data file used by the project.

newdeatails.txt

Supporting project data file.

How the System Works

The application starts with a role-selection page:

01. Guest Mode
02. For Sellers
03. For Buyers
04. Exit

After selecting a role, the user is taken to the relevant menu. Book information is read from and written to .txt files, allowing the system to preserve data between program executions.

How to Run

Requirements

Windows operating system

A C++ compiler such as MinGW/G++, Code::Blocks, or Visual Studio

Using G++

Open a terminal inside the project folder and compile the source file:

g++ FIP.cpp -o FIP.exe

Run the application:

FIP.exe

The project uses Windows console commands such as cls and pause, so it is intended primarily for a Windows environment.

Login Details

The current source code contains the following demo credentials for both buyer and seller login:

Username: shehan
Password: 1234

These credentials are included for demonstration purposes only. For a production system, authentication should be implemented securely rather than storing credentials directly in source code.

Documentation

The repository includes:

GeniusBookshop_Code_Explanation_and_Test_Cases.docx

This document contains the project code explanation and test cases used to evaluate the system's functionality.

Learning Outcomes

This project demonstrates practical experience with:

Designing menu-driven C++ applications

Breaking a program into reusable functions

Reading and writing structured text data

Searching and updating file-based records

Implementing shopping cart and purchase workflows

Calculating sales totals

Handling separate user roles

Applying basic input validation

Managing a complete small-scale software project

Future Improvements

Possible future enhancements include:

Database integration using MySQL or SQL Server

Secure user authentication and registration

Password hashing

A graphical user interface (GUI)

Inventory and stock-quantity management

Online payment integration

Customer purchase history

Better error handling and input validation

Automated unit testing

Author

Rankothge Shehan Sewmina

Software Engineering Student | C++ Developer

