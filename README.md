# Parallel Matrix Arithmetic

## Introduction
Matrix.c performs parallel addition, subtraction, and multiplication on a matrix of any NxN size using pThreads.

### Run
Once in the matrix, directory run

`make`

and then

`./matrix`

You are then prompted to enter an integer which represents the size of an NxN matrix.

You should see an output that looks like this:

`What NxN matrix size would you like? Please enter an integer N.`

`4`

    Matrix A:

      3    7    4    5

      5    6    4    8

      8    6    4    6

      7    3    2   10


    Matrix B:

      2    8    2    6

      6    1    4    7

      1    7    7    6

      5    1    5    7


    Results:

    Sum:

      5   15    6   11

      11    7    8   15

      9   13   11   12

      12    4    7   17


    Difference:

      1   -1    2   -1

      -1    5    0    1

      7   -1   -3    0

      2    2   -3    3
    

    Product:

       77   64   87  126

       90   82  102  152

       86  104   98  156

       84   83   90  145
