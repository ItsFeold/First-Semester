#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// Struct for each city. Every city has a name and a code (similiar to a vertex of a graph, for clarity during calculations)
typedef struct myCity 
{
    char* name;
    int code;
} city;

// DP function that returns the minimum cost. This is the Held Karp algorithm.
int totalCost(int mask, int curr, int n, int cost[64][64], int **memo, int **path) 
{
    //return 0 if all cities are visited (for regular tsp, this would have been the cost to go back to city 0)
    if (mask == (1 << n) - 1) 
        return 0; 
    //check if we have already calculated current iteration in DP table
    if (memo[curr][mask] != -1) 
        return memo[curr][mask];

    //initialize ans to max for comparison later
    int ans = INT_MAX;
    //iterating through every city
    for (int i = 0; i < n; i++) 
    {
        //check if city i is not visited
        if((mask & (1 << i)) == 0) 
        {
            //newCost is the cost to go from curr to i, + the rest of the way 
            int newCost = cost[curr][i] + totalCost(mask | (1 << i), i, n, cost, memo, path);
            if (newCost < ans) 
            {
                ans = newCost;
                //update this array to keep track of index. 
                path[curr][mask] = i; 
            }
        }
    }
    //store in DP table 
    memo[curr][mask] = ans;
    return ans;
}

//this is a preperation function to initialize matrixes that we need such as memo table and array to keep track of the path we took
int tsp(int cost[64][64], int cityCounter, city cities[64]) 
{
    
    int n = cityCounter;
    //initialize memo table for DP, as well as path to store the path we took. These are n * 2^n size.
    int **memo = malloc(n * sizeof(int *));
    int **path = malloc(n * sizeof(int *));
    if (memo == NULL || path == NULL) 
    {
        fprintf(stderr, "Failed to allocate memory!");
        exit(1);
    }

    for (int i = 0; i < n; i++) 
    {
        memo[i] = malloc((1 << n) * sizeof(int));
        path[i] = malloc((1 << n) * sizeof(int));
        //check if malloc failed;
        if (memo[i] == NULL || path[i] == NULL) 
        {
            fprintf(stderr, "Failed to allocate memory!");
            exit(1);
        }
        //apparently i get segmentation fault if not using memset. Calloc failed as well for some reason?
        memset(memo[i], -1, (1 << n) * sizeof(int));
        memset(path[i], -1, (1 << n) * sizeof(int));
    }

    //calculate cost using Held-Karp algorithm (DP)
    int result = totalCost(1, 0, n, cost, memo, path);

    // Print the path
    printf("We will visit the cities in the following order:\n");
    //start at city 0 (mask = 1 because, for eg, in the form 0001, only city 0 is visited)
    int mask = 1, curr = 0;

    //counter to get correct format (e.g, 4 cities every line)
    int newlineCounter = 0;

    //print first city
    printf("%s", cities[curr].name); 
    //while not every city is visited:
    while (mask != (1 << n) - 1) 
    {
        //store current city
        int tempCode = curr;
        //get next city
        curr = path[curr][mask];

        //this spaghetti code counter is to print 4 cities per line
        if(newlineCounter < 3)
        {
            printf(" -(%d)-> %s", cost[curr][tempCode], cities[curr].name);
            newlineCounter++;
        }
        else
        {
            printf(" -(%d)->\n%s", cost[curr][tempCode], cities[curr].name);
            newlineCounter = 0;
        }
        //this enables the bit of the current city in the mask (our binary number to represent visited cities)
        mask = mask | (1 << curr);
    }
    printf("\n");
    //deallocating memory
    for (int i = 0; i < n; i++) 
    {
        free(memo[i]);
        free(path[i]);
    }
    free(memo);
    free(path);

    return result;
}

//driver code
int main(int argc, char* argv[]) 
{
    //check for correct usage, print instructions if incorrect and return 1
    if (argc != 2) 
    {
        fprintf(stderr, "Usage: ./jabbamaps <filename>\n");
        return 1;
    }

    //open map.txt
    FILE *data = fopen(argv[1], "r");
    if (data == NULL) 
    {
        fprintf(stderr, "Failed to open input file!\n");
        return 1;
    }

    //up to 64 cities so make a static array for it, to store names and code of each city.
    city cities[64];
    
    //Buffer to hold string of arbitary size (read entire line and then get each string seperately)
    char *line = NULL;
    size_t n = 0;

    //variable for storing distance between each city 
    int distance;

    //matrix to store costs of moving from one city to another(up to 64 cities so we dont need more)
    int costs[64][64];
    //variable for storing the amount of cities
    int cityCounter = 0;

    //read file data and store in matrix
    while (getline(&line, &n, data) != -1) 
    {
        //since we know the format of each line, just use strtok to get each string we need seperately
        char *cityName1 = strtok(line, "-");
        char *cityName2 = strtok(NULL, ":");
        char *distanceStr = strtok(NULL, "\n");

        // Create dynamic copies of the city names. If i dont strdup these i get core dumped.
        cityName1 = strdup(cityName1);
        cityName2 = strdup(cityName2);

        //convert string to integer
        distance = atoi(distanceStr);

        //helper variables for checking whether city already exists, and for storing code of each city. 
        int found1 = 0; 
        int found2 = 0; 
        int code1; 
        int code2;

        //check if cities already exist in cities[] array
        for (int j = 0; j < cityCounter; j++) 
        {
            //pray for non-null values 
            if (strcmp(cities[j].name, cityName1) == 0) 
            {
                found1 = 1;
                code1 = cities[j].code;
            }
            if (strcmp(cities[j].name, cityName2) == 0) {
                found2 = 1;
                code2 = cities[j].code;
            }
        }

        //if city1 isnt found, make a new one.
        if (found1 == 0) 
        {
            cities[cityCounter].name = cityName1;
            cities[cityCounter].code = cityCounter;
            code1 = cityCounter++;
        } 
        //if not used then free otherwise segmentation fault
        else   
            free(cityName1);

        //if city2 isnt found, make a new one.
        if (found2 == 0) 
        {
            cities[cityCounter].name = cityName2;
            cities[cityCounter].code = cityCounter;
            code2 = cityCounter++;
        } 
        //if not used then free otherwise segmentation fault
        else    
            free(cityName2);
        
        //assign values to costs matrix. Our matrix is symmetric, since costs[i][j] = costs[j][i]
        //Obviously, because going from i to j is the same as going from j to i.
        costs[code1][code2] = distance;
        costs[code2][code1] = distance;
    }
    //free "buffer"
    free(line);

    //close file
    fclose(data);
    if(cityCounter == 0)
    {
        fprintf(stderr, "Error: File is empty!\n");
        return 1;
    }
    
    //calculate result.
    int result = tsp(costs, cityCounter, cities);
    printf("Total cost: %d\n", result);

    //free strings used for names.
    for (int i = 0; i < cityCounter; i++) 
        free(cities[i].name);
    
    //Terminate gracefully.
    return 0;
}
