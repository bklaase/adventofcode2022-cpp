project('adventofcode2022-cpp', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3','cpp_std=c++20'])

incdir = include_directories('include')

# exe for some cpp experiments
experiments = executable('exp', 'src/cpp-experiments/experiments.cpp', include_directories : include_directories('src/cpp-experiments'))

# solutions
day1 = executable('day1', 'src/day1/day1.cpp', include_directories : incdir)
