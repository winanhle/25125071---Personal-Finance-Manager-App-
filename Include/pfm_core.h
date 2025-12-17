#pragma once
#include "pfm_state.h"

// Forward declarations
struct AppState;
struct IncomeData;
struct ExpenseData;

// Transaction management
void addIncome(AppState& st, const IncomeData& t);
void addExpense(AppState& st, const ExpenseData& t);

// Recurring transactions
void applyRecurring(AppState& st);

// Statistics
void statsTimeRangeTotals(const AppState& st, int d1, int m1, int y1, int d2, int m2, int y2);
void statsTimeRangeByWallet(const AppState& st, int d1, int m1, int y1, int d2, int m2, int y2);
void statsYearOverview(const AppState& st, int yFrom, int yTo);
void statsIncomeBreakdownBySource(const AppState& st, int yFrom, int yTo);
void statsExpenseBreakdownByCategory(const AppState& st, int yFrom, int yTo);
