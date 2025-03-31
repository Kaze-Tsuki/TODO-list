#include <iostream>
#include <string>
#include <sstream>
#include <list> // 改為使用 std::list
#include <algorithm> // For std::find_if
#include <map>
#include <typeinfo>
#include <fstream> // For std::ofstream
#include "dependency/dependency.h"
#include "dependency/cmd_set.h"

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
string *completed;            // 全域指標變數，儲存任務完成狀態
bool *ascending;            // 全域指標變數，儲存排序順序
int *list_id;               // 全域指標變數，儲存清單 ID
int *task_id;               // 全域指標變數，儲存任務 ID
int *index1, *index2;       // 全域指標變數，儲存交換任務的索引
list<CommandCustomizer> *customs;

// Function declarations
void cmd_help();
void cmd_build_li();
void cmd_add();
void cmd_addsp();
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
void delete_cmd();
void customize_cmd();
void execute_cmd();
void cmd_userdefined();
void cmd_store();
void cmd_load();

int find_id_by_name(list<todos> &li, string &name)
{
    int* id = new int(0);
    for (auto &l : li)
    {
        if (l.get_name() == name)
            return *id;
        (*id)++;
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
    else if (cmd == "addsp")
    {
        cmd_addsp();
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
    else if (cmd == "define")
    {
        customize_cmd();
    }
    else if (cmd == "exec")
    {
        execute_cmd();
    }
    else if (cmd == "rmcmd")
    {
        delete_cmd();
    }
    else if (cmd == "usercmd")
    {
        cmd_userdefined();
    }
    else if (cmd == "store")
    {
        cmd_store();
    }
    else if (cmd == "load")
    {
        cmd_load();
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
            << "addsp <list name> <name> <category> <completed> <date;=piority>\n"
         << "pr <list name> <id>\n"
         << "prall <list name>\n"
         << "chg <list name> <id> <name/category> <new value>\n"
         << "chgli <list name> <new name>\n"
         << "swId <list name> <id1> <id2>\n"
         << "cpy <list name> <new name>\n"
         << "merge <list name1> <list name2> <new name>\n"
         << "inter <list name1> <list name2> <new name>\n"
         << "rm <list name> <type> <id/name/category>\n"
         << "rm <list name> list\n"
         << "sort <list name> <type> <ascending>\n"
         << "filter <list name> <type> <category> <new name>\n"
         << "clear <id/all> <list name>\n"
         << "ls\n"
         << "define <command name> <number of parameters>\n"
         << "exec <command name> <args>\n"
         << "usercmd\n"
         << "store <filename>\n"
         << "load <filename>\n"
         << "exit\n";
}

void cmd_build_li()
{
    while(*ss >> *name)
    {
        for (auto &l : *li)
        {
            if (l.get_name() == *name)
            {
                cout << "List name already exists\n";
                return;
            }
        }
        li->emplace_back(*name); // 使用 emplace_back 直接在容器中構造物件
        cout << "built list " << *name << '\n';
    }
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
        it->add_task(new norm_task(*name, *category, *completed == "1" || *completed == "yes"));
    }
}

void cmd_addsp()
{
    *ss >> *liname;
    auto it = find_if(li->begin(), li->end(), [&](todos &l) { return l.get_name() == *liname; });
    if (it == li->end())
    {
        cout << "Invalid list name\n";
        return;
    }
    *ss >> *name >> *category >> *completed >> *value;
    it->add_task(new special_task(*name, *category, *completed == "1" || *completed == "yes", *value));
    
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
    li->emplace_back(*name, *it);
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
    li->emplace_back(*(it1->merge(*it2)));
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
    li->emplace_back(*(it1->inter(*it2)));
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
    else if (*type == "date")
    {
        if (typeid(*it->get_task(*task_id - 1)) == typeid(special_task))
        {
            (dynamic_cast<special_task*>(it->get_task(*task_id - 1)))->change_date(*value);
        }
        else
        {
            cout << "Invalid type\n";
        }
    }
    else if (*type == "piority")
    {
        if (typeid(*it->get_task(*task_id - 1)) == typeid(special_task))
        {
            (dynamic_cast<special_task*>(it->get_task(*task_id - 1)))->change_piority(stoi(*value));
        }
        else
        {
            cout << "Invalid type\n";
        }
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
    *name = "";
    *ss >> *liname >> *type >> *category >> *name;
    auto it = find_if(li->begin(), li->end(), [&](todos &l) { return l.get_name() == *liname; });
    if (it == li->end())
    {
        cout << "Invalid list name\n";
        return;
    }
    auto temp = it->filter(*type, *category);
    if (temp == nullptr)
    {
        delete temp;
        return;
    }
    li->emplace_back(*temp);
    delete temp; // 釋放記憶體
    if (*name != "")
        li->back().change_name(name);
    cout << "Filtered list " << *liname << '\n';
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
    *ss >> *type >> *liname;
    auto it = find_if(li->begin(), li->end(), [&](todos &l) { return l.get_name() == *liname; });
    if (it == li->end() && *type != "all")
    {
        cout << "Invalid list name\n";
        return;
    }
    if (*type == "list")
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

void delete_cmd()
{
    *ss >> *liname;
    auto it = find_if(customs->begin(), customs->end(), [&](CommandCustomizer &l) { return l.get_name() == *liname; });
    if (it == customs->end())
    {
        cout << "Invalid command name\n";
        return;
    }
    customs->erase(it); // 移除自定義命令
}

void customize_cmd()
{
    getline(*ss, *liname);
    try
    {
        customs->emplace_back(*liname); // Use emplace_back to construct in-place
        cout << "Custom command created\n";
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void execute_cmd()
{
    *ss >> *cmd;
    vector<string> *args = new vector<string>();
    string *arg = new string();
    while (*ss >> *arg)
    {
        args->push_back(*arg);
    }
    try
    {
        for (auto &custom : *customs)
        {
            if (custom.get_name() == *cmd)
            {
                stringstream *result = new stringstream(custom.execute(*args));
                string *line = new string();
                while (getline(*result, *line))
                {
                    cout << *line << '\n';
                    processor(*line);
                }
                return;
            }
        }
        cout << "Command not found\n";
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void cmd_userdefined()
{
    if (customs->size() == 0)
    {
        cout << "No custom command\n";
        return;
    }
    cout << "custom command Name\n";
    for (auto &l : *customs)
    {
        cout << l.get_name() << ";\tpara: "<< l.get_numParams() << '\n';
    }
}

void cmd_store()
{
    *ss >> *name;
    ofstream *file = new ofstream();
    file->open(*name + ".txt", ios::out | ios::trunc);
    if (!file->is_open())
    {
        cout << "Failed to open file\n";
        return;
    }
    for (auto &l : *li)
    {
        *file << l.to_commands();
    }
    file->close();
    delete file;
}

void cmd_load()
{
    *ss >> *name;
    ifstream *file = new ifstream();
    file->open(*name + ".txt", ios::in);
    if (!file->is_open())
    {
        cout << "Failed to open file\n";
        return;
    }
    string* line = new string();
    while (getline(*file, *line))
    {
        processor(*line);
    }
    file->close();
    delete file;
    delete line;
}