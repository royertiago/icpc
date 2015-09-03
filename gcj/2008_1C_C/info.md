Increasing Speed Limits
=======================

Source: https://code.google.com/codejam/contest/32015/dashboard#s=p2

This problem requires a "double mapping" to be solved.
First, one needs to perceive that,
if the speed limits are processed in increasing order,
the program can use a technique that resembles dynamic programming
to compute the number of strictly increasing subsequences
that uses only the speed limits already processed.
(The actual number of strictly increasing subsequences
will appear in the end, when all speed limits were processed.)

Then, one needs to see that the inner loop
(which updates the "iterative dynamic programming" vector)
only needs to do update queries and prefix sum queries,
thus it may be sped up using binary indexed trees (Fenwick trees).

(I called this technique "iterative dynamic programming"
because the structure starts with a complete dynamic programming solution
for an empty subset of the input data;
and then, one by one,
the speed limits are processed,
and the "iterative dynamic programming" vector is updated
with each new data inserted.
In this problem, this update can be done with a binary indexed tree,
thus costing only `log n` steps for each value,
instead of walking through the entire vector.)

Concepts
========
- Binary indexed tree
- Sorting with index retrieval
- Inner loop speeding
- Iterative dynamic programming

Difficulty
==========
- Implementation: easy
- Conceptual: medium-hard

