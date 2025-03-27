#include <string>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

class base_task
{
protected:
    string *name;
    string *category;
    bool *completed;
public:
    base_task(string name, string category, bool completed);
    base_task(const base_task &t);
    virtual void print();
    virtual void change_completed(bool ncompleted);
    virtual void change_name(string& name);
    virtual void change_category(string& category);
    virtual bool get_completed();
    virtual string get_name();
    virtual string get_category();
    
    bool operator<(base_task &t);
    bool operator>(base_task &t);
    bool operator==(base_task &t);
    bool operator!=(base_task &t);
    friend ostream &operator<<(ostream &os, base_task &t);
    virtual ~base_task();
};

class norm_task : public base_task
{
public:
    norm_task(string name, string category, bool completed);
    norm_task(const base_task &t);
};

class list
{
protected:
    vector <base_task*>* tasks;
    string* name;
public:
    list();
    list(string* name);
    list(const list &l);
    list(string* name, const list &l);
    string& get_name();
    void change_name(string* name);
    void add_task(base_task *task);
    base_task* get_task(int index);
    void printAll();
    void printtask(int index);
    void switch_id(int index1, int index2);
    void rm_taskWid(int index);
    void rm_taskWname(string name);
    void rm_taskWcate(string category);
    void sort(const string type, const bool ascending);
    list filter(const string category);
    void clear();
    list operator+(list &l);
    list operator&(list &l);

    ~list();
};