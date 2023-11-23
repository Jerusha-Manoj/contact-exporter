#include <iostream>
#include <fstream>
#include <vector>
#include <ostream>
#include <string>
#include "base64.h"

using namespace std;
//Information that each contact willhave
struct Contact{
    string First;
    string Last;
    string phonenum;
    string email;
    string note;
    string bday;
    string image;
};

//Reading in information from the user to create the contact
void makeCard(ofstream& file,Contact& c);
int main(){
    Contact c;
    cout << "Enter your name (First Last): ";
    cin >> c.First >> c.Last;

    cout << "Enter your phone number (##########): ";
    cin >> c.phonenum;
    while(c.phonenum.length()!=10){
        cout << "Phone number must be 10 digits (no spaces/dashes): ";
        cin >> c.phonenum;
    }

    cout << "Enter your email: ";
    cin >> c.email;

    cout << "Enter their roles in KTP (potential big, E-board, etc.): ";
    cin.ignore();
    getline(cin, c.note);

    string month, day, year;
    cout << "Enter their birthday (MM DD, YYYY): ";
    cin >> month >> day >> year;
    c.bday = year+month+day;

    cout << "Input the Base64 text of the pfp: ";
    ifstream f;f.open("img.txt");
    f >> c.image;
    f.close();

    ofstream file;
    makeCard(file,c);

    return 0;
}
//Creating the vCard file
void makeCard(ofstream& file,Contact& c){
    file.open(c.First+"_"+c.Last+".vcf");
    file << "BEGIN:VCARD\nVERSION:3.0\nPRODID:-//Apple Inc.//iPhone OS 17.0.3//EN\n";
    file << "N:"<<c.Last<<";"<<c.First<<";;;\n";
    file << "TEL;type=pref:+1"<<c.phonenum<<"\n";
    file << "EMAIL:"<<c.email<<"\n";
    file << "NOTE:"<<c.note<<"\n";
    file << "BDAY:"<<c.bday<<"\n";
    file << "ORG:KTP\nPHOTO;ENCODING=b;TYPE=JPEG:"<<c.image<<"\n";
    file << "END:VCARD\n";
    file.close();
}


