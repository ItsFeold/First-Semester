# Question7

In this directory (Question7) exists a module for the implementation of the [Skiplist](https://en.wikipedia.org/wiki/Skip_list) ADT. This data type is very useful as it allows for faster search time compared to a regualr linked list. The program contains a Makefile as well as a `main` program that showcases the various functions implemented. Upon successful runtime, the program exits with no memory leaks and exit code `0`. Otherwise, it terminates with exit code `1`. 

# Module Details

The module contains the following functions:
- STinit(max): Initializes a skiplist with the maximum level of forward pointers that can be achieved being `max`. Note that usually it is preferable that this maximum number should be constant for all skip lists, but for testing versatility it has been included
  as a parameter.
- STinsert(list, item): Adds an `item` to an existing skip list `list`
- STsearch(list, key): Searches for an item in the skip list with key(item) = `key`. If the search is successful, the function returns the item correspdoning to the key (in this case, it's the number itself), otherwise (if the key doesnt exist) it returns `NULLitem`.
- STdelete(list, key): Deletes an item with key(item) = key from a skip list
- STmerge(list1, list2): Merges two skiplists into one, and destroys the original lists. Note that the algorithm used for the implementation of this function is the smae as the one in Figure 7 of
  [this](https://cgi.di.uoa.gr/~k08/manolis/2024-2025/lectures/skip_list_cookbook.pdf) PDF.
- STprint(list): Prints the items of a skip list
- STdestroy(list): Destroys a skip list

# Compilation & Running

The directory contains a Makefile for compilation. In order to compile, simply type: 
```sh
make
```
In order to run a demo of the program, type: 
```sh
./main
```
