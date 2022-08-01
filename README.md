# Unix-Shell-from-Scratch
Implemented a UNIX shell using standard C libraries and system calls.<br>

**Method** : There are two type of commands to be processed, internal and external commands, to get the external commands process started we use the fork() system call, when this function is called the operating system makes a duplicate of the process and starts them both running. The original process is called the “parent”, and the new one is called the “child”. Then exec() system call is used to execute another process on the cloned process, and waitpid is used to let the child process finish before moving on for further use of the shell.

**builtin functions** :

cd<br>
help<br>
exit

System calls and functions used :
```
fork() : For Creating new processes<br>
exec() : Replaces the current running process with new process<br>
execvp() : variatn of exec(), takes array(vector) of string arguments as input<br>
chdir() : Change the current working directory<br>
pid_t : Signed integer data type capable of representing a process id<br>
waitpid() : Suspends execution of the current process until a child specified by pid argument has changed state<br>
malloc() : Memory allocation<br>
realloc() : Resize memory block allocated<br>
free() : deallocates the memory previously allocated<br>
exit() : Terminates process<br>
strcmp() : Compares two strings<br>
strtok() : Breaks string into a series of tokens based on delimiter
```
## How to run the Shell
compile : 
```
gcc -o main main.c
```
run : 
```
./main
```
