This program is for ITCS 4145 EXC MergeSort-Tasking Assignment

But before you begin, make sure you have access to

- A Linux-based system with SLURM workload management
- gcc compiler (this is critical to execute the program)
- Access to hpc lab computer Centaurus
- UNC Charlotte VPN if you are outside of campus or not using "eduroam" network

Steps to compile and experiment:

1. Connecting hpc lab computer by "ssh hpc-student.charlotte.edu -l your-username"
2. Authenticate with Duo
3. Type "g++ -fopenmp mst.cpp -o gtg -I ~/rapidjson/include -lcurl" to create executable file.
4. Schedule the job by "sbatch mst.sh"
5. Outcome should be something like "Submitted batch job [????]". Pay attention to the number since the outcome will be in the file named under "slurm-[????].out"
6. Wait a bit for command to finish running and record the time it takes.
7. If you would like a csv file recording the time, type "sbatch mst.sh > timelog.csv". It will schedule the job and record the time onto csv file called timelog.csv. You can name the file whatever you desire, but this timelog is what I named.


Example execution result:

- Sorting array of 10 elements took: 3.326e-06 seconds
- Sorting array of 100 elements took: 2.8301e-05 seconds
- Sorting array of 1000 elements took: 0.000289798 seconds
- Sorting array of 10000 elements took: 0.00317631 seconds
- Sorting array of 100000 elements took: 0.035263 seconds
- Sorting array of 1000000 elements took: 0.394745 seconds
- Sorting array of 10000000 elements took: 4.35744 seconds
- Sorting array of 100000000 elements took: 47.1071 seconds

