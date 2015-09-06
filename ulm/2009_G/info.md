Generate random numbers
=======================

Source: <http://www.informatik.uni-ulm.de/acm/Locals/2009/html/generate.html>
Mirror: <https://www.urionlinejudge.com.br/judge/en/problems/view/1639>
Mirror: <https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2681>

In essence, this problem asks to count how many different numbers there are
in a sequence of numbers that eventually repeat.
Since the size of the numbers is small (less than 10^4),
direct simulation (using an array of booleans) is enough; however,
one must remember to mark the first number as part of the sequence.
For example, when starting with 1600,
the sequence is `1600 - 5600 - 3600 - 9600 - 1600`,
which has size 4, not 5.

Concepts
========
- Simulation
- Digit manipulation

Difficulty
==========
- Implementation: trivial
- Conceptual: easy

