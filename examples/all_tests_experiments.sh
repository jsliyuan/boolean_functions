#!/bin/bash

echo "Running all experients"

echo "Make sure experiments compile successfully"

echo "test nl for 9v"
g++ -o test.out test_nl_for_9v.cpp ../Galois_field.cpp ../reed_muller_generator.cpp ../homogenous_bf_generator.cpp ../boolean_fun.cpp ../boolean_fun_decoder.cpp ../affine_trans.cpp 
./test.out

echo "test nl2 for 6v"
g++ -o test.out test_nl2_for_6v.cpp ../Galois_field.cpp ../reed_muller_generator.cpp ../homogenous_bf_generator.cpp ../boolean_fun.cpp ../boolean_fun_decoder.cpp ../affine_trans.cpp 
./test.out

echo "test nl2 for 7v"
g++ -o test.out test_nl2_for_7v.cpp ../Galois_field.cpp ../reed_muller_generator.cpp ../homogenous_bf_generator.cpp ../boolean_fun.cpp ../boolean_fun_decoder.cpp ../affine_trans.cpp 
./test.out

echo "test nl2 for 8v"
g++ -o test.out test_nl2_for_8v.cpp ../Galois_field.cpp ../reed_muller_generator.cpp ../homogenous_bf_generator.cpp ../boolean_fun.cpp ../boolean_fun_decoder.cpp ../affine_trans.cpp 
./test.out

echo "test nl2 for 9v"
g++ -o test.out test_nl2_for_9v.cpp ../Galois_field.cpp ../reed_muller_generator.cpp ../homogenous_bf_generator.cpp ../boolean_fun.cpp ../boolean_fun_decoder.cpp ../affine_trans.cpp 
./test.out

echo "test nl2 for 10v"
g++ -o test.out test_nl2_for_10v.cpp ../Galois_field.cpp ../reed_muller_generator.cpp ../homogenous_bf_generator.cpp ../boolean_fun.cpp ../boolean_fun_decoder.cpp ../affine_trans.cpp 
./test.out

echo "test nl3 for 7v"
g++ -o test.out test_nl3_for_7v.cpp ../Galois_field.cpp ../reed_muller_generator.cpp ../homogenous_bf_generator.cpp ../boolean_fun.cpp ../boolean_fun_decoder.cpp ../affine_trans.cpp 
./test.out

