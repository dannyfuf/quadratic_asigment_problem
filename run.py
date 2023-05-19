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
  pwd = os.getcwd()
  path = f"{pwd}{instance}"

  outfile = f"{pwd}/results/{instance.split('/')[-1].split('.')[0]}.out"
  if os.path.isfile(path):
    with open(outfile, "w") as f:
      subprocess.call(["./main", path], stdout=f)
  else:
    print(f"File {path} not found")

def runAllInstances(size):
  instances = readDirectory(f"/data/{size}")
  for instance in instances:
    print(f"Running {instance}")
    runInstance(f"/data/{size}/{instance}")

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
    print("2 - Run many instances")
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
      print("1 - Pequeñas")
      print("2 - Grandes")
      size = input("Size: ")
      if size == "1":
        runAllInstances("pequenas")
      elif size == "2":
        runAllInstances("grandes")
      else:
        print("Invalid size")
    elif option == 3:
      removeResults()
    elif option == 0:
      print("Exiting...")
    else:
      print("Invalid option")

main()