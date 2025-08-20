#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <time.h>
#include <stdbool.h>
#include <errno.h>

const unsigned long MIN_THREADS = 1;
const unsigned long MAX_THREADS = 24;
const unsigned long MIN_LIMIT = 100;
const unsigned long BLOCK = 5000;
unsigned long currentIndex = 1;
unsigned long userLimit = 0;
unsigned long evilNumberCount = 0;
unsigned long odiousNumberCount = 0;
pthread_mutex_t currentIndexMutex;
pthread_mutex_t evilNumberCountMutex;
pthread_mutex_t odiousNumberCountMutex;

bool getArguments(int argc, char *argv[]){
    //check number of args
    if(argc != 7){
        printf("Error, invalid command line options.\n");   
        return false;
    }

    //checks for the tags
    if(argv[1][0] != '-' && argv[1][1] != 't' && argv[1][2] != '\0'){
        printf("Error, invalid thread count specifier.\n");   
        return false;
    }

    if(argv[3][0] != '-' && argv[3][1] != 'l' && argv[3][2] != '\0'){
        printf("Error, invalid limit specifier.\n");   
        return false;
    }

    if(argv[5][0] != '-' && argv[5][1] != 'f' && argv[5][2] != '\0'){
        printf("Error, invalid function specifier.\n");   
        return false;
    }

    //check if thread has any non numbers
    int count = 0;
    char check = argv[2][count++];
    while(check != '\0'){
        if(check < 48 || check > 57){
            printf("Error, invalid thread count value.\n");
            return false;
        }
        check = argv[2][count++];
    }
    count = 0;

    //check if thread count out of range
    if(atoi(argv[2]) > MAX_THREADS || atoi(argv[2]) < MIN_THREADS){
        printf("Error, thread count out of range.\n");   
        return false;  
    }
        
    //check if limit has any non numbers
    check = argv[4][count++];
    while(check != '\0'){
        if(check < 48 || check > 57){
            printf("Error, invalid limit value.\n");
            return false;
        }
        check = argv[4][count++];
    }
    count = 0;

    //check if limit too small
    if(atoi(argv[4]) < MIN_LIMIT){
        printf("Error, limit must be > 100.\n");   
        return false;  
    }
    userLimit = atoi(argv[4]);

    //check if function option is a number
    check = argv[6][count++];
    while(check != '\0'){
        if(check < 48 || check > 57){
            printf("Error, invalid function value.\n");
            return false;
        }
        check = argv[4][count++];
    }

    //check if function option is valid
    if(atoi(argv[6]) != 1 && atoi(argv[6]) != 2){
        printf("Error, function option must be 1 or 2.\n");   
        return false;   
    }
    
    return true;
}

void *findEvilNumbersCnt1(){
 
    unsigned long current = 0;
    unsigned long next;

    long count = 0;
    int pos = 0;
    int binary[64] = {0};

    while(current <= userLimit){
        //pthread_mutex_lock(&currentIndexMutex);
        current = currentIndex;
        currentIndex += BLOCK;
        //pthread_mutex_unlock(&currentIndexMutex);
        next = ++current;
        //CRITICAL
        for(int i = 0; i < BLOCK; i++){
            if(current > userLimit){
                break;
            }
            //get binary of current
            while(current > 0){
                binary[pos] = current % 2;
                current = current / 2;
                pos++;
            }
            pos = 0;
            current = next;
            next++;
            //count the 1s
            for(int j = 0; j < 64; j++){
                if(binary[j] == 1)
                    count++;
            }
            for(int j = 0; j < 64; j++){
                binary[j] = 0;
            }
            //find if even or odd # of ones
            if(count % 2 == 0){
                //pthread_mutex_lock(&evilNumberCountMutex);
                evilNumberCount++;
                //pthread_mutex_unlock(&evilNumberCountMutex);
            }
            else{
                //pthread_mutex_lock(&odiousNumberCountMutex);
                odiousNumberCount++;
                //pthread_mutex_unlock(&odiousNumberCountMutex);
            }
            count = 0;
        }
    }
    
    return NULL;

}

void *findEvilNumbersCnt2(){
 
    unsigned long current = 0;
    unsigned long next;


    long count = 0;
    int pos = 0;
    int binary[64] = {0};
    int odiousNums = 0, evilNums = 0;

    while(current <= userLimit){
        //pthread_mutex_lock(&currentIndexMutex);
        current = currentIndex;
        currentIndex += BLOCK;
        //pthread_mutex_unlock(&currentIndexMutex);
        next = ++current;
        //CRITICAL
        for(int i = 0; i < BLOCK; i++){
            if(current > userLimit){
                break;
            }
            //get binary of current
            while(current > 0){
                binary[pos] = current % 2;
                current = current / 2;
                pos++;
            }
            pos = 0;
            current = next;
            next++;
            //count the 1s
            for(int j = 0; j < 64; j++){
                if(binary[j] == 1)
                    count++;
            }
            for(int j = 0; j < 64; j++){
                binary[j] = 0;
            }
            //find if even or odd # of ones
            if(count % 2 == 0)
                evilNums++;
            else
                odiousNums++;
            count = 0;
        }
        //pthread_mutex_lock(&odiousNumberCountMutex);
        odiousNumberCount += odiousNums;
        //pthread_mutex_unlock(&odiousNumberCountMutex);
        //pthread_mutex_lock(&evilNumberCountMutex);
        evilNumberCount += evilNums;
        //pthread_mutex_unlock(&evilNumberCountMutex);
        evilNums = 0;
        odiousNums = 0;
    }
    
    return NULL;

}

int main(int argc, char *argv[]){

    if(!getArguments(argc, argv))
        return 0;

    pthread_t threads[MAX_THREADS];

    printf("Evil/Odious Numbers Program\n\n");

    printf("Hardware Cores: %ld\n",sysconf(_SC_NPROCESSORS_ONLN));
    printf("Thread Count:   %s\n",argv[2]);
    printf("Numbers Limit:  %s\n\n",argv[4]);
    printf("Please wait. Running...\n\n");

    if(atoi(argv[6]) == 1){
        for(int i = 0; i < atoi(argv[2]); i++){
            pthread_create(&threads[i], NULL, &findEvilNumbersCnt1, NULL);
        }
        for(int i = 0; i < atoi(argv[2]); i++){
            pthread_join(threads[i], NULL);
        }
    }
    else{
        for(int i = 0; i < atoi(argv[2]); i++){
            pthread_create(&threads[i], NULL, &findEvilNumbersCnt2, NULL);
        }
        for(int i = 0; i < atoi(argv[2]); i++){
            pthread_join(threads[i], NULL);
        }
    }

    printf("Evil/Odious Numbers Results\n");
    printf("  Evil Number Count:   %ld\n",evilNumberCount);
    printf("  Odious Number Count: %ld\n",odiousNumberCount);

    return 0;
}
