
#ifndef SPORTSLAYOUT_H
#define SPORTSLAYOUT_H

#include <fstream>
#include <iostream>
#include <bits/stdc++.h>
#include <random>
#include <algorithm>
using namespace std;

class SportsLayout
{

private:
    int z, l;
    int **T;
    int **N;
    float time;
    int *mapping;
    int *shuffled;
    int *prev;
    int *temp;
    int *best;
    int temp_i = 0;
    int temp_j = 0;
    int temp_i2 = 0;
    int temp_j2 = 0;
    // int cost=0;
    std::vector<std::tuple<int, int>> iterVector;
    std::random_device rd;
    // long long temp =
    long long cost_mi = numeric_limits<long long>::max();
    int *map_mi;
    vector<int *> visited_maps;

public:
    SportsLayout(string inputfilename);

    bool check_output_format();

    // void readOutputFile(string output_filename);

    long long cost_fn(int *m);
    long long cost_fn2();
    long long cost_swap(int i, int j, int *m);
    long long cost_swap2(int i, int j, int *m);

    void write_to_file(string outputfilename);

    void readInInputFile(string inputfilename);
    // void initial_node();
    void compute_allocation();
};

#endif