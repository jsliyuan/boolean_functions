## How to test

### cr19_ub_random.cpp
Starting with a random 9-variable Boolean function. At each step, modifying one point to see if nl1 increases. Stop until we hit a local maximal.

It turns out the best we can find is 233, which is much worse than 242.

yuanli$ g++ -o cr19_ub_random.out cr19_ub_random.cpp ../boolean_fun.cpp ../affine_trans.cpp

yuanli$ ./cr19_ub_random.out