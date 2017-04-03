# Kruskal
Multithreaded, optimized C++ program to find the average MST weight in various implementations of a complete, undirected graph.
Uses Kruskal's algorithm, the Union-Find data structure, iterative deepening, multithreading, and aggressive optimizations.

Implemented for Harvard's CS 124. Please do not use this code if you are currently taking the course.

Many students' algorithms would take up to 20 minutes and tens of Gigabytes to run the largest trial.
I was able to do so in approximately 38 seconds using only 118MB of memory.
Through aggressive optimizations and multithreading,
the calculation of the entire problem set took 19 minutes (4 types of graph x 6 trials each x 11 sizes = 264 trials).

<br/>


#### Kruskal’s:
I decided to use Kruskal’s algorithm for this problem for a number of reasons. First, I find it to be more interesting and perhaps a bit more challenging than Prim's. While the algorithm itself isn’t necessarily difficult, creating and testing the Union-Find data structure took a bit of thought.
<br/>

#### Growth Rates:
At first I was a bit surprised by the growth rate of the Basic graph, [redacted]. However after thinking it through, it makes sense. This is a complete graph so the more vertices you add, the more likely it becomes that you will get a connection weight close to 0 for each new vertex. Otherwise, I think the average weights weren’t super surprising. It is also nice to see the pattern emerging, since it gives a more intuitive understanding of the relationship between dimensionality and average MST weight.
<br/>

#### Runtime:
There are a few factors that mess with the runtime of the algorithm. At best, I was able to calculate the whole data set (6 trials for every n for each graph type) in just over 19 minutes. I think that is quite good, given the size of the problem. I’m running on a Intel Core i7-4980HQ CPU @ 2.80GHz (Overclocks to 4.0GHz), which has 4 physical and 8 logical cores. By multithreading the trials, I was able to run about 6x faster (Though I’m sure I could’ve taken a look at pset3 q4 and parallelism vs. concurrency to better distribute the processes). Furthermore, by compiling with -Ofast, I was able to reduce the runtime by another 5x.
<br/>

#### Pruning, Iterative Deepening:
For the staff-ready operation (which deals with specific trials rather than full-blast calculation), the 131,072-vertex Hypercube graph calculation runs in about 38 seconds and eats approximately 118MB of RAM. Part of why it is able to operate so speedily is the aggression with which I am able to prune edges. I employed an iterative deepening strategy, which will re-run a trial of Kruskal’s with a looser bound on the maximum considered edge weight in the case of failure. This means that even if my k(n) is a bit too aggressive, the algorithm is still correct. Because I double the bound in the case of a failed run, it doesn’t change the order of the worst-case runtime.
<br/>

#### k(n):
Ultimately I doctored k(n) to make sure that the iterative deepening step happens very infrequently, because it does add a constant factor to the runtime. Also, because edges have to be pruned at creation (rather than just Union-Find insertion) for the Basic/0-Dimension graph, it does have a small chance of failure. Overall though, the effect is faster practical runtime without loss of correctness.
<br/>

#### Random Numbers, Optimization:
I found the random number generator to operate fine. Testing the average edge weight (not MST weight) on the standard graph showed that we were getting good random numbers. I would have liked to spend some time researching speed vs. accuracy tradeoffs for various functions, since the generator is called very frequently. However, when profiling the runtime of the program, it was the edge weight calculation of the Euclidean graphs that ended up taking up the bulk of the runtime (aside from the sort). I would definitely be interested in researching whether there is a faster way to calculate or estimate distance - perhaps in the same vein as the fast-inverse square root algorithm made famous by John Carmack. However in the interest of staying in line with course policy I haven’t looked into it yet.
<br/>

#### Closing Remarks:
Overall, I found this to be a stimulating and enjoyable exercise. While the goal is correctness, I would definitely enjoy a “Big-Board” style algorithm competition to see how different implementations line up. Regardless, I’m glad to have the opportunity to implement some of the data structures and algorithms from class - though I’m enjoying the written problem sets I definitely prefer the more practical aspects of programming.

