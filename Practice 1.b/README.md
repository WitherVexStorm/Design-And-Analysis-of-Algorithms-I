# Practice 1-B

[Back to root folder](/../../)
## About
---
Programming assignment in C++ to analyse performance of sorting algorithms like `Insertion Sort`.

## Steps

1. Install `MinGW` with `g++` (compiler) and `gdb` (debugger).
2. Build in terminal with command `build`.
3. Build and Run in terminal with command `build_and_run`.

## Tasks
---

Consider the following algorithm for insertion sort
Algorithm 1: 
```
Insertion sort(A, n)
input : Array: A[1], A[2]..., A[n]
output: Sorted array; A[1] ≤ A[2] ≤ ..... ≤ A[n]
1 for i: 2 to n do
2 Insert(A[1 . . . i − 1], i) 
  // function searches for an appropriate location j to insert A[i] in A[1 . . . i − 1] so that A[1 . . .i] is sorted.
  // It also inserts A[i] in the jth location.
3 end
```
1. What are the possible locations that `A[i]` may take in the `ith` iteration?

![](answer1.drawio.svg)

2. What is the number of comparisons performed by `Insertion Sort` to insert `A[i]` in location `j`. Give your answer in terms of `i` and `j`.

![](answer2.drawio.svg)

3. Run Insert(A[1...i − 1], i) for `i` = 1 ... 4 for all possible permutations of 1, 2, 3, 4. 

![](permutations.drawio.svg)

For every `j` = 1 ... 4, list down the instances (the permutations) in which `A[i]` is inserted at the `jth` location. What do you observe? Now argue: the probability that `A[i]` will be inserted at the `jth` location is 1/`i`.

![](probabilities.drawio.svg)
![](answer3.drawio.svg)
  - a) For every `i` = 1, 4, Compute the average/expected number of comparisons performed by `Insertion Sort` to insert `A[i]`. Average is taken over all possible permutations.

![](answer3.1.drawio.svg)

  - b) For every `i` = 1, 4, compute the probability that in the `ith` iteration, `A[i]` will be inserted in the `jth` location `j` = 1 ... 4?
  Make a 2d table `P` with `i` at the rows and `j` at the columns where `P[i, j]` stores the above probability.

![](answer3.2.drawio.svg)

  - c) Repeat part (a) using the probabilities computed in part (b).

![](answer3.3.drawio.svg)

4. Consider a random input sequence. What is the probability that in the `ith` iteration, `A[i]` will be inserted in the `jth` location for `j` = 1 ... `i`? Give your answer in terms of `i` (and `j` if required).