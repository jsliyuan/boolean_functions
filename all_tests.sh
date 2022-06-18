#!/bin/bash

echo "Running all tests"


echo "test BooleanFun class"
g++ -o test.out test_boolean_fun.cpp boolean_fun.cpp affine_trans.cpp
./test.out

echo "test AffineTrans class"
g++ -o test.out test_affine_trans.cpp affine_trans.cpp
./test.out

echo "test UpperDiagGenerator class"
g++ -o test.out test_upper_diag_generator.cpp upper_diag_generator.cpp affine_trans.cpp
./test.out

echo "test NonsingularGenerator class"
g++ -o test.out test_nonsingular_generator.cpp nonsingular_generator.cpp affine_trans.cpp
./test.out

echo "test HomogenousBfGenerator class"
g++ -o test.out test_homogenous_bf_generator.cpp homogenous_bf_generator.cpp boolean_fun.cpp affine_trans.cpp
./test.out

echo "test Permutation class"
g++ -o test.out test_permutation.cpp permutation.cpp
./test.out

echo "test Rotationsym class"
g++ -o test.out test_rotationsym.cpp rotationsym.cpp permutation.cpp
./test.out
