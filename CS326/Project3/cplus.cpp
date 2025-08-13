#include<iostream>

void swap(int* a, int* b){
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

int main(){
    int i = 5;
    int lst[2] = {1, 3};

    swap(&i, &lst[0]);

    std::cout<<"i = " <<i <<"\nlst[0] = " <<lst[0] <<std::endl;

    return 0;
}