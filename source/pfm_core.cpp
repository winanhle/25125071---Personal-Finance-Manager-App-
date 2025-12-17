#include "pfm_core.h"
#include "pfm_utils.h"
#include <iostream>

using namespace std;

void addIncome(AppState& st, const IncomeData& t) {
    st.incomes.push_back(t);
    int wi = findWalletIndex(st, t.InW.IWalletID);
    if (wi >= 0) st.wallets[wi].balance += (long long)t.IncomeAmount;
}

void addExpense(AppState& st, const ExpenseData& t) {
    st.expenses.push_back(t);
    int wi = findWalletIndex(st, t.EW.EWalletID);
if (wi >= 0) st.wallets[wi].balance -= (long long)t.ExpenseAmount;
}

void applyRecurring(AppState& st) {
    int curM, curY;
getCurrentMonthYear(curM, curY);

    for (int i = 0; i < st.recurring.size; i++) {
        RecurringItem& r = st.recurring[i];

        int m = r.start.m, y = r.start.y;
        if (r.lastMonth != 0) { 
      m = r.lastMonth; 
            y = r.lastYear; 
     nextMonth(m, y); 
        }

   int endM = r.end.m, endY = r.end.y;

        while (monthYearLE(m, y, curM, curY)) {
            if (r.hasEnd && !monthYearLE(m, y, endM, endY)) break;

            int day = r.start.d;
      if (day < 1) day = 1;
          if (day > 28) day = 28;

    if (r.kind == REC_INCOME) {
  IncomeData t = r.inProto;
            t.InD = { day, m, y };
      addIncome(st, t);
            }
            else {
      ExpenseData t = r.exProto;
     t.ED = { day, m, y };
            addExpense(st, t);
       }

 r.lastMonth = m;
          r.lastYear = y;
nextMonth(m, y);
        }
    }
}

void statsTimeRangeTotals(const AppState& st, int d1, int m1, int y1, int d2, int m2, int y2) {
    int ka = keyDate(d1, m1, y1), kb = keyDate(d2, m2, y2);
    if (ka > kb) { 
        int tmp = ka; 
        ka = kb; 
        kb = tmp; 
    }

    long long sumIn = 0, sumEx = 0;

    for (int i = 0; i < st.incomes.size; i++) {
        int k = keyIncomeDate(st.incomes[i].InD);
        if (k >= ka && k <= kb) sumIn += st.incomes[i].IncomeAmount;
    }
    
    for (int i = 0; i < st.expenses.size; i++) {
   int k = keyExpenseDate(st.expenses[i].ED);
        if (k >= ka && k <= kb) sumEx += st.expenses[i].ExpenseAmount;
    }

    cout << "\n[Time Range Totals]\n";
    cout << "Income : " << sumIn << "\n";
    cout << "Expense: " << sumEx << "\n";
    cout << "Net  : " << (sumIn - sumEx) << "\n";
}

void statsTimeRangeByWallet(const AppState& st, int d1, int m1, int y1, int d2, int m2, int y2) {
    int ka = keyDate(d1, m1, y1), kb = keyDate(d2, m2, y2);
    if (ka > kb) { 
        int tmp = ka; 
        ka = kb; 
        kb = tmp; 
    }

    cout << "\n[Time Range By Wallet]\n";
    if (st.wallets.size == 0) { 
        cout << "(no wallets)\n"; 
        return; 
    }

    for (int w = 0; w < st.wallets.size; w++) {
        const string& wid = st.wallets[w].id;
        long long sumIn = 0, sumEx = 0;

        for (int i = 0; i < st.incomes.size; i++) {
   int k = keyIncomeDate(st.incomes[i].InD);
            if (k >= ka && k <= kb && st.incomes[i].InW.IWalletID == wid)
         sumIn += st.incomes[i].IncomeAmount;
        }

        for (int i = 0; i < st.expenses.size; i++) {
            int k = keyExpenseDate(st.expenses[i].ED);
  if (k >= ka && k <= kb && st.expenses[i].EW.EWalletID == wid)
              sumEx += st.expenses[i].ExpenseAmount;
        }

cout << "- " << wid << " (" << st.wallets[w].name << "): "
<< "Income " << sumIn << ", Expense " << sumEx
            << ", Net " << (sumIn - sumEx) << "\n";
    }
}

void statsYearOverview(const AppState& st, int yFrom, int yTo) {
    if (yFrom > yTo) { 
     int t = yFrom; 
        yFrom = yTo; 
        yTo = t; 
    }

    cout << "\n[Year Overview]\n";
    for (int y = yFrom; y <= yTo; y++) {
        long long sumIn = 0, sumEx = 0;

        for (int i = 0; i < st.incomes.size; i++)
    if (st.incomes[i].InD.year == y) sumIn += st.incomes[i].IncomeAmount;

        for (int i = 0; i < st.expenses.size; i++)
   if (st.expenses[i].ED.year == y) sumEx += st.expenses[i].ExpenseAmount;

        cout << "- " << y << ": Income " << sumIn
            << ", Expense " << sumEx
<< ", Net " << (sumIn - sumEx) << "\n";
    }
}

void statsIncomeBreakdownBySource(const AppState& st, int yFrom, int yTo) {
    if (yFrom > yTo) { 
        int t = yFrom; 
     yFrom = yTo; 
        yTo = t; 
    }

    cout << "\n[Income Breakdown By Source]\n";
    if (st.incomeSources.size == 0) { 
        cout << "(no income sources)\n"; 
        return; 
    }

    for (int s = 0; s < st.incomeSources.size; s++) {
        int sid = st.incomeSources[s].id;
        long long sum = 0;

        for (int i = 0; i < st.incomes.size; i++) {
 int y = st.incomes[i].InD.year;
   if (y >= yFrom && y <= yTo && st.incomes[i].InS.sourceID == sid)
   sum += st.incomes[i].IncomeAmount;
 }

cout << "- (" << sid << ") " << st.incomeSources[s].name
            << ": " << sum << "\n";
    }
}

void statsExpenseBreakdownByCategory(const AppState& st, int yFrom, int yTo) {
    if (yFrom > yTo) { 
        int t = yFrom; 
      yFrom = yTo; 
 yTo = t; 
    }

    cout << "\n[Expense Breakdown By Category]\n";
    if (st.expenseCategories.size == 0) { 
      cout << "(no expense categories)\n"; 
        return; 
    }

    for (int c = 0; c < st.expenseCategories.size; c++) {
        int cid = st.expenseCategories[c].id;
        long long sum = 0;

        for (int i = 0; i < st.expenses.size; i++) {
       int y = st.expenses[i].ED.year;
            if (y >= yFrom && y <= yTo && st.expenses[i].ES.CategoryID == cid)
    sum += st.expenses[i].ExpenseAmount;
 }

        cout << "- (" << cid << ") " << st.expenseCategories[c].name
    << ": " << sum << "\n";
    }
}
