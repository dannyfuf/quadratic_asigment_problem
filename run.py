# run make all command in the current directory
import os
import sys
import subprocess

def makeAll():
    subprocess.call(["make", "all"])

def readDirectory(directory):
  pwd = os.getcwd()
  return os.listdir(pwd + directory)

def runInstance(instance):
  print(f"Running instance {instance}")
  pwd = os.getcwd()
  path = f"{pwd}{instance}"

  outfile = f"{pwd}/results/{instance.split('/')[-1].split('.')[0]}.out"
  if os.path.isfile(path):
    with open(outfile, "w") as f:
      subprocess.call(["./main", path], stdout=f)
  else:
    print(f"File {path} not found")

def runManyInstances(path):
  instances = readDirectory(path)
  for instance in instances:
    runInstance(f"{path}/{instance}")

def removeResults():
  pwd = os.getcwd()
  results = readDirectory("/results")
  for result in results:
    os.remove(f"{pwd}/results/{result}")
  print("Results removed")

def main():
  makeAll()
  if not os.path.isdir("results"):
    os.mkdir("results")

  option  = -1
  while option != 0:
    print("---------------------------------")
    print("1 - Run instance")
    print("2 - Run many instances in path")
    print("3 - Remove results")
    print("0 - Exit")
    try:
      option = int(input("Option: "))
    except ValueError:
      print("Invalid option")
      continue
    print("---------------------------------")
    if option == 1:
      path = input("Path: ")
      runInstance(path)
    elif option == 2:
      runManyInstances(input("Path: "))
    elif option == 3:
      removeResults()
    elif option == 0:
      print("Exiting...")
    else:
      print("Invalid option")

if __name__ == "__main__":
  main()
