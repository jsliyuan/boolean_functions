# boolean_functions
Basic operations on Boolean functions (viewed as GF(2) polynomials)

The motiviation is to use this library to study the covering radius of Reed Muller codes.

## Classes
BooleanFun: Boolean function class

AffineTrans: affine transformation Ax + b

UpperDiagGenerator: generates all affine transformation Ax one by one, where A is an upper diagonal matrix and the diagonal elements are all 1

NonsingularGenerator: generates all nonsingular n-by-n matrices one by one.

HomogenousBfGenerator: generates all homogenous Boolean functions of degree r

Permutation: permutation table of the binary input x.

## How to test
Before commit, please run 

$ bash all_tests.sh

to make sure all tests pass.

### BooleanFun class
yuanli$ g++ -o test.out test_boolean_fun.cpp boolean_fun.cpp affine_trans.cpp

yuanli$ ./test.out

### AffineTrans class
yuanli$ g++ -o test.out test_affine_trans.cpp affine_trans.cpp 

yuanli$ ./test.out

### Permutation class
$ g++ -o test.out test_permutation.cpp permutation.cpp 

$ ./test.out

### UpperDiagGenerator class
yuanli$ g++ -o test.out test_upper_diag_generator.cpp upper_diag_generator.cpp affine_trans.cpp

yuanli$ ./test.out

### NonsingularGenerator class
yuanli$ g++ -o test.out test_nonsingular_generator.cpp nonsingular_generator.cpp affine_trans.cpp

yuanli$ ./test.out

### HomogenousBfGenerator class
yuanli$ g++ -o test.out test_homogenous_bf_generator.cpp homogenous_bf_generator.cpp boolean_fun.cpp affine_trans.cpp

yuanli$ ./test.out

### example64.cpp
yuanli$ g++ -o example64.out example64.cpp boolean_fun.cpp affine_trans.cpp upper_diag_generator.cpp

yuanli$ ./example64.out

### example_nonsingular.cpp
yuanli$ g++ -o example_nonsingular.out example_nonsingular.cpp affine_trans.cpp nonsingular_generator.cpp boolean_fun.cpp

yuanli$ ./example_nonsingular.out

### example_orbit.cpp
yuanli$ g++ -o example.out example_orbit.cpp boolean_fun.cpp affine_trans.cpp

yuanli$ ./example.out

### bfs_orbit.cpp
Use BFS to find the full orbit of a given Boolean function under affine transformation.

yuanli$ g++ -o bfs.out bfs_orbit.cpp boolean_fun.cpp affine_trans.cpp

yuanli$ ./bfs.out

### ffn_distribution.cpp
Compute F_f(r) = {homo g : nl_2(f+g) = r}, and wrtie the results into a file.

The file is ~100MB, and it takes about one day to finish

yuanli$ g++ -o ffn.out ffn_distribution.cpp boolean_fun.cpp homogenous_bf_generator.cpp affine_trans.cpp

yuanli$ ./ffn.out

### verification.cpp
Verify that f6(Ax+b) + g || f10 must have nl3 < 21.

yuanli$ g++ -o verification.out verification.cpp boolean_fun.cpp homogenous_bf_generator.cpp affine_trans.cpp

yuanli$ ./verification.out


### cr19_ub_random.cpp
Starting with a random 9-variable Boolean function. At each step, modifying one point to see if nl1 increases. Stop until we hit a local maximal.

It turns out the best we can find is 233, which is much worse than 242.

yuanli$ g++ -o cr19_ub_random.out cr19_ub_random.cpp boolean_fun.cpp affine_trans.cpp

yuanli$ ./cr19_ub_random.out
