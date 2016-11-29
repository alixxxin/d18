#!/bin/bash

if test -f RayTracer; then rm RayTracer; fi
./compile.sh;
./RayTracer 1024 8 1 alixxxx
eog alixxxx
