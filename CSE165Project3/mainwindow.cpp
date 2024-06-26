#include "mainwindow.h"
#include <QDebug>

void Date::display(int taskNumber) const {
    qDebug() << "Task" << taskNumber << ":" << QString::fromStdString(task) << "(Due:" << month << "/" << day << "/" << year << ")";
}

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    mainLayout = new QVBoxLayout(this);
    taskList = new QListWidget(this);
    addButton = new QPushButton("Add Task", this);
    deleteButton = new QPushButton("Delete Task", this);
    sortAscButton = new QPushButton("Sort Ascending", this);
    sortDescButton = new QPushButton("Sort Descending", this);
    filterButton = new QPushButton("Filter Tasks", this);

    mainLayout->addWidget(taskList);
    mainLayout->addWidget(addButton);
    mainLayout->addWidget(deleteButton);
    mainLayout->addWidget(sortAscButton);
    mainLayout->addWidget(sortDescButton);
    mainLayout->addWidget(filterButton);

    setLayout(mainLayout);

    connect(addButton, &QPushButton::clicked, this, &MainWindow::addTask);
    connect(deleteButton, &QPushButton::clicked, this, &MainWindow::deleteTask);
    connect(sortAscButton, &QPushButton::clicked, this, &MainWindow::sortTasksAscending);
    connect(sortDescButton, &QPushButton::clicked, this, &MainWindow::sortTasksDescending);
    connect(filterButton, &QPushButton::clicked, this, &MainWindow::filterTask);
}

MainWindow::~MainWindow() {
    for (auto task : tasks) {
        delete task;
    }
}

void MainWindow::addTask() {
    QString newTask = QInputDialog::getText(this, "Add Task", "Enter the task:");
    if (!newTask.isEmpty()) {
        bool ok;
        int day, month, year;

        month = QInputDialog::getInt(this, "Add Task", "Enter the month:", 1, 1, 12, 1, &ok);
        if (!ok) return;

        day = QInputDialog::getInt(this, "Add Task", "Enter the day:", 1, 1, 31, 1, &ok);
        if (!ok) return;

        year = QInputDialog::getInt(this, "Add Task", "Enter the year:", 2024, 0, 9999, 1, &ok);
        if (!ok) return;

        if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
            QMessageBox::critical(this, "Error", "Invalid day for the selected month. Please try again.");
            return;
        } else if (month == 2) {
            bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
            if (!isLeapYear && day > 28) {
                QMessageBox::critical(this, "Error", "Invalid date for February. Please try again.");
                return;
            } else if (day > 29) {
                QMessageBox::critical(this, "Error", "Invalid date. Please try again.");
                return;
            }
        }

        tasks.push_back(new Date(day, month, year, newTask.toStdString()));
        displayTasks();
    }
}

void MainWindow::deleteTask() {
    int index = taskList->currentRow();
    if (index >= 0 && index < taskList->count()) {
        taskList->takeItem(index);
        delete tasks[index];
        tasks.erase(tasks.begin() + index);
    }
}

void MainWindow::sortTasksAscending() {
    compareAscending();
    displayTasks();
}

void MainWindow::sortTasksDescending() {
    compareDescending();
    displayTasks();
}

void MainWindow::filterTask() {
    bool ok;
    int month = QInputDialog::getInt(this, "Filter Tasks", "Enter the month to filter by:", 1, 1, 12, 1, &ok);
    if (!ok) return;

    int year = QInputDialog::getInt(this, "Filter Tasks", "Enter the year to filter by:", 2024, 0, 9999, 1, &ok);
    if (!ok) return;

    taskList->clear();
    int taskNumber = 1;
    for (const auto& task : tasks) {
        const Date* dateTask = dynamic_cast<const Date*>(task);
        if (dateTask && dateTask->getMonth() == month && dateTask->getYear() == year) {
            QListWidgetItem *item = new QListWidgetItem(QString("Task %1: %2").arg(taskNumber++).arg(QString::fromStdString(dateTask->getTask())));
            taskList->addItem(item);
        }
    }
}

void MainWindow::displayTasks() {
    taskList->clear();
    int taskNumber = 1;
    for (const auto& task : tasks) {
        const Date* dateTask = dynamic_cast<const Date*>(task);
        if (dateTask) {
            QListWidgetItem *item = new QListWidgetItem(QString("Task %1: %2 (Due: %3/%4/%5)").arg(taskNumber++).arg(QString::fromStdString(dateTask->getTask())).arg(dateTask->getMonth()).arg(dateTask->getDay()).arg(dateTask->getYear()));
            taskList->addItem(item);
        }
    }
}

void MainWindow::compareAscending() { //bubble sort
    int n = tasks.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            const Date* date1 = dynamic_cast<const Date*>(tasks[j]);
            const Date* date2 = dynamic_cast<const Date*>(tasks[j + 1]);
            if (date1 && date2) {
                if (date1->getYear() != date2->getYear()) {
                    if (date1->getYear() > date2->getYear()) {
                        std::swap(tasks[j], tasks[j + 1]);
                    }
                } else if (date1->getMonth() != date2->getMonth()) {
                    if (date1->getMonth() > date2->getMonth()) {
                        std::swap(tasks[j], tasks[j + 1]);
                    }
                } else if (date1->getDay() > date2->getDay()) {
                    std::swap(tasks[j], tasks[j + 1]);
                }
            }
        }
    }
}

void MainWindow::compareDescending() {  //bubble sort
    int n = tasks.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            const Date* date1 = dynamic_cast<const Date*>(tasks[j]);
            const Date* date2 = dynamic_cast<const Date*>(tasks[j + 1]);
            if (date1 && date2) {
                if (date1->getYear() != date2->getYear()) {
                    if (date1->getYear() < date2->getYear()) {
                        std::swap(tasks[j], tasks[j + 1]);
                    }
                } else if (date1->getMonth() != date2->getMonth()) {
                    if (date1->getMonth() < date2->getMonth()) {
                        std::swap(tasks[j], tasks[j + 1]);
                    }
                } else if (date1->getDay() < date2->getDay()) {
                    std::swap(tasks[j], tasks[j + 1]);
                }
            }
        }
    }
}
