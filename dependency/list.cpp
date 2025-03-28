#include "dependency.h"
#include <algorithm>
#include <typeinfo>

using namespace std;

todos::todos(string name)
{
    this->name = new string(name);
    tasks = new vector<base_task*>;
}

todos::todos(const todos &l)
{
    name = new string(*l.name);
    tasks = new vector<base_task*>();
    for (int i = 0; i < l.tasks->size(); i++)
        tasks->push_back(l.tasks->at(i)->clone());
}

todos::todos(const string name, const todos &l)
{
    this->name = new string(name);
    tasks = new vector<base_task*>;
    for (int i = 0; i < l.tasks->size(); i++)
        tasks->push_back(l.tasks->at(i)->clone());
}

string& todos::get_name()
{return *name;}

void todos::change_name(string* name)
{*this->name = *name;}

void todos::add_task(base_task *task)
{
    tasks->push_back(task);
}

base_task* todos::get_task(int index)
{
    if (index < 0 || index >= tasks->size())
    {
        cout << "Invalid ID\n";
        return nullptr;
    }
    return tasks->at(index);
}

void todos::printAll()
{
    if(tasks->size() == 0)
    {
        cout << "No tasks\n";
        return;
    }
    cout << "todos:" << *name << "\nID:\tName\tCategory\tCompleted\n";
    for (int i = 0; i < tasks->size(); i++)
        cout << i+1 << ":\t" << *tasks->at(i);
}

void todos::printtask(int id)
{
    if (id < 0 || id >= tasks->size())
    {
        cout << "Invalid ID\n";
        return;
    }
    cout << "ID:\tName\tCategory\tCompleted\n";
    cout << id+1 << ":\t" << *(tasks->at(id));
}

void todos::switch_id(int index1, int index2)
{
    if(index1 < 0 || index1 >= tasks->size() || index2 < 0 || index2 >= tasks->size())
    {
        cout << "Invalid ID\n";
        return;
    }
    swap(tasks->at(index1), tasks->at(index2));
    // cout << "Switch " << index1+1 << " and " << index2+1 << " completed\n";
}

void todos::rm_taskWid(int index)
{
    if (index < 0 || index >= tasks->size())
    {
        cout << "Invalid ID\n";
        return;
    }
    delete tasks->at(index);
    tasks->erase(tasks->begin() + index);
}

void todos::rm_taskWname(string name)
{
    for (int i = 0; i < tasks->size(); i++)
        if (tasks->at(i)->get_name() == name)
        {
            rm_taskWid(i--);
        }
}

void todos::rm_taskWcate(string category)
{
    for (int i = 0; i < tasks->size(); i++)
        if (tasks->at(i)->get_category() == category)
        {
            rm_taskWid(i--);
        }
}

void todos::sort(const string type, const bool ascending)
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

todos todos::filter(const string category)
{
    string name = *this->name + "-" + category;
    todos temp(name);
    for (int i = 0; i < tasks->size(); i++)
        if (tasks->at(i)->get_category() == category)
            temp.add_task(tasks->at(i)->clone());
    return temp;
}

void todos::clear()
{
    cout << tasks->size() << " tasks deleted\n";
    while (tasks->size() > 0)
    {
        cout << "Deleting " << tasks->back()->get_name() << "\n";
        delete tasks->back(); // 釋放記憶體
        tasks->pop_back(); // 移除最後一個元素
    }

}

todos* todos::merge(todos &l)
{
    todos* temp = new todos(*name + "-" + *l.name);
    for (int i = 0; i < tasks->size(); i++)
        temp->add_task(tasks->at(i)->clone());
    for (int i = 0; i < l.tasks->size(); i++)
        temp->add_task(l.tasks->at(i)->clone());
    // 去除重複的任務 
    for (int i = 0; i < temp->tasks->size(); i++)
        for (int j = i + 1; j < temp->tasks->size(); j++)
            if (*temp->tasks->at(i) == *temp->tasks->at(j))
            {
                delete temp->tasks->at(j);
                temp->tasks->erase(temp->tasks->begin() + j--);
            }

    return temp; // 返回合併後的 todos
}

todos* todos::inter(todos &l)
{
    todos* temp = new todos(*name + "-" + *l.name);
    for (int i = 0; i < tasks->size(); i++)
        for (int j = 0; j < l.tasks->size(); j++)
            if (*tasks->at(i) == *l.tasks->at(j))
                temp->add_task(tasks->at(i)->clone());
    return temp;
}

todos::~todos()
{
    cout << tasks->size() << " tasks deleted\n";
    while (tasks->size() > 0)
    {
        cout << "Deleting " << tasks->back()->get_name() << "\n";
        delete tasks->back(); // 釋放記憶體
        tasks->pop_back(); // 移除最後一個元素
    }
}