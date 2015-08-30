ICPC problems
=============

This repository is a database of ICPC-like problems.
The goal is to have,
for each problem,
all of the following:
-   Statement (in PDF or text form)
-   Solution (commented solution for more complex problems)
-   Discussion on conceptual/coding difficulty
-   Main categories this problem fits in
-   Main/secondary concepts needed to its resolution
-   Test cases or test cases generator
but most likely each problem will have only the solution
and some discussion on the conceptual difficulty.

File structure for each problem
===============================
-   `info.md`: Disscussion about the problem,
    concepts involved, coding/conceptual difficulty.
    Each concept is listed in a line,
    allowing for easy `grep`ping of problems with specific concepts.
-   `solution.cpp`: Code that solves the problem.
-   `analysis.tex`: Presents the more involved aspects of the problem.
    Tipically appears only in harder problems.
