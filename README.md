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
- `USA-road-d.NY.in`
```
Execution Program: dijkstra_serial
Average time: 126.706

Execution Program: dijkstra_boost
Average time: 0.0502973

Execution Program: dijkstra_openmp
Execute with 2 threads
Average time: 27.6407
Execute with 4 threads
Average time: 16.6618
Execute with 8 threads
Average time: 15.3539
Execute with 12 threads
Average time: 12.5597

Execution Program: dijkstra_thread
Execute with 2 threads
Average time: 63.4278
Execute with 4 threads
Average time: 66.2788
Execute with 8 threads
Average time: 104.011
Execute with 12 threads
Average time: 149.858

Execution Program: dijkstra_pthread
Execute with 2 threads
Average time: 39.5435
Execute with 4 threads
Average time: 30.2162
Execute with 8 threads
Average time: 46.9703
Execute with 12 threads
Average time: 70.8268
```