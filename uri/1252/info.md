Sort! Sort!! And Sort!!!
========================

Source: https://www.urionlinejudge.com.br/judge/en/problems/view/1252

Simple sorting problem with custom comparison operator.
The major difficulty of this problem is dealing with negative numbers,
since `-3 % 2 == -1`, according to C rules.
Thus, the conditional

      if( n % 2 == 1 )

does not tests wether n is odd, it tests if both n is odd and positive.

Concepts
========
- Sorting
- Custom functors

Difficulty
==========
- Implementation: easy
- Conceptual: easy