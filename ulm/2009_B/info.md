Ballot Evaluation
=================

Source: <http://www.informatik.uni-ulm.de/acm/Locals/2009/html/ballot.html>
Mirror: <https://www.urionlinejudge.com.br/judge/en/problems/view/1635>
Mirror: <https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2676>

Parsing problem.
The implementation using `iostream`, `std::string` and `std::map`
is very straightforward,
but requieres a decent knowledge of the C++ Standard Library.

To work around the imprecision of floating point numbers,
one can use a small tolerance (say `1e-9`) to treat two numbers as equal,
but is best to use the guarantee the program gives
of all numbers having exactly one decimal place
(simulating fixed-point arithmetics).

Concepts
========
- Input parsing
- Fixed-point arithmetics
- std::map

Difficulty
==========
- Conceptual: trivial
- Implementation: medium