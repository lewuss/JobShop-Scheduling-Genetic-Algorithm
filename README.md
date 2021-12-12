# JobShop-Scheduling-Genetic-Algorithm

Genetic Algorithm solution to a Job Shop Scheduling problem. Flexible for Beasley and Tailard input type.

# How it Works?

J - number of jobs\
M - number of machines\
Chromosome length - J*M\

Generate a random population with a rule that in each chromosomes of length J*M every job appears M times.

Repeat until you get a satisfying result 
1. Crossover the chromosomes (random part of chromosome A becames the coresponding part of chromosome B).
2. Repair chromosomes so that that every job still appears M times.
3. Mutate the chromosomes (swap random genes).
4. Calculate the makespan of each chromosome. 
5. Select the best chromosomes based on the makespan from the starting population and the evolved one.

Print out the best sequence of putting the jobs on machines.

Done as a part of Combinatorial Optimization classes with M. Drozdowski at PUT. Feel free to use it as an inspiration to your problem.
