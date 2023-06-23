import os
import sys

from run import readDirectory

results = readDirectory("/results")
results.sort()
names = [result.split(".")[0] for result in results]

with open("results.csv", "w") as r:
  r.write("instance,time\n")
  for i in range(len(results)):
    with open(f"results/{results[i]}", "r") as f:
      lines = f.readlines()
      if(len(lines) > 0):
        time = lines[0].split(" ")[1]
        r.write(f"{names[i]},{time}")
