#include "income.h"
#include "pfm_state.h"
#include "pfm_utils.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

IncomeDate InputIncomeDate() {
  IncomeDate date;
    
    while (true) {
        cout << "Enter date (dd mm yyyy): ";
        cin >> date.day >> date.month >> date.year;
        
  if (cin.fail()) {
            cin.clear();
        flushLine();
     cout << "Error: Invalid input. Please enter numbers only.\n";
    continue;
  }
        
        if (!isValidDate(date.day, date.month, date.year)) {
  flushLine();
        cout << "Please enter a valid date.\n";
            continue;
        }
    
     if (isFutureDate(date.day, date.month, date.year)) {
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
    
    return date;
}

IncomeSource inputIncomeSource(const AppState& st) {
    IncomeSource source;
    
    // Display available income sources
    cout << "\nAvailable Income Sources:\n";
    if (st.incomeSources.size == 0) {
        cout << "  (none available)\n";
      source.sourceID = -1;
      source.sourceName = "";
     return source;
}
    
    for (int i = 0; i < st.incomeSources.size; i++) {
        cout << "  " << (i + 1) << ") " 
           << st.incomeSources[i].name 
     << " (ID: " << st.incomeSources[i].id << ")\n";
    }
    
    int choice;
 cout << "Select option (1-" << st.incomeSources.size << "): ";
    cin >> choice;
  
    if (choice >= 1 && choice <= st.incomeSources.size) {
  int idx = choice - 1;
        source.sourceID = st.incomeSources[idx].id;
        source.sourceName = st.incomeSources[idx].name;
    } else {
        cout << "Invalid selection. Using first source as default.\n";
        source.sourceID = st.incomeSources[0].id;
        source.sourceName = st.incomeSources[0].name;
    }
    
    return source;
}

IncomeWallet InputIncomeWallet(const AppState& st) {
    IncomeWallet wallet;
    
    // Display available wallets
    cout << "\nAvailable Wallets:\n";
    if (st.wallets.size == 0) {
  cout << "  (none available)\n";
        wallet.IWalletID = "";
        wallet.IWalletName = "";
        return wallet;
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
        wallet.IWalletID = st.wallets[idx].id;
        wallet.IWalletName = st.wallets[idx].name;
    } else {
        cout << "Invalid selection. Using first wallet as default.\n";
        wallet.IWalletID = st.wallets[0].id;
   wallet.IWalletName = st.wallets[0].name;
    }

    return wallet;
}

IncomeData InputIncomeData(const AppState& st) {
    IncomeData data;
    
    data.InD = InputIncomeDate();
    
    data.InS = inputIncomeSource(st);
    
    cout << "\nEnter amount: ";
    cin >> data.IncomeAmount;
    cin.ignore();
    
    cout << "Enter description: ";
    getline(cin, data.IncomeDescription);
    
    data.InW = InputIncomeWallet(st);
    
    return data;
}