#include <iostream>
#include <string>
#include <queue>
#include <fstream>
#include "customer.h"
using namespace std;

void Menu();      // Menu that displays options.
void CheckIn(queue<Customer>& myqueue);   // Check in a customer.
void CheckOut(queue<Customer>& history, queue<Customer>& myqueue);  // Remove customer from list.
void Search(queue<Customer>& history);    // Search for a customer.
void Quit(queue<Customer>& history, queue<Customer>& myqueue);      // Quit program.
void Save(queue<Customer>& history, queue<Customer>& myqueue);
void Load(queue<Customer>& history, queue<Customer>& myqueue);

int main() {
    queue<Customer> myqueue;
    queue<Customer> history;
    bool loop = true;
    int selection;
    do {
        Menu();
        cout << "Input: ";
        cin >> selection;
        cin.ignore();
        switch (selection)
        {
        case 1:
            cout << endl;
            CheckIn(myqueue);
            cout << endl;
            break;
        case 2:
            cout << endl;
            CheckOut(history, myqueue);
            cout << endl;
            break;
        case 3:
            cout << endl;
            Search(history);
            cout << endl;
            break;
        case 4:
            cout << endl;
            Save(history, myqueue);
            cout << endl;
            break;
        case 5:
            cout << endl;
            Load(history, myqueue);
            cout << endl;
            break;
        case 6:
            cout << endl;
            Quit(history, myqueue);
            loop = false;
            cout << "Exiting program...\n";
            break;
        default:
            break;
        }
    } while (loop);
}
void Menu() {
    cout << "\nWelcome to the Carwash\n";
    cout << "\n1) Check in\n";
    cout << "2) Check out\n";
    cout << "3) Search\n";
    cout << "4) Save\n";
    cout << "5) Load\n";
    cout << "6) Quit\n\n";
}
void CheckIn(queue<Customer>& myqueue) {
  string name, lp, pw;
  cout << "Name: ";
  cin >> name;
  cout << "License Plate: ";
  cin >> lp;
  cout << "Premium Wash? (y/n): ";
  cin >> pw;
    bool wash;
    if (pw == "y")
      wash = true;
    else
      wash = false;
  cout << "Customer checked in" << endl;
  Customer c1(name, lp, wash);
  myqueue.push(c1);
}
void CheckOut(queue<Customer>& history, queue<Customer>& myqueue) {
  if (myqueue.empty())
    cout << "No customers to checkout" << endl;
  else {
    Customer person1 = myqueue.front();
    myqueue.pop();
    history.push(person1);
    cout << person1.get_name() << " checked out." << endl;
  }
}
void Search(queue<Customer>& history) {
  string name;
  cout << "Name: ";
  cin >> name;
  for (size_t i = 0; i < history.size(); i++) {
    Customer temp;
    temp = history.front();
    if (temp.get_name() == name){
      cout << temp;
      return;
    }
    history.pop();
    history.push(temp);
  }
  cout << "Customer not found." << endl;
}
void Quit(queue<Customer>& history, queue<Customer>& myqueue) {
  while (!myqueue.empty()) {
    CheckOut(history, myqueue);
  }
  while(!history.empty()){
    history.pop();
  }
}
void Save(queue<Customer>& history, queue<Customer>& myqueue) {
  ofstream myfile;
  //ofstream myfile("save.txt");
  myfile.open("myqueue.txt");
  if (!myfile.is_open())
    cout << "File Error. ";
  else {
    for (size_t i = 0; i < myqueue.size(); i++) {
      Customer temp;
      temp = myqueue.front();
      myfile << temp;
      myfile << endl;
      myqueue.pop();
      myqueue.push(temp);
    }
  }
  ofstream myfile2;
  myfile2.open("history.txt");
  if (!myfile2.is_open())
    cout << "File Error. ";
  else {
    for (size_t i = 0; i < history.size(); i++) {
      Customer temp;
      temp = history.front();
      myfile2 << temp;
      myfile2 << endl;
      history.pop();
      history.push(temp);
    }
  }
  cout << "Files are saved. " << endl;
}
void Load(queue<Customer>& history, queue<Customer>& myqueue) {
  string line;
  ifstream readfile;
  int counter = 0;
  readfile.open("myqueue.txt");
  if (!readfile.is_open())
    cout << "Error Opening File. " << endl;
  else{
    while (getline(readfile, line)) {
      if (line.find("Name") != string::npos)
        counter++;
    }
  }
    cout << "Number of people in save file: " << counter << endl;
    string line2;
    ifstream readfile2;
    int counter2 = 0;
    readfile2.open("myqueue.txt");
    if (!readfile2.is_open())
      cout << "Error Opening File. " << endl;
    else{
      while (getline(readfile, line2)) {
        if (line2.find("Name") != string::npos)
          counter2++;
      }
    }
      cout << "Number of people in history file: " << counter2 << endl;
}
