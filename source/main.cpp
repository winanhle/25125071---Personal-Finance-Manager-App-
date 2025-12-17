#include <iostream>
#include "pfm_ui.h"
#include "pfm_core.h"
#include "pfm_persist.h"
#include "pfm_utils.h"

using namespace std;

int main() {
    AppState st;

    loadState(st, "pfm.bin");   
    applyRecurring(st);         

    while (true) {
        showDashboard(st);
        int choice; 
        cin >> choice;
        flushLine();

        if (choice == 1) uiAddIncome(st);
        else if (choice == 2) uiAddExpense(st);
        else if (choice == 3) uiMasterData(st);
        else if (choice == 4) uiRecurring(st);
        else if (choice == 5) uiStatistics(st);
        else if (choice == 6) { 
            saveState(st, "pfm.bin"); 
            cout << "Data saved successfully.\n"; 
        }
        else if (choice == 0) { 
            saveState(st, "pfm.bin"); 
            cout << "Data saved. Goodbye!\n"; 
          break; 
        }
        else cout << "Invalid choice. Please select 0-6.\n";
    }
    return 0;
}
