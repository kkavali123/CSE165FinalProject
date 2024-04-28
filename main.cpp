#include <iostream>
#include <vector>
#include <string>
using namespace std;

// getter/setter method in the Date class but dont know if should be used elsewhere
// ascending/descending function needs to print immediatly 


class Task{
public:
    virtual void display(int taskNumber) const = 0;
    virtual ~Task() {}
};
// abstract base class = class designed to be used as a base class
// contains at least one pure virtual function (=0)
// can create an array of objects to save space 

class Date : public Task { 
    string task;
    int day, month, year;
public: 
    Date() : day(0), month(0), year(0) {}
    Date(int d, int m, int y, const string& t) : day(d), month(m), year(y), task(t) {}
    string getTask() const { return task; }
    void setTask(const string& t) { task = t; }
    int getDay() const { return day; }
    void setDay(int d) { day = d; }
    int getMonth() const { return month; }  //ask tomorrow if anything else is needed for getter/setter methods (need to add more?)
    void setMonth(int m) { month = m; }
    int getYear() const { return year; }
    void setYear(int y) { year = y; }
    void display(int taskNumber) const override {
        cout << "Task " << taskNumber << ": " << task << "(Due: " << month << "/" << day << "/" << year << ")" << endl;
    }
    ~Date() {} 
};

class ToDo : public Task{
    vector<Task*> tasks;
    int option = -1;
public:
    ~ToDo() {
        for(auto task : tasks){
            delete task;
        }
    } 
    void options();
    // void displayAll();
    void addTask();
    void deleteTask();
    void sortTasksAscending();
    void sortTasksDescending();
    void filterTask();
    void display(int taskNumber) const override;
    // void showBy(int month, int year); 
};

void ToDo::display(int taskNumber) const{
    if(tasks.empty()){
        cout << "No tasks to display!" << endl;
        return;
    }
    cout << "To-Do List: " << endl;
    for(const auto& task : tasks){
        task->display(taskNumber); 
        // polymorphism
        taskNumber++;
    }
}
// void ToDo::showBy(int month, int year){
//     cout << "Tasks Due During " << month << "/" << year <<":" << endl;
//     cout << "------------------------" << endl;
//     bool match = false;
//     for(int i = 0; i < counter; i++){
//         if(task[i].getMonth() == month && task[i].getYear() == year){
//             match = true;
//             cout << "Tasks: " << task[i].getTask() << " (Due: " << task[i].getDay() << "/" << task[i].getMonth() << "/" << task[i].getYear() << ")" << endl;
//         }
//     }
//     if(!match){
//         cout << "There are no tasks due this month!" << endl;
//     }
// }

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
                // displayAll();
                display(1);
                break;
            case 6:
                filterTask();
                break;
        }
    }
}
// void ToDo::displayAll(){
//     cout << "Tasks To Be Completed" << endl;
//     cout << "---------------------" << endl;
//     for(int i = 1; i < counter; i++){
//         Date currentTask = task[i];
//         cout << "Task " << i << " " << currentTask.getTask() << " (" << currentTask.getMonth() << "/" << currentTask.getDay() << "/" << currentTask.getYear() << ")" << endl;
//     }

// }

void ToDo::addTask() {
    // if(counter > 9){
    //     cout << "Tasks are all full!" << endl;
    // }
    // else {
        string newTask;
        int day, month, year;
        cout << "Enter the task: " << endl;
        cin.ignore(); 
        getline(cin, newTask);
        cout << "Enter the month: " << endl;
        cin >> month;
        if(month > 12 || month < 1){
            cout << "Number not valid. Enter a valid number, please." << endl;
            return;
        }
        cout << "Enter the day: " << endl; 
        cin >> day; 
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

        if(month == 2 && day > 29){
            cout << "Not a valid date." << endl;
            return;
        }
        else if((month == 2) && (day == 29) && ((year % 4 != 0) || (year % 100 == 0 && year % 400 != 0))) { 
            cout << "Not a valid date." << endl;
            return;
        }

        if((month == 4 || month == 6 || month == 9 || month == 11) && day > 30){
            cout << "Not a valid date." << endl;
            return;
        }
        tasks.push_back(new Date(day, month, year, newTask));
        // upcasting

        // task[counter] = Date(day, month, year, newTask);
        // counter++;
    // }
}


void ToDo::deleteTask(){  
    int deleteNumber = 0;
    cout << "Enter the number of the task you want to delete: ";
    cin >> deleteNumber;
    if (deleteNumber < 1 || deleteNumber > tasks.size()) { 
        cout << "Invalid task number! Try again." << endl; 
        return;
    }
    // for(int i = deleteNumber; i < counter-1; i++){
    //     task[i] = task[i+1];
    // }
    // counter--;
    tasks.erase(tasks.begin() + (deleteNumber-1));
}



// bool compareAscending(const Date& date1, const Date& date2) { 
bool compareAscending(const Task* task1, const Task* task2){
    const Date* date1 = dynamic_cast<const Date*>(task1);
    const Date* date2 = dynamic_cast<const Date*>(task2);
    if(date1 && date2){
        if(date1->getYear() != date2->getYear()){
            return date1->getYear() < date2->getYear();
        }
        if(date1->getMonth() != date2->getMonth()){
            return date1->getMonth() < date2->getMonth();
        return date1->getDay() < date2->getDay();
        }
        return false;
    }
    // if (date1.getYear() != date2.getYear())
    //     return date1.getYear() > date2.getYear(); 
    // if (date1.getMonth() != date2.getMonth())
    //     return date1.getMonth() > date2.getMonth(); 
    // return date1.getDay() > date2.getDay(); 
}

void ToDo::sortTasksAscending() {   
    cout << "Sorting tasks in ascending order..." << endl;
    int n = tasks.size();
    for(int i = 0; i < n-1; ++i) {
        for(int j = 0; j < n - i - 1; ++j) {
            if(!compareAscending(tasks[j], tasks[j + 1])) {
                Task* temp = tasks[j];
                tasks[j] = tasks[j+1];
                tasks[j+1] = temp;
            }
        }
    }
    display(1);
}

bool compareDescending(const Task* task1, const Task* task2){
    const Date* date1 = dynamic_cast<const Date*>(task1);
    const Date* date2 = dynamic_cast<const Date*>(task2);
    if(date1 && date2){
        if(date1->getYear() != date2->getYear()){
            return date1->getYear() > date2->getYear();
        }
        if(date1->getMonth() != date2->getMonth()){
            return date1->getMonth() > date2->getMonth();
        return date1->getDay() > date2->getDay();
        }
        return false;
    }
}

void ToDo::sortTasksDescending(){   
    cout << "Sorting tasks in descending order..." << endl;
    int n = tasks.size();
    for(int i = 0; i < n-1; ++i) {
        for(int j = 0; j < n - i - 1; ++j) {
            if(!compareDescending(tasks[j], tasks[j + 1])) {
                Task* temp = tasks[j];
                tasks[j] = tasks[j+1];
                tasks[j+1] = temp;
            }
        }
    }
    display(1);
}

void ToDo::filterTask(){  
    int month, year;
    cout << "Enter the month you want to filter by: " << endl;
    cin >> month;
    if(month > 12 || month < 1){
        cout << "Enter a valid number, please." << endl;
        return;
    }
    cout << "Enter the year you want to filter by: " << endl;
    cin >> year;
    if(year < 1){
        cout << "Enter a valid number, please." << endl;
        return;
    }
    cout << "Tasks Due During " << month << "/" << year <<":" << endl;
    cout << "------------------------" << endl;
    bool match = false;
    int taskNumber = 1;
    for(const auto& task : tasks){
        const Date* dateTask = dynamic_cast<const Date*>(task);
        if(dateTask && dateTask->getMonth() == month && dateTask->getYear() == year){
            match = true;
            dateTask->display(taskNumber);
            taskNumber++;
        }
    }
    if(!match){
        cout << "There are no tasks due this month!" << endl;
    }
}

int main(){
    ToDo obj;
    obj.options();
    return 0;
}
