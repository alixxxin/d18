#!/bin/bash

if test -f RayTracer; then rm RayTracer; fi
./compile.sh;
./RayTracer 200 8 1 alixxxx
