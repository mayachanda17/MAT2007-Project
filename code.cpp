#include <iostream>
#include <fstream>
#include <sstream> // to handle string parsing
#include <vector> // to store primes
#include <string> // to handle string parsing
#include <algorithm>
#include <unordered_set> // stores unique elements in no particular order and allows for extremely fast lookups

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

// function to generate all Fibonacci numbers up to 1 million and store in a fast lookup set
unordered_set<long long> GetFibonacciSet(long long max_val) { //unordered set uses hash function to jump directly to where a number is stored rather than checking if it exists
    unordered_set<long long> fibs;
    long long a = 0, b = 1;
    while (a <= max_val) {
        fibs.insert(a);
        long long next = a + b;
        a = b;
        b = next;
    }
    return fibs;
}

//function that extracts prime pairs and fiobanacci primes
// twin pairs first
struct PrimePair { // groups multiple variables under a single custom type name
    long long p1; // first prime in the pair
    long long p2; // second prime in the pair
};

void ExtractPrimes(const vector<long long>& primes, const unordered_set<long long>& fib_set, vector<PrimePair>& twin_pairs, vector <PrimePair>& sexy_pairs, vector<long long>& fib_primes) {

    for (size_t i = 0; i < primes.size(); ++i) {
        long long current_prime = primes[i];
       
    // 1. check if the current prime is a Fibonacci prime
        if (fib_set.count(current_prime)) {
            fib_primes.push_back(current_prime);
        }
        // 2. look for Twin and Sexy pairs
        for (size_t j = i + 1; j < primes.size(); ++j) {
            long long diff = primes[j] - current_prime;

            if (diff == 2) {
                twin_pairs.push_back({current_prime, primes[j]});
            } else if (diff == 6) {
                sexy_pairs.push_back({current_prime, primes[j]});
            } else if (diff > 6) {
                // Since primes are sorted, differences will only get larger
                break; 
            }
        }
    }
}


int main() {
    //ReadFile()
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