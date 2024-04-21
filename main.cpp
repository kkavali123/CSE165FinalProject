#include <iostream>
using namespace std;
// to do list requirements
// be able to add a task
// delete a task
// display all tasks
// display options

class ToDo {
    string task[10] = {""};
    int option = -1;
    int counter = 1;
public:
    void options();
    void displayAll();
    void addTask();
    void deleteTask();
};
void ToDo::options() {
    while (option != 0) {
        cout << "--------To Do List--------" << endl;
        cout << "PRESS 1 TO ADD TASK" << endl;
        cout << "PRESS 2 TO DELETE TASK" << endl;
        cout << "PRESS 3 TO SEE ALL TASKS" << endl;
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
                displayAll();
                break;
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
        cout <<"Task's are all full!" << endl;
    }
    else{
        getline(cin, task[counter]);
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
int main(){
    ToDo obj;
    obj.options();
    return 0;
}