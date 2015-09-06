Food portion sizes
==================

Source: <http://www.informatik.uni-ulm.de/acm/Locals/2009/html/food.html>
Mirror: <https://www.urionlinejudge.com.br/judge/en/problems/view/1638>
Mirror: <https://uva.onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=2680>

The mathematical formalization of this problem is through linear programming,
but since there is only one variable
(the food portion size)
and there is the severe restriction that no student may be required
to fetch more than 3 times,
this problem can be solved through brute-force,
whose complexity is quadratic in the number of students.
(Since there are at most `1e3` students,
quadratic is enough.)

Some ingenuity can simplify the code by avoiding rational arithmetic.

Concepts
========
- Linear programming
- Rational arithmetic
- Brute force

Difficulty
==========
- Conceptual: medium
- Implementation: medium
