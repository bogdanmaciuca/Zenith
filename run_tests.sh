#!/usr/bin/bash

cd build
clear && make && ctest --test-dir ./lib/tests --output-on-failure

