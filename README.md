
This is the final project I made for the course CS160 in APCS, HCMUS. A **C++ console personal finance application (no GUI)**.  
You **download the source code**, then **build/run/debug** it in your IDE (Visual Studio/CLion/VS Code) or via terminal.

---

## Features
- Add **Income** and **Expense** transactions
- Monthly **Recurring Transactions** (with start date + optional end date)
- Manage master data:
  - **Wallets**
  - **Income Sources**
  - **Expense Categories**
- Reports & statistics:
  - By date range: total income/expense/net
  - By wallet
  - By year(s): breakdown by source/category
- Data persistence (Binary or XML):
  - Auto-load on start
  - Auto-save on exit

> **Note:** This project is **CLI only**. All interaction is through console menus.

---

## Tech Constraints
- Language: **C++**
- Use `struct/class`
- Use manual dynamic arrays with pointers (`new/delete`)
  - **No STL containers** (`vector`, `map`, `list`, ...)
- `std::string` allowed
- File I/O with `<fstream>`

---

## How to Run (Typical Workflow)

### Option A — Run/Debug with an IDE (Recommended)
1. Open the project folder in your IDE:
   - **Visual Studio** (Windows)  
   - **CLion**  
   - **VS Code** (with C++ extension + compiler)
2. Configure compiler/toolchain if needed
3. Press **Run** / **Debug**
