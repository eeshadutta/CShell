## RUNNING THE SHELL

run ```make``` to generate the executable
run ```./shell``` to run the shell
run ```quit``` to exit the shell


## FEATURES

Supports common shell commands and foreground/background processes.

#### ls 
- ls takes arguments as flags (as -<flagname>) and directories (as <directory name>)
- It lists the files of the directory mentioned. If no directory is mentioned, it lists the files in the current directory

* "ls" - lists in alphabetical order
* "ls -l" - long list
* "ls -a" - display hidden files
* "ls -al/-la/-a -l/-l -a" - long list including hidden files

#### cd
* "cd <absolute path>" - goes to absolute path
* "cd" - goes to ~/
* "cd ~/<pathname>" - goes to ~/<pathname>
* "cd .." - goes to previous directory
* "cd ." - stays in the same directory

#### echo
* "echo" - prints empty line
* "echo text" - prints text
* "echo "text"" / "echo 'text'" - prints text

#### pwd
* "pwd" - prints absolute path of current directory

#### pinfo
* "pinfo" - prints process info of the shell
* "pinfo <pid>" - prints process info of given pid
