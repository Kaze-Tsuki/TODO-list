#include "dependency.h"
#include <algorithm>

using namespace std;

base_task::base_task(string name, string category, bool completed)
{
    this->name = new string(name);
    this->category = new string(category);
    this->completed = new bool(completed);
}

base_task::base_task(const base_task &t)
{
    name = new string(*t.name);
    category = new string(*t.category);
    completed = new bool(*t.completed);
}

norm_task::norm_task(string name, string category, bool completed) : base_task(name, category, completed)
{}
norm_task::norm_task(const base_task &t) : base_task(t)
{}

bool base_task::operator<(base_task &t)
{
    if (*name < *t.name)
        return true;
    if (*name == *t.name && *category < *t.category)
        return true;
    if (*name == *t.name && *category == *t.category && *completed < *t.completed)
        return true;
    return false;
}

bool base_task::operator>(base_task &t)
{
    if (*name > *t.name)
        return true;
    if (*name == *t.name && *category > *t.category)
        return true;
    if (*name == *t.name && *category == *t.category && *completed > *t.completed)
        return true;
    return false;
}

bool base_task::operator==(base_task &t)
{
    return (*name == *t.name && *category == *t.category && *completed == *t.completed);
}

bool base_task::operator!=(base_task &t)
{return !(*this == t);}

ostream &operator<<(ostream &os, base_task &t)
{
    os << *t.name << '\t'
        << *t.category << "\t\t"
        << ((*t.completed == true)? "Yes" : "No") << "\n";
    return os;
}

void base_task::print()
{
    cout << *name << '\t'
        << *category << '\t'
        << ((*completed == true)? "Yes" : "No") << "\t\n";
}

void base_task::change_completed(bool ncompleted)
{*completed = ncompleted;}

void base_task::change_name(string& nname)
{*name = nname;}

void base_task::change_category(string& ncategory)
{*category = ncategory;}

bool base_task::get_completed()
{return *completed;}

string base_task::get_name()
{return *name;}

string base_task::get_category()
{return *category;}

base_task::~base_task()
{
    delete name;
    delete category;
    delete completed;
}
