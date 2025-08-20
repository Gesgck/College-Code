#include <stdio.h>

int main(int argc, char *argv[]){

    if (argc == 1){
        printf("Usage: time <command>\n");
        return 0;
    }
    
    
    int pid = fork();

    if(pid >0){
        pid = wait(0);
    }



    return 0;
}