#!/bin/bash
#SBATCH --job-name=4145-A1
#SBATCH --partition=Centaurus
#SBATCH --time=01:00:00
#SBATCH --mem=16G

record="record.txt"

./gtg 10 >> $record
./gtg 100 >> $record
./gtg 1000 >> $record
./gtg 10000 >> $record
./gtg 100000 >> $record
./gtg 1000000 >> $record
./gtg 10000000 >> $record
./gtg 100000000 >> $record
./gtg 1000000000 >> $record
