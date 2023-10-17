# Simple Testing Framework for C++ (stfcpp)

Simple and fast, header only testing framework for C++ 

## Installation

Copy the include directory and include it in your compiler's include directory. \
**Ensure** you are using *C++14* or later versions. 

## Platforms

Windows - Tested on Windows 11 \
MacOS - Tested on Intel Mac 

## Benchmarks

    CPU: 12th Gen Intel(R) Core(TM) i9-12900H
    RAM: 16.0 GB Speed:	4800 MHz
    Disk: NVMe Micron_3400_MTFDKBA1T0TFH
    GPU: NVIDIA GeForce RTX 3070 Ti Laptop GPU

    Basic Test Benchmark Results (100000 repetitions):
        Empty test function: 19142858600ns (19.139999s) - 5223.880199 times / second
        Passed test function: 18850336500ns (18.850000s) - 5304.945087 times / second
        Failed test function: 64193082300ns (64.190002s) - 1557.800255 times / second