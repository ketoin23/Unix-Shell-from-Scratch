# Unix-Shell-from-Scratch
Implemented a UNIX shell in C with the following builtin functions :

cd<br>
help<br>
exit

System calls and functions used :

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

## How to run the Shell
compile : 
```
gcc -o main main.c
```
run : 
```
./main
```
