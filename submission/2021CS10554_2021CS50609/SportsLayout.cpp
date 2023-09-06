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
    temp = new int[l];
    best = new int[l];
    for (int i = 0; i < z; i++)
    {
        for (int j = i + 1; j < l; j++)
        {
            iterVector.push_back(make_tuple(i, j));
        }
    }
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

long long SportsLayout::cost_fn(int *m)
{

    long long cost = 0;

    for (int i = 0; i < z; i++)
    {
        for (int j = 0; j < z; j++)
        {
            cost += (long long)N[i][j] * (long long)T[m[i] - 1][m[j] - 1];
        }
    }

    return cost;
}
long long SportsLayout::cost_fn2()
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

long long SportsLayout::cost_swap(int i, int j, int *m)
{
    long long cost = 0;

    for (int k = 0; k < z; k++)
    {
        if (k != i && k != j)
        {
            cost += ((long long)N[i][k] + (long long)N[k][i]) * ((long long)T[m[k] - 1][m[i] - 1] - (long long)T[m[k] - 1][m[j] - 1]);
            cost += ((long long)N[j][k] + (long long)N[k][j]) * ((long long)T[m[k] - 1][m[j] - 1] - (long long)T[m[k] - 1][m[i] - 1]);
        }
    }
    return cost;
}

long long SportsLayout::cost_swap2(int i, int j, int *m)
{
    long long cost = 0;

    for (int k = 0; k < z; k++)
    {
        if (k != i)
        {
            cost += ((long long)N[i][k] + (long long)N[k][i]) * ((long long)T[m[k] - 1][m[i] - 1] - (long long)T[m[k] - 1][m[j] - 1]);
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
        outputFile << mapping[i] << " ";

    // Close the file
    outputFile.close();

    cout << "Allocation written to the file successfully." << endl;
}

// void SportsLayout::successor_fn(m)
// {

// }

/*
void SportsLayout::initial_node()
{

    if (z < 3)
    {
        for (int i = 0; i < l; i++)
            temp[i] = i + 1;            // randomly kuch start kra
        random_shuffle(temp, temp + l); // random start node
        return;
    }

    vector<int[3]> T_sorted;
    vector<int[2]> *T_adjacency_list;

    for (int i = 0; i < l; i++)
    {
        vector<int[2]> sorted_row;
        for (int j = 0; j < l; j++)
        {
            sorted_row[j][0] = j;
            sorted_row[j][1] = T[i][j];
            if (j >= i)
                T_sorted.push_back({T[i][j], i, j});
        }
        std::sort(sorted_row.begin(), sorted_row.end(), [](const auto &a, const auto &b)
                  { return a[1] < b[1]; });
        T_adjacency_list[i] = sorted_row;
    }

    vector<int[3]> N_sorted;
    vector<int[2]> *N_adjacency_list;
    for (int i = 0; i < z; i++)
    {
        vector<int[2]> sorted_row;
        for (int j = 0; j < z; j++)
        {
            sorted_row[j][0] = j;
            sorted_row[j][1] = N[i][j];
            if (j >= i)
                N_sorted.push_back({N[i][j] + N[j][i], i, j});
        }
        std::sort(sorted_row.begin(), sorted_row.end(), [](const auto &a, const auto &b)
                  { return a[1] > b[1]; });
        N_adjacency_list[i] = sorted_row;
    }

    std::sort(T_sorted.begin(), T_sorted.end(), [](const auto &a, const auto &b)
              { return a[0] < b[0]; });
    std::sort(N_sorted.begin(), N_sorted.end(), [](const auto &a, const auto &b)
              { return a[0] > b[0]; });

    // we have two sorted vectors with (value, (x,y)) format from the matrices.
    // The above can be used in many ways to get more logical start states
    // we shall iterate through both and match them
    int z_filled = 0;
    bool *l_taken;
    bool *z_taken;
    for (int i = 0; i < l; i++)
    {
        l_taken[i] = false;
        if (i < z)
        {
            z_taken[i] = false;
        }
    }
    int i = 0;
    int j = 0;

    while (z_filled < z)
    {
        int x = rand() % 100;
        if (x < 50)
            break;
        // 50% chance it will stop in between

        if (z_taken[N_sorted[i][1]] == true && z_taken[N_sorted[i][2]] == true)
        {
            i++;
            continue;
        }
        if (l_taken[T_sorted[j][1]] == true && l_taken[T_sorted[j][2]] == true)
        {
            j++;
            continue;
        }

        // case 1: when both z pairs and l pairs are available
        if (z_taken[N_sorted[i][1]] == true && z_taken[N_sorted[i][2]] == true && l_taken[T_sorted[j][1]] == true && l_taken[T_sorted[j][2]] == true)
        {
            temp[N_sorted[i][1]] = T_sorted[j][1];
            temp[N_sorted[i][2]] = T_sorted[j][2];
            z_taken[N_sorted[i][1]] = true;
            z_taken[N_sorted[i][2]] = true;
            l_taken[T_sorted[j][1]] = true;
            l_taken[T_sorted[j][2]] = true;
            i++;
            j++;
            z_filled += 2;
            continue;
        }

        if ((z_taken[N_sorted[i][1]] == true && z_taken[N_sorted[i][2]] == false) || (z_taken[N_sorted[i][1]] == false && z_taken[N_sorted[i][2]] == true))
        {
            int z_free;
            if (z_taken[N_sorted[i][2]] == false)
                z_free = N_sorted[i][2];
            else
                z_free = N_sorted[i][1];
            int l_free;
            if (l_taken[T_sorted[i][2]] == false)
                l_free = T_sorted[i][2];
            else
                l_free = T_sorted[i][1];

            if (z_filled == z - 1)
            {
                temp[z_free] = l_free;
                z_filled++;
                continue;
            }

            for (int i = 0; i < z; i++)
            {
                if (!z_taken[N_adjacency_list[z_free][i][0]])
                {
                    for (int j = 0; j < l; j++)
                    {
                        if (!l_taken[T_adjacency_list[l_free][i][0]])
                        {
                            temp[z_free] = l_free;
                            temp[N_adjacency_list[z_free][i][0]] = T_adjacency_list[l_free][i][0];
                            i++;
                            j++;
                            z_filled += 2;
                            break;
                        }
                    }
                    break;
                }
            }
            continue;
        }
    }
    int li = 0;
    int zi = 0;
    vector<int> remaining_l;
    vector<int> remaining_z;
    for (int i = 0; i < l; i++)
    {
        if (!l_taken[i])
            remaining_l.push_back(i);
        if (i < z)
            if (!z_taken[i])
                remaining_z.push_back(i);
    }
    std::mt19937 gen(rd());
    shuffle(remaining_l.begin(), remaining_l.end(), gen);
    int zz = (sizeof(remaining_z) / sizeof(int));

    for (int i = 0; i < zz; i++)
        temp[remaining_z[zz]] = remaining_l[zz];
}

*/

void SportsLayout::compute_allocation()
{
    for (int i = 0; i < l; i++)
        temp[i] = i + 1;

    auto startTime = std::chrono::steady_clock::now();
    std::mt19937 gen(rd());
    shuffle(temp, temp + l, gen);
    // initial_node();
    for (int i = 0; i < z; i++)
        mapping[i] = temp[i];

    long long c = cost_fn(mapping);
    cost_mi = c;
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
    long long temp_cost = 0;

    while (elapsedTime <= time * 60 - 5)
    {

        shuffle(iterVector.begin(), iterVector.end(), gen);
        // cout<<cost_mi<<"\n";
        // cout<<temp_cost<<"\n";
        bool swap = false;
        temp_cost = 0;
        temp_i = 0;
        temp_j = 0;
        for (int k = 0; k < iterVector.size(); k++)
        {
            auto t = iterVector[k];
            int i = get<0>(t);
            int j = get<1>(t);
            if (j < z)
            {
                long long c = cost_swap(i, j, temp);
                if (c > 0)
                {
                    temp_i = i;
                    temp_j = j;
                    swap = true;
                    break;
                }
            }
            else
            {
                long long c = cost_swap2(i, j, temp);
                if (c > 0)
                {
                    temp_i = i;
                    temp_j = j;
                    swap = true;
                    break;
                }
            }
        }

        if (swap)
        {
            int t = temp[temp_i];
            temp[temp_i] = temp[temp_j];
            temp[temp_j] = t;
            temp_cost = cost_fn(temp);
            // cout<<temp_cost<<"\n";
            if (temp_cost < cost_mi)
            {
                cost_mi = temp_cost;
                for (int i = 0; i < z; i++)
                    mapping[i] = temp[i];
            }
        }
        else
        {
            temp_cost = cost_fn(temp);
            // cout<<"Lessgooo"<<"\n";
            if (temp_cost < cost_mi)
            {
                cost_mi = temp_cost;
                for (int i = 0; i < z; i++)
                    mapping[i] = temp[i];
            }
            auto current = std::chrono::steady_clock::now();
            elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(current - startTime).count();
            // cout<< elapsedTime << "\n";
            if (elapsedTime <= time * 60 - 5)
            {
                // shuffle(temp, temp + l, gen);
                shuffle(temp, temp + l, gen);
            }
        }
        auto current = std::chrono::steady_clock::now();
        elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(current - startTime).count();
        // cout<< elapsedTime << "\n";
    }
}

// input0 - 606717
//