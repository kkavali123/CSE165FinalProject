#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QInputDialog>
#include <vector>
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

    void display(int taskNumber) const override;
    ~Date() {}
};

class ToDo : public Task {
    std::vector<Task*> tasks;
    int option = -1;

public:
    ~ToDo();

    void options();
    void addTask();
    void deleteTask();
    void sortTasksAscending();
    void sortTasksDescending();
    void filterTask();
    void display(int taskNumber) const override;
};

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addTask();
    void deleteTask();
    void sortTasksAscending();
    void sortTasksDescending();
    void filterTask();

private:
    void displayTasks();

    QVBoxLayout *mainLayout;
    QListWidget *taskList;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QPushButton *sortAscButton;
    QPushButton *sortDescButton;
    QPushButton *filterButton;

    std::vector<Task*> tasks;
};

#endif // MAINWINDOW_H

//mainwindow.h for project 3
