#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <errno.h> 

const unsigned int VEHICLE_CNT_MIN = 10;
const unsigned int VEHICLE_CNT_MAX = 500;

const unsigned int LIGHT_WAIT = 4;
const unsigned int YELLOW_WAIT = 1;
const unsigned int TRANSIT_TIME_BASE = 1;
const unsigned int ARRIVAL_INTERVAL = 2;

const unsigned int NORTH = 0;
const unsigned int EAST = 1;
const unsigned int SOUTH = 2;
const unsigned int WEST = 3;

sem_t *lights;

bool getArguments(int argc, char *argv[]){
    //check number of args
    if(argc != 3){
        printf("Usage: ./traffic -vc <vehicleCount>\n");   
        return false;
    }

    //checks for the tags
    if(argv[1][0] != '-' || argv[1][1] != 'v' || argv[1][2] != 'c' || argv[1][3] != '\0'){
        printf("Error, invalid item count specifier.\n");   
        return false;
    }

    //check if vc has any non numbers
    int count = 0;
    char check = argv[2][count++];
    while(check != '\0'){
        if(check < 48 || check > 57){
            printf("Error, invalid vehicle count value.\n");
            return false;
        }
        check = argv[2][count++];
    }

    //check if vc count is out of range
    if(atoi(argv[2]) > VEHICLE_CNT_MAX || atoi(argv[2]) < VEHICLE_CNT_MIN){
        printf("Error, vehicle count value out of range.\n");   
        return false;  
    }
    
    return true;
}


void *car(void *arg){

    int *direction = (int *)arg;


    switch(*direction){
        case 0:
            printf("↕ Vehicle approaching from North\n");
            sem_wait(&lights[NORTH]);
            printf("↔ Vehicle passing through from North\n");
            sleep(TRANSIT_TIME_BASE + usleep(rand()%5000));
            sem_post(&lights[NORTH]);
            break;
        case 1:
            printf("↕ Vehicle approaching from East\n");
            sem_wait(&lights[EAST]);
            printf("↔ Vehicle passing through from East\n");
            sleep(TRANSIT_TIME_BASE + usleep(rand()%5000));
            sem_post(&lights[EAST]);
            break;
        case 2:
            printf("↕ Vehicle approaching from South\n");
            sem_wait(&lights[SOUTH]);
            printf("↔ Vehicle passing through from South\n");
            sleep(TRANSIT_TIME_BASE + usleep(rand()%5000));
            sem_post(&lights[SOUTH]);
            break;
        case 3:
            printf("↕ Vehicle approaching from West\n");
            sem_wait(&lights[WEST]);
            printf("↔ Vehicle passing through from West\n");
            sleep(TRANSIT_TIME_BASE + usleep(rand()%5000));
            sem_post(&lights[WEST]);
            
    }

    return NULL;
}


void *lightController(){

    do{
        printf("\033[0;92mGreen light for North-South\033[0m\n");
        sem_post(&lights[NORTH]);
        sem_post(&lights[SOUTH]);
        sleep(LIGHT_WAIT);
        printf("\033[0;93mYellow light for North-South\033[0m\n");
        sleep(YELLOW_WAIT);
        printf("\033[0;31mRed light for North-South\033[0m\n");
        sem_wait(&lights[NORTH]);
        sem_wait(&lights[SOUTH]);
        printf("\033[0;92mGreen light for East-West\033[0m\n");
        sem_post(&lights[EAST]);
        sem_post(&lights[WEST]);
        sleep(LIGHT_WAIT);
        printf("\033[0;93mYellow light for East-West\033[0m\n");
        sleep(YELLOW_WAIT);
        printf("\033[0;31mRed light for East-West\033[0m\n");
        sem_wait(&lights[EAST]);
        sem_wait(&lights[WEST]);
    }while(true);

    return NULL;
}


int main(int argc, char *argv[]){

    if(!getArguments(argc, argv))
        return 0;
    
    printf("\033[0;4mCS 370 Project #5B -> Traffic Light "
    "Simulation Project\033[0m\n");
    printf("\tVehicles: ");
    printf("%s\n\n", argv[2]);

    lights = (sem_t*)malloc(4*sizeof(sem_t));

    //0 = north, 1 = east, 2 = south, 3 = west
    sem_init(&lights[NORTH], 0, 0);
    sem_init(&lights[SOUTH], 0, 0);
    sem_init(&lights[EAST], 0, 0);
    sem_init(&lights[WEST], 0, 0);

    pthread_t *cars = (pthread_t*)malloc(atoi(argv[2]) * sizeof(pthread_t));
    pthread_t controller;

    pthread_create(&controller, NULL, lightController, NULL);

    for(int i = 0; i < atoi(argv[2]); i++){
        int direction = rand()%4;
        pthread_create(&cars[i], NULL, car, &direction);
        sleep(ARRIVAL_INTERVAL);
    }
    for(int i = 0; i < atoi(argv[2]); i++){
        pthread_join(cars[i], NULL);
    }
    
    pthread_cancel(controller);
    pthread_join(controller, NULL);

    //deallocate and destroy everything
    free(cars);
    sem_destroy(&lights[NORTH]);
    sem_destroy(&lights[EAST]);
    sem_destroy(&lights[SOUTH]);
    sem_destroy(&lights[WEST]);
    free(lights);

    printf("All vehicles successfully passed through the intersection.\n");

    return 0;
}
