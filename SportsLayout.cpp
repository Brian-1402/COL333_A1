#include <fstream>
#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
#include <chrono>
#include <limits>
#include <ctime>

using namespace std;

#include "SportsLayout.h"

SportsLayout::SportsLayout(string inputfilename)
{

    readInInputFile(inputfilename);
    mapping = new int[z];
    shuffled = new int[l];
}

bool SportsLayout::check_output_format()
{

    vector<bool> visited(l, false);
    for (int i = 0; i < z; i++)
    {
        if ((mapping[i] >= 1 && mapping[i] <= l))
        {
            if (!visited[mapping[i] - 1])
                visited[mapping[i] - 1] = true;
            else
            {
                cout << "Repeated locations, check format\n";
                return false;
            }
        }
        else
        {
            cout << "Invalid location, check format\n";
            return false;
        }
    }

    return true;
}

// void SportsLayout::readOutputFile(string output_filename)
// {
//         fstream ipfile;
//         ipfile.open(output_filename, ios::in);
//         if (!ipfile) {
//             cout << "No such file\n";
//             exit( 0 );
//         }
//         else {

//             vector<int> ip;

//             while (1) {
//                 int t;
//                 ipfile >> t;
//                 ip.push_back(t);
//                 if (ipfile.eof())
//                     break;

//             }

//         if(ip.size()!=z)
//         {
//             cout<<"number of values not equal to number of zones, check output format\n";
//             exit(0);
//         }
//         for(int i=0;i<z;i++)
//         mapping[i]=ip[i];
//     ipfile.close();

//     if(!check_output_format())
//         exit(0);
//     cout<<"Read output file, format OK"<<endl;

//         }

// }

long long SportsLayout::cost_fn()
{

    long long cost = 0;

    for (int i = 0; i < z; i++)
    {
        for (int j = 0; j < z; j++)
        {
            cost += (long long)N[i][j] * (long long)T[mapping[i] - 1][mapping[j] - 1];
        }
    }

    return cost;
}

void SportsLayout::readInInputFile(string inputfilename)
{
    fstream ipfile;
    ipfile.open(inputfilename, ios::in);
    if (!ipfile)
    {
        cout << "No such file\n";
        exit(0);
    }
    else
    {

        ipfile >> time;
        ipfile >> z;
        ipfile >> l;

        if (z > l)
        {
            cout << "Number of zones more than locations, check format of input file\n";
            exit(0);
        }

        int **tempT;
        int **tempN;

        tempT = new int *[l];
        for (int i = 0; i < l; ++i)
            tempT[i] = new int[l];

        tempN = new int *[z];
        for (int i = 0; i < z; ++i)
            tempN[i] = new int[z];

        for (int i = 0; i < z; i++)
        {
            for (int j = 0; j < z; j++)
                ipfile >> tempN[i][j];
        }

        for (int i = 0; i < l; i++)
        {
            for (int j = 0; j < l; j++)
                ipfile >> tempT[i][j];
        }

        ipfile.close();

        T = tempT;
        N = tempN;
    }
}

void SportsLayout::write_to_file(string outputfilename)
{

    // Open the file for writing
    ofstream outputFile(outputfilename);

    // Check if the file is opened successfully
    if (!outputFile.is_open())
    {
        cerr << "Failed to open the file for writing." << std::endl;
        exit(0);
    }

    for (int i = 0; i < z; i++)
        outputFile << map_mi[i] << " ";

    // Close the file
    outputFile.close();

    cout << "Allocation written to the file successfully." << endl;
}

int *SportsLayout::intial_node()
{
    std::vector<std::pair<int, std::pair<int, int>>> T_sorted;

    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < l; j++)
        {
            T_sorted.push_back({T[i][j], {i, j}});
        }
    }

    std::vector<std::pair<int, std::pair<int, int>>> N_sorted;

    for (int i = 0; i < z; i++)
    {
        for (int j = 0; j < z; j++)
        {
            N_sorted.push_back({N[i][j], {i, j}});
        }
    }

    std::sort(T_sorted.begin(), T_sorted.end());
    std::reverse(T_sorted.begin(), T_sorted.end());
    std::sort(N_sorted.begin(), N_sorted.end());
    std::reverse(N_sorted.begin(), N_sorted.end());

    // we have two decreasing order sorted vectors with (value, (x,y)) format from the matrices.
    // The above can be used in many ways to get more logical start states
    // we shall iterate through both and match them
    int *new_mapping;
    for (size_t i = 0; i < T_sorted.size() && i < N_sorted.size(); ++i)
    {
        new_mapping[N_sorted[i].second.first] = T_sorted[i].second.first;
        new_mapping[N_sorted[i].second.second] = T_sorted[i].second.second;
        // !!!!!!! NEED TO AVOID OVERLAPS AND ADD RANDOMNESS IN BETWEEN
    }
    return new_mapping;
}
void SportsLayout::compute_allocation()
{
    // you can write your code here
    // comment out following dummy code
    for (int i = 0; i < l; i++)
        shuffled[i] = i + 1;
    auto startTime = std::chrono::steady_clock::now();
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
    while (elapsedTime <= time * 60)
    {
        random_shuffle(shuffled, shuffled + l);
        for (int i = 0; i < z; i++)
            mapping[i] = shuffled[i];
        long long c = cost_fn();
        if (c < cost_mi)
        {
            cost_mi = c;
            map_mi = mapping;
        }
        // if (count(visited_maps.begin(), visited_maps.end(), mapping))
        // time_t time_tCurrent = chrono::system_clock::to_time_t(currentTime);
        auto current = std::chrono::steady_clock::now();
        std::chrono::steady_clock::duration duration = current.time_since_epoch();
        std::chrono::seconds seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
        std::time_t time_tCurrent = seconds.count();
        // cout << ctime(&time_tCurrent) << "\n";
        elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(current - startTime).count();
        // cout<< elapsedTime << "\n";
    }
}
