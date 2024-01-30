# 42-pipex
Pipex is a project that re-creates in C the way two commands are piped together via `|` in the shell

```bash
pipe()
 |
 |-- fork()
      |
      |-- child // cmd1
      :     |--dup2()
      :     |--close fd[0]
      :     |--execve(cmd1)
      :
      |-- parent // cmd2
      :     |--dup2()
      :     |--close fd[1]
      :     |--execve(cmd2)
 
# pipe() sends the output of the first execve() as input to the second execve()
# fork() runs two processes (i.e. two commands) in one single program
# dup2() swaps our files with stdin and stdout
 ```

</br>

# Content

1. [Installation](#installation)
2. [Description](#description)
3. [Algorithm](#algorithm)

</br>

## Installation

Follow the steps below to test the project: 

1. Clone the repository:
```bash
$> git clone https://github.com/Sepahsalar/42-pipex.git
```
2. Compile the project:
```bash
$> make
```
3. Run the program with the following syntax:
```bash
$> ./pipex infile cmd1 cmd2 outfile
```
The program should repeat the behaviour of the next shell command
```bash
$> < infile cmd1 | cmd2 > outfile
```

### Examples
```bash
$> ./pipex infile cat "wc -l" outfile
```

</br>

## Description

This program takes the infile, outfile to redirect the STDIN (<), STDOUT (>) and 2 commands to pipe. To execute the mandatory program, type the command listed below. 
```bash
$> ./pipex infile cmd1 cmd2 outfile
```
The arguments will be processed as same as below on the shell.
```bash
$>  < infile cmd1 | cmd2 > outfile
```
To execute the bonus program, the project needs to be compiled with the bonus rule before. Then, it takes the infile, outfile to redirect STDIN (<), STDOUT (>) like previous one, but multiple commands can be accepted.
```bash
$> ./pipex infile cmd1 cmd2 cmd3 ... outfile
```
The arguments will be processed as same as below on the shell.
```bash
$>  < infile cmd1 | cmd2 | cmd3 ... > outfile
```
Only for the bonus program, it supports not only the single angle bracket for the STDOUT (>), but also the double angle bracket for the STDOUT (>>). The single angle bracket will overwite the entire file, but the double angle bracket will append after the file. This can be done by writing the arguments with the index 1 has the here_doc. In this case, the double bracket for the STDIN (<<) will be supported instead of the single bracket for the STDIN (<). That means, infile will be replaced and the lines that a user typed will be written on the STDIN until typing the limiter. When the limiter is typed, the first commands will be executed by taking all of the lines of the STDIN (except the limiter).
```bash
$> ./pipex here_doc lIMITER cmd1 cmd2 cmd3 ... outfile
```
The arguments will be processed as same as below on the shell.
```bash
$>  cmd1 << LIMITER | cmd2 | cmd3 ... >> outfile
```

</br>

## Algorithm

### Setting the pipe

The `pipe()` function takes an array of two integers and links them together. What is written into `fd[0]` is visible to `fd[1]`, and vice versa. `pipe()` assigns a file descriptor (fd) to each end. By obtaining an fd for each end, files can be read from and written to, allowing communication between the two ends. `fd[1]` will write to its own fd, while `fd[0]` will read from `fd[1]`'s fd and write to its own.



### Forking the processes

The `fork()` function divides the process into two sub-processes, running in parallel and simultaneously. It returns 0 for the child process, a non-zero value for the parent process, and -1 in case of an error. In this scenario, `fd[1]` corresponds to the child process, while `fd[0]` corresponds to the parent process; the child writes, and the parent reads. Since data must be written before it can be read, `cmd1` will be executed by the child, and `cmd2` by the parent. 



### FDs
 
FDs 0, 1 and 2 are by default assigned to stdin, stdout and stderr. `infile`, `outfile`, the pipe, the `stdin` and `stdout` are all FDs. Our fd table right now looks like this:
```bash
                           -----------------    
                 0         |     stdin     |  
                           -----------------    
                 1         |     stdout    |    
                           -----------------    
                 2         |     stderr    |  
                           -----------------
                 3         |     infile    |  // open()
                           -----------------
                 4         |     outfile   |  // open()
                           -----------------
                 5         |     fd[0]    | 
                           -----------------
                 6         |     fd[1]    |  
                           -----------------
```



### Swapping fds with dup2()

For the child process, we want infile to be our stdin (as input), and `fd[1]` to be our stdout (we write to `fd[1]` the output of `cmd1`). In the parent process, we want `fd[0]` to be our stdin (`fd[0]` reads from `fd[1]` the output of `cmd1`), and outfile to be our stdout (we write to it the output of `cmd2`)
Visually,
```bash
# Each cmd requires an input (from stdin) and produces an output (to stdout).
   
    infile                                             outfile
as stdin for cmd1                                 as stdout for cmd2            
       |                        PIPE                        ↑
       |           |---------------------------|            |
       ↓             |                       |              |
      cmd1   -->    fd[1]       ↔       fd[0]   -->     cmd2           
                     |                       |
            	   |---------------------------|
      cmd1 output                       fd[0] reads fd[1] and
      is written to fd[1]               sends cmd1 output to cmd2
      (fd[1] becomes                    (fd[0] becomes 
       cmd1 stdout)                      cmd2 stdin)

```



### Executing with execve()

The `execve()` function attempts to execute the command by searching through every possible path until it finds a valid one. If the command does not exist, `execve()` will take no action and return -1. However, if the command exists, `execve()` will execute it and replace the current process, ensuring no memory leaks occur by deleting all ongoing processes.



### Using access()

If the command does not exist, `execve()` will execute nothing and won't display any error messages. To ensure proper handling, you should check if the command exists before attempting execution using `access()`. If the command does not exist, you should then send an error message.