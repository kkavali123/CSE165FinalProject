#include <iostream>
using namespace std;

// 4/21 Amrita - accessor/mutators + properly destroy all memory + any initlaization stuff that i did wrong 

//getter/setter methods are accessors/mutators - ADD LATER after discussing in 4/23 meeting tomorrow

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
    ~Date() {} 
};
class ToDo {
    Date task[10]; 
    int option = -1;
    int counter = 1;
public:
    ~ToDo() {} 
    void options();
    void displayAll();
    void addTask();
    void deleteTask();
    void sortTasksAscending();
    void sortTasksDescending();
    void filterTask();
    void showBy(int month, int year); 
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
        cout << "There are no tasks due this month!" << endl;
    }
}

void ToDo::options() {
    while (option != 0) {
        cout << "--------To Do List--------" << endl;
        cout << "PRESS 1 TO ADD TASK" << endl;
        cout << "PRESS 2 TO DELETE TASK" << endl;
        cout << "PRESS 3 TO SORT TASKS IN ASCENDING ORDER" << endl;
        cout << "PRESS 4 TO SORT TASKS IN DESCENDING ORDER" << endl;
        cout << "PRESS 5 TO SEE ALL TASKS" << endl;
        cout << "PRESS 6 TO FILTER TASKS BY MONTH" << endl;
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
                sortTasksAscending();
                break;
            case 4:
                sortTasksDescending();
                break;
            case 5:
                displayAll();
                break;
            case 6:
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

void ToDo::addTask(){  //maybe add extra if statements for certain months/years for valid dates? check comments below (DISCUSS)
    if(counter > 9){
        cout << "Task's are all full!" << endl;
    }
    else{
        string newTask;
        int day, month, year;
        cout << "Enter the task: " <<endl;
        getline(cin, newTask);
        cout << "Enter the month: " << endl;
        cin >> month;
        if(month > 12 || month < 1){
            cout << "Number not valid. Enter a valid number, please." << endl;
            return;
        }
        cout << "Enter the day: " << endl;  //add option later to see that for certain months, certain numbers can't be used (ex. Feb, April)
        cin >> day;         //think about leap year for February? (i.e. having the ability to only add 29 when it is a leap year? - discuss later)
        if(day > 31 || day < 1){
            cout << "Number not valid. Enter a valid number, please." << endl;
            return;
        }
        cout << "Enter the year: " << endl;
        cin >> year;
        if(year < 0){
            cout << "Number not valid. Enter a valid number, please." << endl;
            return;
        }

        task[counter] = Date(day, month, year, newTask);
        counter++;
        
    }
}

void ToDo::deleteTask(){  //maybe add another aspect where you can delete multiple tasks in one command? (discuss tomorrow)     
    int deleteNumber = 0;
    cout << "Enter the number of the task you want to delete: ";
    cin >> deleteNumber;
    if (deleteNumber < 1 || deleteNumber >= counter) { 
        cout << "Invalid task number! Try again." << endl; 
        return;
    }
    for(int i = deleteNumber; i < counter-1; i++){
        task[i] = task[i+1];
    }
    counter--;
}



bool compareAscending(const Date& date1, const Date& date2) { 
    if (date1.getYear() != date2.getYear())
        return date1.getYear() > date2.getYear(); 
    if (date1.getMonth() != date2.getMonth())
        return date1.getMonth() > date2.getMonth(); 
    return date1.getDay() > date2.getDay(); 
}

void ToDo::sortTasksAscending() {
    for(int i = 1; i < counter; ++i) {
        for(int j = 1; j < counter - i; ++j) {
            if(compareAscending(task[j], task[j + 1])) {
                swap(task[j], task[j + 1]);
            }
        }
    }
}

bool compareDescending(const Date& date1, const Date& date2) { 
    if (date1.getYear() != date2.getYear())
        return date1.getYear() < date2.getYear(); 
    if (date1.getMonth() != date2.getMonth())
        return date1.getMonth() < date2.getMonth(); 
    return date1.getDay() < date2.getDay(); 
}

void ToDo::sortTasksDescending(){
    for(int i = 1; i < counter; ++i) {
        for(int j = 1; j < counter - i; ++j) {
            if(compareDescending(task[j], task[j + 1])) {
                swap(task[j], task[j + 1]);
            }
        }
    }
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