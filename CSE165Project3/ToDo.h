#ifndef TODO_H
#define TODO_H

#include <vector>
#include <iostream>
#include <string>

class Task {
public:
    virtual void display(int taskNumber) const = 0;
    virtual ~Task() {}
};

class Date : public Task {
    std::string task;
    int day, month, year;
public:
    Date() : day(0), month(0), year(0) {}
    Date(int d, int m, int y, const std::string& t) : day(d), month(m), year(y), task(t) {}
    std::string getTask() const { return task; }
    void setTask(const std::string& t) { task = t; }
    int getDay() const { return day; }
    void setDay(int d) { day = d; }
    int getMonth() const { return month; }
    void setMonth(int m) { month = m; }
    int getYear() const { return year; }
    void setYear(int y) { year = y; }
    void display(int taskNumber) const override {
        std::cout << "Task " << taskNumber << ": " << task << "(Due: " << month << "/" << day << "/" << year << ")" << std::endl;
    }
    ~Date() {}
};

class ToDo {
    std::vector<Task*> tasks;
public:
    ~ToDo() {
        for(auto task : tasks){
            delete task;
        }
    }
    void addTask(Task* task) {
        tasks.push_back(task);
    }
    void options();
    void deleteTask(); // Moved definition to cpp file
    void sortTasksAscending();
    void sortTasksDescending();
    void filterTask();
    void display(int taskNumber) const; // Moved definition to cpp file
    const std::vector<Task*>& getTasks() const { return tasks; }
};

#endif // TODO_H
