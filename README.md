# Parallel Dijkstra's Algorithm
Parallel Programming Final Project

## Setup
- Download data from http://www.dis.uniroma1.it/challenge9/download.shtml (recommand `New York City`)
- Unzip download file by `gunzip {download file}` or `gzip -d {download file}`
- Put `gr file` to `Data` folder under project directory

## Usage
- `./convert.sh {gr file}` convert `gr file` to `input file`
- `make` compile source code
- `./dijkstra_{version} {input file} {thread num=8}` execute program, only (openmp, thread, pthread) can set `thread num`
- `./measure.sh` measure all version execution time

## Result
- `USA-road-d.NY`
```
Execution Program: dijkstra_serial
Average time: 203.161

Execution Program: dijkstra_boost
Average time: 0.0892974

Execution Program: dijkstra_openmp
Execute with 2 threads
Average time: 44.8758
Execute with 4 threads
Average time: 26.7877
Execute with 8 threads
Average time: 24.5876
Execute with 12 threads
Average time: 21.2391

Execution Program: dijkstra_thread
Execute with 2 threads
Average time: 125.247
Execute with 4 threads
Average time: 134.905
Execute with 8 threads
Average time: 197.161
Execute with 12 threads
Average time: 279.293

Execution Program: dijkstra_pthread
Execute with 2 threads
Average time: 78.4632
Execute with 4 threads
Average time: 51.0636
Execute with 8 threads
Average time: 70.977
Execute with 12 threads
Average time: 79.2343
```
- `USA-road-d.COL`
```
Execution Program: dijkstra_serial
Average time: 553.298

Execution Program: dijkstra_boost
Average time: 0.139782

Execution Program: dijkstra_openmp
Execute with 2 threads
Average time: 107.055
Execute with 4 threads
Average time: 64.9189
Execute with 8 threads
Average time: 65.8284
Execute with 12 threads
Average time: 42.1925

Execution Program: dijkstra_thread
Execute with 2 threads
Average time: 263.837
Execute with 4 threads
Average time: 234.452
Execute with 8 threads
Average time: 332.798
Execute with 12 threads
Average time: 496.817

Execution Program: dijkstra_pthread
Execute with 2 threads
Average time: 205.596
Execute with 4 threads
Average time: 104.664
Execute with 8 threads
Average time: 142.784
Execute with 12 threads
Average time: 211.979
```
- `USA-road-d.BAY`
```
Execution Program: dijkstra_serial
Average time: 274.676

Execution Program: dijkstra_boost
Average time: 0.109961

Execution Program: dijkstra_openmp
Execute with 2 threads
Average time: 64.1026
Execute with 4 threads
Average time: 39.5637
Execute with 8 threads
Average time: 38.8665
Execute with 12 threads
Average time: 30.7227

Execution Program: dijkstra_thread
Execute with 2 threads
Average time: 150.101
Execute with 4 threads
Average time: 146.436
Execute with 8 threads
Average time: 249.013
Execute with 12 threads
Average time: 315.677

Execution Program: dijkstra_pthread
Execute with 2 threads
Average time: 115.404
Execute with 4 threads
Average time: 69.6879
Execute with 8 threads
Average time: 85.7063
Execute with 12 threads
Average time: 109.186
```
- `USA-road-d.FLA`
```
Execution Program: dijkstra_serial
Average time: 3023.36

Execution Program: dijkstra_boost
Average time: 0.222378

Execution Program: dijkstra_openmp
Execute with 2 threads
Average time: 474.115
Execute with 4 threads
Average time: 369.986
Execute with 8 threads
Average time: 264.65
Execute with 12 threads
Average time: 285.696

Execution Program: dijkstra_thread
Execute with 2 threads
Average time: 1339.31
Execute with 4 threads
Average time: 1109.15
Execute with 8 threads
Average time: 1325.58
Execute with 12 threads
Average time: 1319.36

Execution Program: dijkstra_pthread
Execute with 2 threads
Average time: 816.768
Execute with 4 threads
Average time: 631.947
Execute with 8 threads
Average time: 581.455
Execute with 12 threads
Average time: 536.549
```