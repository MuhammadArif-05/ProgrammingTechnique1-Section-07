/* 
Group member:
    1. MUHAMMAD ARIF BIN MUHAMAD SUHAIMI A24CS0126
    2. DANIAL NUR IRFAN BIN AZEZE A22EC0046

    Date of completion: 23/1/2025
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;

struct Hub {
    string code, name, location;
};

struct Revenues {
    double annual, percentage;
};

struct Quarterly {
    int q1, q2, q3, q4;
};

void calculate(vector<Quarterly> &q, vector<Hub> &hubn);
void report(const vector<Hub> &hubn, const vector<Quarterly> &q, const vector<Revenues> &rv, int hQa, int lQa, string highQ, string lowQ, int high, int low, string hname, string lname, string hloc, string lloc, int total, int tot1, int tot2, int tot3, int tot4);

int main() {
ifstream readFile,inp1,inp2,inp3,inp4; // declare file
readFile.open("hubs.txt");
inp1.open("q1.txt");
inp2.open("q2.txt");
inp3.open("q3.txt");
inp4.open("q4.txt"); // open the file

    if (!readFile || !inp1 || !inp2 || !inp3 || !inp4) {
        cerr << "Error: One or more input files are missing!" << endl;
        return 1;
    }

    vector<Hub> hb;
    vector<Quarterly> qtr;

    string hubCode;
    while (readFile >> hubCode) {
        Hub h;
        h.code = hubCode;

        Quarterly q;
        if (!(inp1 >> q.q1) || !(inp2 >> q.q2) || !(inp3 >> q.q3) || !(inp4 >> q.q4)) {
            cerr << "Error: Inconsistent data across files." << endl;
            return 1;
        }

        hb.push_back(h);
        qtr.push_back(q);
    }

    if (!inp1.eof() || !inp2.eof() || !inp3.eof() || !inp4.eof()) {
        cerr << "Error: Number of lines between files do not match." << endl;
        return 1;
    }

    for (auto &h : hb) {
        if (h.code == "KLS101") {
            h.name = "KL Sentral";
            h.location = "Kuala Lumpur";
        } else if (h.code == "PNS202") {
            h.name = "Penang Sentral";
            h.location = "Penang";
        } else if (h.code == "JBS303") {
            h.name = "JB Sentral";
            h.location = "Johor Bahru";
        } else if (h.code == "IPS404") {
            h.name = "Ipoh Sentral";
            h.location = "Ipoh";
        } else if (h.code == "MKS505") {
            h.name = "Melaka Sentral";
            h.location = "Melaka";
        } else if (h.code == "KKS606") {
            h.name = "KK Sentral";
            h.location = "Kota Kinabalu";
        } else if (h.code == "KTS707") {
            h.name = "Kuantan Sentral";
            h.location = "Kuantan";
        } else {
            cerr << "Error: Invalid hub code " << h.code << endl;
            return 1;
        }
    }

    calculate(qtr, hb);

    readFile.close();
    inp1.close();
    inp2.close();
    inp3.close();
    inp4.close();

    system("pause");
    return 0;
}

void calculate(vector<Quarterly> &q, vector<Hub> &hubn) {
    vector<Revenues> rv(hubn.size());
    double total = 0.0;

    for (size_t i = 0; i < hubn.size(); i++) {
        rv[i].annual = q[i].q1 + q[i].q2 + q[i].q3 + q[i].q4;
        total += rv[i].annual;
    }

    for (size_t i = 0; i < hubn.size(); i++) {
        rv[i].percentage = (rv[i].annual / total) * 100;
    }

    int high = rv[0].annual, low = rv[0].annual;
    string hname = hubn[0].name, hloc = hubn[0].location;
    string lname = hubn[0].name, lloc = hubn[0].location;

    for (size_t i = 1; i < hubn.size(); i++) {
        if (rv[i].annual > high) {
            high = rv[i].annual;
            hname = hubn[i].name;
            hloc = hubn[i].location;
        }
        if (rv[i].annual < low) {
            low = rv[i].annual;
            lname = hubn[i].name;
            lloc = hubn[i].location;
        }
    }

    int totQ1 = 0, totQ2 = 0, totQ3 = 0, totQ4 = 0;
    for (const auto &qt : q) {
        totQ1 += qt.q1;
        totQ2 += qt.q2;
        totQ3 += qt.q3;
        totQ4 += qt.q4;
    }

    string highQ = "Quarter 1", lowQ = "Quarter 1";
    int hQa = totQ1, lQa = totQ1;

    if (totQ2 > hQa) { highQ = "Quarter 2"; hQa = totQ2; }
    if (totQ3 > hQa) { highQ = "Quarter 3"; hQa = totQ3; }
    if (totQ4 > hQa) { highQ = "Quarter 4"; hQa = totQ4; }

    if (totQ2 < lQa) { lowQ = "Quarter 2"; lQa = totQ2; }
    if (totQ3 < lQa) { lowQ = "Quarter 3"; lQa = totQ3; }
    if (totQ4 < lQa) { lowQ = "Quarter 4"; lQa = totQ4; }

    report(hubn, q, rv, hQa, lQa, highQ, lowQ, high, low, hname, lname, hloc, lloc, total, totQ1, totQ2, totQ3, totQ4);
}

void report(const vector<Hub> &hubn, const vector<Quarterly> &q, const vector<Revenues> &rv, int hQa, int lQa, string highQ, string lowQ, int high, int low, string hname, string lname, string hloc, string lloc, int total, int tot1, int tot2, int tot3, int tot4) {
    double totP = 0.0;
    for (const auto &r : rv) {
        totP += r.percentage;
    }

    cout << left << setw(12) << "HUB CODE"
         << setw(18) << "HUB NAME"
         << setw(28) << "LOCATION"
         << setw(16) << "Q1"
         << setw(16) << "Q2"
         << setw(16) << "Q3"
         << setw(12) << "Q4"
         << setw(17) << "ANNUAL REV"
         << setw(16) << "CONTRIBUTION" << endl;

    for (int i = 0; i < 147; i++) cout << "-";
    cout << endl;

    for (size_t i = 0; i < hubn.size(); i++) {
        cout << left << setw(12) << hubn[i].code
             << setw(18) << hubn[i].name
             << setw(14) << hubn[i].location
             << right << setw(18) << q[i].q1
             << right << setw(16) << q[i].q2
             << right << setw(16) << q[i].q3
             << right << setw(16) << q[i].q4
             << right << setw(16) << fixed << setprecision(0) << rv[i].annual
             << right << setw(16) << fixed << setprecision(2) << rv[i].percentage << "%" << endl;
    }

    for (int i = 0; i < 147; i++) cout << "-";
    cout << endl;

    cout << right << setw(21) << " "
         << left << setw(32) << "AVERAGE"
         << setw(16) << fixed << setprecision(2) << (tot1 / (double)hubn.size())
         << setw(16) << (tot2 / (double)hubn.size())
         << setw(16) << (tot3 / (double)hubn.size())
         << setw(16) << (tot4 / (double)hubn.size())
         << setw(20) << (total / (double)hubn.size())
         << fixed << setprecision(2) << (totP / (double)hubn.size()) << "%" << endl;

    for (int i = 0; i < 147; i++) cout << "-";
    cout << endl;

    cout << endl << "OVERALL REPORT" << endl;
    for (int i = 0; i < 14; i++) cout << "=";
    cout << endl;
    cout << left << setw(22) << "GRAND TOTAL REVENUE    = " << total << endl
    << "HIGHEST ANNUAL REVENUE = " << high << " (" << hname << ", " << hloc << ")" << endl
    << "LOWEST ANNUAL REVENUE  = " << low << " (" << lname << ", " << lloc << ")" << endl
    << "QUARTER WITH HIGHEST TOTAL REVENUE: " << highQ << " (" << hQa << ")" << endl
    << "QUARTER WITH LOWEST TOTAL REVENUE : " << lowQ << " (" << lQa << ")" << endl;
}
