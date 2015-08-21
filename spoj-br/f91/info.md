1831\. f91
==========

Source: http://br.spoj.com/problems/F91/

Implementation of a recursive function.
This function was designed as a stress test for automated theorem provers.
The function has, in fact, a simple nonrecursive formulation;
but the program is accepted in the online judge
even with the recursive implementation.

This problem behaves pathologically in respect to choosing between C and C++.
In several runs with C++'s std::cin and std::cout,
the runtime was near 0.6 seconds;
simply replacing the iostream objects with printf/scanf
reduced the runtime to 0.1 second.
Even using `sync_with_stdio(false)` had no effect.
I have no idea why...

Concepts
========
- Recursion

Difficulty
==========
- Implementation: easy
- Conceptual: trivial
