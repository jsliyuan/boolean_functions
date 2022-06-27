## How to test

### example64.cpp
yuanli$ g++ -o example_nonsingular.out ../example_nonsingular.cpp ../affine_trans.cpp ../nonsingular_generator.cpp ../boolean_fun.cpp
yuanli$ ./example64.out

### cr19_ub_random.cpp
Starting with a random 9-variable Boolean function. At each step, modifying one point to see if nl1 increases. Stop until we hit a local maximal.

It turns out the best we can find is 233, which is much worse than 242.

yuanli$ g++ -o cr19_ub_random.out cr19_ub_random.cpp ../boolean_fun.cpp ../affine_trans.cpp

yuanli$ ./cr19_ub_random.out

### perm_cycle.cpp
Decompose a permutation in S_9 into cycles. Returns the length of each cycle.

yuanli$ g++ -o test.out perm_cycle.cpp ../permutation.cpp

yuanli$ ./test.out