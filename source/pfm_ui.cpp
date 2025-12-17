#include "pfm_ui.h"
#include "pfm_core.h"
#include "pfm_persist.h"
#include "pfm_utils.h"
#include "income.h"
#include "expense.h"
#include <iostream>
#include <string>

using namespace std;

void showDashboard(const AppState& st) {
    cout << "\n==============================\n";
    cout << " Personal Finance Manager (CLI)\n";
    cout << " Total money: " << totalMoney(st) << "\n";
    cout << " Wallets:\n";
    if (st.wallets.size == 0) cout << "  (none)\n";
    for (int i = 0; i < st.wallets.size; i++) {
        cout << "  - " << st.wallets[i].id << " | " << st.wallets[i].name
            << " | balance: " << st.wallets[i].balance << "\n";
    }
    cout << "==============================\n";
    cout << "1) Add Income\n";
    cout << "2) Add Expense\n";
    cout << "3) Master Data\n";
    cout << "4) Recurring\n";
 cout << "5) Statistics\n";
    cout << "6) Save\n";
    cout << "0) Save & Exit\n";
    cout << "Choose: ";
}

void listIncomeSources(const AppState& st) {
    cout << "\nIncome Sources:\n";
    if (st.incomeSources.size == 0) cout << " (none)\n";
    for (int i = 0; i < st.incomeSources.size; i++)
        cout << " - " << st.incomeSources[i].id << ": " << st.incomeSources[i].name << "\n";
}

void listExpenseCategories(const AppState& st) {
    cout << "\nExpense Categories:\n";
    if (st.expenseCategories.size == 0) cout << " (none)\n";
    for (int i = 0; i < st.expenseCategories.size; i++)
  cout << " - " << st.expenseCategories[i].id << ": " << st.expenseCategories[i].name << "\n";
}

void listWallets(const AppState& st) {
    cout << "\nWallets:\n";
    if (st.wallets.size == 0) cout << " (none)\n";
    for (int i = 0; i < st.wallets.size; i++) {
  cout << " - " << st.wallets[i].id << ": " << st.wallets[i].name
       << " (Balance: $" << st.wallets[i].balance << ")\n";
    }
}

void uiAddWallet(AppState& st) {
    WalletMaster w{};
    cout << "Wallet ID (no spaces): ";
    cin >> w.id;
    if (findWalletIndex(st, w.id) >= 0) { 
   cout << "ID exists.\n"; 
        flushLine();
        return; 
    }
    flushLine();
    cout << "Wallet name: ";
    getline(cin, w.name);
    cout << "Initial balance: ";
    cin >> w.balance;
    flushLine();
    st.wallets.push_back(w);
    cout << "Added wallet.\n";
}

void uiEditWallet(AppState& st) {
    string id;
    cout << "Wallet ID to edit: ";
    cin >> id;
    int wi = findWalletIndex(st, id);
    if (wi < 0) { 
        cout << "Not found.\n"; 
        flushLine();
        return; 
    }
    flushLine();
 cout << "New name: ";
    getline(cin, st.wallets[wi].name);
    cout << "Updated.\n";
}

void uiDeleteWallet(AppState& st) {
    string id;
    cout << "Wallet ID to delete: ";
    cin >> id;
    int wi = findWalletIndex(st, id);
    if (wi < 0) { 
      cout << "Not found.\n"; 
        flushLine();
        return; 
    }
    if (walletUsed(st, id)) { 
        cout << "Cannot delete: used by tx/recurring.\n"; 
  flushLine();
     return; 
    }
    st.wallets.removeAt(wi);
    cout << "Deleted.\n";
    flushLine();
}

void uiAddIncomeSource(AppState& st) {
    IncomeSourceMaster s{};
    cout << "Income Source ID (int): ";
    cin >> s.id;
    if (findIncomeSourceIndex(st, s.id) >= 0) { 
        cout << "ID exists.\n"; 
        flushLine();
        return; 
    }
    flushLine();
    cout << "Source name: ";
    getline(cin, s.name);
  st.incomeSources.push_back(s);
    cout << "Added.\n";
}

void uiDeleteIncomeSource(AppState& st) {
 int id; 
    cout << "Income Source ID to delete: "; 
    cin >> id;
    int si = findIncomeSourceIndex(st, id);
    if (si < 0) { 
      cout << "Not found.\n"; 
        flushLine();
      return; 
    }
    if (incomeSourceUsed(st, id)) { 
   cout << "Cannot delete: used by tx/recurring.\n"; 
        flushLine();
        return; 
    }
    st.incomeSources.removeAt(si);
    cout << "Deleted.\n";
    flushLine();
}

void uiAddExpenseCategory(AppState& st) {
    ExpenseCategoryMaster c{};
    cout << "Expense Category ID (int): ";
    cin >> c.id;
    if (findExpenseCategoryIndex(st, c.id) >= 0) { 
        cout << "ID exists.\n"; 
        flushLine();
        return; 
    }
    flushLine();
    cout << "Category name: ";
    getline(cin, c.name);
    st.expenseCategories.push_back(c);
    cout << "Added.\n";
}

void uiDeleteExpenseCategory(AppState& st) {
    int id; 
    cout << "Expense Category ID to delete: "; 
    cin >> id;
    int ci = findExpenseCategoryIndex(st, id);
    if (ci < 0) { 
        cout << "Not found.\n"; 
        flushLine();
 return; 
    }
    if (expenseCategoryUsed(st, id)) { 
     cout << "Cannot delete: used by tx/recurring.\n"; 
        flushLine();
      return; 
    }
    st.expenseCategories.removeAt(ci);
    cout << "Deleted.\n";
    flushLine();
}

void uiMasterData(AppState& st) {
    while (true) {
     cout << "\n========== MASTER DATA ==========\n";
   cout << "--- Wallets ---\n";
        cout << "1) Add Wallet\n";
    cout << "2) Delete Wallet\n";
        cout << "3) List Wallets\n";
 cout << "--- Income Sources ---\n";
        cout << "4) Add Income Source\n";
cout << "5) Delete Income Source\n";
        cout << "6) List Income Sources\n";
        cout << "--- Expense Categories ---\n";
        cout << "7) Add Expense Category\n";
    cout << "8) Delete Expense Category\n";
    cout << "9) List Expense Categories\n";
        cout << "=================================\n";
        cout << "0) Back to Main Menu\n";
      cout << "Choose: ";
 
        int c; 
        cin >> c;
        flushLine();
 
        if (c == 0) return;
 
        // Wallets: Add ? Delete ? List
        if (c == 1) uiAddWallet(st);
        else if (c == 2) uiDeleteWallet(st);
        else if (c == 3) listWallets(st);
   
     // Income Sources: Add ? Delete ? List
        else if (c == 4) uiAddIncomeSource(st);
        else if (c == 5) uiDeleteIncomeSource(st);
        else if (c == 6) listIncomeSources(st);
   
        // Expense Categories: Add ? Delete ? List
else if (c == 7) uiAddExpenseCategory(st);
   else if (c == 8) uiDeleteExpenseCategory(st);
        else if (c == 9) listExpenseCategories(st);
  
        else cout << "Invalid choice.\n";
    }
}

void uiAddIncome(AppState& st) {
    // Check for missing wallets
    if (st.wallets.size == 0) { 
        cout << "\n*** No wallets found! ***\n";
      cout << "You need to create at least one wallet before adding income.\n";
        cout << "Would you like to create a wallet now? (y/n): ";
        
        char response;
        cin >> response;
        flushLine();
        
        if (response == 'y' || response == 'Y') {
        uiAddWallet(st);
     
       // Check if wallet was successfully created
   if (st.wallets.size == 0) {
     cout << "Wallet creation cancelled. Returning to main menu.\n";
            return;
            }
        } else {
 cout << "Operation cancelled. Returning to main menu.\n";
     return;
        }
    }
    
    // Check for missing income sources
    if (st.incomeSources.size == 0) { 
        cout << "\n*** No income sources found! ***\n";
        cout << "You need to create at least one income source before adding income.\n";
        cout << "Would you like to create an income source now? (y/n): ";
        
        char response;
        cin >> response;
        flushLine();
   
        if (response == 'y' || response == 'Y') {
            uiAddIncomeSource(st);
            
      // Check if income source was successfully created
            if (st.incomeSources.size == 0) {
       cout << "Income source creation cancelled. Returning to main menu.\n";
     return;
            }
   } else {
            cout << "Operation cancelled. Returning to main menu.\n";
            return;
        }
    }

    // Proceed with adding income
    cout << "\n=== Adding Income Transaction ===\n";
    IncomeData t = InputIncomeData(st);

    if (findIncomeSourceIndex(st, t.InS.sourceID) < 0) { 
        cout << "Error: Invalid source ID.\n"; 
        return; 
    }
    if (findWalletIndex(st, t.InW.IWalletID) < 0) { 
        cout << "Error: Invalid wallet ID.\n"; 
        return; 
    }

    addIncome(st, t);
    cout << "\n? Income added successfully!\n";
}

void uiAddExpense(AppState& st) {
    // Check for missing wallets
    if (st.wallets.size == 0) { 
        cout << "\n*** No wallets found! ***\n";
      cout << "You need to create at least one wallet before adding expense.\n";
      cout << "Would you like to create a wallet now? (y/n): ";
        
        char response;
        cin >> response;
      flushLine();
        
if (response == 'y' || response == 'Y') {
            uiAddWallet(st);
         
     // Check if wallet was successfully created
     if (st.wallets.size == 0) {
          cout << "Wallet creation cancelled. Returning to main menu.\n";
      return;
 }
        } else {
cout << "Operation cancelled. Returning to main menu.\n";
            return;
      }
    }
    
 // Check for missing expense categories
    if (st.expenseCategories.size == 0) { 
        cout << "\n*** No expense categories found! ***\n";
        cout << "You need to create at least one expense category before adding expense.\n";
        cout << "Would you like to create an expense category now? (y/n): ";
      
        char response;
        cin >> response;
        flushLine();
        
        if (response == 'y' || response == 'Y') {
         uiAddExpenseCategory(st);
     
        // Check if expense category was successfully created
     if (st.expenseCategories.size == 0) {
       cout << "Expense category creation cancelled. Returning to main menu.\n";
      return;
            }
        } else {
   cout << "Operation cancelled. Returning to main menu.\n";
            return;
        }
    }

    // Proceed with adding expense
    cout << "\n=== Adding Expense Transaction ===\n";
    ExpenseData t = InputExpenseData(st);

    if (findExpenseCategoryIndex(st, t.ES.CategoryID) < 0) { 
        cout << "Error: Invalid category ID.\n"; 
return; 
 }
    if (findWalletIndex(st, t.EW.EWalletID) < 0) { 
        cout << "Error: Invalid wallet ID.\n"; 
        return; 
    }

    addExpense(st, t);
    cout << "\n? Expense added successfully!\n";
}

void uiRecurring(AppState& st) {
    while (true) {
  cout << "\n--- Recurring ---\n";
      cout << "1) Add Recurring Income\n";
        cout << "2) Add Recurring Expense\n";
        cout << "3) List Recurring\n";
    cout << "0) Back\nChoose: ";
  int c; 
        cin >> c;
      flushLine();
  
        if (c == 0) return;

if (c == 3) {
  cout << "\nRecurring list:\n";
       if (st.recurring.size == 0) cout << " (none)\n";
            for (int i = 0; i < st.recurring.size; i++) {
       auto& r = st.recurring[i];
             cout << "- #" << i << " kind=" << (r.kind == REC_INCOME ? "IN" : "EX")
      << " start " << r.start.d << "/" << r.start.m << "/" << r.start.y
   << " last " << r.lastMonth << "/" << r.lastYear << "\n";
   }
     continue;
        }

        // Check prerequisites for recurring income
 if (c == 1) {
   bool needsWallet = (st.wallets.size == 0);
        bool needsSource = (st.incomeSources.size == 0);
          
         if (needsWallet || needsSource) {
           cout << "\n*** Missing required master data! ***\n";
  
     if (needsWallet) {
     cout << "- No wallets found\n";
                }
     if (needsSource) {
        cout << "- No income sources found\n";
  }
          
           cout << "\nWould you like to create the missing data now? (y/n): ";
                char response;
         cin >> response;
        flushLine();
        
          if (response != 'y' && response != 'Y') {
        cout << "Operation cancelled.\n";
          continue;
          }
    
      // Create wallet if needed
         if (needsWallet) {
     cout << "\n--- Creating Wallet ---\n";
                    uiAddWallet(st);
      if (st.wallets.size == 0) {
    cout << "Wallet creation cancelled.\n";
   continue;
        }
        }
  
                // Create income source if needed
 if (needsSource) {
  cout << "\n--- Creating Income Source ---\n";
          uiAddIncomeSource(st);
     if (st.incomeSources.size == 0) {
cout << "Income source creation cancelled.\n";
              continue;
          }
   }
           
    cout << "\n? Master data created. Continuing with recurring income...\n";
  }
  }
        
        // Check prerequisites for recurring expense
     if (c == 2) {
       bool needsWallet = (st.wallets.size == 0);
        bool needsCategory = (st.expenseCategories.size == 0);
       
    if (needsWallet || needsCategory) {
       cout << "\n*** Missing required master data! ***\n";
  
    if (needsWallet) {
    cout << "- No wallets found\n";
         }
    if (needsCategory) {
     cout << "- No expense categories found\n";
    }
     
       cout << "\nWould you like to create the missing data now? (y/n): ";
     char response;
  cin >> response;
    flushLine();
      
     if (response != 'y' && response != 'Y') {
               cout << "Operation cancelled.\n";
     continue;
            }
   
        // Create wallet if needed
        if (needsWallet) {
cout << "\n--- Creating Wallet ---\n";
 uiAddWallet(st);
        if (st.wallets.size == 0) {
       cout << "Wallet creation cancelled.\n";
   continue;
         }
           }
    
           // Create expense category if needed
     if (needsCategory) {
          cout << "\n--- Creating Expense Category ---\n";
  uiAddExpenseCategory(st);
 if (st.expenseCategories.size == 0) {
        cout << "Expense category creation cancelled.\n";
            continue;
   }
       }
    
    cout << "\n? Master data created. Continuing with recurring expense...\n";
   }
        }

        RecurringItem r{};
      r.lastMonth = 0; 
   r.lastYear = 0;

        while (true) {
          cout << "Start date (dd mm yyyy): ";
            cin >> r.start.d >> r.start.m >> r.start.y;
  
       if (cin.fail()) {
    cin.clear();
         flushLine();
            cout << "Error: Invalid input. Please enter numbers only.\n";
   continue;
            }
   
   if (!isValidDate(r.start.d, r.start.m, r.start.y)) {
          flushLine();
                cout << "Please enter a valid start date.\n";
         continue;
            }
  
      break;
        }

        cout << "Has end date? (1 yes / 0 no): ";
        int he; 
     cin >> he;
        r.hasEnd = (he == 1);
        
        if (r.hasEnd) {
 while (true) {
    cout << "End date (dd mm yyyy): ";
          cin >> r.end.d >> r.end.m >> r.end.y;
       
           if (cin.fail()) {
           cin.clear();
            flushLine();
        cout << "Error: Invalid input. Please enter numbers only.\n";
                continue;
           }
    
     if (!isValidDate(r.end.d, r.end.m, r.end.y)) {
       flushLine();
      cout << "Please enter a valid end date.\n";
      continue;
     }

  // Check if end date is after start date
int startKey = keyDate(r.start.d, r.start.m, r.start.y);
    int endKey = keyDate(r.end.d, r.end.m, r.end.y);
         
         if (endKey <= startKey) {
        flushLine();
           cout << "Error: End date must be after start date.\n";
        continue;
      }
    
      break;
  }
    }
        else {
     r.end = { 0, 0, 0 };
        }
        
   flushLine();

 if (c == 1) {
     r.kind = REC_INCOME;
   cout << "\nFill recurring income prototype:\n";
            r.inProto = InputIncomeData(st);
            if (findIncomeSourceIndex(st, r.inProto.InS.sourceID) < 0) { 
    cout << "Invalid source.\n"; 
      continue; 
            }
       if (findWalletIndex(st, r.inProto.InW.IWalletID) < 0) { 
cout << "Invalid wallet.\n"; 
  continue; 
      }
            st.recurring.push_back(r);
            cout << "\n? Recurring income added successfully!\n";
        }
 else if (c == 2) {
 r.kind = REC_EXPENSE;
        cout << "\nFill recurring expense prototype:\n";
      r.exProto = InputExpenseData(st);
   if (findExpenseCategoryIndex(st, r.exProto.ES.CategoryID) < 0) { 
          cout << "Invalid category.\n"; 
   continue; 
            }
 if (findWalletIndex(st, r.exProto.EW.EWalletID) < 0) { 
        cout << "Invalid wallet.\n"; 
          continue; 
     }
    st.recurring.push_back(r);
            cout << "\n? Recurring expense added successfully!\n";
      }
    }
}

void uiStatistics(const AppState& st) {
    while (true) {
        cout << "\n--- Statistics ---\n";
      cout << "1) Time range totals (Income/Expense/Net)\n";
        cout << "2) Time range totals by wallet\n";
        cout << "3) Year overview (y1..y2)\n";
      cout << "4) Income breakdown by source (y1..y2)\n";
        cout << "5) Expense breakdown by category (y1..y2)\n";
        cout << "0) Back\nChoose: ";

   int c; 
        cin >> c;
        flushLine();
      
        if (c == 0) return;

        if (c == 1 || c == 2) {
   int d1, m1, y1, d2, m2, y2;
            
         while (true) {
          cout << "From (dd mm yyyy): "; 
         cin >> d1 >> m1 >> y1;
        
    if (cin.fail()) {
       cin.clear();
    flushLine();
 cout << "Error: Invalid input. Please enter numbers only.\n";
         continue;
                }
        
  if (!isValidDate(d1, m1, y1)) {
        flushLine();
 cout << "Please enter a valid 'from' date.\n";
continue;
 }
         
    break;
      }
        
        while (true) {
       cout << "To   (dd mm yyyy): "; 
       cin >> d2 >> m2 >> y2;
     
                if (cin.fail()) {
         cin.clear();
  flushLine();
        cout << "Error: Invalid input. Please enter numbers only.\n";
          continue;
   }
  
                if (!isValidDate(d2, m2, y2)) {
    flushLine();
            cout << "Please enter a valid 'to' date.\n";
     continue;
        }

                // Check if 'to' date is after or equal to 'from' date
       int fromKey = keyDate(d1, m1, y1);
    int toKey = keyDate(d2, m2, y2);
 
  if (toKey < fromKey) {
         flushLine();
         cout << "Error: 'To' date must be on or after 'from' date.\n";
        continue;
      }

         break;
     }
       
            flushLine();

            if (c == 1) statsTimeRangeTotals(st, d1, m1, y1, d2, m2, y2);
            else statsTimeRangeByWallet(st, d1, m1, y1, d2, m2, y2);
        }
 else if (c == 3 || c == 4 || c == 5) {
       int yFrom, yTo;
     
    while (true) {
     cout << "Year from: "; 
   cin >> yFrom;
       
    if (cin.fail()) {
         cin.clear();
    flushLine();
      cout << "Error: Invalid input. Please enter a number.\n";
           continue;
        }
        
  if (yFrom < 1900 || yFrom > 2100) {
            flushLine();
              cout << "Error: Year must be between 1900 and 2100.\n";
   continue;
}
             
        break;
        }
      
       while (true) {
         cout << "Year to  : "; 
         cin >> yTo;
        
         if (cin.fail()) {
   cin.clear();
   flushLine();
           cout << "Error: Invalid input. Please enter a number.\n";
       continue;
    }
      
       if (yTo < 1900 || yTo > 2100) {
             flushLine();
               cout << "Error: Year must be between 1900 and 2100.\n";
  continue;
    }
   
   if (yTo < yFrom) {
     flushLine();
           cout << "Error: 'Year to' must be greater than or equal to 'year from'.\n";
   continue;
   }
     
          break;
         }
 
            flushLine();

if (c == 3) statsYearOverview(st, yFrom, yTo);
            else if (c == 4) statsIncomeBreakdownBySource(st, yFrom, yTo);
            else statsExpenseBreakdownByCategory(st, yFrom, yTo);
        }
        else {
     cout << "Invalid.\n";
        }
    }
}
