#pragma once
#include <string>
#include "dynamic_array.h"
#include "income.h"
#include "expense.h"

struct WalletMaster {
    std::string id;
    std::string name;
    long long balance;
};

struct IncomeSourceMaster {
    int id;
    std::string name;
};

struct ExpenseCategoryMaster {
    int id;
    std::string name;
};

struct SimpleDate {
    int d, m, y;
};

enum RecKind { REC_INCOME = 1, REC_EXPENSE = 2 };

struct RecurringItem {
    int kind; // REC_INCOME / REC_EXPENSE
    SimpleDate start;
    bool hasEnd;
    SimpleDate end;

    int lastMonth; // 0 => never applied
    int lastYear;

    IncomeData inProto;   // dùng nếu kind=income (date sẽ bị ignore khi apply)
    ExpenseData exProto;  // dùng nếu kind=expense
};

struct AppState {
    DynamicArray<WalletMaster> wallets;
    DynamicArray<IncomeSourceMaster> incomeSources;
    DynamicArray<ExpenseCategoryMaster> expenseCategories;

    DynamicArray<IncomeData> incomes;
    DynamicArray<ExpenseData> expenses;

    DynamicArray<RecurringItem> recurring;
};
