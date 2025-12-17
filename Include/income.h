#pragma once
#include<iostream>
#include<string>
using namespace std;

// Forward declaration
struct AppState;

struct IncomeDate {
	int day;
	int month;
	int year;
	};

struct IncomeSource {
	int sourceID;
	string sourceName;
	};


struct IncomeWallet {
	string IWalletID;
	string IWalletName;
	};

struct IncomeData {
	int IncomeAmount;
	string IncomeDescription;
	IncomeDate InD;
	IncomeSource InS;
	IncomeWallet InW;
};

IncomeDate InputIncomeDate();
IncomeSource inputIncomeSource(const AppState& st);
IncomeWallet InputIncomeWallet(const AppState& st);
IncomeData InputIncomeData(const AppState& st);
