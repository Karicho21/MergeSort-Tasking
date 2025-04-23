#!/bin/bash
#SBATCH --job-name=4145-exc1
#SBATCH --partition=Centaurus
#SBATCH --time=01:00:00
#SBATCH --mem=32G

./gtg 10 
./gtg 100
./gtg 1000
./gtg 10000
./gtg 100000
./gtg 1000000
./gtg 10000000
./gtg 100000000
./gtg 1000000000
