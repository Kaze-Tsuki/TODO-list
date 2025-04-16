#include <string>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

#ifndef _TASK_H
#define _TASK_H

class base_task
{
protected:
    string *name;
    string *category;
    bool *completed;
public:
    base_task(string* name, string* category, bool* completed);
    base_task(const base_task *t);
    virtual string to_commands(string& liname) const = 0;
    virtual void change_completed(bool ncompleted);
    virtual void change_name(string& name);
    virtual void change_category(string& category);
    virtual bool get_completed();
    virtual string get_name();
    virtual string get_category();
    
    virtual bool operator<(base_task &t) = 0;
    virtual bool operator>(base_task &t) = 0;
    virtual bool operator==(base_task &t) = 0;
    virtual bool operator!=(base_task &t) = 0;
    friend ostream &operator<<(ostream &os, base_task &t);
    virtual void output(ostream &os) = 0;
    virtual base_task* clone() const = 0; // Pure virtual function for cloning
    virtual ~base_task();
};

class norm_task : public base_task
{
public:
    norm_task(string* name, string* category, bool* completed);
    norm_task(const base_task *t);
    virtual bool operator<(base_task &t) override;
    virtual bool operator>(base_task &t) override;
    virtual bool operator==(base_task &t) override;
    virtual bool operator!=(base_task &t) override;
    virtual base_task* clone() const override;
    virtual void output(ostream &os) override;
    virtual string to_commands(string& liname) const override;
};

class special_task : public base_task
{
protected:
    string *date;
    int *piority;
public:
    special_task(string* name, string* category, bool* completed, string* left);
    special_task(const special_task *t);
    virtual base_task* clone() const override;
    virtual bool operator<(base_task &t) override;
    virtual bool operator>(base_task &t) override;
    virtual bool operator==(base_task &t) override;
    virtual bool operator!=(base_task &t) override;
    void change_date(string& date);
    void change_piority(int piority);
    string get_date();
    int get_piority();
    ~special_task();
    virtual void output(ostream &os) override;
    virtual string to_commands(string& liname) const override;
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
    void printtask(int* index);
    void switch_id(int* index1, int* index2);
    void rm_taskWid(int* index);
    void rm_taskWname(string* name);
    void rm_taskWcate(string* category);
    void sort(const string* type, const bool* ascending);
    todos* filter(const string type, const string category);
    void clear();
    todos* merge(todos &l);
    todos* inter(todos &l);
    string to_commands();

    ~todos();
};

#endif