/*
Name: Tracy Mai
Course Number: CSC3350 Operating Systems Programming
Assignment Title: Threads Assignment
Date: 27 May 2025
*/

#include <iostream>
#include <iomanip>
#include <thread>
#include <string>
#include <chrono>
#include <vector>
#include <fstream>
#include <random>

using namespace std;
using namespace chrono;

struct ThreadStruct {
    string identifier;
    long long time_ms;
};

void threading(ThreadStruct& info) {
    auto start = high_resolution_clock::now();

    ifstream input_file("Data.txt");
    ofstream output_file("Data_Thread_" + info.identifier + ".txt");

    int count, num = 0;
    double total = 0;

    while (input_file >> num) {
        output_file << num << "\n";
        total += num;
        count++;
    }

    double average = (count > 0) ? total / count : 0.0;
    auto end = high_resolution_clock::now();
    info.time_ms = duration_cast<milliseconds>(end - start).count();

    cout << "Thread " << info.identifier << ": Average = " << fixed << setprecision(2) << average
         << ", " << "\n" <<"Time = " << info.time_ms << " milliseconds" << endl;
}

void create_data(const string& file) {
    ofstream out(file);
    random_device random_num;
    mt19937 gen(random_num());
    uniform_int_distribution<> dist(0, 100);
    for (int i = 0; i < 1000000; ++i) {
        out << dist(gen) << "\n";
    }
}




int main() {
    auto start_time = high_resolution_clock::now();

    // Step 1: Generate data
    create_data("Data.txt");

    // Step 2: Create threads A, B, C
    ThreadStruct infoA{"A", 0}, infoB{"B", 0}, infoC{"C", 0};

    thread tA(threading, ref(infoA));
    thread tB(threading, ref(infoB));
    thread tC(threading, ref(infoC));

    // Step 3: Join threads
    tA.join();
    tB.join();
    tC.join();

    auto end_time = high_resolution_clock::now();
    auto total_time = duration_cast<milliseconds>(end_time - start_time).count();
    cout << "Main: Total wall-clock time = " << total_time << " milliseconds" << endl;

    return 0;
}
