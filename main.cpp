#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <cctype>
#include <iomanip>
using namespace std;

const int MAX_CUSTOMERS = 100;
const int MAX_TRANSACTIONS = 100;
const int RECENT_COUNT = 5;

class Transaction {
public:
	string type;
	double amount;
	string details;

	Transaction() {
		type = "";
		amount = 0;
		details = "";
	}

	Transaction(string t, double a, string d) {
		type = t;
		amount = a;
		details = d;
	}

	void display() {
		cout << left << setw(15) << type
			<< setw(12) << fixed << setprecision(2) << amount
			<< details << endl;
	}
};

class Account {
private:
	int accountNumber;
	double balance;
	Transaction transactions[MAX_TRANSACTIONS];
	int transactionCount;

public:
	Account() {
		accountNumber = 0;
		balance = 0;
		transactionCount = 0;
	}

	void createAccount(int number) {
		accountNumber = number;
		balance = 0;
		transactionCount = 0;
	}

	int getAccountNumber() {
		return accountNumber;
	}

	double getBalance() {
		return balance;
	}

	int getTransactionCount() {
		return transactionCount;
	}

	void addTransaction(string type, double amount, string details) {
		if (transactionCount < MAX_TRANSACTIONS) {
			transactions[transactionCount] =
				Transaction(type, amount, details);

			transactionCount++;
		}
	}

	bool deposit(double amount) {
		if (amount <= 0 || transactionCount >= MAX_TRANSACTIONS)
			return false;

		balance += amount;

		addTransaction(
			"Deposit",
			amount,
			"Cash deposit"
		);

		return true;
	}

	bool withdraw(double amount) {
		if (amount <= 0 ||
			amount > balance ||
			transactionCount >= MAX_TRANSACTIONS)
			return false;

		balance -= amount;

		addTransaction(
			"Withdraw",
			amount,
			"Cash withdrawal"
		);

		return true;
	}

	bool transfer(Account& receiver, double amount) {
		if (amount <= 0 ||
			amount > balance ||
			this == &receiver ||
			transactionCount >= MAX_TRANSACTIONS ||
			receiver.transactionCount >= MAX_TRANSACTIONS)
			return false;

		balance -= amount;
		receiver.balance += amount;

		addTransaction(
			"Transfer Out",
			amount,
			"To account " + to_string(receiver.accountNumber)
		);

		receiver.addTransaction(
			"Transfer In",
			amount,
			"From account " + to_string(accountNumber)
		);

		return true;
	}

	void displayAccount() {
		cout << "\nAccount Number: "
			<< accountNumber << endl;

		cout << "Balance: Rs. "
			<< fixed << setprecision(2)
			<< balance << endl;
	}

	void displayRecentTransactions() {
		if (transactionCount == 0) {
			cout << "\nNo transactions found.\n";
			return;
		}

		int start = transactionCount - RECENT_COUNT;

		if (start < 0)
			start = 0;

		cout << "\nRecent Transactions\n";
		cout << "---------------------------------------------\n";

		cout << left
			<< setw(15) << "Type"
			<< setw(12) << "Amount"
			<< "Details\n";

		cout << "---------------------------------------------\n";

		for (int i = start; i < transactionCount; i++) {
			transactions[i].display();
		}
	}

	void saveToFile(ofstream& file) {
		file << accountNumber << '\n';
		file << setprecision(17) << balance << '\n';
		file << transactionCount << '\n';

		for (int i = 0; i < transactionCount; i++) {
			file << transactions[i].type << '\n';
			file << setprecision(17)
				<< transactions[i].amount << '\n';
			file << transactions[i].details << '\n';
		}
	}

	bool loadFromFile(ifstream& file) {
		string line;

		if (!getline(file, line))
			return false;

		accountNumber = stoi(line);

		if (!getline(file, line))
			return false;

		balance = stod(line);

		if (!getline(file, line))
			return false;

		transactionCount = stoi(line);

		if (transactionCount < 0 ||
			transactionCount > MAX_TRANSACTIONS)
			return false;

		for (int i = 0; i < transactionCount; i++) {

			if (!getline(file, transactions[i].type))
				return false;

			if (!getline(file, line))
				return false;

			transactions[i].amount = stod(line);

			if (!getline(file, transactions[i].details))
				return false;
		}

		return true;
	}
};

class Customer {
private:
	int customerID;
	string name;
	string phone;
	Account account;

public:
	Customer() {
		customerID = 0;
		name = "";
		phone = "";
	}

	void createCustomer(
		int id,
		string n,
		string p,
		int accountNo
	) {
		customerID = id;
		name = n;
		phone = p;

		account.createAccount(accountNo);
	}

	int getCustomerID() {
		return customerID;
	}

	string getName() {
		return name;
	}

	string getPhone() {
		return phone;
	}

	int getAccountNumber() {
		return account.getAccountNumber();
	}

	Account& getAccount() {
		return account;
	}

	void displayCustomer() {
		cout << "\nCustomer ID: "
			<< customerID << endl;

		cout << "Name: "
			<< name << endl;

		cout << "Phone: "
			<< phone << endl;

		account.displayAccount();
	}

	void saveToFile(ofstream& file) {
		file << "CUSTOMER\n";
		file << customerID << '\n';
		file << name << '\n';
		file << phone << '\n';

		account.saveToFile(file);
	}

	bool loadFromFile(ifstream& file) {
		string line;

		if (!getline(file, line))
			return false;

		if (line != "CUSTOMER")
			return false;

		if (!getline(file, line))
			return false;

		customerID = stoi(line);

		if (!getline(file, name))
			return false;

		if (!getline(file, phone))
			return false;

		return account.loadFromFile(file);
	}
};

class BankingSystem {
private:
	Customer customers[MAX_CUSTOMERS];

	int customerCount;
	int nextCustomerID;
	int nextAccountNumber;

	string fileName;

	bool readInt(string message, int& value) {
		while (true) {
			cout << message;

			if (cin >> value) {
				cin.ignore(
					numeric_limits<streamsize>::max(),
					'\n'
				);

				return true;
			}

			cout << "Invalid input! Please enter a number.\n";

			cin.clear();

			cin.ignore(
				numeric_limits<streamsize>::max(),
				'\n'
			);
		}
	}

	bool readAmount(string message, double& amount) {
		while (true) {
			cout << message;

			if (cin >> amount &&
				amount > 0) {

				cin.ignore(
					numeric_limits<streamsize>::max(),
					'\n'
				);

				return true;
			}

			cout << "Invalid amount! "
				<< "Please enter a positive number.\n";

			cin.clear();

			cin.ignore(
				numeric_limits<streamsize>::max(),
				'\n'
			);
		}
	}

public:

	BankingSystem() {
		customerCount = 0;
		nextCustomerID = 1001;
		nextAccountNumber = 50001;
		fileName = "bank_data.txt";

		loadData();
	}

	void saveData() {
		ofstream file(fileName);

		if (!file) {
			cout << "\nError: Could not save data.\n";
			return;
		}

		file << customerCount << '\n';

		for (int i = 0; i < customerCount; i++) {
			customers[i].saveToFile(file);
		}

		file.close();
	}

	void loadData() {
		ifstream file(fileName);

		if (!file) {
			return;
		}

		string line;

		if (!getline(file, line))
			return;

		customerCount = stoi(line);

		if (customerCount < 0 ||
			customerCount > MAX_CUSTOMERS) {

			customerCount = 0;
			return;
		}

		int maxID = 1000;
		int maxAccount = 50000;

		for (int i = 0; i < customerCount; i++) {

			if (!customers[i].loadFromFile(file)) {
				customerCount = 0;
				return;
			}

			if (customers[i].getCustomerID() > maxID)
				maxID = customers[i].getCustomerID();

			if (customers[i].getAccountNumber() > maxAccount)
				maxAccount = customers[i].getAccountNumber();
		}

		nextCustomerID = maxID + 1;
		nextAccountNumber = maxAccount + 1;

		file.close();
	}

	bool validName(string name) {

		if (name.empty())
			return false;

		for (int i = 0; i < (int)name.length(); i++) {

			if (!isalpha((unsigned char)name[i]) &&
				name[i] != ' ') {

				return false;
			}
		}

		return true;
	}

	bool validPhone(string phone) {

		if (phone.length() != 11)
			return false;

		for (int i = 0; i < (int)phone.length(); i++) {

			if (!isdigit((unsigned char)phone[i]))
				return false;
		}

		return true;
	}

	bool phoneExists(string phone) {

		for (int i = 0; i < customerCount; i++) {

			if (customers[i].getPhone() == phone)
				return true;
		}

		return false;
	}

	int findCustomerByAccount(int accountNo) {

		for (int i = 0; i < customerCount; i++) {

			if (customers[i].getAccountNumber() == accountNo)
				return i;
		}

		return -1;
	}

	void createCustomer() {

		if (customerCount >= MAX_CUSTOMERS) {

			cout << "\nCustomer limit reached.\n";
			return;
		}

		string name;
		string phone;

		while (true) {

			cout << "\nEnter customer name: ";
			getline(cin, name);

			if (validName(name))
				break;

			cout << "Invalid name!\n";
			cout << "Use letters and spaces only.\n";
		}

		while (true) {

			cout << "Enter phone number (11 digits): ";
			getline(cin, phone);

			if (!validPhone(phone)) {

				cout << "Invalid phone number!\n";
				cout << "Phone must contain exactly 11 digits.\n";

				continue;
			}

			if (phoneExists(phone)) {

				cout << "This phone number is already registered!\n";

				continue;
			}

			break;
		}

		customers[customerCount].createCustomer(
			nextCustomerID,
			name,
			phone,
			nextAccountNumber
		);

		cout << "\nCustomer created successfully!\n";

		cout << "Customer ID: "
			<< nextCustomerID << endl;

		cout << "Account Number: "
			<< nextAccountNumber << endl;

		customerCount++;

		nextCustomerID++;
		nextAccountNumber++;

		saveData();
	}

	void depositMoney() {

		int accountNo;
		double amount;

		int index;

		while (true) {

			readInt(
				"\nEnter account number: ",
				accountNo
			);

			index = findCustomerByAccount(accountNo);

			if (index != -1)
				break;

			cout << "Account not found!\n";
			cout << "Please enter a valid account number.\n";
		}

		readAmount(
			"Enter deposit amount: ",
			amount
		);

		if (customers[index].getAccount().deposit(amount)) {

			cout << "\nDeposit successful!\n";

			cout << "New Balance: Rs. "
				<< fixed << setprecision(2)
				<< customers[index].getAccount().getBalance()
				<< endl;

			saveData();
		}
		else {

			cout << "\nTransaction limit reached.\n";
		}
	}

	void withdrawMoney() {

		int accountNo;
		double amount;

		int index;

		while (true) {

			readInt(
				"\nEnter account number: ",
				accountNo
			);

			index = findCustomerByAccount(accountNo);

			if (index != -1)
				break;

			cout << "Account not found!\n";
		}

		while (true) {

			readAmount(
				"Enter withdrawal amount: ",
				amount
			);

			if (amount <=
				customers[index].getAccount().getBalance()) {

				break;
			}

			cout << "Insufficient balance!\n";

			cout << "Available Balance: Rs. "
				<< fixed << setprecision(2)
				<< customers[index].getAccount().getBalance()
				<< endl;
		}

		if (customers[index].getAccount().withdraw(amount)) {

			cout << "\nWithdrawal successful!\n";

			cout << "Remaining Balance: Rs. "
				<< fixed << setprecision(2)
				<< customers[index].getAccount().getBalance()
				<< endl;

			saveData();
		}
		else {

			cout << "Transaction failed.\n";
		}
	}

	void transferMoney() {

		int senderNo;
		int receiverNo;

		double amount;

		int sender;
		int receiver;

		while (true) {

			readInt(
				"\nEnter sender account number: ",
				senderNo
			);

			sender = findCustomerByAccount(senderNo);

			if (sender != -1)
				break;

			cout << "Sender account not found!\n";
		}

		while (true) {

			readInt(
				"Enter receiver account number: ",
				receiverNo
			);

			receiver = findCustomerByAccount(receiverNo);

			if (receiver == -1) {

				cout << "Receiver account not found!\n";
				continue;
			}

			if (sender == receiver) {

				cout << "Sender and receiver cannot "
					<< "be the same account!\n";

				continue;
			}

			break;
		}

		while (true) {

			readAmount(
				"Enter transfer amount: ",
				amount
			);

			if (amount <=
				customers[sender].getAccount().getBalance()) {

				break;
			}

			cout << "Insufficient balance!\n";

			cout << "Available Balance: Rs. "
				<< fixed << setprecision(2)
				<< customers[sender].getAccount().getBalance()
				<< endl;
		}

		if (customers[sender].getAccount().transfer(
			customers[receiver].getAccount(),
			amount)) {

			cout << "\nTransfer successful!\n";

			cout << "Sender New Balance: Rs. "
				<< fixed << setprecision(2)
				<< customers[sender].getAccount().getBalance()
				<< endl;

			cout << "Receiver New Balance: Rs. "
				<< fixed << setprecision(2)
				<< customers[receiver].getAccount().getBalance()
				<< endl;

			saveData();
		}
		else {

			cout << "\nTransfer failed.\n";
		}
	}

	void viewAccount() {

		int accountNo;

		while (true) {

			readInt(
				"\nEnter account number: ",
				accountNo
			);

			int index = findCustomerByAccount(accountNo);

			if (index == -1) {

				cout << "Account not found!\n";
				continue;
			}

			customers[index].displayCustomer();

			break;
		}
	}

	void viewTransactions() {

		int accountNo;

		while (true) {

			readInt(
				"\nEnter account number: ",
				accountNo
			);

			int index = findCustomerByAccount(accountNo);

			if (index == -1) {

				cout << "Account not found!\n";
				continue;
			}

			customers[index]
				.getAccount()
				.displayRecentTransactions();

			break;
		}
	}

	void displayAllCustomers() {

		if (customerCount == 0) {

			cout << "\nNo customers registered.\n";
			return;
		}

		cout << "\n========== ALL CUSTOMERS ==========\n";

		for (int i = 0; i < customerCount; i++) {

			customers[i].displayCustomer();

			cout << "---------------------------------\n";
		}
	}

	void menu() {

		int choice;

		do {

			system("cls");

			cout << "========================================\n";
			cout << "       BANKING MANAGEMENT SYSTEM\n";
			cout << "========================================\n";

			cout << "1. Create Customer / Account\n";
			cout << "2. Deposit Money\n";
			cout << "3. Withdraw Money\n";
			cout << "4. Transfer Money\n";
			cout << "5. View Account Details\n";
			cout << "6. View Recent Transactions\n";
			cout << "7. Display All Customers\n";
			cout << "0. Exit\n";

			cout << "========================================\n";

			while (true) {

				cout << "Enter choice: ";

				if (cin >> choice &&
					choice >= 0 &&
					choice <= 7) {

					cin.ignore(
						numeric_limits<streamsize>::max(),
						'\n'
					);

					break;
				}

				cout << "Invalid choice!\n";
				cout << "Please enter a number from 0 to 7.\n";

				cin.clear();

				cin.ignore(
					numeric_limits<streamsize>::max(),
					'\n'
				);
			}

			switch (choice) {

			case 1:
				createCustomer();
				break;

			case 2:
				depositMoney();
				break;

			case 3:
				withdrawMoney();
				break;

			case 4:
				transferMoney();
				break;

			case 5:
				viewAccount();
				break;

			case 6:
				viewTransactions();
				break;

			case 7:
				displayAllCustomers();
				break;

			case 0:
				saveData();

				cout << "\nData saved successfully.\n";
				cout << "Thank you for using the Banking System!\n";

				break;
			}

			if (choice != 0) {

				cout << "\n";
				system("pause");
			}

		} while (choice != 0);
	}
};

int main() {

	BankingSystem bank;

	bank.menu();

	return 0;
}