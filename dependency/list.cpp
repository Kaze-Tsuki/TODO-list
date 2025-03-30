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
    for (auto iter = l.tasks->begin(); iter != l.tasks->end(); ++iter)
        tasks->emplace_back((*iter)->clone());
}

todos::todos(const string name, const todos &l)
{
    this->name = new string(name);
    tasks = new vector<base_task*>;
    for (auto iter = l.tasks->begin(); iter != l.tasks->end(); ++iter)
        tasks->emplace_back((*iter)->clone());
}

string& todos::get_name()
{return *name;}

void todos::change_name(string* name)
{*this->name = *name;}

void todos::add_task(base_task *task)
{
    tasks->emplace_back(task);
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
    cout << "list: " << *name << "\nID:\tName\tCategory\tCompleted\n";
    int* i = new int(0);
    for (; *i < tasks->size(); (*i)++)
        cout << (*i)+1 << ":\t" << *tasks->at(*i);
    delete i;
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
    int* i = new int (0);
    for (; *i < tasks->size(); (*i)++)
        if (tasks->at(*i)->get_name() == name)
        {
            rm_taskWid((*i)--);
        }
    delete i;
}

void todos::rm_taskWcate(string category)
{
    int* i = new int (0);
    for (; *i < tasks->size(); (*i)++)
        if (tasks->at(*i)->get_category() == category)
        {
            rm_taskWid((*i)--);
        }
    delete i;
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
    else if (type == "piority")
    {
        std::sort(tasks->begin(), tasks->end(), [ascending](base_task* a, base_task* b) {
            special_task* st1 = dynamic_cast<special_task*>(a);
            special_task* st2 = dynamic_cast<special_task*>(b);
            if (st1 == nullptr)
                return ascending;
            if (st2 == nullptr)
                return !ascending;
            return ascending ? st1->get_piority() < st2->get_piority() : st1->get_piority() > st2->get_piority();
        });
    }
    else if (type == "date")
    {
        std::sort(tasks->begin(), tasks->end(), [ascending](base_task* a, base_task* b) {
            special_task* st1 = dynamic_cast<special_task*>(a);
            special_task* st2 = dynamic_cast<special_task*>(b);
            if (st1 == nullptr)
                return ascending;
            if (st2 == nullptr)
                return !ascending;
            return ascending ? st1->get_date() < st2->get_date() : st1->get_date() > st2->get_date();
        });
    }
    else if (type == "default")
    {
        // name -> category -> completed
        std::sort(tasks->begin(), tasks->end(), [ascending](base_task* a, base_task* b) {
            if (ascending)
            {
                if (*a < *b) return true;
                else if (*a > *b) return false;
                else if (a->get_category() < b->get_category()) return true;
                else if (a->get_category() > b->get_category()) return false;
                else return a->get_completed() < b->get_completed();
            }
            else
            {
                if (*a > *b) return true;
                else if (*a < *b) return false;
                else if (a->get_category() > b->get_category()) return true;
                else if (a->get_category() < b->get_category()) return false;
                else return a->get_completed() > b->get_completed();
            }
        });
    }
    else
    {
        cout << "Invalid type\n";
    }
}

todos* todos::filter(const string category)
{
    todos* temp = new todos(*this->name + "-" + category);
    for (int i = 0; i < tasks->size(); i++)
        if (tasks->at(i)->get_category() == category)
            temp->add_task(tasks->at(i)->clone());
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
    for (auto it1 = temp->tasks->begin(); it1 != temp->tasks->end(); ++it1)
        for (auto it2 = it1 + 1; it2 != temp->tasks->end();)
            if (**it1 == **it2)
            {
                delete *it2;
                it2 = temp->tasks->erase(it2);
            }
            else
            {
                ++it2;
            }

    return temp; // 返回合併後的 todos
}

todos* todos::inter(todos &l)
{
    todos* temp = new todos(*name + "-" + *l.name);
    for (auto it1 = tasks->begin(); it1 != tasks->end(); ++it1)
        for (auto it2 = l.tasks->begin(); it2 != l.tasks->end(); ++it2)
            if (**it1 == **it2)
                temp->add_task((*it1)->clone());
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