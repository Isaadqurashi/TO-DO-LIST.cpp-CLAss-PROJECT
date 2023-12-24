#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int choice;
const string filename = "todo.txt";
void displayMenu()
{
    cout << "\n\n===== To-Do List Menu =====" << endl;
    cout << "1. Add Task" << endl;
    cout << "2. Search Task" << endl;
    cout << "3. Remove Task" << endl;
    cout << "4. View Tasks" << endl;
    cout << "5. Exit" << endl;
    cout << "===========================" << endl;
    cout << "Enter your Choice: ";
    cin >> choice;
}

void addTask();
void searchTask();
void removeTask();
void viewTAsks();

int main()
{
    do
    {
        displayMenu();
        switch (choice)
        {
        case 1:
        {
            addTask();
            break;
        }
        case 2:
        {
            searchTask();
            break;
        }
        case 3:
        {
            removeTask();
            break;
        }
        case 4:
        {
            viewTAsks();
            break;
        }
        case 5:
        {
            cout << "Exiting program. GoodBye!!" << endl;
            break;
        }
        default:
        {
            cout << "Invalid Choice. Please Try again!" << endl;
        }
        }
    } while (choice != 5);
}
void addTask()
{
    string task;
    cout << "Enter a Task: ";
    cin.ignore();
    getline(cin, task, '\n');
    ofstream myFile(filename, ios::app);
    if (myFile.is_open())
    {

        myFile << task << endl;
        cout << "Task Added Successfully!" << endl;
        myFile.close();
    }
    else
    {
        cout << "Error Opening the file!" << endl;
    }
}
void searchTask()
{
    ifstream myFile(filename);
    if (myFile.is_open())
    {
        string searchTask;
        cout << "Enter the task to search: ";
        cin.ignore();
        getline(cin, searchTask);
        string line;
        bool taskFound = false;
        while (getline(myFile, line))
        {
            if (line.find(searchTask) != string::npos)
            {
                cout << "Task found: " << line << endl;
                taskFound = true;
            }
        }
        if (!taskFound)
        {
            cout << "Task not found." << endl;
        }
        myFile.close();
    }
    else
    {
        cout << "Error Opening the file!" << endl;
    }
}
void removeTask()
{
    string removeTask;
    cout << "Enter the task to remove: ";
    cin.ignore();
    getline(cin, removeTask);

    ifstream inMyFile(filename);
    ofstream outMyFile("temporaryTodo.txt");

    if (!inMyFile.is_open() || !outMyFile.is_open())
    {
        cout << "Error opening files!" << endl;
        return;
    }
    string line;
    bool removed = false;
    while (getline(inMyFile, line))
    {
        if (line != removeTask)
        {
            outMyFile << line << endl;
        }
        else
        {
            removed = true;
        }
    }

    inMyFile.close();
    outMyFile.close();

    remove(filename.c_str());
    rename("temporaryTodo.txt", filename.c_str());

    if (removed)
    {
        cout << "Task removed successfully!" << endl;
    }
    else
    {
        cout << "Task not found." << endl;
    }
}
void viewTAsks()
{
    ifstream myFile(filename);
    if (myFile.is_open())
    {
        cout << "\n===== Current Tasks =====" << endl;
        string line;
        while (getline(myFile, line))
        {
            cout << line << endl;
        }
        cout << "===========================" << endl;
        myFile.close();
    }
    else
    {
        cout << "Error opening the file!" << endl;
    }
}