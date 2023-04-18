Project Title: 0x16. C - Simple Shell

Description
This is a collaborative project by Rohan Sewraj and Shaline Msole, which is part of the curriculum for the Holberton School Full Stack Software Engineering program. It involves creating a simple shell program in C that emulates the basic functionalities of the Unix shell, such as executing commands, managing processes, and handling I/O redirection.

Learning Objectives
At the end of this project, we are expected to be able to explain, without the help of Google, the following concepts:

Who designed and implemented the original Unix operating system
Who wrote the first version of the UNIX shell
Who invented the B programming language (the direct predecessor to the C programming language)
Who is Ken Thompson
How does a shell work
What is a pid and a ppid
How to manipulate the environment of the current process
What is the difference between a function and a system call
How to create processes
What are the three prototypes of main
How does the shell use the PATH to find the programs
How to execute another program with the execve system call
How to suspend the execution of a process until one of its children terminates
What is EOF / "end-of-file"?

Requirements
General requirements for the project are as follows:

Allowed editors: vi, vim, emacs
All files will be compiled on Ubuntu 20.04 LTS using gcc, with the options -Wall -Werror -Wextra -pedantic -std=gnu89
All files should end with a new line
A README.md file at the root of the project folder is mandatory
Code should use the Betty style and will be checked using betty-style.pl and betty-doc.pl
The shell should not have any memory leaks
No more than 5 functions per file
All header files should be include guarded
Use system calls only when necessary
Write a README with the description of the project
An AUTHORS file should be included at the root of the repository, listing all individuals who have contributed content to the repository
Output
Unless specified otherwise, the program must have the exact same output as the /bin/sh shell, including error output. The only difference is when printing an error, the name of the program must be equivalent to argv[0] of the shell.

Example of error with /bin/sh:

bash
Copy code
$ echo "qwerty" | /bin/sh
/bin/sh: 1: qwerty: not found
$ echo "qwerty" | /bin/../bin/sh
/bin/../bin/sh: 1: qwerty: not found
Same error with our program hsh:

bash
Copy code
$ echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found
$ echo "qwerty" | ./././hsh
./././hsh: 1: qwerty: not found

List of allowed functions and system calls

access (man 2 access)
chdir (man 2 chdir)
close (man 2 close)
closedir (man 3 closedir)
execve (man 2 execve)
exit (man 3 exit)
_exit (man 2 _exit)
fflush (man 3 fflush)
fork (man 2 fork)
free (man 3 free)
getcwd (man 3 getcwd)
getline (man 3 getline)
getpid (man 2 getpid)
isatty (man 3 isatty)
kill (man 2 kill)
malloc (man 3 malloc)
open (man 2 open)
opendir (man 3 opendir)
perror (man 3 perror)
read (man 2 read)
readdir (man 3 readdir)
signal (man 2 signal)
stat (__xstat) (man 2 stat)
lstat (__lxstat) (man 2 lstat)
fstat (__fxstat) (man 2 fstat)
strtok (man 3 strtok)
wait (man 2 wait)
waitpid (man 2 waitpid)
wait3 (man 2 wait3)
wait4 (man 2 wait4)
write (man 2 write)

Compilation
Your shell will be compiled this way:

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

Checks
The Checker will be released at the end of the project (1-2 days before the deadline). We strongly encourage the entire class to work together to create a suite of checks covering both regular tests and edge cases for each task. See task 8. Test suite.
