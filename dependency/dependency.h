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
    virtual base_task* clone() const = 0; // Pure virtual function for cloning
    virtual ~base_task();
};

class norm_task : public base_task
{
public:
    norm_task(string name, string category, bool completed);
    norm_task(const base_task &t);
    virtual base_task* clone() const override;
};

class todos
{
protected:
    vector <base_task*>* tasks;
    string* name;
public:
    todos(string name);
    todos(const todos &l);
    todos(const string name, const todos &l);
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
    todos filter(const string category);
    void clear();
    todos* merge(todos &l);
    todos* inter(todos &l);

    ~todos();
};