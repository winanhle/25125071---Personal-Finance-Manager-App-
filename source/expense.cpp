#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include "expense.h"
#include "pfm_state.h"
#include "pfm_utils.h"
using namespace std;

ExpenseDate InputExpenseDate() {
	ExpenseDate d{};
	
	while (true) {
		cout << "Expense Day: ";
		cin >> d.day;
	
		if (cin.fail()) {
			cin.clear();
			flushLine();
			cout << "Error: Invalid input. Please enter a number.\n";
			continue;
		}
		
		cout << "Expense Month: ";
		cin >> d.month;
		
		if (cin.fail()) {
			cin.clear();
			flushLine();
			cout << "Error: Invalid input. Please enter a number.\n";
			continue;
		}
		
		cout << "Expense Year: ";
		cin >> d.year;
		
		if (cin.fail()) {
			cin.clear();
			flushLine();
			cout << "Error: Invalid input. Please enter a number.\n";
			continue;
		}
		
		if (!isValidDate(d.day, d.month, d.year)) {
			cout << "Please enter a valid date.\n";
			continue;
		}
		
		if (isFutureDate(d.day, d.month, d.year)) {
			cout << "Warning: This is a future date. Continue? (y/n): ";
			flushLine();
			char confirm;
			cin >> confirm;
			if (confirm != 'y' && confirm != 'Y') {
				flushLine();
				continue;
			}
		}
		
		break;
	}
	
	return d;
}

ExpenseSource InputExpenseSource(const AppState& st) {
	ExpenseSource s{};
	
	// Display available expense categories
	cout << "\nAvailable Expense Categories:\n";
	if (st.expenseCategories.size == 0) {
		cout << "  (none available)\n";
		s.CategoryID = -1;
		s.CatergoryName = "";
		return s;
	}
	
	for (int i = 0; i < st.expenseCategories.size; i++) {
		cout << "  " << (i + 1) << ") " 
		     << st.expenseCategories[i].name 
		     << " (ID: " << st.expenseCategories[i].id << ")\n";
	}
	
	int choice;
	cout << "Select option (1-" << st.expenseCategories.size << "): ";
	cin >> choice;
	
	// Validate and retrieve from master data
	if (choice >= 1 && choice <= st.expenseCategories.size) {
		int idx = choice - 1;
		s.CategoryID = st.expenseCategories[idx].id;
		s.CatergoryName = st.expenseCategories[idx].name;
	} else {
		cout << "Invalid selection. Using first category as default.\n";
		s.CategoryID = st.expenseCategories[0].id;
		s.CatergoryName = st.expenseCategories[0].name;
	}
	
	return s;
}

ExpenseWallet InputExpenseWallet(const AppState& st) {
	ExpenseWallet w{};
	
	// Display available wallets
	cout << "\nAvailable Wallets:\n";
	if (st.wallets.size == 0) {
		cout << "  (none available)\n";
		w.EWalletID = "";
		w.EWalletName = "";
		return w;
	}
	
	for (int i = 0; i < st.wallets.size; i++) {
		cout << "  " << (i + 1) << ") " 
		 << st.wallets[i].name 
		     << " (ID: " << st.wallets[i].id 
		     << ", Balance: $" << fixed << setprecision(2) 
		     << st.wallets[i].balance << ")\n";
	}
	
	int choice;
	cout << "Select option (1-" << st.wallets.size << "): ";
	cin >> choice;
	
	// Validate and retrieve from master data
	if (choice >= 1 && choice <= st.wallets.size) {
		int idx = choice - 1;
		w.EWalletID = st.wallets[idx].id;
		w.EWalletName = st.wallets[idx].name;
	} else {
		cout << "Invalid selection. Using first wallet as default.\n";
		w.EWalletID = st.wallets[0].id;
		w.EWalletName = st.wallets[0].name;
	}
	
	return w;
}

ExpenseData InputExpenseData(const AppState& st) {
	ExpenseData e{};

	cout << "Expense amount: ";
	cin >> e.ExpenseAmount;

	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	cout << "Expense Description: ";
	getline(cin, e.Description);

	cout << "Expense Date: \n";
	e.ED = InputExpenseDate();

	e.ES = InputExpenseSource(st);

	e.EW = InputExpenseWallet(st);

	return e;
}