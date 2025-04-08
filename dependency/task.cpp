#include "dependency.h"
#include <algorithm>
#include <sstream>
#include <memory>

using namespace std;

base_task::base_task(string name, string category, bool completed)
{
    this->name = new string(name);
    this->category = new string(category);
    this->completed = new bool(completed);
}

base_task::base_task(const base_task &t)
{
    name = new string(*t.name);
    category = new string(*t.category);
    completed = new bool(*t.completed);
}

norm_task::norm_task(string name, string category, bool completed) : base_task(name, category, completed)
{}
norm_task::norm_task(const base_task &t) : base_task(t)
{}

base_task* norm_task::clone() const
{
    return new norm_task(*this);
}



ostream &operator<<(ostream &os, base_task &t)
{
    t.output(os);
    return os;
}

void base_task::print()
{
    cout << *name << '\t'
        << *category << '\t'
        << ((*completed == true)? "Yes" : "No") << "\t\n";
}

void base_task::change_completed(bool ncompleted)
{*completed = ncompleted;}

void base_task::change_name(string& nname)
{*name = nname;}

void base_task::change_category(string& ncategory)
{*category = ncategory;}

bool base_task::get_completed()
{return *completed;}

string base_task::get_name()
{return *name;}

string base_task::get_category()
{return *category;}

base_task::~base_task()
{
    delete name;
    delete category;
    delete completed;
}

bool norm_task::operator<(base_task &t)
{
    return *name < (t.get_name());
}

bool norm_task::operator>(base_task &t)
{
    return *name > (t.get_name());
}
bool norm_task::operator==(base_task &t)
{
    norm_task* nt = dynamic_cast<norm_task*>(&t);
    if (nt == nullptr)
        return false;
    return (*name == *(nt->name) && *category == *(nt->category) && *completed == *(nt->completed));
}
bool norm_task::operator!=(base_task &t)
{
    norm_task* nt = dynamic_cast<norm_task*>(&t);
    if (nt == nullptr)
        return false;
    return (*name != *(nt->name) || *category != *(nt->category) || *completed != *(nt->completed));
}

void norm_task::output(ostream &os)
{
    os << *name << '\t'
        << *category << "\t\t"
        << ((*completed == true)? "Yes" : "No") << "\n";
}

string norm_task::to_commands(string& liname) const
{
    return "add "+ liname+ " " + *name + " " + *category + " " + (*completed == true ? "1" : "0");
}

special_task::special_task(string name, string category, bool completed, string left)
: base_task(name, category, completed)
{
    // parse yyyy/mm/dd;p
    unique_ptr<stringstream> ss(new stringstream(left));
    unique_ptr<string> ldate(new string);
    unique_ptr<string> lpiority(new string);
    getline(*ss, *ldate, ';');
    getline(*ss, *lpiority, ';');
    date = new string(*ldate);
    try {
        if (*lpiority == "")
            *lpiority = "0";
        piority = new int(stoi(*lpiority));
    } catch (const invalid_argument& e) {
        cerr << "Invalid argument for lpiority: " << *lpiority << endl;
        piority = new int(0); // Default to 0 if conversion fails
    } catch (const out_of_range& e) {
        cerr << "Out of range value for lpiority: " << *lpiority << endl;
        piority = new int(0); // Default to 0 if conversion fails
    }
}

special_task::special_task(const special_task &t) : base_task(t)
{
    date = new string(*t.date);
    piority = new int(*t.piority);
}

special_task::~special_task()
{
    delete date;
    delete piority;
}
base_task* special_task::clone() const
{
    return new special_task(*this);
}

void special_task::change_date(string& ndate)
{*date = ndate;}
void special_task::change_piority(int npiority)
{*piority = npiority;}

string special_task::get_date()
{return *date;}
int special_task::get_piority()
{return *piority;}

bool special_task::operator<(base_task &t)
{
    return *name < t.get_name();
}
bool special_task::operator>(base_task &t)
{
    return *name > t.get_name();
}
bool special_task::operator==(base_task &t)
{
    special_task* st = dynamic_cast<special_task*>(&t);
    if (st == nullptr)
        return false;
    return (*name == *(st->name) && *category == *(st->category) && *completed == *(st->completed) && *date == *(st->date) && *piority == *(st->piority));
}
bool special_task::operator!=(base_task &t)
{
    special_task* st = dynamic_cast<special_task*>(&t);
    if (st == nullptr)
        return true;
    return (*name != *(st->name) || *category != *(st->category) || *completed != *(st->completed) || *date != *(st->date) || *piority != *(st->piority));
}

void special_task::output(ostream &os)
{
    os << *name << '\t'
        << *category << "\t\t"
        << ((*completed == true)? "Yes" : "No") << "\t\t"
        << *date << "\t\t"
        << *piority << "\n";
}

string special_task::to_commands(string& liname) const
{
    return "addsp "+ liname+ " " + *name + " " + *category + " " + (*completed == true ? "1" : "0") + " " + *date + ";" + to_string(*piority);
}