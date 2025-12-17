#pragma once
#include <fstream>
#include <string>
#include "pfm_state.h"

inline void writeString(std::ofstream& out, const std::string& s) {
    int len = (int)s.size();
    out.write((char*)&len, sizeof(len));
    if (len > 0) out.write(s.c_str(), len);
}

inline std::string readString(std::ifstream& in) {
    int len = 0;
    in.read((char*)&len, sizeof(len));
    if (!in || len < 0) return "";
    std::string s;
    s.resize(len);
    if (len > 0) in.read(&s[0], len);
    return s;
}

inline void saveState(const AppState& st, const std::string& path) {
    std::ofstream out(path, std::ios::binary);
    if (!out) return;

    int MAGIC = 0x50464D31; // PFM1
    out.write((char*)&MAGIC, sizeof(MAGIC));

    // wallets
    out.write((char*)&st.wallets.size, sizeof(int));
    for (int i = 0; i < st.wallets.size; i++) {
        writeString(out, st.wallets[i].id);
        writeString(out, st.wallets[i].name);
        out.write((char*)&st.wallets[i].balance, sizeof(long long));
    }

    // income sources
    out.write((char*)&st.incomeSources.size, sizeof(int));
    for (int i = 0; i < st.incomeSources.size; i++) {
        out.write((char*)&st.incomeSources[i].id, sizeof(int));
        writeString(out, st.incomeSources[i].name);
    }

    // expense categories
    out.write((char*)&st.expenseCategories.size, sizeof(int));
    for (int i = 0; i < st.expenseCategories.size; i++) {
        out.write((char*)&st.expenseCategories[i].id, sizeof(int));
        writeString(out, st.expenseCategories[i].name);
    }

    // incomes
    out.write((char*)&st.incomes.size, sizeof(int));
    for (int i = 0; i < st.incomes.size; i++) {
        out.write((char*)&st.incomes[i].IncomeAmount, sizeof(int));
        writeString(out, st.incomes[i].IncomeDescription);
        out.write((char*)&st.incomes[i].InD, sizeof(IncomeDate));
        out.write((char*)&st.incomes[i].InS.sourceID, sizeof(int));
        writeString(out, st.incomes[i].InW.IWalletID);
    }

    // expenses
    out.write((char*)&st.expenses.size, sizeof(int));
    for (int i = 0; i < st.expenses.size; i++) {
        out.write((char*)&st.expenses[i].ExpenseAmount, sizeof(int));
        writeString(out, st.expenses[i].Description);
        out.write((char*)&st.expenses[i].ED, sizeof(ExpenseDate));
        out.write((char*)&st.expenses[i].ES.CategoryID, sizeof(int));
        writeString(out, st.expenses[i].EW.EWalletID);
    }

    // recurring
    out.write((char*)&st.recurring.size, sizeof(int));
    for (int i = 0; i < st.recurring.size; i++) {
        const RecurringItem& r = st.recurring[i];
        out.write((char*)&r.kind, sizeof(int));
        out.write((char*)&r.start, sizeof(SimpleDate));
        out.write((char*)&r.hasEnd, sizeof(bool));
        out.write((char*)&r.end, sizeof(SimpleDate));
        out.write((char*)&r.lastMonth, sizeof(int));
        out.write((char*)&r.lastYear, sizeof(int));

        if (r.kind == REC_INCOME) {
            out.write((char*)&r.inProto.InS.sourceID, sizeof(int));
            writeString(out, r.inProto.InW.IWalletID);
            out.write((char*)&r.inProto.IncomeAmount, sizeof(int));
            writeString(out, r.inProto.IncomeDescription);
        }
        else {
            out.write((char*)&r.exProto.ES.CategoryID, sizeof(int));
            writeString(out, r.exProto.EW.EWalletID);
            out.write((char*)&r.exProto.ExpenseAmount, sizeof(int));
            writeString(out, r.exProto.Description);
        }
    }
}

inline void loadState(AppState& st, const std::string& path) {
    std::ifstream in(path, std::ios::binary);
    if (!in) return;

    int MAGIC = 0;
    in.read((char*)&MAGIC, sizeof(MAGIC));
    if (!in || MAGIC != 0x50464D31) return;

    int n = 0;

    // wallets
    in.read((char*)&n, sizeof(int));
    for (int i = 0; i < n; i++) {
        WalletMaster w{};
        w.id = readString(in);
        w.name = readString(in);
        in.read((char*)&w.balance, sizeof(long long));
        st.wallets.push_back(w);
    }

    // income sources
    in.read((char*)&n, sizeof(int));
    for (int i = 0; i < n; i++) {
        IncomeSourceMaster s{};
        in.read((char*)&s.id, sizeof(int));
        s.name = readString(in);
        st.incomeSources.push_back(s);
    }

    // expense categories
    in.read((char*)&n, sizeof(int));
    for (int i = 0; i < n; i++) {
        ExpenseCategoryMaster c{};
        in.read((char*)&c.id, sizeof(int));
        c.name = readString(in);
        st.expenseCategories.push_back(c);
    }

    // incomes
    in.read((char*)&n, sizeof(int));
    for (int i = 0; i < n; i++) {
        IncomeData t{};
        in.read((char*)&t.IncomeAmount, sizeof(int));
        t.IncomeDescription = readString(in);
        in.read((char*)&t.InD, sizeof(IncomeDate));
        in.read((char*)&t.InS.sourceID, sizeof(int));
        t.InW.IWalletID = readString(in);
        st.incomes.push_back(t);
    }

    // expenses
    in.read((char*)&n, sizeof(int));
    for (int i = 0; i < n; i++) {
        ExpenseData t{};
        in.read((char*)&t.ExpenseAmount, sizeof(int));
        t.Description = readString(in);
        in.read((char*)&t.ED, sizeof(ExpenseDate));
        in.read((char*)&t.ES.CategoryID, sizeof(int));
        t.EW.EWalletID = readString(in);
        st.expenses.push_back(t);
    }

    // recurring
    in.read((char*)&n, sizeof(int));
    for (int i = 0; i < n; i++) {
        RecurringItem r{};
        in.read((char*)&r.kind, sizeof(int));
        in.read((char*)&r.start, sizeof(SimpleDate));
        in.read((char*)&r.hasEnd, sizeof(bool));
        in.read((char*)&r.end, sizeof(SimpleDate));
        in.read((char*)&r.lastMonth, sizeof(int));
        in.read((char*)&r.lastYear, sizeof(int));

        if (r.kind == REC_INCOME) {
            in.read((char*)&r.inProto.InS.sourceID, sizeof(int));
            r.inProto.InW.IWalletID = readString(in);
            in.read((char*)&r.inProto.IncomeAmount, sizeof(int));
            r.inProto.IncomeDescription = readString(in);
        }
        else {
            in.read((char*)&r.exProto.ES.CategoryID, sizeof(int));
            r.exProto.EW.EWalletID = readString(in);
            in.read((char*)&r.exProto.ExpenseAmount, sizeof(int));
            r.exProto.Description = readString(in);
        }

        st.recurring.push_back(r);
    }
}
