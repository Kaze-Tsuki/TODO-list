#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include "command.h"

using namespace std;

int main()
{
    // Initialize global pointers
    cmd = new string();
    liname = new string();
    name = new string();
    category = new string();
    type = new string();
    value = new string();
    completed = new bool();
    ascending = new bool();
    list_id = new int();
    task_id = new int();
    index1 = new int();
    index2 = new int();
    li = new list<todos>();
    ss = new stringstream();
    customs = new list<CommandCustomizer>();

    while (getline(cin, *cmd))
    {
        if (*cmd == "exit")
            break;

        else
            processor(*cmd);
    }

    // Free memory
    for (auto &l : *li)
    {
        l.~todos(); // Clear each list
    }
    li->clear(); // Clear the vector of lists
    for (auto &custom : *customs)
    {
        custom.~CommandCustomizer(); // Clear each custom command
    }
    customs->clear(); // Clear the vector of custom commands
    delete li;
    delete ss;
    delete cmd;
    delete liname;
    delete name;
    delete category;
    delete type;
    delete value;
    delete completed;
    delete ascending;
    delete list_id;
    delete task_id;
    delete index1;
    delete index2;

    return 0;
}