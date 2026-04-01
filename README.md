*This project has been created as part of the 42 curriculum by pcaplat.*

# Philosopher

## Description

Philosopher is an introduction to **multi-threading** and **shared resources** using *mutexes*.

The goal of this project is to create a simulation where n philosophers sit around a table with food placed in the center.
Each philosopher has access to one fork and follow a routine: eat, sleep and think. Since eating with only one fork
is quite difficult, a philosopher must take another fork to eat. The simulation stops when a philosopher dies or when all philosophers have 
eaten a specified number of times. (see the Usage section below)

The *bonus* part follow the same simulation rules but uses **processes** and **semaphores** instead of **POSIX threads** and **mutexes**.

## Instructions

The *mandatory* and the *bonus* parts each have their own Makefile but the compilation rules are exactly the same.

The *bonus* program take the same arguments as the *mandatory* one. The only difference between the two parts is the binary name:
- ***philo*** for the *mandatory* part 
- ***philo_bonus*** for the *bonus* part.

### Compilation instructions

To compile the project:
```bash
make
```

To recompile the project:
```bash
make re
```

To clean object files:
```bash
make clean
```

to clean object files and binaries:
```bash
make fclean
```

### Usage

```bash
./philo nb_philosophers time_to_die time_to_eat time_to_sleep max_meals
```
- *max_meals* is optional.
- All time values are expressed in milliseconds

## Exemples

```bash
./philo 200 130 60 60 5
```
Here, no philosopher should die, and each philosopher must eat at least 5 times.

```bash
./philo 4 300 200 200 
```
Here, a philosopher should die because the total time spent eating and sleeping is greater than the time allowed before dying.

## Resources

- [geeks for geeks thread tutorial](https://www.geeksforgeeks.org/c/thread-functions-in-c-c/)
- Linux man pages about threads, mutexes, fork and semaphores.

I also used AI to improve my understanding of the concepts and to help refine this README in a better English than mine.
