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
        mapping= new int[z];
        // shuffled = new int[l];
        prev = new int[z];
        temp = new int[l];
    }

    bool SportsLayout::check_output_format()
    {

        vector<bool> visited(l,false);
        for(int i=0;i<z;i++)
        {
            if((mapping[i]>=1 && mapping[i]<=l))
            {
                if(!visited[mapping[i]-1])
                visited[mapping[i]-1]=true;
                else
                {
                    cout<<"Repeated locations, check format\n";
                    return false;
                }
            }
            else
            {
                cout<<"Invalid location, check format\n";
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


    long long SportsLayout::cost_fn(int* m){


        long long cost=0;

        for(int i=0;i<z;i++)
        {
           for(int j=0;j<z;j++) 
           {
                cost+=(long long)N[i][j]*(long long)T[m[i]-1][m[j]-1];
           }
        }

        return cost;
    }
    long long SportsLayout::cost_fn2(){


        long long cost=0;

        for(int i=0;i<z;i++)
        {
           for(int j=0;j<z;j++) 
           {
                cost+=(long long)N[i][j]*(long long)T[mapping[i]-1][mapping[j]-1];
           }
        }

        return cost;
    }

    void SportsLayout::readInInputFile(string inputfilename)
    {
            fstream ipfile;
	        ipfile.open(inputfilename, ios::in);
            if (!ipfile) {
                cout << "No such file\n";
                exit( 0 );
            }
            else {
                

                ipfile>> time;
                ipfile >> z;
                ipfile >> l;

                if(z>l)
                {
                    cout<<"Number of zones more than locations, check format of input file\n";
                    exit(0);
                }


            

            int **tempT;
            int **tempN;

          tempT = new int*[l];
        for (int i = 0; i < l; ++i)
            tempT[i] = new int[l];
        
        tempN = new int*[z];
        for (int i = 0; i < z; ++i)
            tempN[i] = new int[z];

        for(int i=0;i<z;i++)
        {
            for(int j=0;j<z;j++)
            ipfile>>tempN[i][j];
        }

        for(int i=0;i<l;i++)
        {
            for(int j=0;j<l;j++)
            ipfile>>tempT[i][j];
        }

        ipfile.close();

        T= tempT;
        N= tempN;
            }

    }

    void SportsLayout::write_to_file(string outputfilename){

         // Open the file for writing
    ofstream outputFile(outputfilename);

    // Check if the file is opened successfully
    if (!outputFile.is_open()) {
        cerr << "Failed to open the file for writing." << std::endl;
        exit(0);
    }

    for(int i=0;i<z;i++)
    outputFile<<mapping[i]<<" ";

    // Close the file
    outputFile.close();

    cout << "Allocation written to the file successfully." << endl;

    }

    // void SportsLayout::successor_fn(m)
    // {
        
    // }

    void SportsLayout::compute_allocation()
    {
        //you can write your code here 
        //comment out following dummy code
        for(int i=0;i<l;i++)
        temp[i]=i+1;    //randomly kuch start kra
        auto startTime = std::chrono::steady_clock::now();
        random_shuffle(temp, temp + l);    //random start node
        for(int i=0;i<z;i++)
        mapping[i]=temp[i];                  // shall store overall ans at any given pt.
        // for(int i=0;i<l;i++)
        // prev[i]= shuffled[i];                    // previous node - to be implemented
        // for(int i=0;i<l;i++)
        // temp[i]= shuffled[i];                  // temp initialised
        long long c = cost_fn(mapping);
        cost_mi = c;
        
                // map_mi = mapping;
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
        int iter = 1;
        // int lm = 1;
        long long temp_cost = cost_fn(temp);
        while (elapsedTime <= time*60-1)
        {
            // cout<<cost_mi<<"\n";
            // int* mapping
            bool swap = false;
            // cout<<"hi0"<<"\n";
            for(int i=0;i<z;i++)
            {
                // cout<<"hi1"<<"\n";
                for(int j=i;j<l;j++)
                {
                    // cout<<"hi2"<<"\n";
                    int t = temp[i];
                    temp[i] = temp[j];
                    temp[j] = t;
                    long long c = cost_fn(temp);
                    // cout<<"kuch h"<<"\n";

                    // cout<<c<<"\n";
                    // cout<<cost_mi<<"\n";
                    if (c < temp_cost)
                    {
                            temp_i2 = temp_i;
                            temp_j2 = temp_j;
                            temp_cost = c;
                            temp_i = i;
                            temp_j = j;
                            swap = true;
                    }
                    t = temp[i];
                    temp[i] = temp[j];
                    temp[j] = t;
                }
            }

            if (swap)
            {
                // cout<<"lessgoo"<<"\n";
                int x = rand()%10000;
                if (x < 1000)
                {
                    int t = temp[temp_i2];
                    temp[temp_i2] = temp[temp_j2];
                    temp[temp_j2] = t;
                    temp_cost = cost_fn(temp);
                    // temp[temp_i2] = mapping[temp_i2];
                    // temp[temp_j2] = mapping[temp_j2];
                    // cost_mi = cost_fn(mapping);
                }
                else
                {
                // if (temp_j < z)
                // {
                    int t = temp[temp_i];
                    temp[temp_i] = temp[temp_j];
                    temp[temp_j] = t;
                    temp_cost = cost_fn(temp);
                    // temp[temp_i] = [temp_i];
                    // temp[temp_j] = mapping[temp_j];
                    // shuffled[temp_i] = mapping[temp_i];
                    // shuffled[temp_j] = mapping[temp_j];
                // }
                // else
                // {
                //     int t = mapping[temp_i];
                //     mapping[temp_i] = temp[temp_j];
                //     temp[temp_i] = mapping[temp_i];
                //     temp[temp_j] = t;
                // }
                }
                iter++;
            }
            else
            {
                if (temp_cost<cost_mi)
                {
                    cost_mi = temp_cost;
                    for(int i=0;i<z;i++)
                    mapping[i]=temp[i];
                }
                auto current = std::chrono::steady_clock::now();
                // std::chrono::steady_clock::duration duration = current.time_since_epoch();
                // std::chrono::seconds seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
                // std::time_t time_tCurrent = seconds.count();
                // cout << ctime(&time_tCurrent) << "\n";
                elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(current - startTime).count();
                // cout<< elapsedTime << "\n";
                if (elapsedTime <= time*60-1)
                {
                    random_shuffle(temp, temp + l);
                    // lm++;
                    // cout<<lm<<"\n";
                    temp_cost = cost_fn(temp);
                // for(int i=0;i<l;i++)
                // temp[i]=shuffled[i];
                    // long long c = cost_fn(temp);
                    // while (c >=cost_mi && elapsedTime <= time*60-1)
                    // {                   
                    //     random_shuffle(temp, temp + l);
                    //     // for(int i=0;i<l;i++)
                    //     // temp[i]=shuffled[i];
                    //     long long c = cost_fn(temp);
                    //     lm++;
                    //     cout<<lm<<"\n";
                    //     auto current = std::chrono::steady_clock::now();
                    //     elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(current - startTime).count();
                    //     // cout<<elapsedTime<<"\n";
                    // }
                    // if (c<cost_mi)
                    // {
                    //     temp_cost = cost_fn(temp);
                    //     cost_mi = c;
                    // }
                    // else
                    // {
                    //     break;
                    // }
                }
                // else
                
            }
            
            
            // if (c < cost_mi)
            // {
            //     cost_mi = c;
            //     map_mi = mapping;
            // }
            // if (count(visited_maps.begin(), visited_maps.end(), mapping))
            // time_t time_tCurrent = chrono::system_clock::to_time_t(currentTime);
            auto current = std::chrono::steady_clock::now();
            // std::chrono::steady_clock::duration duration = current.time_since_epoch();
            // std::chrono::seconds seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
            // std::time_t time_tCurrent = seconds.count();
            // cout << ctime(&time_tCurrent) << "\n";
            elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(current - startTime).count();
            // cout<< elapsedTime << "\n";
        }
    }


