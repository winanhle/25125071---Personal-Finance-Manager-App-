#pragma once
#include<iostream>
#include<string>
using namespace std;

// Forward declaration
struct AppState;

struct ExpenseDate {
	int day;
	int month;
	int year;
};

struct ExpenseSource {
	int CategoryID;
	string CatergoryName;
};
	

struct ExpenseWallet {
	string EWalletID;
	string EWalletName;
};

struct ExpenseData {
	ExpenseDate ED;
	int ExpenseAmount;
	string Description;
	ExpenseSource ES;
	ExpenseWallet EW;
};

ExpenseDate InputExpenseDate();
ExpenseSource InputExpenseSource(const AppState& st);
ExpenseWallet InputExpenseWallet(const AppState& st);
ExpenseData InputExpenseData(const AppState& st);
