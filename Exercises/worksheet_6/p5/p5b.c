#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

struct operands{

    int a;
    int b;

};

void* sum_func_arr(void* arg){

    int* ops = (int*)arg;

    int* result = (int*) malloc(sizeof(int));
    *result =ops[0]+ops[1];

    return (void*)result;
}

void* sub_func_struct(void* arg){

    struct operands* ops = (struct operands*) arg;

    int* result = (int*) malloc(sizeof(int));
    *result =ops->a - ops->b;

    return (void*)result;
}

void* div_func_struct(void* arg){

    struct operands* ops = (struct operands*) arg;

    float* result = (float*) malloc(sizeof(float));
    *result = (float)ops->a / ops->b;

    return (void*)result;
}

void* mul_func_struct(void* arg){

    struct operands* ops = (struct operands*) arg;
    int* result = (int*) malloc(sizeof(int));
    *result =ops->a * ops->b;

    return (void*)result;
}

int main(int argc, char* arv[]){

    int a,b;


    printf("Number A ? ");
    fflush(stdout);
    scanf("%d",&a);
    printf("Number B ? ");
    fflush(stdout);
    scanf("%d",&b);
    
    int opArr[2] = {a,b};
    struct operands ops = {a,b};
    pthread_t sumTh,subTh,divTh,mulTh;

    pthread_create(&sumTh,NULL,&sum_func_arr,(void*)&opArr);
    pthread_create(&subTh,NULL,&sub_func_struct,(void*)&ops);
    pthread_create(&divTh,NULL,&div_func_struct,(void*)&ops);
    pthread_create(&mulTh,NULL,&mul_func_struct,(void*)&ops);

    int* sumRes, *subRes, *mulRes;
    float* divRes;

    pthread_join(sumTh,(void*)&sumRes);
    pthread_join(subTh,(void*)&subRes);
    pthread_join(divTh,(void*)&divRes);
    pthread_join(mulTh,(void*)&mulRes);

    printf("%d + %d = %d \n",opArr[0],opArr[1],*sumRes);
    printf("%d - %d = %d \n",opArr[0],opArr[1],*subRes);
    printf("%d / %d = %f \n",opArr[0],opArr[1],*divRes);
    printf("%d * %d = %d \n",opArr[0],opArr[1],*mulRes);


    pthread_exit(0);
}