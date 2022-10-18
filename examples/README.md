## How to test the examples

### test the nonlinearity for 9-variable Boolean functions
$  g++ -o test.out test_nl_for_9v.cpp reed_muller_generator.cpp boolean_fun.cpp boolean_fun_decoder.cpp affine_trans.cpp

$ ./test.out

### test second-order nonlinearity for 6-variable Boolean functions
$  g++ -o test.out test_nl2_for_6v.cpp reed_muller_generator.cpp boolean_fun.cpp boolean_fun_decoder.cpp affine_trans.cpp

$ ./test.out

### test second-order nonlinearity for 7-variable Boolean functions
$  g++ -o test.out test_nl2_for_7v.cpp reed_muller_generator.cpp boolean_fun.cpp boolean_fun_decoder.cpp affine_trans.cpp

$ ./test.out

### test second-order nonlinearity for 8-variable Boolean functions
$  g++ -o test.out test_nl2_for_8v.cpp reed_muller_generator.cpp boolean_fun.cpp boolean_fun_decoder.cpp affine_trans.cpp

$ ./test.out

### test second-order nonlinearity for 9-variable Boolean functions
$  g++ -o test.out test_nl2_for_9v.cpp reed_muller_generator.cpp boolean_fun.cpp boolean_fun_decoder.cpp affine_trans.cpp

$ ./test.out

### test second-order nonlinearity for 10-variable Boolean functions
$  g++ -o test.out test_nl2_for_10v.cpp reed_muller_generator.cpp boolean_fun.cpp boolean_fun_decoder.cpp affine_trans.cpp

$ ./test.out

### test third-order nonlinearity for 7-variable Boolean functions
$  g++ -o test.out test_nl3_for_7v.cpp reed_muller_generator.cpp boolean_fun.cpp boolean_fun_decoder.cpp affine_trans.cpp

$ ./test.out

