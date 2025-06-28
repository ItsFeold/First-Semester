# Question 8

In this directory (Question8) we implement [Chord](https://en.wikipedia.org/wiki/Chord_(peer-to-peer)): A scalable peer-to-peer lookup protocol for internet applications. Although Chord is generally used for distributed networks, we will use it on a single computer, in a program to simulate its real usage. The directory contains a main function that showcases the implemented functions, as well as a makefile

# Module Details

The nodes in a real Chord ring are usually servers, with IDs assigned to them via hashing of their ip-addresses (that's one usage at least). In our program, the chord ring will consist of objects of type `struct Server`. Each server holds an array of files, its successor (next server in ring) as well as a finger table, which is essentially a list of pointers to other servers in the ring, which will allow for faster lookup times (O(logn) time complexity). Note that each server has a unique ID assigned to it during the `initialize` function. The IDs are given based on a very simple formula to guarantee unique IDs, but one could assign IPs and hash them. This wasn't done for simplicity, as it is irrelevant to showcase the usage of Chord. The files that we store in the servers consist of a `filename` and a `size`. The filename is the key by which we will identify each file, and the size is the value for each key. 

So in short, this program stores files in servers, and retrieves their size based on their filename. 

The functions implemented for this simplified version of Chord are: 
- void initialize(void): Function that initializes a chord ring with MAXNODENUMBER (constant in header file) servers
- void insert(Server* server, char* filename, int size): Function to insert a file into the Chord Ring (this is asked from the server in the parameter)
- int lookup(Server* server, char* filename): Function to search for value (this is asked from the server in the parameter) in the Chord Ring and return it. If the key doesnt exist, return nullSize (-1)
- int smartLookup(Server* server, char* filename): Lookup function using finger tables for higher efficiency. Also returns the value correspdoning to the file. 

# Compilation & Running

The directory contains a Makefile for compilation. In order to compile, simply type: 
```sh
make
```
In order to run a demo of the program, type: 
```sh
./main
```

# Sources

- [Wikipedia](https://en.wikipedia.org/wiki/Chord_(peer-to-peer))
- [MIT Paper](https://pdos.csail.mit.edu/papers/ton:chord/paper-ton.pdf)
