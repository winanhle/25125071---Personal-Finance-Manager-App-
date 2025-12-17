#include "pfm_utils.h"
#include <iostream>
#include <limits>
#include <ctime>

using namespace std;

void flushLine() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int keyDate(int d, int m, int y) { 
    return y * 10000 + m * 100 + d; 
}

int keyIncomeDate(const IncomeDate& d) { 
    return keyDate(d.day, d.month, d.year); 
}

int keyExpenseDate(const ExpenseDate& d) { 
    return keyDate(d.day, d.month, d.year); 
}

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int getDaysInMonth(int month, int year) {
    if (month < 1 || month > 12) return 0;
    
    int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    
    if (month == 2 && isLeapYear(year)) {
      return 29;
  }
    
    return daysInMonth[month];
}

bool isValidDate(int day, int month, int year) {
    // Check year range (reasonable range for personal finance)
    if (year < 1900 || year > 2100) {
        cout << "Error: Year must be between 1900 and 2100.\n";
        return false;
    }
    
    // Check month range
    if (month < 1 || month > 12) {
        cout << "Error: Month must be between 1 and 12.\n";
return false;
    }
    
    // Check day range
    int maxDays = getDaysInMonth(month, year);
    if (day < 1 || day > maxDays) {
        cout << "Error: Day must be between 1 and " << maxDays 
    << " for month " << month << " in year " << year << ".\n";
        return false;
    }
    
    return true;
}

bool isFutureDate(int day, int month, int year) {
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    
    int currentYear = now->tm_year + 1900;
  int currentMonth = now->tm_mon + 1;
    int currentDay = now->tm_mday;
    
    int inputKey = keyDate(day, month, year);
    int currentKey = keyDate(currentDay, currentMonth, currentYear);
    
    return inputKey > currentKey;
}

void getCurrentMonthYear(int& month, int& year) {
    time_t t = time(nullptr);
    tm* lt = localtime(&t);
    month = lt->tm_mon + 1;
  year = lt->tm_year + 1900;
}

void nextMonth(int& m, int& y) {
    m++;
  if (m > 12) { 
      m = 1; 
     y++; 
    }
}

bool monthYearLE(int m1, int y1, int m2, int y2) {
    if (y1 != y2) return y1 < y2;
    return m1 <= m2;
}

int findWalletIndex(const AppState& st, const string& id) {
    for (int i = 0; i < st.wallets.size; i++)
        if (st.wallets[i].id == id) return i;
    return -1;
}

int findIncomeSourceIndex(const AppState& st, int id) {
    for (int i = 0; i < st.incomeSources.size; i++)
   if (st.incomeSources[i].id == id) return i;
    return -1;
}

int findExpenseCategoryIndex(const AppState& st, int id) {
    for (int i = 0; i < st.expenseCategories.size; i++)
     if (st.expenseCategories[i].id == id) return i;
    return -1;
}

bool walletUsed(const AppState& st, const string& wid) {
    for (int i = 0; i < st.incomes.size; i++)
   if (st.incomes[i].InW.IWalletID == wid) return true;
    
    for (int i = 0; i < st.expenses.size; i++)
   if (st.expenses[i].EW.EWalletID == wid) return true;
    
    for (int i = 0; i < st.recurring.size; i++) {
   if (st.recurring[i].kind == REC_INCOME && st.recurring[i].inProto.InW.IWalletID == wid) 
    return true;
     if (st.recurring[i].kind == REC_EXPENSE && st.recurring[i].exProto.EW.EWalletID == wid) 
            return true;
    }
    
    return false;
}

bool incomeSourceUsed(const AppState& st, int sid) {
    for (int i = 0; i < st.incomes.size; i++)
     if (st.incomes[i].InS.sourceID == sid) return true;
    
    for (int i = 0; i < st.recurring.size; i++)
     if (st.recurring[i].kind == REC_INCOME && st.recurring[i].inProto.InS.sourceID == sid) 
      return true;

    return false;
}

bool expenseCategoryUsed(const AppState& st, int cid) {
    for (int i = 0; i < st.expenses.size; i++)
    if (st.expenses[i].ES.CategoryID == cid) return true;
    
    for (int i = 0; i < st.recurring.size; i++)
        if (st.recurring[i].kind == REC_EXPENSE && st.recurring[i].exProto.ES.CategoryID == cid) 
         return true;
    
  return false;
}

long long totalMoney(const AppState& st) {
    long long sum = 0;
    for (int i = 0; i < st.wallets.size; i++) 
    sum += st.wallets[i].balance;
    return sum;
}
