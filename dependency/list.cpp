#include "dependency.h"
#include <algorithm>
#include <typeinfo>

using namespace std;

list::list(string name)
{
    this->name = new string(name);
    tasks = new vector<base_task*>;
}

list::list(const list &l)
{
    name = new string(*l.name);
    tasks = new vector<base_task*>();
    for (int i = 0; i < l.tasks->size(); i++)
        tasks->push_back(l.tasks->at(i)->clone());
}

list::list(string* name, const list &l)
{
    this->name = new string(*name);
    tasks = new vector<base_task*>;
    for (int i = 0; i < l.tasks->size(); i++)
        tasks->push_back(l.tasks->at(i)->clone());
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
{
    if (index < 0 || index >= tasks->size())
    {
        cout << "Invalid ID\n";
        return nullptr;
    }
    return tasks->at(index);
}

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
    swap(tasks->at(index1), tasks->at(index2));
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
    list temp(name);
    for (int i = 0; i < tasks->size(); i++)
        if (tasks->at(i)->get_category() == category)
            temp.add_task(tasks->at(i)->clone());
    return temp;
}

void list::clear()
{
    cout << tasks->size() << " tasks deleted\n";
    while (tasks->size() > 0)
    {
        cout << "Deleting " << tasks->back()->get_name() << "\n";
        delete tasks->back(); // 釋放記憶體
        tasks->pop_back(); // 移除最後一個元素
    }

}

list* list::merge(list &l)
{
    list* temp = new list(*name + "-" + *l.name);
    
    for (int i = 0; i < tasks->size(); i++)
        temp->add_task(tasks->at(i)->clone());

    for (int i = 0; i < l.tasks->size(); i++)
        temp->add_task(l.tasks->at(i)->clone());

    temp->sort("default", true);

    // 使用 `unique` 來標記重複元素
    auto it = std::unique(temp->tasks->begin(), temp->tasks->end(),
        [](base_task* a, base_task* b) { return *a == *b; });

    // 刪除 `unique` 之後剩下的指標（這些指標指向被標記為重複的物件）
    for (auto iter = it; iter != temp->tasks->end(); ++iter)
        delete *iter; // 釋放記憶體，避免記憶體洩漏

    // `erase()` 只移除 vector 內的指標，不會影響未刪除的 task
    temp->tasks->erase(it, temp->tasks->end());

    return temp; // 返回合併後的 list
}

list* list::inter(list &l)
{
    list* temp = new list(*name + "-" + *l.name);
    for (int i = 0; i < tasks->size(); i++)
        for (int j = 0; j < l.tasks->size(); j++)
            if (*tasks->at(i) == *l.tasks->at(j))
                temp->add_task(tasks->at(i)->clone());
    return temp;
}

list::~list()
{
    cout << tasks->size() << " tasks deleted\n";
    while (tasks->size() > 0)
    {
        cout << "Deleting " << tasks->back()->get_name() << "\n";
        delete tasks->back(); // 釋放記憶體
        tasks->pop_back(); // 移除最後一個元素
    }
}