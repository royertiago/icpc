Black Box
=========

Source: <https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=442>
Mirror: <https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&page=show_problem&problem=3646>

Nice ad-hoc problem featuring an unorthodox instruction input format.
The simplest solution seems to logically separate the code that
"untangle" the input format and
the code that computes the Black Box output.

To compute the black box output,
the program must somehow keep everything sorted
at least in the "surroundings" of the current index.
This can be done,
for instance,
by using a std::set (to keep all the data sorted)
and a std::set::iterator (to keep the current index),
or using two priority queues to separate
the data larger and smaller than the current index.

Concepts
========
- Unorthodox input format
- std::set iterators
- iterator adjustment

Difficulty
==========
- Implementation: easy
- Conceptual: medium
