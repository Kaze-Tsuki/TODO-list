#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include "dependency/dependency.h"
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
    li = new vector<list>();
    ss = new stringstream();

    while (getline(cin, *cmd))
    {
        if (*cmd == "exit")
            break;
        processor(*cmd);
    }

    // Free memory
    for (int i = 0; i < li->size(); i++)
    {
        (*li)[i].~list();
    }
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