#pragma once
#include <string>
#include "pfm_state.h"

// Forward declarations
struct AppState;
struct IncomeDate;
struct ExpenseDate;

// Input utilities
void flushLine();

// Date conversion
int keyDate(int d, int m, int y);
int keyIncomeDate(const IncomeDate& d);
int keyExpenseDate(const ExpenseDate& d);

// Date validation
bool isLeapYear(int year);
int getDaysInMonth(int month, int year);
bool isValidDate(int day, int month, int year);
bool isFutureDate(int day, int month, int year);

// Date utilities
void getCurrentMonthYear(int& month, int& year);
void nextMonth(int& m, int& y);
bool monthYearLE(int m1, int y1, int m2, int y2);

// Search utilities
int findWalletIndex(const AppState& st, const std::string& id);
int findIncomeSourceIndex(const AppState& st, int id);
int findExpenseCategoryIndex(const AppState& st, int id);

// Usage check utilities
bool walletUsed(const AppState& st, const std::string& wid);
bool incomeSourceUsed(const AppState& st, int sid);
bool expenseCategoryUsed(const AppState& st, int cid);

// Calculation utilities
long long totalMoney(const AppState& st);
