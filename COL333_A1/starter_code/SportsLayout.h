
#ifndef SPORTSLAYOUT_H
#define	SPORTSLAYOUT_H

#include <fstream>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class SportsLayout{

    private:
    int z,l;
    int** T;
    int **N;
    int time;
    int *mapping;
    int *shuffled;
    int *prev;
    int *temp;
    int temp_i;
    int temp_j;
    // long long temp = 
    long long cost_mi = numeric_limits<long long>::max();
    int *map_mi;
    vector<int*> visited_maps; 

    public:
    SportsLayout(string inputfilename);

    bool check_output_format();

    // void readOutputFile(string output_filename);
    
    long long cost_fn(int* m);
    long long cost_fn2();
    void write_to_file(string outputfilename);

    void readInInputFile(string inputfilename);

    void compute_allocation();


};


#endif