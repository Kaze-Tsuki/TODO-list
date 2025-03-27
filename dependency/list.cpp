#include "dependency.h"
#include <algorithm>
#include <typeinfo>

using namespace std;

list::list()
{}

list::list(string* name)
{
    this->name = new string(*name);
    tasks = new vector<base_task*>;
}

list::list(const list &l)
{
    name = new string(*l.name);
    tasks = new vector<base_task*>;
    for (int i = 0; i < l.tasks->size(); i++)
        tasks->push_back(new base_task(*l.tasks->at(i)));
}

list::list(string* name, const list &l)
{
    this->name = new string(*name);
    tasks = new vector<base_task*>;
    for (int i = 0; i < l.tasks->size(); i++)
        tasks->push_back(new base_task(*l.tasks->at(i)));
}

string& list::get_name()
{return *name;}

void list::change_name(string* name)
{*this->name = *name;}

void list::add_task(base_task *task)
{
    tasks->push_back(task);
}

base_task* list::get_task(int index)
{return tasks->at(index);}

void list::printAll()
{
    if(tasks->size() == 0)
    {
        cout << "No tasks\n";
        return;
    }
    cout << "List:" << *name << "\nID:\tName\tCategory\tCompleted\n";
    for (int i = 0; i < tasks->size(); i++)
        cout << i+1 << ":\t" << *tasks->at(i);
}

void list::printtask(int id)
{
    if (id < 0 || id >= tasks->size())
    {
        cout << "Invalid ID\n";
        return;
    }
    cout << "ID:\tName\tCategory\tCompleted\n";
    cout << id+1 << ":\t" << *(tasks->at(id));
}

void list::switch_id(int index1, int index2)
{
    if(index1 < 0 || index1 >= tasks->size() || index2 < 0 || index2 >= tasks->size())
    {
        cout << "Invalid ID\n";
        return;
    }
    base_task *temp = tasks->at(index1);
    tasks[index1] = tasks[index2];
    tasks->at(index2) = temp;
    delete temp;
    // cout << "Switch " << index1+1 << " and " << index2+1 << " completed\n";
}

void list::rm_taskWid(int index)
{
    if (index < 0 || index >= tasks->size())
    {
        cout << "Invalid ID\n";
        return;
    }
    delete tasks->at(index);
    tasks->erase(tasks->begin() + index);
}

void list::rm_taskWname(string name)
{
    for (int i = 0; i < tasks->size(); i++)
        if (tasks->at(i)->get_name() == name)
        {
            rm_taskWid(i--);
        }
}

void list::rm_taskWcate(string category)
{
    for (int i = 0; i < tasks->size(); i++)
        if (tasks->at(i)->get_category() == category)
        {
            rm_taskWid(i--);
        }
}

void list::sort(const string type, const bool ascending)
{
    cout << "Sorting by " << type << " in " << (ascending ? "ascending" : "descending") << " order\n";

    if (type == "name")
    {
        std::sort(tasks->begin(), tasks->end(), [ascending](base_task* a, base_task* b) {
            return ascending ? *a < *b : *a > *b;
        });
    }
    else if (type == "cate")
    {
        std::sort(tasks->begin(), tasks->end(), [ascending](base_task* a, base_task* b) {
            return ascending ? a->get_category() < b->get_category() : a->get_category() > b->get_category();
        });
    }
    else if (type == "comp")
    {
        std::sort(tasks->begin(), tasks->end(), [ascending](base_task* a, base_task* b) {
            return ascending ? a->get_completed() < b->get_completed() : a->get_completed() > b->get_completed();
        });
    }
    else if (type == "default")
    {
        // name -> category -> completed
        std::sort(tasks->begin(), tasks->end(), [ascending](base_task* a, base_task* b) {
            if (*a < *b)
                return ascending;
            if (*a == *b)
                return true;
            return false;
        });
    }
    else
    {
        cout << "Invalid type\n";
    }
}

list list::filter(const string category)
{
    string name = *this->name + "-" + category;
    list temp(&name);
    for (int i = 0; i < tasks->size(); i++)
        if (tasks->at(i)->get_category() == category)
            temp.add_task(new base_task(*tasks->at(i)));
    return temp;
}

void list::clear()
{
    for (int i = 0; i < tasks->size(); i++)
        delete tasks->at(i);
    tasks->clear();
}

list list::operator+(list &l)
{
    list temp(name);
    for (int i = 0; i < tasks->size(); i++)
        temp.add_task(new base_task(*tasks->at(i)));
    for (int i = 0; i < l.tasks->size(); i++)
        temp.add_task(new base_task(*l.tasks->at(i)));
    // delete repeated tasks
    temp.sort("default", true);
    for (int i = 0; i < temp.tasks->size() - 1; i++)
        if (*temp.tasks->at(i) == *temp.tasks->at(i + 1))
        {
            delete temp.tasks->at(i);
            temp.tasks->erase(temp.tasks->begin() + i);
            i--;
        }
    return temp;
}

list list::operator&(list &l)
{
    list temp(name);
    for (int i = 0; i < tasks->size(); i++)
        for (int j = 0; j < l.tasks->size(); j++)
            if (*tasks->at(i) == *l.tasks->at(j))
                temp.add_task(new base_task(*tasks->at(i)));
    return temp;
}

list::~list()
{
    clear();
    for (int i = 0; i < tasks->size(); i++)
        delete tasks->at(i);
    delete tasks;
    delete name;
}