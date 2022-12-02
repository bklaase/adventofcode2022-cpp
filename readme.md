# Advent of Code 2022 - C++
My solutions to AoC 2022, this time in c++.

https://adventofcode.com/2022

## building and running
this was build using meson with ninja backend.  
g++ compiler with c++20 standard library.  

with all reqs installed, run:

``` sh
meson setup build
meson compile -C build
```

solution executables will now be in the `build` folder.
To run a solution do

``` sh
./dayn ../path/to/input.txt
```
