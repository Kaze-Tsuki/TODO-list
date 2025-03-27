#include "dependency.h"
#include <algorithm>

using namespace std;

norm_task::norm_task(string name, string category, bool completed)
{
    this->name = new string(name);
    this->category = new string(category);
    this->completed = new bool(completed);
}

norm_task::norm_task(const norm_task &t)
{
    name = new string(*t.name);
    category = new string(*t.category);
    completed = new bool(*t.completed);
}

bool norm_task::operator<(norm_task &t)
{
    if (*name < *t.name)
        return true;
    if (*name == *t.name && *category < *t.category)
        return true;
    if (*name == *t.name && *category == *t.category && *completed < *t.completed)
        return true;
    return false;
}

bool norm_task::operator>(norm_task &t)
{
    if (*name > *t.name)
        return true;
    if (*name == *t.name && *category > *t.category)
        return true;
    if (*name == *t.name && *category == *t.category && *completed > *t.completed)
        return true;
    return false;
}

bool norm_task::operator==(norm_task &t)
{
    return (*name == *t.name && *category == *t.category && *completed == *t.completed);
}

bool norm_task::operator!=(norm_task &t)
{return !(*this == t);}

ostream &operator<<(ostream &os, norm_task &t)
{
    os << *t.name << '\t'
        << *t.category << "\t\t"
        << ((*t.completed == true)? "Yes" : "No") << "\n";
    return os;
}

void norm_task::print()
{
    cout << *name << '\t'
        << *category << '\t'
        << ((*completed == true)? "Yes" : "No") << "\t\n";
}

void norm_task::change_completed(bool ncompleted)
{*completed = ncompleted;}

void norm_task::change_name(string& nname)
{*name = nname;}

void norm_task::change_category(string& ncategory)
{*category = ncategory;}

bool norm_task::get_completed()
{return *completed;}

string norm_task::get_name()
{return *name;}

string norm_task::get_category()
{return *category;}

norm_task::~norm_task()
{
    delete name;
    delete category;
    delete completed;
}

list::list()
{}

list::list(string* name)
{
    this->name = new string(*name);
}

list::list(const list &l)
{
    name = new string(*l.name);
    for (int i = 0; i < l.tasks.size(); i++)
        tasks.push_back(new norm_task(*l.tasks[i]));
}

list::list(string* name, const list &l)
{
    this->name = new string(*name);
    for (int i = 0; i < l.tasks.size(); i++)
        tasks.push_back(new norm_task(*l.tasks[i]));
}

string& list::get_name()
{return *name;}

void list::change_name(string* name)
{*this->name = *name;}

void list::add_task(norm_task *task)
{
    tasks.push_back(task);
}

norm_task* list::get_task(int index)
{return tasks[index];}

void list::printAll()
{
    if(tasks.size() == 0)
    {
        cout << "No tasks\n";
        return;
    }
    cout << "List:" << *name << "\nID:\tName\tCategory\tCompleted\n";
    for (int i = 0; i < tasks.size(); i++)
        cout << i+1 << ":\t" << *tasks[i];
}

void list::printtask(int id)
{
    if (id < 0 || id >= tasks.size())
    {
        cout << "Invalid ID\n";
        return;
    }
    cout << "ID:\tName\tCategory\tCompleted\n";
    cout << id+1 << ":\t" << *(tasks[id]);
}

void list::switch_id(int index1, int index2)
{
    if(index1 < 0 || index1 >= tasks.size() || index2 < 0 || index2 >= tasks.size())
    {
        cout << "Invalid ID\n";
        return;
    }
    norm_task *temp = tasks[index1];
    tasks[index1] = tasks[index2];
    tasks[index2] = temp;
    // cout << "Switch " << index1+1 << " and " << index2+1 << " completed\n";
}

void list::rm_taskWid(int index)
{
    if (index < 0 || index >= tasks.size())
    {
        cout << "Invalid ID\n";
        return;
    }
    delete tasks[index];
    tasks.erase(tasks.begin() + index);
}

void list::rm_taskWname(string name)
{
    for (int i = 0; i < tasks.size(); i++)
        if (tasks[i]->get_name() == name)
        {
            rm_taskWid(i--);
        }
}

void list::rm_taskWcate(string category)
{
    for (int i = 0; i < tasks.size(); i++)
        if (tasks[i]->get_category() == category)
        {
            rm_taskWid(i--);
        }
}

void list::sort(const string type, const bool ascending)
{
    cout << "Sorting by " << type << " in " << (ascending ? "ascending" : "descending") << " order\n";

    if (type == "name")
    {
        std::sort(tasks.begin(), tasks.end(), [ascending](norm_task* a, norm_task* b) {
            return ascending ? *a < *b : *a > *b;
        });
    }
    else if (type == "cate")
    {
        std::sort(tasks.begin(), tasks.end(), [ascending](norm_task* a, norm_task* b) {
            return ascending ? a->get_category() < b->get_category() : a->get_category() > b->get_category();
        });
    }
    else if (type == "comp")
    {
        std::sort(tasks.begin(), tasks.end(), [ascending](norm_task* a, norm_task* b) {
            return ascending ? a->get_completed() < b->get_completed() : a->get_completed() > b->get_completed();
        });
    }
    else if (type == "default")
    {
        // name -> category -> completed
        std::sort(tasks.begin(), tasks.end(), [ascending](norm_task* a, norm_task* b) {
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
    for (int i = 0; i < tasks.size(); i++)
        if (tasks[i]->get_category() == category)
            temp.add_task(new norm_task(*tasks[i]));
    return temp;
}

void list::clear()
{
    for (int i = 0; i < tasks.size(); i++)
        delete tasks[i];
    tasks.clear();
}

list list::operator+(list &l)
{
    list temp(name);
    for (int i = 0; i < tasks.size(); i++)
        temp.add_task(new norm_task(*tasks[i]));
    for (int i = 0; i < l.tasks.size(); i++)
        temp.add_task(new norm_task(*l.tasks[i]));
    // delete repeated tasks
    temp.sort("default", true);
    for (int i = 0; i < temp.tasks.size() - 1; i++)
        if (*temp.tasks[i] == *temp.tasks[i+1])
        {
            delete temp.tasks[i];
            temp.tasks.erase(temp.tasks.begin() + i);
            i--;
        }
    return temp;
}

list list::operator&(list &l)
{
    list temp(name);
    for (int i = 0; i < tasks.size(); i++)
        for (int j = 0; j < l.tasks.size(); j++)
            if (*tasks[i] == *l.tasks[j])
                temp.add_task(new norm_task(*tasks[i]));
    return temp;
}

list::~list()
{
    clear();
    delete name;
}