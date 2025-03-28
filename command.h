#include <iostream>
#include <string>
#include <sstream>
#include <list> // 改為使用 std::list
#include <algorithm> // For std::find_if
#include <map>
#include "dependency/dependency.h"

using namespace std;

// Global variables
list<todos> *li;             // 全域指標變數，儲存所有清單
stringstream *ss;           // 全域指標變數，用於解析輸入
string *cmd;                // 全域指標變數，儲存當前指令
string *liname;             // 全域指標變數，儲存清單名稱
string *name;               // 全域指標變數，儲存任務名稱或新清單名稱
string *category;           // 全域指標變數，儲存任務類別
string *type;               // 全域指標變數，儲存操作類型
string *value;              // 全域指標變數，儲存操作值
bool *completed;            // 全域指標變數，儲存任務完成狀態
bool *ascending;            // 全域指標變數，儲存排序順序
int *list_id;               // 全域指標變數，儲存清單 ID
int *task_id;               // 全域指標變數，儲存任務 ID
int *index1, *index2;       // 全域指標變數，儲存交換任務的索引

// Function declarations
void cmd_help();
void cmd_build_li();
void cmd_add();
void cmd_pr();
void cmd_prall();
void cmd_swId();
void cmd_cpy();
void cmd_merge();
void cmd_inter();
void cmd_chg();
void cmd_chgli();
void cmd_rm();
void cmd_sort();
void cmd_filter();
void cmd_clear();
void cmd_ls();
void processor(string& cmd);

int find_id_by_name(list<todos> &li, string &name)
{
    int id = 0;
    for (auto &l : li)
    {
        if (l.get_name() == name)
            return id;
        id++;
    }
    return -1;
}

void processor(string& cmd)
{
    ss->clear();
    ss->str(cmd);
    *ss >> cmd;

    if (cmd == "help")
    {
        cmd_help();
    }
    else if (cmd == "build_li" || cmd == "bui")
    {
        cmd_build_li();
    }
    else if (cmd == "add")
    {
        cmd_add();
    }
    else if (cmd == "pr")
    {
        cmd_pr();
    }
    else if (cmd == "prall")
    {
        cmd_prall();
    }
    else if (cmd == "swId")
    {
        cmd_swId();
    }
    else if (cmd == "cpy")
    {
        cmd_cpy();
    }
    else if (cmd == "merge")
    {
        cmd_merge();
    }
    else if (cmd == "inter")
    {
        cmd_inter();
    }
    else if (cmd == "chg")
    {
        cmd_chg();
    }
    else if (cmd == "chgli")
    {
        cmd_chgli();
    }
    else if (cmd == "rm")
    {
        cmd_rm();
    }
    else if (cmd == "sort")
    {
        cmd_sort();
    }
    else if (cmd == "filter")
    {
        cmd_filter();
    }
    else if (cmd == "ls")
    {
        cmd_ls();
    }
    else if (cmd == "clear")
    {
        cmd_clear();
    }
    else
    {
        cout << "Invalid command\n";
    }
}

void cmd_help()
{
    cout << "build_li (<name>)\n"
         << "add <list name> <name> <category> <completed>\n"
         << "pr <list name> <id>\n"
         << "prall <list name>\n"
         << "chg <list name> <id> <name/category> <new value>\n"
         << "chgli <list name> <new name>\n"
         << "swId <list name> <id1> <id2>\n"
         << "cpy <list name> <new name>\n"
         << "merge <list name1> <list name2> <new name>\n"
         << "inter <list name1> <list name2> <new name>\n"
         << "rm <list name> <type> <id/name/category>\n"
         << "rm list <list name>\n"
         << "sort <list name> <type> <ascending>\n"
         << "filter <list name> <category>\n"
         << "clear <list name> <id/all>\n"
         << "exit\n";
}

void cmd_build_li()
{
    *ss >> *name;
    for (auto &l : *li)
    {
        if (l.get_name() == *name)
        {
            cout << "List name already exists\n";
            return;
        }
    }
    li->push_back(todos(*name));
    cout << "built list " << *name << '\n';
}

void cmd_add()
{
    *ss >> *liname;
    auto it = find_if(li->begin(), li->end(), [&](todos &l) { return l.get_name() == *liname; });
    if (it == li->end())
    {
        cout << "Invalid list name\n";
        return;
    }
    while (*ss >> *name)
    {
        *ss >> *category >> *completed;
        it->add_task(new norm_task(*name, *category, *completed));
    }
}

void cmd_pr()
{
    *ss >> *liname;
    auto it = find_if(li->begin(), li->end(), [&](todos &l) { return l.get_name() == *liname; });
    if (it == li->end())
    {
        cout << "Invalid list name\n";
        return;
    }
    *ss >> *task_id;
    it->printtask(*task_id - 1);
}

void cmd_prall()
{
    while(*ss >> *liname)
    {
        auto it = find_if(li->begin(), li->end(), [&](todos &l) { return l.get_name() == *liname; });
        if (it == li->end())
        {
            cout << "Invalid list name\n";
            return;
        }
        it->printAll();
    }
}

void cmd_swId()
{
    *ss >> *liname;
    auto it = find_if(li->begin(), li->end(), [&](todos &l) { return l.get_name() == *liname; });
    if (it == li->end())
    {
        cout << "Invalid list name\n";
        return;
    }
    *ss >> *index1 >> *index2;
    it->switch_id(*index1 - 1, *index2 - 1);
}

void cmd_cpy()
{
    *ss >> *liname >> *name;
    auto it = find_if(li->begin(), li->end(), [&](todos &l) { return l.get_name() == *liname; });
    if (it == li->end())
    {
        cout << "Invalid list name\n";
        return;
    }
    for (auto &l : *li)
    {
        if (l.get_name() == *name)
        {
            cout << "List name already exists\n";
            return;
        }
    }
    li->push_back(todos(*name, *it));
    cout << "copied list " << *name << '\n';
}

void cmd_merge()
{
    *ss >> *liname >> *name;
    auto it1 = find_if(li->begin(), li->end(), [&](todos &l) { return l.get_name() == *liname; });
    auto it2 = find_if(li->begin(), li->end(), [&](todos &l) { return l.get_name() == *name; });
    if (it1 == li->end() || it2 == li->end())
    {
        cout << "Invalid list name\n";
        return;
    }
    *ss >> *name;
    for (auto &l : *li)
    {
        if (l.get_name() == *name)
        {
            cout << "List name already exists\n";
            return;
        }
    }
    li->push_back(*(it1->merge(*it2)));
    li->back().change_name(name);
    cout << "merged list " << *name << '\n';
}

void cmd_inter()
{
    *ss >> *liname >> *name;
    auto it1 = find_if(li->begin(), li->end(), [&](todos &l) { return l.get_name() == *liname; });
    auto it2 = find_if(li->begin(), li->end(), [&](todos &l) { return l.get_name() == *name; });
    if (it1 == li->end() || it2 == li->end())
    {
        cout << "Invalid list name\n";
        return;
    }
    *ss >> *name;
    for (auto &l : *li)
    {
        if (l.get_name() == *name)
        {
            cout << "List name already exists\n";
            return;
        }
    }
    li->push_back(*(it1->inter(*it2)));
    li->back().change_name(name);
    cout << "intersected list " << *name << '\n';
}

void cmd_chg()
{
    *ss >> *liname >> *task_id >> *type >> *value;
    auto it = find_if(li->begin(), li->end(), [&](todos &l) { return l.get_name() == *liname; });
    if (it == li->end())
    {
        cout << "Invalid list name\n";
        return;
    }
    if (*type == "name")
    {
        it->get_task(*task_id - 1)->change_name(*value);
    }
    else if (*type == "cate")
    {
        it->get_task(*task_id - 1)->change_category(*value);
    }
    else if (*type == "comp")
    {
        it->get_task(*task_id - 1)->change_completed(*value == "1");
    }
    else
    {
        cout << "Invalid type\n";
    }
}

void cmd_chgli()
{
    *ss >> *liname >> *name;
    auto it = find_if(li->begin(), li->end(), [&](todos &l) { return l.get_name() == *liname; });
    if (it == li->end())
    {
        cout << "Invalid list name\n";
        return;
    }
    for (auto &l : *li)
    {
        if (l.get_name() == *name)
        {
            cout << "List name already exists\n";
            return;
        }
    }
    it->change_name(name);
}

void cmd_rm()
{
    *ss >> *liname >> *type;
    auto it = find_if(li->begin(), li->end(), [&](todos &l) { return l.get_name() == *liname; });
    if (it == li->end())
    {
        cout << "Invalid list name\n";
        return;
    }

    if (*type == "list")
    {
        li->erase(it); // 移除清單
    }
    else if (*type == "id")
    {
        *ss >> *task_id;
        it->rm_taskWid(*task_id - 1);
    }
    else if (*type == "name")
    {
        *ss >> *value;
        it->rm_taskWname(*value);
    }
    else if (*type == "cate")
    {
        *ss >> *value;
        it->rm_taskWcate(*value);
    }
    else
    {
        cout << "Invalid type\n";
    }
}

void cmd_sort()
{
    *ss >> *liname >> *type >> *ascending;
    auto it = find_if(li->begin(), li->end(), [&](todos &l) { return l.get_name() == *liname; });
    if (it == li->end())
    {
        cout << "Invalid list name\n";
        return;
    }
    it->sort(*type, *ascending);
}

void cmd_filter()
{
    *ss >> *liname >> *category;
    auto it = find_if(li->begin(), li->end(), [&](todos &l) { return l.get_name() == *liname; });
    if (it == li->end())
    {
        cout << "Invalid list name\n";
        return;
    }
    todos temp(it->filter(*category));
    temp.printAll();
    li->push_back(temp);
    cout << "filtered list " << temp.get_name() << '\n';
}

void cmd_ls()
{
    cout << "List Name\n";
    for (auto &l : *li)
    {
        cout << l.get_name() << '\n';
    }
}

void cmd_clear()
{
    *ss >> *liname >> *type;
    auto it = find_if(li->begin(), li->end(), [&](todos &l) { return l.get_name() == *liname; });
    if (it == li->end())
    {
        cout << "Invalid list name\n";
        return;
    }
    if (*type == "id")
    {
        it->clear();
    }
    else if (*type == "all")
    {
        for (auto &l : *li)
        {
            l.clear();
        }
    }
}