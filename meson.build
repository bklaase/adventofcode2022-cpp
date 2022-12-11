project('adventofcode2022-cpp', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3','cpp_std=c++20'])

incdir = include_directories('include')

aocLib = library('aoc', './include/aoc.cpp')

# exe for some cpp experiments
experiments = executable('exp', 'src/cpp-experiments/experiments.cpp',
                         include_directories : include_directories('src/cpp-experiments'))

# solutions
day1 = executable('day1', 'src/day1/day1.cpp', include_directories : incdir, link_with : aocLib)
day2 = executable('day2', 'src/day2/day2.cpp', include_directories : incdir, link_with : aocLib)
day3 = executable('day3', 'src/day3/day3.cpp', include_directories : incdir, link_with : aocLib)
day4 = executable('day4', 'src/day4/day4.cpp', include_directories : incdir, link_with : aocLib)
day5 = executable('day5', 'src/day5/day5.cpp', include_directories : incdir, link_with : aocLib)
day6 = executable('day6', 'src/day6/day6.cpp', include_directories : incdir, link_with : aocLib)
day7 = executable('day7', 'src/day7/day7.cpp', include_directories : incdir, link_with : aocLib)
day8 = executable('day8', 'src/day8/day8.cpp', include_directories : incdir, link_with : aocLib)
day9 = executable('day9', 'src/day9/day9.cpp', include_directories : incdir, link_with : aocLib)
