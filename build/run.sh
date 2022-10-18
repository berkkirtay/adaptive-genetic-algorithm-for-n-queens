#!/bin/bash
#./build.sh

# Cmd args: -t 20 -p 200 -pp 2 -sp 1 -mp 5
./main.exe $@

cd ../chart
py PlotChart.py