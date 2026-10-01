#include <iostream>
#include <fstream>
#include <sstream> // to handle string parsing
#include <vector> // to store primes
#include <string> // to handle string parsing
#include <algorithm>
#include <unordered_set> // stores unique elements in no particular order and allows for extremely fast lookups
#include <iomanip> // required for setw (column width), left, right (sets text alignment)
#include <cctype> // for toupper

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

// generating table 
void PrintTable(const vector<PrimePair>& twin_pairs, const vector<PrimePair>& sexy_pairs, const vector<long long>& fib_primes, long long max_val = 1000000, long long step = 100000) {
    //open a csv file and write the header row, csv file will be used by plots.py to produce plots, so that values don't have to be hardcoded
    ofstream csv("prime_stats.csv");
    csv << "range,twin,sexy,fib\n";

    // printing table headers
std::cout << "\n===================================================================\n";
    std::cout << left 
              << setw(20) << "Range"
              << setw(15) << "Twin Pairs"
              << setw(15) << "Sexy Pairs"
              << setw(18) << "Fibonacci Primes" << "\n";
    std::cout << "===================================================================\n";

    // Trackers for list positions to keep the count O(N) fast
    size_t twin_idx = 0;
    size_t sexy_idx = 0;
    size_t fib_idx = 0;

    //Iterate through each 100k bucket
    for (long long start = 0; start < max_val; start += step) {
        long long end = start + step;

        int twin_count = 0;
        int sexy_count = 0;
        int fib_count = 0;

        // Count Twin Pairs in this range [start, end)
        while (twin_idx < twin_pairs.size() && twin_pairs[twin_idx].p1 < end) {
            if (twin_pairs[twin_idx].p1 >= start) {
                twin_count++;
            }
            twin_idx++;
        }

        // Count Sexy Pairs in this range [start, end)
        while (sexy_idx < sexy_pairs.size() && sexy_pairs[sexy_idx].p1 < end) {
            if (sexy_pairs[sexy_idx].p1 >= start) {
                sexy_count++;
            }
            sexy_idx++;
        }

        // Count Fibonacci Primes in this range [start, end)
        while (fib_idx < fib_primes.size() && fib_primes[fib_idx] < end) {
            if (fib_primes[fib_idx] >= start) {
                fib_count++;
            }
            fib_idx++;
        }

        // Format label e.g. "0 - 100k" or "100k - 200k"
        string label = to_string(start / 1000) + "k - " + to_string(end / 1000) + "k";

        // write to csv
        csv << label << "," << twin_count << "," << sexy_count << "," << fib_count << "\n";  
        // Print Row
        std::cout << left 
                  << setw(20) << label
                  << setw(15) << twin_count
                  << setw(15) << sexy_count
                  << setw(18) << fib_count << "\n";
    }
    csv.close();
    std::cout << "===================================================================\n\n";
}

// Helper Function
int GetValidIndex(int max_size) {
    int n;
    while (true) {
        cout << "Enter N (1 - " << max_size << "): ";
        if (cin >> n && n >= 1 && n <= max_size) {
            return n;
        }
        cout << "Invalid selection. Please enter a number between 1 and " << max_size << ".\n";
        cin.clear();            // Clear error flags
        cin.ignore(10000, '\n'); // Discard bad input
    }
}

// Menu Function
void RunInteractiveMenu(const vector<PrimePair>& twin_pairs,
                        const vector<PrimePair>& sexy_pairs,
                        const vector<long long>& fib_primes) {
    char choice;
    char repeat;

    do {
        cout << "\n---------------------------------------------------\n";
        cout << "               PRIME LOOKUP MENU\n";
        cout << "---------------------------------------------------\n";
        cout << "Choose a type of prime to inspect:\n";
        cout << "  [T] Twin Prime Pairs\n";
        cout << "  [S] Sexy Prime Pairs\n";
        cout << "  [F] Fibonacci Primes\n";
        cout << "  [E] Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        choice = toupper(choice); // Handle lowercase inputs ('t', 's', 'f')

        if (choice == 'E') {
            cout << "Exiting program. Goodbye!\n";
            break;
        }

        switch (choice) {
            case 'T': {
                if (twin_pairs.empty()) {
                    cout << "No Twin Primes found in dataset.\n";
                    break;
                }
                int n = GetValidIndex(twin_pairs.size());
                cout << "\n--> The " << n << "th Twin Prime pair is: (" 
                     << twin_pairs[n - 1].p1 << ", " << twin_pairs[n - 1].p2 << ")\n";
                break;
            }
            case 'S': {
                if (sexy_pairs.empty()) {
                    cout << "No Sexy Primes found in dataset.\n";
                    break;
                }
                int n = GetValidIndex(sexy_pairs.size());
                cout << "\n--> The " << n << "th Sexy Prime pair is: (" 
                     << sexy_pairs[n - 1].p1 << ", " << sexy_pairs[n - 1].p2 << ")\n";
                break;
            }
            case 'F': {
                if (fib_primes.empty()) {
                    cout << "No Fibonacci Primes found in dataset.\n";
                    break;
                }
                int n = GetValidIndex(fib_primes.size());
                cout << "\n--> The " << n << "th Fibonacci Prime is: " 
                     << fib_primes[n - 1] << "\n";
                break;
            }
            default:
                cout << "Invalid option. Please choose T, S, F, or E.\n";
                continue; // Skip repeat prompt and restart loop
        }

        // Prompt to run another query or leave
        cout << "\nWould you like to search again? (Y/N): ";
        cin >> repeat;
        repeat = toupper(repeat);

    } while (repeat == 'Y');

    cout << "\nProgram finished.\n";
}


int main() {
    //ReadFile()
    // load primes
    vector<long long> primes = ReadFile("1m.csv");

    // check output is successful
    std::cout << "===================================================================\n";
    cout << "Successfully loaded " << primes.size() << " primes." << endl;
    if (!primes.empty()) {
        cout << "First prime: " << primes.front() << endl;
        cout << "Last prime: " << primes.back() << endl;}
        std::cout << "===================================================================\n";

        //Generate Fibonacci set up to 1,000,000
    unordered_set<long long> fib_set = GetFibonacciSet(1000000);

    //Containers for our results
    vector<PrimePair> twin_pairs;
    vector<PrimePair> sexy_pairs;
    vector<long long> fib_primes;

    // Run Step 2 extraction
    ExtractPrimes(primes, fib_set, twin_pairs, sexy_pairs, fib_primes);
/*
    // Test output
    cout << "Found " << twin_pairs.size() << " twin prime pairs.\n";
    cout << "Found " << sexy_pairs.size() << " sexy prime pairs.\n";
    cout << "Found " << fib_primes.size() << " Fibonacci primes.\n";*/
    
    PrintTable(twin_pairs, sexy_pairs, fib_primes, 1000000, 100000); // outputting table

    // Run interactive user menu
    RunInteractiveMenu(twin_pairs, sexy_pairs, fib_primes);

    return 0;
}