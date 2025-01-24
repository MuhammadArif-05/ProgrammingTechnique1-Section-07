//ASSIGNMENT 2A
//MUHAMMAD ARIF BIN MUHAMAD SUHAIMI (A24CS0126)
//DANIAL NUR IRFAN BIN AZEZE (A22EC0046)
//11.1.2025


#include <iostream>
#include <fstream>
#include <iomanip>
#define SIZE 50 //set maximum size to 50
using namespace std;

string name[SIZE]; //Holder type
string type[SIZE]; //utility type
double bill[SIZE]; // monthly bil
double lateFee[SIZE]; //late payments fees
double totAmt[SIZE]; //total payments amounts
char lateStat[SIZE]; //late payments status

void readInput(int &totHold, string name[],string type[],double bill[],char lateStat[]){
ifstream readFile; //file declaration

readFile.open("inp.txt"); //open file
totHold=0;

if(!readFile)
    cout << "Can't open file, please provide correct file." << endl; // provide error message

while (totHold<SIZE && getline (readFile, name[totHold], ',')) //copy data from  input file into array
{
    readFile.ignore();
    readFile >>type[totHold];
    readFile >> bill[totHold];
    readFile >> lateStat[totHold];
    readFile.ignore();
    totHold++; //count total number of households
}
readFile.close(); //close file
}


int calculateLateFee(string type[], char lateStat[], double lateFee[], int totHold){ //determine late fee
    int count=0;
    for(int i=0;i<totHold;i++){
        if (lateStat[i]=='Y' && type[i]=="Electricity")
            lateFee[i] = 20.00;
        else if(lateStat[i]=='Y' && type[i]=="Water")
            lateFee[i] = 10.00;
        else if (lateStat[i]=='Y' && type[i]=="Internet")
            lateFee[i] = 15.00;
        else
            lateFee[i] = 0.00;      
        
        count++;
        }    
return count; //return count to complete return value function
}

void calculateTotalPayment(double bill[], double lateFee[], double totAmt[], int totHold){ //calculate total payment amount
    
    for (int i=0;i<totHold;i++)
    {
        totAmt[i]=bill[i]+lateFee[i];
    }
}

void displayOutput(int totHold, string name[], string type[], double bill[], double lateFee[], double totAmt[]){

    cout << "Household Name" << "\t " 
         << "Utility Type" << "\t"
         << "Monthly Bill (MYR)" << "\t"
         << "Late Fee (MYR)" << "\t"
         << "Total Payment (MYR)" << endl;
    
    for(int i=0;i<94;i++)
        cout << "-";

    cout << endl;

    for(int i=0;i<totHold;i++)
    {
        cout << name[i] << "\t  ";
        if (type[i]!= "Water"){
            cout << type[i] << "\t"
                 << setw(10) << fixed << setprecision(2) << bill[i] << "\t"
                 << setw(17) << fixed << setprecision(2) << lateFee[i] << "\t"
                 << setw(19) << fixed << setprecision(2) << totAmt[i] << endl; 
        } else {
            cout << type[i] << "\t\t"
                 << setw(10) << fixed << setprecision(2) << bill[i] << "\t"
                 << setw(17) << fixed << setprecision(2) << lateFee[i] << "\t"
                 << setw(19) << fixed << setprecision(2) << totAmt[i] << endl; 
        }

    }
} 

void displayAnalysis(string name[], string type[], double totAmt[], char lateStat[], int totHold){
    int totWhold=0, totIhold=0, totEhold=0, lateWpay=0, lateIpay=0, lateEpay=0;
    double totWpay=0.00, totEpay=0.00, totIpay=0.00;  
    for(int i=0;i<totHold;i++)
    { 
        if(type[i]=="Water" ){
            totWhold++;
            totWpay+=totAmt[i];
            if(lateStat[i]=='Y')
                lateWpay++;
        }
        else if(type[i]=="Internet" ){
            totIhold++; 
            totIpay+=totAmt[i];
            if(lateStat[i]=='Y')
                lateIpay++;
        }
        else if(type[i]=="Electricity" ){
            totEhold++;
            totEpay+=totAmt[i];
            if(lateStat[i]=='Y')
                lateEpay++;
        }
        else 
            cout << "Invalid type for entry " << i << ":" << type[i] << endl;
    
    }

double high = totAmt[0]; //highest payment amount
string hName = name[0]; //name with highest payment
string hType = type[0]; //utility type with highest payment
for(int i=1;i<totHold;i++){
    if(totAmt[i]>high){
        high=totAmt[i];
        hName=name[i];
        hType=type[i];
    }
}

double low = totAmt[0]; //lowest payment amount
string lName = name[0]; //name with lowest payment amount
string lType = type[0]; //utility type with lowest payment
for(int i=1;i<totHold;i++){
    if(totAmt[i]<low){
        low=totAmt[i];
        lName=name[i];
        lType=type[i];
    }
}

double percent = ((lateWpay+lateEpay+lateIpay)/(20.00))*100.00; //calculate percentage

double late = lateWpay;
string mostLate; //compare which utility type have the most total late payment
if (late < lateEpay)
    mostLate = "Electricity";
else if (late < lateIpay) 
    mostLate = "Internet";
else 
    mostLate = "Water";

cout << endl;
cout << "Utility Type" << "\t"
     << "Households" << "\t"
     << "Late payments" << "\t"
     << "Total Payments (MYR)" << "\t"
     << "Average Payments (MYR)" << endl;

for(int i=0;i<94;i++)
    cout << "-";

cout << endl;

cout << "Water" << setw(16) << totWhold << setw(18) << lateWpay << setw(24) << fixed << setprecision(2) << totWpay << setw(30) <<  (totWpay/totWhold) << endl
     << "Internet" << setw(13) << totIhold << setw(18) << lateIpay << setw(24) << fixed << setprecision(2) << totIpay << setw(30) << (totIpay/totIhold) << endl
     << "Electricity" << setw(10) << totEhold << setw(18) << lateEpay << setw(24) << fixed << setprecision(2) << totEpay << setw(30) << (totEpay/totEhold) << endl;

cout << endl;
cout << "Overall Total Payment : MYR" << fixed << setprecision(2) << (totWpay+totIpay+totEpay) << endl; // Total payment for all utility types
cout << "Overall Average Payment : MYR" << fixed << setprecision(2) << (((totWpay+totIpay+totEpay)/(totIhold+totWhold+totEhold))) << endl; //Total payment for all utility type divided by total utility type holder.
cout << "Highest Payment : " << hName << " (MYR " << high << ") for " << hType << endl;
cout << "Lowest Payment : " << lName << " (MYR " << low << ") for " << lType << endl;
cout << "Percentage of Household with Late Payments : " << fixed << setprecision(1) << percent << "%" << endl;
cout << "Utility Type with the Most Late Payments : " << mostLate << endl;


}

int main(){

int totLate;
int totHold;

readInput(totHold, name, type, bill, lateStat); 
totLate=calculateLateFee(type, lateStat, lateFee, totHold);
calculateTotalPayment(bill, lateFee, totAmt, totHold);
displayOutput(totHold, name, type, bill, lateFee, totAmt);
displayAnalysis(name, type, totAmt, lateStat, totHold);

system("pause");
return 0;
}