import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("prime_stats.csv") # read file produced by code.cpp
x = np.arange(len(df)) # makes array of consecutive integers starting at 0, up to number of rows
width = 0.25 #make bars 0.25, have 3 bars per interval and 1 break before next interval = 1

fig, ax = plt.subplots(figsize=(12, 6))

ax.bar(x - width, df["twin"], width, label="Twin Pairs", color = "darkred")
ax.bar(x,         df["sexy"], width, label="Sexy Pairs", color = "seagreen")
ax.bar(x + width, df["fib"],  width, label="Fibonacci Primes", color = "darkviolet")

ax.set_xlabel("Range")
ax.set_ylabel("Count")
ax.set_title("Prime Types by Range")
ax.set_xticks(x)
ax.set_xticklabels(df["range"], rotation=45, ha="right") # labels x axis
ax.legend()

plt.tight_layout()
plt.show()