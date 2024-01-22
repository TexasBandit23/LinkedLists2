//Author: Tejas Pandit
//LinkedLists Part 2
//Last Edited: 1/21/2024
//This code allows the user to create a student list that can be added to, subtracted from, or printed.
//The user can also ask for the average of all of the GPAs of the students in the list and can quit anytime.
//Worked with Jazveer Kaler and Arjun Pai

//imports
#include <iostream>
#include <vector>
#include <iomanip>
#include "node.h"
#include "student.h"
using namespace std;

//function prototypes, so many parameters
void ADD(Node* &head, Node* current, Node* previous, Node* node);
void PRINT(Node* head);
void DELETE (Node* &head, Node* previous, Node* current, int ID);
void AVERAGE(Node* head, float totalSum, int numOfEntries);

int main() {
  //initialize variables used throughout code
  bool run = true; //code runs when true, when QUIT is entered, set to false stopping code
  char input[81];
  Node* head = nullptr; 
    
  cout << "This is StudentList..." << endl;

  //starts the program, will run until run is false
  while (run == true) {
    cout << endl;
    cout << "Type: ADD, PRINT, DELETE, AVERAGE, or QUIT." << endl;
    cout << "Type ADD to add a student." << endl;
    cout << "Type PRINT to print all students, their ID, and their GPA." << endl;
    cout << "Type AVERAGE to return the average GPA of the students currently in the list." << endl;
    cout << "Type DELETE to delete a student by ID." << endl;
    cout << "Type QUIT to end the program." << endl;

    //get user input
    cin.get(input, 81);
    cin.ignore(81, '\n');

    //if the user typed add
    if (strcmp(input, "ADD") == 0) {
      //need to create a new student
      Student* newStudent = new Student();

      //takes in the new student's information (name, id, GPA)

      cout << "Enter First Name: " << endl;
      char inputName[20];
      cin.get(inputName, 20);
      cin.ignore(80, '\n');
      //set the first name of the new student using getFirst
      //a setFirst function could have been used here
      strcpy(newStudent->getFirst(), inputName);
      
      cout << "Enter Last Name: " << endl;
      cin.get(inputName, 20);
      cin.ignore(80, '\n');
      //set the last name of the new student using getLast
      //a setLast function could have been used here
      strcpy(newStudent->getLast(), inputName);
      
      cout << "Enter Student ID: " << endl;
      int num1;
      cin >> num1;
      cin.ignore(80, '\n');
      //set the id of the new student
      newStudent->setID(num1);
      
      cout << "Enter Student GPA: " << endl;
      float num2;
      cin >> num2;
      cin.ignore(80, '\n');
      //set the GPA of the new student
      newStudent->setGPA(num2);

      //make a new node using the new student
      Node* newNode = new Node(newStudent);

      cout << "Adding..." << endl;
      
      ADD(head, head, head, newNode); //runs add function to add the new node to the list
    }

    //if the user typed print
    else if (strcmp(input, "PRINT") == 0) {
      cout << "Printing..." << endl;
      PRINT(head); //call the print function
    }

    //if the user typed delete
    //having some error with this function that causes it to keep printing out the instructions
    //most likely has to do with the fact that I am taking in user input after the DELETE keyword is entered
    //fixed the error, it had to do with the uder input
    else if (strcmp(input, "DELETE") == 0) {
      //ask the user for an ID to be deleted and delete the student by ID as no ID should be the same
      int ID = 0;
      cout << "Enter the ID of the Student You Would Like to Delete" << endl;
      cin >> ID;
      cin.ignore(11, '\n'); //was missing this line 

      cout << "Deleting..." << endl;
	
      DELETE(head, head, head, ID); //call the delete function
    }

    //if the user typed delete
    else if (strcmp(input, "AVERAGE") == 0) {
      //to take the average we need the sum of all GPAs and the number of students in the list
      float totalSum = 0;
      int numOfEntries = 0;

      cout << "Averaging..." << endl;
      
      AVERAGE(head, totalSum, numOfEntries); //call the average function
      
    }

    //if the user typed quit
    else if (strcmp(input, "QUIT") == 0) {
      cout << "Quitting..." << endl;
      run = false; //no function to be called, just set run to false to end the while loop
    }

    //the entered word was not recognized
    else {
      cout << "Please enter one of the specified commands" << endl;
    }
  }
}

//add student function
//all functions will check if the list is empty to prevent errors from occuring
void ADD(Node* &head, Node* current, Node* previous, Node* node) {
  //the list is currently empty, the student being inputted should be the head node
  if (head == nullptr) {
    head = node;
  }

  //inserts student based on id, from least to greatest
  else {
    if (node->getStudent()->getID() < head->getStudent()->getID()) {
      Node* temp = head;
      head = node;
      head->setNext(temp);
    }
    
    else if (node->getStudent()->getID() < current->getStudent()->getID()) {
      previous->setNext(node);
      node->setNext(current);
    }
    //end of list has been reached
    else if (current->getNext() == nullptr) {
      current->setNext(node);
    }
    else {
      ADD(head, current->getNext(), current, node); //recursive call
    }
    return;
  }
  return;
}

//print function
void PRINT(Node* head) {
  //keeps calling the print function on the next node until the next node does not exist
  if (head != nullptr) {
    head->getStudent()->print(); //call print function on the current node
    PRINT(head->getNext()); //recursive call
  }
}

//delete function
void DELETE(Node* &head, Node* previous, Node* current, int ID) {
  //there are no students in the list to be deleted
  if (head == nullptr) {
        cout << "No Students" << endl;
        return;
  }
  //if the node we are looking for is the head, set the next node to head and delete the node
  if (ID == current->getStudent()->getID()) {
    if (current == head){
      head = head->getNext();
      delete current; //destructor
    }
    //to not break the list, set next of the previous node to be the node after current and delete current
    else {
    previous->setNext(current->getNext());
    delete current; // destructor
    }
    cout << "Student " << ID << " Deleted Successfully." << endl;
    return;
  }
  if (current->getNext() != nullptr) {
    DELETE(head, current, current->getNext(), ID); // recursive call
  }
  else {
    cout << "Student " << ID << " not found." << endl;
  }
}

//average function
void AVERAGE(Node* head, float totalSum, int numOfEntries) {
  //check to make sure the list has entries
  if (head == nullptr && numOfEntries == 0) {
    cout << "No Students Currently in the List" << endl;
  }
  //if we have not reached the end of the list (a nullptr) add the students GPA to the total and increase the   number of entries by one
  else if (head != nullptr) {
    totalSum += head->getStudent()->getGPA();
    numOfEntries++;
    AVERAGE(head->getNext(), totalSum, numOfEntries); //recursive call
  }
  //when the end of the end of the list has been reached (nullptr) calculate the average GPA
  else {
    cout << "Average GPA: ";
    //the average GPA is the sum of all GPAs divided by the number of entries
    cout << fixed << setprecision(2) << (totalSum / numOfEntries) << endl; //show to two decimal places
  }
}


//Some code that I was working on when I had no idea how to do recursion. Code did not work so I restarted
/*
void add(Node* &current) {
    if (current == nullptr) {
        Student* newStudent = new Student();
        cout << "Enter first name: " << endl;
        cin >> newStudent->firstName;
        cout << "Enter GPA: " << endl;
        cin >> newStudent->GPA;

        current = new Node(newStudent);
        cout << "Student added..." << endl;
    }
    else if (current->next == nullptr && current->student->studentID >= current->student->ID) {
        Student* newStudent = new Student();
        cout << "Enter GPA: " << endl;
        cin >> newStudent->GPA;

        Node* newNode = new Node(newStudent);
        newNode->next = current->next;
        current->next = newNode;
        cout << "Student added..." << endl;
    } else {
        add(current->next);
    }
}
*/
