# Instruction of TODO List

## Catalog

- [Command Summary](#cs)
- [data structure](#ds)
- [test cases](#tc)
- how to run

<h2 id = "cs">Command Summary </h2>

### Basic Commands

#### `help` : show all commands

#### `build_li <name>`
create a new list with the given name
<details><summary>Support</summary>
*Enable multi paraments*
</details>


#### `add <name> <task>`
add a new task to the list with the given name.

<details><summary>Support</summary>
add [li_name] [task]

[task] = [name] [category] [completeness]

*Enable multi paraments*
</details>

#### `addsp <name> <task> <date;piority>`
add a new task to the list with the given name.

<details><summary>add special task</summary>
add [li_name] [task] [date;=piority]
</details>

#### `pr <list> <id>` 
print the task with the given id in the list.

#### `prall <list>` 
print all tasks in the list.
<details><summary>print all tasks</summary>
prall [list] [list] ...

*Enable multi paraments* 
</details>

#### `swId <list> <id1> <id2>`
swap the tasks with the given ids in the list.

#### `cpy <list> <new_list>`: copy the list with the given name to a new list.

#### `rm <list> <type> <value>`
remove the tasks in the list with the given type and value.

<details><summary>Example</summary>
rm $list list

rm $list id 1

rm $list name $name

rm $list cate $category
</details>


#### `clear <type> <list name>`
clear the list.
<details><summary>Support</summary>
type = list, all

clear all the tasks without removing the list.
</details>

#### `chg <list> <id> <type> <value>`
change the task with the given id in the list.

#### `chgli <list> <new name>`
change the list with the given name to a new list.

### Advanced Commands

#### `sort <list> <type> <order>`
sort the tasks in the list with the given type and order.
<details><summary>Support</summary>
type = name, cate, comp

order = 0, 1 (if not given, default is 0)
</details>

#### `filter <list> <type>`
filter the tasks in the list with category.

#### `merge <list1> <list2> <new_list>`
merge the two lists into a new list.
<details><summary>Notice</summary>
All tasks must be unique in the new list.

-> No duplicate tasks in the new list.

-> No tasks will have all same attributes.

*auto sorted*
</details>

#### `inter <list1> <list2> <new_list>`
intersect the two lists into a new list.

#### `define <cmd name> <num of parameters>`
define a new command.
<details><summary>Example</summary>
define mycmd 4

inter 1 2 3

merge 1 2 4

prall 3 4

end

**Legal: add 1 2 3 4**

**Illegal: add 1 task sleep 1**
</details>

#### `exec <cmd name>`
execute the command defined by `define`.
<details><summary>Example</summary>
exec mycmd a b c d
</details>

#### `usercmd` 
show all user defined commands.

#### `exit` : exit the program.

<h2 id = "ds">Data Structure</h2>

### List

Store a list of tasks.
```cpp
struct Todo {
    string name; // list name
    vector<Task*> tasks; // tasks in the list
};
```
**Note**:

`vector<Task*>` enable Polymorphism for task.

### Task

include all attr of task.
```cpp
struct Task {
    string name; // task name
    string cate;
    int comp;
    int piority;
    string date;
};
```
**Note**:

`comp` 0 means not completed, 1 means completed.

`date` Has no restrictions.

### List<todo>
Using list for vector can't store class of pointers.
[vector iterator validility](https://cplusplus.com/reference/vector/vector/erase/#validity)

I fix the leak bug for 6 hours and find that vector doesn't fit the object, so use list instead.

### Custom Command

combined one command and its following params
```cpp
struct UserCmd {
    vector<pair<string, vector<int>>> commandList; // command and its corresponding params
    string name; // new command name
    int numParams; // num of parameters
};
```


<h2 id = "tc">Test Cases</h2>

<details>
<summary>basic add/del/view</summary>

```
build_li First
add First task1 test 0
add First task2 test 1
add First task3 test 0
prall First
swId First 2 3
add First new nothing 0
prall First
chg First 4 comp 1
sort First name
prall First
sort First cate
prall First
sort First comp 1
prall First
sort First name 0
prall First
filter First test
prall First-test
rm First-test cate test
rm First name new
rm First id 4
prall First
prall First-test
rm First list
add First task again 1
add First-test task again 1
prall First-test
```
</details>

<details>
<summary>basic copy/edit</summary>

```
build_li a
add a new task 1
cpy a b
prall b
chg b 1 name newname
chg b 1 cate newtask
chg b 1 comp 0
chgli b newb
prall newb
rm a list
```
</details>

<details>
<summary>Advanced merge/intersect</summary>

```
build_li a
add a task1 norm 1 task1 norm 0 task2 emer 1
add a
cpy a b
add b task no 0
merge a b merged
inter a b intersect
prall a
prall b
prall merged
prall intersect
rm a list
rm b list
prall merged intersect
```
</details>