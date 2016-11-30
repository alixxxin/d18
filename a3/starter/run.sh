#!/bin/bash

if test -f RayTracer; then rm RayTracer; fi
./compile.sh;
./RayTracer 2048 11 1 alixxxx_highres
