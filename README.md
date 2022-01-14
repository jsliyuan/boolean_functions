# boolean_functions
Basic operations on Boolean functions (viewed as GF(2) polynomials)

The motiviation is to use this library to study the covering radius of Reed Muller codes.

## Classes
BooleanFun: Boolean function class

AffineTrans: affine transformation Ax + b

UpperDiagGenerator: generates all affine transformation Ax one by one, where A is an upper diagonal matrix and the diagonal elements are all 1

## How to test
### BooleanFun class
yuanli$ g++ -o test.out test_boolean_fun.cpp boolean_fun.cpp affine_trans.cpp

yuanli$ ./test.out

### AffineTrans class
yuanli$ g++ -o test.out test_affine_trans.cpp affine_trans.cpp 

yuanli$ ./test.out

### UpperDiagGenerator
yuanli$ g++ -o test.out test_upper_diag_generator.cpp upper_diag_generator.cpp affine_trans.cpp

yuanli$ ./test.out

### example64.cpp
yuanli$ g++ -o example64.out example64.cpp boolean_fun.cpp affine_trans.cpp upper_diag_generator.cpp

yuanli$ ./example64.out
