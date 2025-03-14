# Dining Philosophers Problem

## Description
This project is an implementation of the classic **[Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)**, a synchronization problem originally formulated by **[Edsger Dijkstra](https://en.wikipedia.org/wiki/Edsger_W._Dijkstra)** in 1965.
The challenge revolves around a group of philosophers who alternately **think**, **eat** and **sleep** at a round table while sharing a limited number of forks. The problem was designed to illustrate the challenges of allocating limited resources (forks) to multiple competing processes (philosophers) without conflicts, deadlocks, or starvation. It is widely used to study mutex locks, semaphores, and thread synchronization techniques. Proper synchronization mechanisms must be implemented to prevent deadlocks, starvation, and race conditions.

The project consists of a mandatory part that implements the problem using threads and mutexes, with an optional bonus part for further enhancements.

## Compilation & Usage
### Compilation
To compile the project, simply run:
```bash
make
```
This will generate the executable `philo`.

### Running the Simulation
The program takes the following arguments:
```bash
./philosophers <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```
#### Arguments:
- `number_of_philosophers` – Number of philosophers (and forks).
- `time_to_die` (ms) – Time limit before a philosopher dies if they haven't eaten.
- `time_to_eat` (ms) – Time required for a philosopher to eat.
- `time_to_sleep` (ms) – Time a philosopher spends sleeping after eating.
- `number_of_times_each_philosopher_must_eat` *(optional)* – If specified, the simulation ends once each philosopher has eaten this many times.

#### Example Usage:
```bash
./philosophers 5 800 200 200
```
This starts a simulation with 5 philosophers, 800ms before dying, 200ms to eat, and 200ms to sleep.

## Log Format
During execution, the program prints the actions of philosophers:
```
[timestamp_in_ms] X has taken a fork
[timestamp_in_ms] X is eating
[timestamp_in_ms] X is sleeping
[timestamp_in_ms] X is thinking
[timestamp_in_ms] X died
```
- `timestamp_in_ms` – The time elapsed since the start of the simulation.
- `X` – The philosopher's ID.

## Implementation Details
### Synchronization Mechanisms
- **Threads**: Each philosopher runs in its own thread.
- **Mutexes**: Used to prevent data races and ensure proper access to shared resources (forks).
- **Fork Handling**: Each fork is shared between two neighboring philosophers and must be acquired before eating.
- **Death Detection**: The simulation must detect when a philosopher starves and stop immediately.

## Challenges Faced
1. **Preventing Deadlocks**: If every philosopher picks up the left fork at the same time, no one can pick up the right fork, leading to a deadlock. Solutions include:
   - Using an **odd/even** strategy for picking up forks.
   - Ensuring at least one philosopher can eat at a time.

2. **Avoiding Starvation**: If one philosopher eats too frequently while others wait, some might starve. Ensuring fairness was a key challenge.

3. **Precise Timing**: The program must ensure that time calculations (for eating, sleeping, and dying) are accurate to avoid unexpected behaviors.

## Conclusion
This project is an excellent exercise in **multithreading**, **mutex synchronization**, and **concurrency handling**. Properly managing shared resources while ensuring fairness and avoiding deadlocks presents a real-world challenge in system programming.

---
### Author
This project was implemented as part of a system programming exercise.

