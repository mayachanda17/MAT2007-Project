#include <iostream>
#include <fstream>
#include <sstream> // to handle string parsing
#include <vector> // to store primes
#include <string> // to handle string parsing
#include <algorithm>

using namespace std;

//function to read csv file and return a vector of primes
vector<long long> ReadFile(const string& filename) {
    vector<long long> primes;
    ifstream infile("1m.csv");
    
    //check if file opened successfully
    if (!infile.is_open()) {
        cerr << "Error: Could not open file '1m.csv'" << endl; // protection for code
        return primes;
    }

    string line;

    // 1. Read and skip the header line ("Rank,Num,Interval")
    getline(infile, line);

    // 2. Read the rest of the file line by line
   while (getline(infile, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string rank_str, num_str, interval_str;

        // Extract rank (column 1) and prime number (column 2) separated by commas
        if (getline(ss, rank_str, ',') && getline(ss, num_str, ',')) {
            long long prime_val = stoll(num_str);

            // Stop loading if the prime value exceeds 1,000,000
            if (prime_val > 1000000) {
                break;
            }

            // Convert string to long long and add to vector
            primes.push_back(prime_val);
        }
    }

    infile.close();
    return primes;
}

int main() {
    // load primes
    vector<long long> primes = ReadFile("1m.csv");

    // check output is successful
    cout << "Successfully loaded " << primes.size() << " primes." << endl;
    if (!primes.empty()) {
        cout << "First prime: " << primes.front() << endl;
        cout << "Last prime: " << primes.back() << endl;
    }

    return 0;
}