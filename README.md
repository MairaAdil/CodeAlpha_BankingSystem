# 🏦 Banking Management System — CodeAlpha C++ Internship

A console-based **Banking Management System** developed in C++ as part of the **CodeAlpha C++ Programming Internship — Task 3**.

The application simulates essential banking operations including customer and account creation, deposits, withdrawals, fund transfers, account information, and recent transaction history. It also saves banking data to a local file so that customer and account information can be loaded again when the program starts.

---

## 📌 Project Overview

The **Banking Management System** is an object-oriented C++ application designed to demonstrate the basic functionality of a banking environment.

The system allows users to:

* Create customers and their accounts
* Generate customer IDs and account numbers
* Deposit money
* Withdraw money
* Transfer funds between accounts
* View account details
* View recent transactions
* Display all registered customers
* Save banking data to a file
* Load previously saved banking data

The project combines **Object-Oriented Programming, file handling, input validation, arrays, functions, and transaction management** into one console application.

---

## 🏢 CodeAlpha Internship

**Internship:** CodeAlpha C++ Programming Internship
**Task:** Task 3 — Banking System
**Language:** C++
**Application Type:** Console Application
**Storage:** Local text file
**Platform:** C++

---

## ✨ Main Features

### 👤 Customer Management

The system allows new customers to be registered with:

* Customer name
* Phone number
* Automatically generated customer ID
* Automatically generated account number

Customer names are validated to allow letters and spaces only.

Phone numbers must contain exactly **11 digits**, and duplicate phone numbers are rejected.

---

### 🏦 Account Management

Each customer is assigned an account when the customer is created.

The system automatically generates:

```text
Customer ID: 1001+
Account Number: 50001+
```

The next available IDs and account numbers are updated as new customers are created.

---

### 💰 Deposit Money

Users can deposit a positive amount into an existing account.

After a successful deposit, the system displays the updated balance and records the transaction as a **Deposit**.

---

### 💸 Withdraw Money

The withdrawal system:

* Accepts a positive amount
* Checks the account balance
* Prevents withdrawals greater than the available balance
* Updates the account balance
* Records the withdrawal transaction

The user is shown the available balance if the requested withdrawal exceeds the account balance.

---

### 🔄 Fund Transfer

Money can be transferred between two different accounts.

The system checks:

* Sender account exists
* Receiver account exists
* Sender and receiver are different
* Transfer amount is positive
* Sender has sufficient balance

A successful transfer creates two transaction records:

```text
Transfer Out → Sender
Transfer In  → Receiver
```

The updated balances of both accounts are displayed after the transfer.

---

### 📜 Transaction History

Every successful deposit, withdrawal, and transfer is recorded as a transaction.

The system stores:

* Transaction type
* Amount
* Transaction details

## The application displays up to the **5 most recent transactions** for an account.

### 💾 Data Persistence

Unlike a temporary in-memory banking simulation, this implementation saves its data to:

```text
bank_data.txt
```

## Customer information, account information, balances, and transaction records are written to the file and loaded again when the application starts.

## 🧱 Object-Oriented Design

The project is built around four main classes:

```text
BankingSystem
      │
      └── Customer
             │
             └── Account
                    │
                    └── Transaction
```

---

## 🔹 `Transaction` Class

The `Transaction` class represents an individual banking transaction.

### Attributes

```cpp
string type;
double amount;
string details;
```

### Responsibilities

* Store transaction type
* Store transaction amount
* Store transaction details
* Display transaction information

The system uses transaction types such as:

```text
Deposit
Withdraw
Transfer Out
Transfer In
```

---

## 🔹 `Account` Class

The `Account` class manages an individual bank account.

### Main Data

* Account number
* Balance
* Transaction array
* Transaction count

### Main Operations

```text
Create Account
Deposit
Withdraw
Transfer
Display Account
Display Recent Transactions
Save Account Data
Load Account Data
```

The class supports up to **100 transactions per account**.

---

## 🔹 `Customer` Class

The `Customer` class stores customer information and contains the customer's account.

### Customer Information

```text
Customer ID
Name
Phone Number
Account
```

Each customer object manages its associated account and can display the customer's information together with account details.

---

## 🔹 `BankingSystem` Class

The `BankingSystem` class acts as the main controller of the application.

It manages:

* Customers
* Customer IDs
* Account numbers
* File storage
* Input validation
* Banking operations
* Application menu

The program supports up to **100 customers** and uses `bank_data.txt` for data persistence.

---

## 📊 System Limits

The project defines the following limits:

| Item                             | Limit |
| -------------------------------- | ----: |
| Maximum Customers                |   100 |
| Maximum Transactions per Account |   100 |
| Recent Transactions Displayed    |     5 |
| Starting Customer ID             |  1001 |
| Starting Account Number          | 50001 |

---

## 🖥️ Main Menu

When the application starts, users are presented with:

```text
========================================
       BANKING MANAGEMENT SYSTEM
========================================

1. Create Customer / Account
2. Deposit Money
3. Withdraw Money
4. Transfer Money
5. View Account Details
6. View Recent Transactions
7. Display All Customers
0. Exit

========================================
Enter choice:
```

---

## 🔄 Application Workflow

```text
                 START
                   │
                   ▼
          Load Saved Bank Data
                   │
                   ▼
              Main Menu
                   │
      ┌────────────┼────────────┐
      ▼            ▼            ▼
   Create       Deposit      Withdraw
  Customer      Money          Money
      │            │            │
      └────────────┼────────────┘
                   │
                   ▼
             Transfer Money
                   │
                   ▼
          View Account Details
                   │
                   ▼
       View Recent Transactions
                   │
                   ▼
        Display All Customers
                   │
                   ▼
             Save Data
                   │
                   ▼
                  EXIT
```

---

## 🧮 Transaction Processing

### Deposit

```text
Account Balance
      +
Deposit Amount
      =
New Balance
```

A successful deposit is recorded as:

```text
Deposit | Amount | Cash deposit
```

---

### Withdrawal

```text
Account Balance
      -
Withdrawal Amount
      =
Remaining Balance
```

The withdrawal is only completed when sufficient funds are available.

---

### Transfer

For a transfer between two accounts:

```text
Sender Balance
      -
Transfer Amount
      ↓
Receiver Balance
      +
Transfer Amount
```

The system records both sides of the transaction:

```text
Transfer Out
Transfer In
```

---

## 💾 File Storage

The application uses:

```text
bank_data.txt
```

The `BankingSystem` class automatically loads saved information when the program starts and saves updated information after banking operations.

Data is saved when:

* A customer/account is created
* A deposit is completed
* A withdrawal is completed
* A transfer is completed
* The program exits

The file stores customer information, account details, balances, and transaction records.

---

## ✅ Input Validation

The application includes validation for several types of user input.

### Customer Name

Only letters and spaces are accepted.

### Phone Number

The phone number must:

* Contain exactly 11 digits
* Contain digits only
* Not already belong to another customer

### Amounts

Deposit, withdrawal, and transfer amounts must be positive numbers.

### Account Numbers

The system verifies that the requested account exists before performing account operations.

### Menu Selection

The main menu accepts choices from:

```text
0 – 7
```

## Invalid choices are rejected and the user is asked to enter a valid option.

## 🛠️ Technologies & C++ Concepts

### Language

**C++**

### Libraries

```cpp
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <cctype>
#include <iomanip>
```

### Concepts Demonstrated

* Object-Oriented Programming
* Classes and objects
* Encapsulation
* Constructors
* Member functions
* Arrays
* References
* File handling
* Data persistence
* Input validation
* String processing
* Loops
* Conditional statements
* Formatted output
* Transaction management

---

## 📁 Project Structure

```text
CodeAlpha_BankingSystem/
├── 1. Screenshot.jpg
├── 2. Screenshot.jpg
├── 3. Screenshot.jpg
├── 4. Screenshot.jpg
├── 5. Screenshot.jpg
├── 6. Screenshot.jpg
├── 7. Screenshot.jpg
├── 8. Screenshot.jpg
├── 9. Screenshot.jpg
├── README.md
└── main.cpp
```

> `bank_data.txt` is generated/updated by the application to store banking information.

---

## ⚙️ Requirements

To run this project, you need:

* A C++ compiler
* C++17 or compatible C++ environment
* Any C++ IDE or compiler such as:

  * Visual Studio
  * Code::Blocks
  * Dev-C++
  * MinGW/GCC

The program uses standard C++ libraries and does not require external frameworks.

---

## ▶️ How to Run

### 1. Clone the Repository

```bash
git clone https://github.com/MairaAdil/CodeAlpha_BankingSystem.git
```

### 2. Open the Project

Open the project in a C++ compatible IDE.

### 3. Compile

Compile `main.cpp` using your C++ compiler.

### 4. Run

Start the application and select an option from the banking management menu.

The application will automatically load existing data from `bank_data.txt` if the file is available.

---

## 🧪 Example Operations

### Creating a Customer

```text
Enter customer name: Maira Adil
Enter phone number (11 digits): 03001234567

Customer created successfully!

Customer ID: 1001
Account Number: 50001
```

### Depositing Money

```text
Enter account number: 50001
Enter deposit amount: 50000

Deposit successful!
New Balance: Rs. 50000.00
```

### Withdrawing Money

```text
Enter account number: 50001
Enter withdrawal amount: 10000

Withdrawal successful!
Remaining Balance: Rs. 40000.00
```

### Transferring Money

```text
Enter sender account number: 50001
Enter receiver account number: 50002
Enter transfer amount: 5000

Transfer successful!
```

---

## 📜 Recent Transaction Example

The application displays recent transactions in a structured format:

```text
Recent Transactions
---------------------------------------------
Type           Amount      Details
---------------------------------------------
Deposit        50000.00    Cash deposit
Withdraw       10000.00    Cash withdrawal
Transfer Out    5000.00    To account 50002
---------------------------------------------
```

The program displays a maximum of **5 recent transactions** for an account.

---

## 🎯 Learning Outcomes

Through this project, practical experience was gained in:

* Designing multiple interacting C++ classes
* Implementing customer and account management
* Building deposit and withdrawal functionality
* Implementing account-to-account transfers
* Maintaining transaction records
* Working with file input/output
* Creating persistent application data
* Validating user input
* Managing relationships between classes
* Building a complete console-based application

---

## 🚀 Future Improvements

Possible improvements for a more advanced version include:

* Multiple accounts per customer
* Customer login and authentication
* PIN/password protection
* Account types such as savings and current accounts
* Interest calculation
* Account deletion and editing
* Transaction search and filtering
* Date and time for every transaction
* Bank statements
* Transaction export
* Database integration
* Improved data encryption
* Administrative controls
* Graphical user interface
* More flexible storage using `vector` and modern C++ containers

---

## ⚠️ Project Scope

This project is an **educational banking simulation** developed for the CodeAlpha C++ Programming Internship.

It demonstrates core banking operations and local data persistence, but it is not intended to represent a real banking infrastructure.

It does not implement real-world banking security, financial regulations, external banking APIs, or production-grade database security.

---

## 👩‍💻 Author

**Maira Adil**

**BS Artificial Intelligence Student**
University of Central Punjab

### Connect With Me

* **LinkedIn:** [linkedin.com/in/mairaadil](https://www.linkedin.com/in/mairaadil)
* **GitHub:** [github.com/MairaAdil](https://github.com/MairaAdil)

---

## 🏆 CodeAlpha Internship

**CodeAlpha C++ Programming Internship**

### Task 3 — Banking System

This project was developed as part of the CodeAlpha internship to apply C++ concepts to a practical banking management application.

---

## 🎇 Acknowledgment

Special thanks to **CodeAlpha** for providing the opportunity to work on practical C++ programming tasks and strengthen software development skills through project-based learning.

---

⭐ If you find this project useful, consider giving the repository a star.
