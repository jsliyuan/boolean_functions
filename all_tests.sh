#!/bin/bash

echo "Running all tests"


echo "test BooleanFun class"
g++ -o test.out test_boolean_fun.cpp Galois_field.cpp boolean_fun.cpp affine_trans.cpp rotation_sym.cpp permutation.cpp
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
g++ -o test.out test_homogenous_bf_generator.cpp Galois_field.cpp homogenous_bf_generator.cpp boolean_fun.cpp affine_trans.cpp
./test.out

echo "test Permutation class"
g++ -o test.out test_permutation.cpp permutation.cpp
./test.out

echo "test Rotationsym class"
g++ -o test.out test_rotation_sym.cpp rotation_sym.cpp permutation.cpp
./test.out

echo "test PermGroup class"
g++ -o test.out test_perm_group.cpp perm_group.cpp permutation.cpp
./test.out

echo "test ReedMullerGenerator class"
g++ -o test.out test_reed_muller_generator.cpp Galois_field.cpp reed_muller_generator.cpp boolean_fun.cpp affine_trans.cpp
./test.out

echo "Galois_field class"
g++ -o test.out test_Galois_field.cpp Galois_field.cpp 
./test.out


echo "Make sure experiments compile successfully"

g++ -o example_nonsingular.out example_nonsingular.cpp Galois_field.cpp affine_trans.cpp nonsingular_generator.cpp boolean_fun.cpp

g++ -o example.out example_orbit.cpp Galois_field.cpp boolean_fun.cpp affine_trans.cpp

g++ -o bfs.out bfs_orbit.cpp Galois_field.cpp boolean_fun.cpp affine_trans.cpp

g++ -o ffn.out ffn_distribution.cpp Galois_field.cpp boolean_fun.cpp homogenous_bf_generator.cpp affine_trans.cpp

g++ -o verification.out verification.cpp Galois_field.cpp boolean_fun.cpp homogenous_bf_generator.cpp affine_trans.cpp

