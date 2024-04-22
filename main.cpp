#include <iostream>
using namespace std;
// Keerthi
// to do list requirements
// be able to add a task
// delete a task
// display all tasks
// display options
// another class called deadlines where you can put important dates
// sort deadline by priority????
// April 20 Keerthi - add another class Amrita - some kind of algorithm implementation
// April 21 Keerthi - inheritcance/polymorphism and deriving objects from the abstract class + upcasting

// potentially a seperate date class
// now use a sorting algorithm to sort the display based on due date (Amrita)
// gives the dates a restriction


// 4/21 Amrita - destructor for date class + accessor/mutators + properly destroy all memory + any initlaization stuff that i did wrong 
// sort by deadlines, with earliest deadlines being first
// invalid options in the to do list + invalid options for dates
// optional Amrita - sort by farthest away deadline
// 4/21 Keerthi - include polymmorphism/inheritance of some kind + abstract class + upcasting

class Date {
    string task;
    int day, month, year;
public: 
    Date() : day(0), month(0), year(0) {}
    Date(int d, int m, int y, const string& t) : day(d), month(m), year(y), task(t) {}
    string getTask() const { return task; }
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }
};
class ToDo {
    Date task[10]; 
    int option = -1;
    int counter = 1;
public:
    void options();
    void displayAll();
    void addTask();
    void deleteTask();
    void filterTask();
    void showBy(int month, int year); // Move the function declaration here
};

void ToDo::showBy(int month, int year){
    cout << "Tasks Due During " << month << "/" << year <<":" << endl;
    cout << "------------------------" << endl;
    bool match = false;
    for(int i = 0; i < counter; i++){
        if(task[i].getMonth() == month && task[i].getYear() == year){
            match = true;
            cout << "Tasks: " << task[i].getTask() << " (Due: " << task[i].getDay() << "/" << task[i].getMonth() << "/" << task[i].getYear() << ")" << endl;
        }
    }
    if(!match){
        cout <<"There are no tasks due this month!" << endl;
    }
}

void ToDo::options() {
    while (option != 0) {
        cout << "--------To Do List--------" << endl;
        cout << "PRESS 1 TO ADD TASK" << endl;
        cout << "PRESS 2 TO DELETE TASK" << endl;
        cout << "PRESS 3 TO SEE ALL TASKS" << endl;
        cout << "PRESS 4 TO FILTER TASKS BY MONTH" << endl;
        cout << "PRESS 0 TO EXIT OUT OF PROGRAM" << endl;
        cout << "--------------------------" << endl;
        cin >> option;
        cin.ignore(); 
        switch(option) {
            case 1:
                addTask();
                break;
            case 2:
                deleteTask();
                break;
            case 3:
                displayAll();
                break;
            case 4:
                filterTask();
                break;
        }
    }
}
void ToDo::displayAll(){
    cout << "Tasks To Be Completed" << endl;
    cout << "---------------------" << endl;
    for(int i = 1; i < counter; i++){
        Date currentTask = task[i];
        cout << "Task " << i << " " << currentTask.getTask() << " (" << currentTask.getMonth() << "/" << currentTask.getDay() << "/" << currentTask.getYear() << ")" << endl;
    }

}

void ToDo::addTask(){
    if(counter > 9){
        cout <<"Task's are all full!" << endl;
    }
    else{
        string newTask;
        int day, month, year;
        cout << "Enter the task: " <<endl;
        getline(cin, newTask);
        cout << "Enter the month: " << endl;
        cin >> month;
        cout << "Enter the day: " << endl;
        cin >> day;
        cout << "Enter the year: " << endl;
        cin >> year;

        task[counter] = Date(day, month, year, newTask);
        counter++;
        
    }
}

void ToDo::deleteTask(){
    int deleteNumber = 0;
    cout << "Enter the Number of the Task you Want to Delete" << endl;
    cin >> deleteNumber;
    for(int i = deleteNumber; i <counter-1; i++){
        task[i] = task[i+1];
    }
    counter--;
}

void ToDo::filterTask(){
    int month, year;
    cout << "Enter the month you want to filter by: " << endl;
    cin >> month;
    cout << "Enter the year you want to filter by: " << endl;
    cin >> year;
    showBy(month, year);
}

int main(){
    ToDo obj;
    obj.options();
    return 0;
}