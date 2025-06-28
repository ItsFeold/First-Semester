#include "chord.h"
#include <stdlib.h>
#include <stdio.h>

// Pointer to access all servers in main.c
Server* serverList = NULL;

static CHashtable* chord;

//DJB2 hash function
unsigned int DJB2Hash(char *filename){

    unsigned int hash = 5381;
    unsigned int c;

    while ((c = *filename++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % (1 << M);
}

// Helper function to be used as a compare function in qsort
int sortInt(const void* a, const void* b) {
    return ((const Server *)a)->id - ((const Server *)b)->id;
}

// Ask server n to find the successor of id
Server* find_successor(Server* server, int hash) {
    // Iterate through circle to find successor
    Server* curr = server;
    while(1) {
        // Base condition
        if(curr->id < curr->successor->id) {
            // if id is in the range (n, succesor], return
            if(hash > curr->id && hash <= curr->successor->id)
            return curr->successor;
        } else {    // Wrap around logic
            if (hash > curr->id || hash <= curr->successor->id)
                return curr->successor;
        }
        curr = curr->successor;
    }

}



// Function that initializes a chord ring with MAXNODENUMBER servers
void initialize(void) {
    // Allocate memory for chord and its servers
    chord = malloc(sizeof(CHashtable));
    if(!chord) {
        fprintf(stderr, "Failed to allocate chord memory!\n");
        return;
    }
    chord->serverCount = MAXNODENUMBER;
    chord->servers = malloc(MAXNODENUMBER*(sizeof(Server)));
    if(!chord->servers) {
        fprintf(stderr, "Failed to allocate chord server memory!\n");
        return;
    }
    // Normally we would assign IDs based on some other information, like an ip address, but this is easier 
    for(int i=0; i<MAXNODENUMBER; i++) 
        chord->servers[i].id = i * ( (1 << M) / MAXNODENUMBER);    
    
        
    // Sort array based on ID for nice clockwise pattern
    qsort(chord->servers, MAXNODENUMBER, sizeof(Server), sortInt);

    // Loop over servers and initialize members
    for(int i=0; i<MAXNODENUMBER; i++) {
        // Assign Successors. The % MAXNODENUMBER is basically just for the wrap around
        chord->servers[i].successor = &chord->servers[(i+1) % MAXNODENUMBER];
        chord->servers[i].fileCount = 0;    
    }
    
    for(int i=0; i<MAXNODENUMBER; i++) {
        // Initialize fingers to NULL 
        for(int k=0; k<M; k++)  
            chord->servers[i].fingers[k] = find_successor(&chord->servers[i], (chord->servers[i].id + (1 << k)) % (1 << M));
    }
    serverList = chord->servers;
}

// Function to insert a file into the Chord Ring (this is asked from the server in the parameter)
// (We will insert a file with filename and size)
void insert(Server *server, char* filename, int size) {
    // Get hash of file
    int hash = DJB2Hash(filename);
    // Find successor of id (hash)
    Server* curr = find_successor(server, hash);
    
    // Check for storage
    if(curr->fileCount < MAXFILES)
        curr->files[(curr->fileCount)++] = (Sfile){filename, size};
    else
        printf("Attempt to add file to server with no more storage!\n");

    return;
}

// Function to search for value (this is asked from the server in the parameter) in the Chord Ring
// If the key doesnt exist, return nullSize
int lookup(Server* server, char* filename) {
    int hash = DJB2Hash(filename);
    // Find successor of id (hash)
    Server* correctServer = find_successor(server, hash);
    // Scan the server's storage for the correct file
    for(int i=0; i<correctServer->fileCount; i++) {
        if(correctServer->files[i].filename == filename)
            return correctServer->files[i].size;
    }
    return nullSize;
}

// Search the local table for the highest predecessor of id (need this function for smart lookup)
Server* closest_preceding_node(Server* server, int id) {
    // Loop through fingers to find the node closest to id
    for(int i=M-1; i>=0; i--) {
        if(server->fingers[i]->id > server->id && server->fingers[i]->id < id)
            return server->fingers[i];
    }
    return server;
}

// Function to find successor using finger table (for smart lookup)
Server* smart_find_successor(Server* server, int id) {
    // Iterate through circle to find successor
    Server* curr = server;
    while(1) {
        // Base condition
        if(curr->id < curr->successor->id) {
            // if id is in the range (n, succesor], return
            if(id > curr->id && id <= curr->successor->id)
            return curr->successor;
        } else {    // Wrap around logic
            if (id > curr->id || id <= curr->successor->id)
                return curr->successor;
        }
        Server* next = closest_preceding_node(curr, id);
        if(next != curr)
            curr = next;
        else 
            curr = curr->successor;
    }
}

// lookup function using finger tables for higher efficiency
// If the key doesnt exist, return nullSize
int smartLookup(Server* server, char* filename) {
    int hash = DJB2Hash(filename);
    Server* correctServer = smart_find_successor(server, hash);
    // Scan the server's storage for the correct file
    for(int i=0; i<correctServer->fileCount; i++) {
        if(correctServer->files[i].filename == filename)
            return correctServer->files[i].size;
    }
    return nullSize;
}

// Function to deallocate memory for chord ring
void Destroy() {
    free(chord->servers);
    free(chord);
}


