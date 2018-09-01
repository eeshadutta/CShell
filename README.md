## RUNNING THE SHELL

run `make` to generate the executable

run `./shell` to run the shell

run `quit` to exit the shell


## FEATURES

#### Foreground processes
- The shell waits for the current process to execute

#### Background processes
- Use '&' at the end of any command to invoke a background process
- The process will then run in the background and when exited, a message will be displayed

#### ls command
- ls takes arguments as flags (as -<flagname>) and directories (as <directory name>)
- It lists the files of the directory mentioned. If no directory is mentioned, it lists the files in the current directory
- `ls` - lists in alphabetical order
- `ls -l` - long list
- `ls -a` - display hidden files
- `ls -al/-la/-a -l/-l -a` - long list including hidden files

#### cd command
- `cd <absolute path>` - goes to absolute path
- `cd` - goes to ~/
- `cd ~/<pathname>` - goes to ~/<pathname>
- `cd ..` - goes to previous directory
- `cd .` - stays in the same directory

#### echo command
- `echo` - prints empty line
- `echo text` - prints text
- `echo "text"` / `echo 'text'` - prints text

#### pwd command
- `pwd` - prints absolute path of current directory

#### pinfo command
- `pinfo` - prints process info of the shell
- `pinfo <pid>` - prints process info of given pid


## ADITIONAL FEATURES

#### reminder
- type `remindme <no of seconds> "task"` to set a reminder

#### clock
- type `clock -t <interval time> -n <duration>` to display the date and time after specified interval and for the specified duration
- made using hardware clock "/sys/class/rtc/rtc0"
