# TODO List

<br>
<div>
    <img alt="C++" src="https://img.shields.io/badge/C++-17-%2300599C?logo=cplusplus">
</div>
<div>
    <img alt="platform" src="https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-blueviolet">
</div>
<div>
    <img alt="commit" src="https://img.shields.io/github/commit-activity/m/Kaze-Tsuki/TODO-list?color=%23ff69b4">
</div>
<div>
    <a href="https://github.com/Kaze-Tsuki/TODO-list">
    <img alt="Static Badge" src="https://img.shields.io/badge/GitHub-Link-%23B766AD"></a>

</div>
<br>

## Catalog

- [Command Summary](#cs)
- [Data Structure](#ds)
- [How to Run](#compile)
- [Test Cases](#tc)

<h2 id = "cs">Command Summary </h2>

### Basic Commands

#### `help` 
show all commands

#### `build_li <name>`
create a new list with the given name
<details><summary>Support</summary>

No format restriction for name.

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
add a new special task to the list with the given name and properties.

#### `pr <list> <id>` 
print the task with the given id in the list.

#### `prall <list>` 
print all tasks in the list.

*Enable multi paraments* 

#### `swId <list> <id1> <id2>`
swap the tasks with the given ids in the list.

#### `cpy <list> <new_list>`
copy the list with the given name to a new list.

#### `rm <list> <type> <value>`
remove the tasks in the list with the given type and value.

<details><summary>Example</summary>

rm $list$ list

rm $list$ id $id$

rm $list$ name $name$

rm $list$ cate $category$
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

#### `filter <list> <type> <value> <new_list>`
filter the tasks in the list with category.
<details><summary>Support</summary>
type = name, cate, comp, date, piority

comp value = 1(yes), otherwise no

date, piority support compare.

compare value "b" + "the value", like piority b15 or date b2023-10-01.

If not given 'b'(bigger), default is smaller.

new list is optional. If not given, the value will be \<list>-\<value>.
</details>

#### `merge <list1> <list2> <new_list>`
merge the two lists into a new list.
<details><summary>Notice</summary>
All tasks must be unique in the new list.

-> No duplicate tasks in the new list.

-> No tasks will have all same attributes.
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

**Note**: num of parameters must be the same as defined.
</details>

#### `usercmd` 
show all user defined commands.

#### `rmcmd <cmd name>`
remove the user defined command.

#### `store <file name>`
store all lists to a file.

*file name don't need .txt end*

#### `load <file name>`
load all lists from a file.

*file name don't need .txt end*

#### `exit` : exit the program.

<h2 id = "ds">Data Structure</h2>

### Todo List

Store a list of tasks.
```cpp
class Todo {
    string name; // list name
    vector<Task*> tasks; // tasks in the list
};
```
**Note**:

`vector<Task*>` enable Polymorphism for task.

### Task

include all attr of task.
```cpp
class Task {
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

`piority` and `date` are attributes of special tasks.

### List of Todo List
Using list for vector can't store class of pointers.

I fix the leak bug for 6 hours and find that vector doesn't fit the object, so use list instead.

### Custom Command

combined one command and its following params
```cpp
class UserCmd {
    vector<pair<string, vector<int>>> commandList; // command and its corresponding params
    string name; // new command name
    int numParams; // num of parameters
};
```

<h2 id = "compile">How to run</h2>

### 📌 Dependencies
- C++17 or later
- CMake (Recommended for Windows: [CMake](https://cmake.org/))
- GNU Make (Linux/macOS)
- MinGW or MSVC (Windows)

### Linux/MacOS

```bash
make clean
make
```

### Windows

Method 1: use CMake
```shell
mkdir build
cd build
cmake ..
cmake --build .
```

Create a `CMakeLists.txt` file in the workspace with the following content:
```cmake
cmake_minimum_required(VERSION 3.10)
project(TODO-list)

set(CMAKE_CXX_STANDARD 17) # Set C++ version

# Specify the directory for header files (already included in .cpp files)
include_directories(./)

# Add .cpp files from the dependency directory
add_executable(todo 
    main.cpp 
    dependency/list.cpp 
    dependency/task.cpp
)
```

Method 2: Use `mingw-make`
```shell
mingw32-make
```

<h2 id = "tc">Test Cases</h2>

### Basic Commands

<details><summary>Add View Edit</summary>

```
bui a b
add a task norm 1 task1 norm 0
add b task2 norm 0 task3 essential yes
prall a b
chg a 1 name task4
chg a 1 cate essential
chg b 1 comp 1
chgli a new_name
prall new_name b
exit
```
</details>

<details><summary>Copy Remove Special</summary>

```
bui a
add a task1 norm 0
addsp a task2 norm 0 2023-10-01;1
addsp a task3 esse 0 2023-10-02;2
cpy a b
chg b 2 piority 10
prall a b
rm a id 1
rm b cate norm
rm a name task2
add b task1 esse 0
swId b 1 2
prall a b
rm a list
prall b a
exit
```
</details>

### Advanced Commands

<details><summary>Store Load</summary>

```
bui a
add a task1 norm 1 task2 norm 0 task3 esse 0
addsp a task4 esse 0 2023-10-01;1
addsp a task5 esse 1 2023-10-02;2
store test
exit
```
***
(start a new session)  
```
load test
prall a
exit
```
</details>

<details><summary>Sort Filter</summary>

```
load test
sort a name 0
filter a cate esse b
sort b piority 1
filter a comp 1 c
sort a date 0
filter a date b2023-10-01 d
prall a d
exit
```
</details>

<details><summary>Merge Intersect</summary>

```
load test
bui b
add b task1 norm 1 task4 esse 1
addsp b task4 esse 0 2023-10-31;3
addsp b task5 esse 1 2023-10-02;2
store test
merge a b c
prall c
inter a b d
prall d
exit
```
</details>


<details><summary>Custom Command</summary>

```
load test
define mycmd 4
merge 1 2 3
inter 1 2 4
end
exec mycmd a b c d
usercmd
rmcmd mycmd
usercmd
exit
```
</details>
