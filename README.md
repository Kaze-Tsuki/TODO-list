# Instruction of todo list

## test cases

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
```
</details>

<details>
<summary>Advanced merge/intersect</summary>

```
build_li a
add a task1 norm 1
add a task1 norm 0
add a task2 emer 1
cpy a b
add b task no 0
merge a b merged
inter a b intersect
prall a
prall b
prall merged
prall intersect
```
</details>