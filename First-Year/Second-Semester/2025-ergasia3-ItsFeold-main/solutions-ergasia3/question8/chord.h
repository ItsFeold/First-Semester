#ifndef CHORD_H
#define CHORD_H

// Useful defines & Struct definitions

// Maximum number of nodes in Chord ring
#define MAXNODENUMBER 50
// Maximum number of fingers (also will be used to assign IDs to nodes)
#define M 6
// Maximum number of files each server can hold 
#define MAXFILES 100
// Define nullSize for failure during lo okup
#define nullSize -1



// Struct definition for a server file (this simulates the data (keys) we store in the Chord ring)
typedef struct server_file {
    // Name of file
    char* filename;     // This is the "key" 
    // Size of file
    int size;           // This is the "value"
} Sfile;

// Struct definition for a chord server (this simulates the node in the Chord ring)
typedef struct chord_server {
    unsigned int id;     // Number between 0 and 2^M-1
    struct chord_server* successor;     // Successor node in the ring
    struct chord_server* fingers[M];    // Fingertable (m+1 for indexing at 1)
    Sfile files[MAXFILES];              // List of files saved in server
    int fileCount;                           // Number of files saved in the server
} Server;

extern Server* serverList;

// The Chord Ring
typedef struct chord_hashtable {
    Server* servers;      // Array of servers
    int serverCount;    // Count of server in Chord Ring
} CHashtable;


/* Function Prototypes */

// Function that initializes a chord ring with MAXNODENUMBER servers
void initialize(void);

// Function to insert a file into the Chord Ring (this is asked from the server in the parameter)
// (We will insert a file with filename and size)
void insert(Server* server, char* filename, int size);

// Function to search for value (this is asked from the server in the parameter) in the Chord Ring
// If the key doesnt exist, return nullSize
int lookup(Server* server, char* filename);

// lookup function using finger tables for higher efficiency
// If the key doesnt exist, return nullSize
int smartLookup(Server* server, char* filename);

// Function to deallocate memory for chord ring
void Destroy();

#endif 