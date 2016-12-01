#!/bin/bash

if test -f RayTracer; then rm RayTracer; fi
./compile.sh;
./RayTracer 300 3 1 alixxx
