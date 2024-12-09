# CPP-HTML-Experiment

CPU Schedule instructions:

1. Compile

complie file by usign the command: make all

if only you want compile only the CPU scheduling file use the command: make CPUSched

2. Ignore making a cutomlist

you will be prompted if you wnat to create a custom process list answer: no

3. Enter txt file

you will then be prompted to enter the name of a txt file to schedule enter: Datafile1.txt

4. Select CPU scheduling algorithm

You will now be prompoted which scheduling algorith you want to run

if you want to run First in first out (FIFO) type: 0
if you want to run Priority with Preemption type: 1


Inorder to run the programs you need the ablity to run makefiles and the windows.h library. To complie the programs run "make all" to generate an executable for both CPUSched and ProducerConsumer. Executebles can be generated seprately by running "make cpusched" or "make ProducerConsumer". After the executable has been generated, run them in the comandline. CPUSched will ask for User inputs and ProducerConsumer will automatically execute based off the information inside of "data/ProducerConsumer.txt". fPruducer COnsumer will generate an output file "data/RuntimeInfo.txt" with the runtime of each interation.
