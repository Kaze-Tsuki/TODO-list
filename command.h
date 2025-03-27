#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include "dependency/dependency.h"

using namespace std;

// Global variables
vector<list> *li;           // 全域指標變數，儲存所有清單
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
void processor(string& cmd);

int find_id_by_name(vector<list> &li, string &name)
{
    for (int i = 0; i < li.size(); i++)
    {
        if (li[i].get_name() == name)
            return i;
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
    else if (cmd == "build_li")
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
    if (find_id_by_name(*li, *name) != -1)
    {
        cout << "List name already exists\n";
        return;
    }
    li->push_back(list(name));
    cout << "built list " << *name << " id: " << li->size() - 1 << '\n';
}

void cmd_add()
{
    *ss >> *liname;
    *list_id = find_id_by_name(*li, *liname);
    if (*list_id == -1)
    {
        cout << "Invalid list name\n";
        return;
    }
    *ss >> *name >> *category >> *completed;
    (*li)[*list_id].add_task(new norm_task(*name, *category, *completed));
}

void cmd_pr()
{
    *ss >> *liname;
    *list_id = find_id_by_name(*li, *liname);
    if (*list_id == -1)
    {
        cout << "Invalid list name\n";
        return;
    }
    *ss >> *task_id;
    (*li)[*list_id].printtask(*task_id - 1);
}

void cmd_prall()
{
    *ss >> *liname;
    *list_id = find_id_by_name(*li, *liname);
    if (*list_id == -1)
    {
        cout << "Invalid list name\n";
        return;
    }
    (*li)[*list_id].printAll();
}

void cmd_swId()
{
    *ss >> *liname;
    *list_id = find_id_by_name(*li, *liname);
    if (*list_id == -1)
    {
        cout << "Invalid list name\n";
        return;
    }
    *ss >> *index1 >> *index2;
    (*li)[*list_id].switch_id(*index1 - 1, *index2 - 1);
}

void cmd_cpy()
{
    *ss >> *liname >> *name;
    *list_id = find_id_by_name(*li, *liname);
    if (*list_id == -1)
    {
        cout << "Invalid list name\n";
        return;
    }
    if (find_id_by_name(*li, *name) != -1)
    {
        cout << "List name already exists\n";
        return;
    }
    
    li->push_back(list(name, (*li)[*list_id]));
    cout << "copied list id: " << li->size() - 1 << '\n';
}

void cmd_merge()
{
    *ss >> *liname >> *name;
    *index1 = find_id_by_name(*li, *liname);
    *index2 = find_id_by_name(*li, *name);
    if (*index1 == -1 || *index2 == -1)
    {
        cout << "Invalid list name\n";
        return;
    }
    *ss >> *name;
    if (find_id_by_name(*li, *name) != -1)
    {
        cout << "List name already exists\n";
        return;
    }
    li->push_back(list(name, (*li)[*index1] + (*li)[*index2]));
    cout << "merged list id: " << li->size() - 1 << '\n';
}

void cmd_inter()
{
    *ss >> *liname >> *name;
    *index1 = find_id_by_name(*li, *liname);
    *index2 = find_id_by_name(*li, *name);
    if (*index1 == -1 || *index2 == -1)
    {
        cout << "Invalid list name\n";
        return;
    }
    *ss >> *name;
    if (find_id_by_name(*li, *name) != -1)
    {
        cout << "List name already exists\n";
        return;
    }
    li->push_back(list(name, (*li)[*index1] & (*li)[*index2]));
    cout << "intersected list id: " << li->size() - 1 << '\n';
}

void cmd_chg()
{
    *ss >> *liname >> *task_id >> *type >> *value;
    *list_id = find_id_by_name(*li, *liname);
    if (*list_id == -1)
    {
        cout << "Invalid list name\n";
        return;
    }
    if (*type == "name")
    {
        (*li)[*list_id].get_task((*task_id) - 1)->change_name(*value);
    }
    else if (*type == "cate")
    {
        (*li)[*list_id].get_task((*task_id) - 1)->change_category(*value);
    }
    else if (*type == "comp")
    {
        (*li)[*list_id].get_task((*task_id) - 1)->change_completed(*value == "1");
    }
    else
    {
        cout << "Invalid type\n";
    }
}

void cmd_chgli()
{
    *ss >> *liname >> *name;
    *list_id = find_id_by_name(*li, *liname);
    if (*list_id == -1)
    {
        cout << "Invalid list name\n";
        return;
    }
    if (find_id_by_name(*li, *name) != -1)
    {
        cout << "List name already exists\n";
        return;
    }
    (*li)[*list_id].change_name(name);
}

void cmd_rm()
{
    *ss >> *liname >> *type;
    *list_id = find_id_by_name(*li, *liname);
    if (*list_id == -1)
    {
        cout << "Invalid list name\n";
        return;
    }
    if (*type == "id")
    {
        *ss >> *task_id;
        (*li)[*list_id].rm_taskWid(*task_id - 1);
    }
    else if (*type == "name")
    {
        *ss >> *value;
        (*li)[*list_id].rm_taskWname(*value);
    }
    else if (*type == "cate")
    {
        *ss >> *value;
        (*li)[*list_id].rm_taskWcate(*value);
    }
    else if (*type == "list")
    {
        li->erase(li->begin() + *list_id);
    }
    else
    {
        cout << "Invalid type\n";
    }
}

void cmd_sort()
{
    *ss >> *liname >> *type >> *ascending;
    *list_id = find_id_by_name(*li, *liname);
    if (*list_id == -1)
    {
        cout << "Invalid list name\n";
        return;
    }
    (*li)[*list_id].sort(*type, *ascending);
}

void cmd_filter()
{
    *ss >> *liname >> *category;
    *list_id = find_id_by_name(*li, *liname);
    if (*list_id == -1)
    {
        cout << "Invalid list name\n";
        return;
    }
    list temp((*li)[*list_id].filter(*category));
    temp.printAll();
    li->push_back(temp);
    cout << "filtered list id: " << li->size() - 1 << '\n';
}

void cmd_clear()
{
    *ss >> *liname >> *type;
    *list_id = find_id_by_name(*li, *liname);
    if (*list_id == -1)
    {
        cout << "Invalid list name\n";
        return;
    }
    if (*type == "id")
    {
        (*li)[*list_id].clear();
    }
    else if (*type == "all")
    {
        for (int i = 0; i < li->size(); i++)
        {
            (*li)[i].clear();
        }
    }
}