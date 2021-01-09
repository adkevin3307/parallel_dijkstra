# Parallel Dijkstra's Algorithm
Parallel Programming Final Project

## Environment
- `g++ 10.2`
- `Boost 1.75.0`
- `OpenMP`
- `pthread`
- `Linux`

## Data
- Download data from http://www.dis.uniroma1.it/challenge9/download.shtml (recommand `New York City`)
- Unzip download file by `gunzip {download file}` or `gzip -d {download file}`
- Put `gr file` to `Data` folder under project directory

## Usage
- `./convert.sh {gr file}` convert `gr file` to `input file`
- `make` compile source code
- `./dijkstra_{version} {input file} {thread num=8}` execute program, only (openmp, thread, pthread) can set `thread num`
- `./measure.sh {input file}` measure all version execution time

## Detail
Other details are written in `proposal.pdf` and `report.pdf`

