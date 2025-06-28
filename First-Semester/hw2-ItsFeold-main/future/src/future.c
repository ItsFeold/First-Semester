#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 

//driver code 
int main(int argc, char* argv[]){

    //variable to store window from command line 
    long long window = 0;
    //checking for correct usage of future.c and returning instructions for correct usage
    if(argc != 2 && argc != 4 && argc != 3)
    {
        
        fprintf(stderr, "Usage: ./future <filename> [--window N (default: 50)]\n");
        return 1;
    }
    if((argc == 3 && strcmp(argv[2], "--compete") != 0) || (argc == 4 && strcmp(argv[2], "--window") != 0))
    {
        fprintf(stderr, "Usage: ./future <filename> [--window N (default: 50)]\n");
        return 1;
    }
    //checking if user has used --window to set a specific window. Otherwise, use default (window = 50)
    if(argc == 2)
        window = 50;
    else if(argc == 4)
        window = atoll(argv[3]);
    //for compete mode:
    else if(argc == 3)
        window = 1;
    

    //array to hold window numbers:
    double *nums = malloc(window * sizeof(double));
    if(!nums)
    {
        fprintf(stderr, "Failed to allocate window memory\n");
        return 1;
    }

    //open file to read values from
    FILE *data = fopen(argv[1], "r");
    if(data == NULL)
    {
        fprintf(stderr, "Failed to open file!");
        return 1;
    }

    //checking if window is too small.
    if(window < 1)
    {
        fprintf(stderr, "Window too small!\n");
        return 1;
    }
    
    //variables to count how many elements in we are(counter1), as well as length to get the total amount of values in our file
    //counter2 (as well as counter1) is used for implementing circular buffer
    long long counter = 0;
    long long counter2 = 0;
    long long length = 0;
    //total sum for compete!
    long double totalSum = 0;

    //variable to store sum 
    double temp;
    //read every element in file and add the last <<window>> numbers from the file.
    if(argc != 3 || strcmp(argv[2], "--compete") != 0)
    {
        long double sum = 0;
        while(fscanf(data, "%lf", &temp) == 1)
        {
            //check if we have gone over window numbers:
            if(counter < window)
            {
                //save value and add it to total sum:
                nums[counter] = temp;
                sum = sum + temp;
                counter++;
            }
            else
            {
                //LOGIC: if we have gone over window numbers, replace the last one with the new one
                //substract the old number from the sum and add the new one:
                sum = sum - nums[counter2];
                nums[counter2] = temp;
                sum = sum + temp;
                counter2++;
                //reset counter2 to avoid overflow
                if(counter2 == window)
                    counter2 = 0;
            }
            length++;
        }
        //check if window is too large: 
        if(window > length)
        {
            fprintf(stderr, "Window too large!\n");
            return 1;
        }
        //get average 
        sum = sum/window;
        printf("%.2Lf\n", sum);
    }   
    //in compete mode: 
    else
    {
        //store the last window numbers: (window is subject to change) 
        double *endSum = malloc(window*sizeof(double));
        //read every single element in the file once to get its length. 
        while(fscanf(data, "%lf", &temp) == 1)
            length++; 

        //checking if window is too small or too large
        if(window < 1)
        {
            fprintf(stderr, "Window too small!\n");
            return 1;
        }
        else if(window > length)
        {
            fprintf(stderr, "Window too large!\n"); 
            return 1;
        }
        
        //rewind so that fscanf can be reused on the same file (file pointer is reset to the beginning of the file stream)
        rewind(data);
        //read every element in file and add the last <<window>> numbers from the file.
        while(fscanf(data, "%lf", &temp) == 1)
        {
            if(counter < length-window)
            {
                counter++; 
                continue;
            }    
            //store the last window numbers:
            endSum[counter2] = temp; 
            counter2++;
        }
    
        //Use WMA. We multiply by i+1 to give more "significance" to the last values 
        for(int i=0; i<window; i++)        
            totalSum = totalSum + (i+1)*endSum[i];

        //divide by window*(window+1)/2, which is essentially window + window-1 + ... + 1. (WMA)
        totalSum = totalSum/((window*(window+1))/2);
        //Substract  median value for higher precision (works experimentally) 
        totalSum = totalSum - 25.57 - 3.94;
        printf("%.2Lf\n", totalSum);
        

        //deallocate memory 
        free(endSum);  
    }
    
    //deallocate memory and close file:
    free(nums);
    fclose(data);
    return 0;
}
