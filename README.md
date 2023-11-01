# Simple Testing Framework for C++ (stfcpp)

Simple and fast, header only testing framework for C++ 

## Installation

Copy the include directory and include it in your compiler's include directory. \
**Ensure** you are using *C++14* or later versions. 

## Platforms

Windows - Tested on Windows 11 \
MacOS - Tested on Intel Mac 

## Benchmarks

### Windows 11 (ROG Zypherus M16)
    CPU: 12th Gen Intel(R) Core(TM) i9-12900H
    RAM: 16.0 GB Speed:	4800 MHz
    GPU: NVIDIA GeForce RTX 3070 Ti Laptop GPU

Basic Test Benchmark Results (In terminal) (100000 repetitions):
Empty test function: 19142858600ns (19.139999s) - 5223.880199 times / second
Passed test function: 18850336500ns (18.850000s) - 5304.945087 times / second
Failed test function: 64193082300ns (64.190002s) - 1557.800255 times / second

### MacOS (2022 Retina Macbook Air)
    CPU: 1.1 GHz Quad-Core Intel Core i5
    RAM: 8 GB 3733 MHz LPDDR4X
    GPU: Intel Iris Plus Graphics 1536 MB

Basic Test Benchmark Results (In terminal) (100000 repetitions):
Empty test function: 1114330024ns (1.110000s) - 89740.021220 times / second
Passed test function: 1475950253ns (1.470000s) - 67752.961048 times / second
Failed test function: 4081088472ns (4.080000s) - 24503.266882 times / second

Basic Test Benchmark Results (To file) (100000 repetitions):
Empty test function: 995946443ns (995.940002ms) - 100407.005520 times / second
Passed test function: 988492146ns (988.489990ms) - 101164.182644 times / second
Failed test function: 2719346482ns (2.710000s) - 36773.541239 times / second
