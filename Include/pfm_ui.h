#pragma once
#include <iostream>
#include <string>
#include "pfm_state.h"

// Forward declarations
struct AppState;
struct IncomeData;
struct ExpenseData;

// Dashboard
void showDashboard(const AppState& st);

// List functions
void listIncomeSources(const AppState& st);
void listExpenseCategories(const AppState& st);
void listWallets(const AppState& st);

// Wallet management
void uiAddWallet(AppState& st);
void uiEditWallet(AppState& st);
void uiDeleteWallet(AppState& st);

// Income source management
void uiAddIncomeSource(AppState& st);
void uiDeleteIncomeSource(AppState& st);

// Expense category management
void uiAddExpenseCategory(AppState& st);
void uiDeleteExpenseCategory(AppState& st);

// Master data menu
void uiMasterData(AppState& st);

// Transaction management
void uiAddIncome(AppState& st);
void uiAddExpense(AppState& st);

// Recurring transactions
void uiRecurring(AppState& st);

// Statistics
void uiStatistics(const AppState& st);
