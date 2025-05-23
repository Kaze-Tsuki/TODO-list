#include "dependency.h"
#include <algorithm>
#include <typeinfo>
#include <iomanip>
#include <list>

using namespace std;

todos::todos(string* name)
{
    this->name = new string(*name);
    tasks = new vector<base_task*>;
}

todos::todos(const todos* l)
{
    name = new string(*l->name);
    tasks = new vector<base_task*>();
    for (auto iter = l->tasks->begin(); iter != l->tasks->end(); ++iter)
        tasks->emplace_back((*iter)->clone());
}

// todos::todos(const string name, const todos &l)
// {
//     this->name = new string(name);
//     tasks = new vector<base_task*>;
//     for (auto iter = l.tasks->begin(); iter != l.tasks->end(); ++iter)
//         tasks->emplace_back((*iter)->clone());
// }

todos::todos(const string* name, list<todos>::iterator &l)
{
    this->name = new string(*name);
    tasks = new vector<base_task*>;
    for (auto iter = l->tasks->begin(); iter != l->tasks->end(); ++iter)
        tasks->emplace_back((*iter)->clone());
}

string& todos::get_name()
{return *name;}

void todos::change_name(string* name)
{*this->name = *name;}

void todos::add_task(base_task *task)
{
    for (auto &t : *tasks)
    {
        if (*t == *task)
        {
            cout << "Task already exists\n";
            return;
        }
    }
    tasks->emplace_back(task);
}

base_task* todos::get_task(int* index)
{
    if (*index < 0 || *index >= (int)tasks->size())
    {
        cout << "Invalid ID\n";
        return nullptr;
    }
    return tasks->at(*index);
}

void todos::printAll()
{
    if(tasks->size() == 0)
    {
        cout << "No tasks\n";
        return;
    }
    cout << "list: " << *name << '\n'
         << left << setw(4) << "ID:"
         << left << setw(12) << "Name"
         << left << setw(18) << "Category"
         << left << setw(12) << "Completed"
         << left << setw(15) << "Date"
         << left << setw(10) << "Piority" << "\n";
    cout << string(68, '-') << "\n";

    size_t* i = new size_t (0);
    for (; *i < tasks->size(); (*i)++)
        cout << setw(4) << (*i)+1 << *tasks->at(*i);
    delete i;
}

void todos::printtask(int* id)
{
    if (*id < 0 || *id >= (int)tasks->size())
    {
        cout << "Invalid ID\n";
        return;
    }
    cout << left << setw(4) << "ID:"
         << left << setw(12) << "Name"
         << left << setw(18) << "Category"
         << left << setw(12) << "Completed";
    if (typeid(*tasks->at(*id)) == typeid(special_task))
        cout << left << setw(15) << "Date"
             << left << setw(10) << "Piority" << "\n"
             << string(68, '-') << "\n";
    else
        cout << "\n" << string(43, '-') << "\n";
    cout << setw(4) << id+1 << *(tasks->at(*id));
}

void todos::switch_id(int* index1, int* index2)
{
    if(*index1 < 0 || *index1 >= (int)tasks->size() || *index2 < 0 || *index2 >= (int)tasks->size())
    {
        cout << "Invalid ID\n";
        return;
    }
    swap(tasks->at(*index1), tasks->at(*index2));
    // cout << "Switch " << index1+1 << " and " << index2+1 << " completed\n";
}

void todos::rm_taskWid(int* index)
{
    if (*index < 0 || *index >= (int)tasks->size())
    {
        cout << "Invalid ID\n";
        return;
    }
    delete tasks->at(*index);
    tasks->erase(tasks->begin() + *index);
}

void todos::rm_taskWname(string* name)
{
    int* i = new int (0);
    for (; *i < (int)tasks->size(); (*i)++)
        if (tasks->at(*i)->get_name() == *name)
        {
            rm_taskWid(i);(*i)--;
        }
    delete i;
}

void todos::rm_taskWcate(string* category)
{
    int* i = new int (0);
    for (; *i < (int)tasks->size(); (*i)++)
        if (tasks->at(*i)->get_category() == *category)
        {
            rm_taskWid(i);(*i)--;
        }
    delete i;
}

void todos::sort(const string* type, const bool* ascending)
{
    cout << "Sorting by " << *type << " in " << (*ascending ? "ascending" : "descending") << " order\n";

    if (*type == "name")
    {
        std::sort(tasks->begin(), tasks->end(), [ascending](base_task* a, base_task* b) {
            return *ascending ? *a < *b : *a > *b;
        });
    }
    else if (*type == "cate")
    {
        std::sort(tasks->begin(), tasks->end(), [ascending](base_task* a, base_task* b) {
            return *ascending ? a->get_category() < b->get_category() : a->get_category() > b->get_category();
        });
    }
    else if (*type == "comp")
    {
        std::sort(tasks->begin(), tasks->end(), [ascending](base_task* a, base_task* b) {
            return *ascending ? a->get_completed() < b->get_completed() : a->get_completed() > b->get_completed();
        });
    }
    else if (*type == "piority")
    {
        std::sort(tasks->begin(), tasks->end(), [ascending](base_task* a, base_task* b) {
            special_task* st1 = dynamic_cast<special_task*>(a);
            special_task* st2 = dynamic_cast<special_task*>(b);
            if (st1 == nullptr)
                return *ascending;
            if (st2 == nullptr)
                return !*ascending;
            return *ascending ? st1->get_piority() < st2->get_piority() : st1->get_piority() > st2->get_piority();
        });
    }
    else if (*type == "date")
    {
        std::sort(tasks->begin(), tasks->end(), [ascending](base_task* a, base_task* b) {
            special_task* st1 = dynamic_cast<special_task*>(a);
            special_task* st2 = dynamic_cast<special_task*>(b);
            if (st1 == nullptr)
                return *ascending;
            if (st2 == nullptr)
                return !*ascending;
            return *ascending ? st1->get_date() < st2->get_date() : st1->get_date() > st2->get_date();
        });
    }
    else if (*type == "default")
    {
        // name -> category -> completed
        std::sort(tasks->begin(), tasks->end(), [ascending](base_task* a, base_task* b) {
            if (*ascending)
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

todos* todos::filter(const string* type, const string* category)
{
    string* temp_name = new string(*name + "-" + *category);
    todos* temp = new todos(temp_name);
    delete temp_name;
    if (*type == "cate")
    {
        for (auto& task : *tasks)
            if (task->get_category() == *category)
                temp->add_task(task->clone());
    }
    else if (*type == "comp")
    {
        for (auto& task : *tasks)
            if (task->get_completed() == (*category == "1" || *category == "yes"))
                temp->add_task(task->clone());
    }
    else if (*type == "name")
    {
        for (auto& task : *tasks)
            if (task->get_name() == *category)
                temp->add_task(task->clone());
    }
    else if (*type == "date")
    {
        bool *bigger = new bool((*category)[0] == 'b');
        string *date;
        if (isdigit((*category)[0]))
            date = new string(*category);
        else
            date = new string(category->substr(1));
        for (auto& task : *tasks)
        {
            special_task* st = dynamic_cast<special_task*>(task);
            if (st == nullptr)
                continue;
            if ((*bigger && st->get_date() > *date) || (!(*bigger) && st->get_date() < *date))
                temp->add_task(task->clone());
        }
        delete bigger;
        delete date;
    }
    else if (*type == "piority")
    {
        bool *bigger = new bool((*category)[0] == 'b');
        int *piority;
        try{
            if (isdigit((*category)[0]))
                piority = new int(stoi(*category));
            else
                piority = new int(stoi(category->substr(1)));
        }
        catch (const invalid_argument& e) {
            cout << "invalid argument for piority" << endl;
            delete bigger;
            return nullptr;
        }
        for (auto& task : *tasks)
        {
            special_task* st = dynamic_cast<special_task*>(task);
            if (st == nullptr)
                continue;
            if ((*bigger && st->get_piority() > *piority) || (!(*bigger) && st->get_piority() < *piority))
                temp->add_task(task->clone());
        }
        delete bigger;
        delete piority;
    }
    else
    {
        cout << "Invalid type\n";
        return nullptr;
    }
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

todos* todos::merge(list<todos>::iterator& l)
{
    string* temp_name = new string(*this->name + "-" + *l->name);
    todos* temp = new todos(temp_name);
    delete temp_name;
    for (auto it1 = tasks->begin(); it1 != tasks->end(); ++it1)
        temp->add_task((*it1)->clone()); // 複製當前清單的任務
    for (auto it2 = l->tasks->begin(); it2 != l->tasks->end(); ++it2)
        temp->add_task((*it2)->clone()); // 複製要合併的清單的任務

    return temp; // 返回合併後的 todos
}

todos* todos::inter(list<todos>::iterator& l)
{
    string* temp_name = new string(*this->name + "-" + *l->name);
    todos* temp = new todos(temp_name);
    delete temp_name;
    for (auto it1 = tasks->begin(); it1 != tasks->end(); ++it1)
        for (auto it2 = l->tasks->begin(); it2 != l->tasks->end(); ++it2)
            if (**it1 == **it2)
                temp->add_task((*it1)->clone());
    return temp;
}

string todos::to_commands()
{
    static string *s = new string();
    *s = "bui " + *name + "\n";
    for (auto &task : *tasks)
    {
        *s += task->to_commands(name) + "\n";
    }
    return *s;
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