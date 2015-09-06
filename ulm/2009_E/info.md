Elias gamma coding
==================

Source: <http://www.informatik.uni-ulm.de/acm/Locals/2009/html/elias.html>
Mirror: <https://www.urionlinejudge.com.br/judge/en/problems/view/1637>
Mirror: <https://uva.onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=2679>

Matricial dynamic programming problem.

The first kind of optimization can be regarded as an special case
of the second kind of optimization; that is,
simply shifting the prefix sizes can be understood as
the combined operation of padding all numbers with size k
(which, as there is no number of size k, does not affect the final result),
followed by a shift of all prefix sizes.

Therefore, any coding represent, in fact,
a mapping of consecutive ranges of sizes to increasing prefix sizes.
That is, the numbers of size 1, 2, ..., i_1 will all be padded to i_1 bits
and have a prefix of size 1; then, the numbers i_1+1, i_1+2, ..., i_2
will be padded to i_2 bits and have a prefix size of 2,
and so on.

This observation can be used to set up the dynamic programming "predicate".

Concepts
========
- Dynamic programming

Difficulty
==========
- Implementation: medium
- Conceptual: hard
