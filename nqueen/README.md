# N-Queens Problem

## How to compile

> You should be able to compile with any C compiler. But i have added a makefile for convenience (compiler=clang)

- **make nq** : create the binary nq with debug information
- **make nqopt** : create the binary nq with O3 compiler flag and no debug information

## How to Run

- **./nq BOARDSIZE** - note the program will probably not be able to solve any board above 30 in a reasonable amount of time.

## Features

The aim of this program is to visually illustrate the workings of backtracking algorithms, and not to efficiently
calculate the number of solutions for a particular board nor to generate solutions efficiently.

The program has a __replay__ feature which shows the backtracking algorithm in action.
When you run the binary without any command line arguments this mode is selected and the default __step__ time is _500ms_

To change the __step__ time use **-t[TIME]** flag where TIME is in milliseconds.
> Use a step time of atleast 50ms

---------------

Another feature is timing the CPU time the backtracking algorithm took.
use the flag **-q** to do this. Note the __replay__ will not be available in this mode, but the output will be shown
in the end

---------------

Also you get statistics on how many times the recursive function was called, and also how many times the validate board
function was called

> Validate board function checks weather a queen placed in a position violates any constraints
