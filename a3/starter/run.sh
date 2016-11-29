#!/bin/bash

if test -f RayTracer; then rm RayTracer; fi
./compile.sh;
./RayTracer 300 8 1 alixxxx
eog alixxxx
