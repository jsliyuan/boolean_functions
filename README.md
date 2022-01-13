# boolean_functions
Basic operations on Boolean functions (viewed as GF(2) polynomials)

The motiviation is to use this library to study the covering radius of Reed Muller codes.


## How to test
### BooleanFun class
yuanli$ g++ -o test.out test_boolean_fun.cpp boolean_fun.cpp 

yuanli$ ./test.out

### AffineTrans class
yuanli$ g++ -o test.out test_affine_trans.cpp affine_trans.cpp 

yuanli$ ./test.out

### UpperDiagGenerator
yuanli$ g++ -o test.out test_upper_diag_generator.cpp upper_diag_generator.cpp affine_trans.cpp

yuanli$ ./test.out
