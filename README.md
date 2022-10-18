# boolean_functions


## Description

Boolean functions in n variables can be viewed as the functions from the n-dimensional vector space $\mathbb{F}_2^n$ over $\mathbb{F}_2$, to $\mathbb{F}_2$ itself, which plays important role in cryptography and error correcting codes. The Reed-Muller code of order $r$, denoted by RM(r,n), consists of all Boolean functions in n variables with algebraic degree bounded above by $k$. The r-order nonlinearity is one of the most important cryptographic properties about n-variable Boolean functions, which is also defined by the covering radius of RM(r,n).

The C++ boolean_functions Library, implements a specialised version of Boolean functions known as extension fields of the form GF(2) polynomials, including basic operations on Boolean functions. The motivation is to use this library to study the covering radius of Reed-Muller codes. The library is simple, consise and straight forward. It is convenient to calculate the first-order and second-order nonlinearity of n-variable Boolean functions for small n ( $n\leq 10$ ). Moreover, it is potential to be developed as a base for programming tasks that involved cryptography and error correcting codes.

The library is broken into nine classes, which are BooleanFun, BooleanFunDecoder, AffineTrans, UpperDiagGenerator, NonsingularGenerator, HomogenousBfGenerator, ReedMullerGenerator, Permutation and PermGroup. Basic operations such as addition, multiplication, fourier transform, changing ANF to truth table (or changing truth table to ANF) can occur over Boolean functions in BooleanFun and BooleanFunDecoder classes. 

## Usage of C++ boolean_functions Library

Initially one must setup a Boolean function before you can begin using operations related to the Boolean function. Boolean functions are setup by intially defining the number of variables which means how many dimensions of this vector space, and also the Algebraic Normal Formal (ANF) or hexadecimal truth table the function will posses. The ANF or hexadecimal truth table that the Boolean function will posses should be string type. 

The Boolean function can be setup as follows:

****
 /* 
   f=x1x2x3x4+x4
   
   A 4-variable Boolean function with ANF "x1x2x3x4+x4"
 */

BooleanFun f(4,''x1x2x3x4+x4");

 /* 
   A 4-variable Boolean function of which the  hexadecimal truth table is "ABCD" 
 */

BooleanFun f1(4) ;

f1.set_truth_table_hex("ABCD");

f1.set_truth_table_done;

****

Performing operations on Boolean functions are as follows:

****

BooleanFun f1(4,''x1x2x3x4+x4");

BooleanFun f2(4,"x1x2+x3x4");

BooleanFun f3(4,"x1x2x4+x2");

/* 
f1= f1+f2 = x1x2x3x4+x1x2+x3x4+x4; 
*/

f1.add(f2);     //addition

/* 
 f2=f2*f3= x1x2x4+x1x2+x1x2x3x4+x2x3x4; 
*/

f2.mult(f3);    //multiplication


****


Calculating the first-order nonlinearity for Boolean function:

****

BooleanFun f(4, "x1x2x3x4");

cout<< f.nonlinearity();


****


Calculating the second-order nonlinearity for Boolean function using Fourquet-Tavernier list decoding algorithm:

****

BooleanFunDecoder  f(4, "x1x2x3x4");

cout << f.second_order_nonlinearity_Fourquet_Tavernier() ;

****

## Classes
- BooleanFun: Boolean function class
 
- BooleanFunDecoder: Inheritance of BooleanFun class, including Fourquet-Tavernier list decoding algorithm for second-order nonlinearity.

- AffineTrans: affine transformation Ax + b

- UpperDiagGenerator: generates all affine transformation Ax one by one, where A is an upper diagonal matrix and the diagonal elements are all 1

- NonsingularGenerator: generates all nonsingular n-by-n matrices one by one.

- HomogenousBfGenerator: generates all homogenous Boolean functions of degree r.

- ReedMullerGenerator: generates all Reed-Muller codes of order r.

- Permutation: includes basic operations on generators of a permutation group.

- PermGroup: generate all orbits under a permutation group.

## Examples
In the "example" folder, there are some simple examples to calculate the nonlinearity and second-order linearity for Boolean functions.


## How to test
Before committing, please run 

$ bash all_tests.sh

to make sure all tests pass.

### BooleanFun class
$ g++ -o test.out test_boolean_fun.cpp boolean_fun.cpp affine_trans.cpp rotation_sym.cpp permutation.cpp

$ ./test.out

Performance test - test nonlinearity()

$ g++ -o test.out test_boolean_fun_nonlinearity_perf.cpp boolean_fun.cpp affine_trans.cpp

$ ./test.out

### AffineTrans class
$ g++ -o test.out test_affine_trans.cpp affine_trans.cpp 

$ ./test.out

### Permutation class
$ g++ -o test.out test_permutation.cpp permutation.cpp 

$ ./test.out


### perm_group class
$g++ -o test.out test_perm_group.cpp perm_group.cpp permutation.cpp

$./test.out

### UpperDiagGenerator class
$ g++ -o test.out test_upper_diag_generator.cpp upper_diag_generator.cpp affine_trans.cpp

$ ./test.out

### NonsingularGenerator class
$ g++ -o test.out test_nonsingular_generator.cpp nonsingular_generator.cpp affine_trans.cpp

$ ./test.out

### test nonlinearity for 9-variable Boolean functions
$ g++ -o test.out test_nl_for_9v.cpp reed_muller_generator.cpp boolean_fun.c
### HomogenousBfGenerator class
$ g++ -o test.out test_homogenous_bf_generator.cpp homogenous_bf_generator.cpp boolean_fun.cpp affine_trans.cpp

$ ./test.out

### example_nonsingular.cpp
$ g++ -o example_nonsingular.out example_nonsingular.cpp affine_trans.cpp nonsingular_generator.cpp boolean_fun.cpp

$ ./example_nonsingular.out

### example_orbit.cpp
$ g++ -o example.out example_orbit.cpp boolean_fun.cpp affine_trans.cpp

$ ./example.out

### bfs_orbit.cpp
Use BFS to find the full orbit of a given Boolean function under affine transformation.

$ g++ -o bfs.out bfs_orbit.cpp boolean_fun.cpp affine_trans.cpp

$ ./bfs.out

### ffn_distribution.cpp
Compute F_f(r) = {homo g : nl_2(f+g) = r}, and write the results into a file.

The file is ~100MB, and it takes about one day to finish

$ g++ -o ffn.out ffn_distribution.cpp boolean_fun.cpp homogenous_bf_generator.cpp affine_trans.cpp

$ ./ffn.out

### verification.cpp
Verify that f6(Ax+b) + g || f10 must have nl3 < 21.

$ g++ -o verification.out verification.cpp boolean_fun.cpp homogenous_bf_generator.cpp affine_trans.cpp

$ ./verification.out

### test_FT_decoding.cpp
Test list decoding for second-order nonlinearity. 

$g++ -o test.out test_FT_decoding.cpp reed_muller_generator.cpp homogenous_bf_generator.cpp boolean_fun.cpp boolean_fun_decoder.cpp affine_trans.cpp

$./test.out


