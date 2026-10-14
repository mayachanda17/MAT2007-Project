# Prime Number Dataset Analysis: Twin, Sexy, and Fibonacci Primes

This project explores the distribution of prime numbers up to a value of $1,000,000$, specifically investigating the frequency and behaviour of **twin primes** (difference of 2), **sexy primes** (difference of 6), and **Fibonacci primes** across 100k intervals.

Developed locally using **Visual Studio Code** as part of the MAT2007 Introduction to Programming course at Maastricht University.

## Name and Student ID
Maya Chanda \
I6393996


## Research Question
* **In what intervals of 100k (from 1 to 1 million) are there the most of certain types of primes, and how do their frequencies compare?**


## Dataset
* **Source:** Kaggle Dataset – *First 1 Million Prime Numbers* by Charles Averill.
* **Link:** [Kaggle - First 1 Million Prime Numbers](https://www.kaggle.com/datasets/charlesaverill/first-100000-prime-numbers)
* **File Used:** `1m.csv` (contains the first 1 million prime numbers in order).
* **Cleaning/Preparation:** The dataset comes pre-sorted. The C++ script loads the file, skips the header, filters primes up to $1,000,000$, and excludes invalid/incomplete rows automatically.


## Software Dependencies
To run this project locally, ensure you have the following installed:
* **C++ Compiler** (e.g., `g++`, Clang, or MSVC) supporting C++11 or later.
* **Python 3.x** with the following libraries:
  * `numpy`
  * `pandas`
  * `matplotlib`


## Repository Structure
* `code.cpp`: The core C++ script that processes the dataset, identifies prime pairs and Fibonacci primes, counts them per 100k interval, and outputs `prime_stats.csv`.
* `plots.py`: Reads `prime_stats.csv` and generates the comparative bar chart.
* `prime_stats.csv`: Generated data file containing interval statistics.
* `figures/`: Folder (in Overleaf) containing output plots (e.g., `prime_stats_plot.png`) used in the report.
* `main.tex`: The LaTeX source code for the final 2-page report.


## How to Run the Code

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/mayachanda17/MAT2007-Project.git](https://github.com/mayachanda17/MAT2007-Project.git)
   cd MAT2007-Project
