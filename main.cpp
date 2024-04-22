#include <iostream>
using namespace std;

class ToDo {
    string task[10] = {""};
    int option = -1;
    int counter = 1;

public:
    void options();
    void displayAll();
    void addTask();
    void deleteTask();
    void sortTasks();
};

void ToDo::options() {
    while (option != 0) {
        cout << "--------To Do List--------" << endl;
        cout << "PRESS 1 TO ADD TASK" << endl;
        cout << "PRESS 2 TO DELETE TASK" << endl;
        cout << "PRESS 3 TO SORT TASKS" << endl;
        cout << "PRESS 4 TO SEE ALL TASKS" << endl;
        cout << "PRESS 0 TO EXIT OUT OF PROGRAM" << endl;
        cout << "--------------------------" << endl;
    
        cin >> option;    
        cin.ignore(); // Clear the newline character from the input buffer
        switch(option) {
            case 1:
                addTask();
                break;
            case 2:
                deleteTask();
                break;
            case 3:
                sortTasks();
                break;
            case 4:
                displayAll();
                break;
            // case 0:
            //     break;
            // default:
            //     cout << "Invalid option. Try again." << endl;
        }
    }
}

void ToDo::displayAll(){
    cout << "Tasks To Be Completed" << endl;
    cout << "---------------------" << endl;
    for(int i = 1; i < counter; i++){
        cout << "Task " << i << " "<< task[i] << endl;
    }
}

void ToDo::addTask(){
    if(counter > 9){
        cout <<"Tasks are all full!" << endl;
    }
    else{
        cout << "Enter task: ";
        getline(cin, task[counter]);
        counter++;
    }
}

void ToDo::deleteTask(){
    int deleteNumber = 0;
    cout << "Enter the Number of the Task you Want to Delete: ";
    cin >> deleteNumber;
    if (deleteNumber < 1 || deleteNumber >= counter) {
        cout << "Invalid task number!" << endl;
        return;
    }
    for(int i = deleteNumber; i < counter-1; i++){
        task[i] = task[i+1];
    }
    counter--;
}

void ToDo::sortTasks(){ //sort tasks in alphabetical order with bubble sort
    for (int i = 1; i < counter; ++i) {
        for (int j = 1; j < counter - i; ++j) {
            if (task[j] > task[j + 1]) {
                swap(task[j], task[j + 1]);
            }
        }
    }
}

int main(){
    ToDo obj;
    obj.options();
    return 0;
}

//add option for invalid input later