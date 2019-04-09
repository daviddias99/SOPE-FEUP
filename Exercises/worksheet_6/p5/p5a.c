#include <stdio.h>
#include <pthread.h>

struct operands{

    int a;
    int b;

};

void* sum_func_arr(void* arg){

    int* ops = (int*)arg;

    printf("%d + %d = %d \n",ops[0],ops[1],ops[0]+ops[1]);

    return NULL;
}

void* sub_func_struct(void* arg){

    struct operands* ops = (struct operands*) arg;

    printf("%d - %d = %d \n",ops->a,ops->b,ops->a - ops->b);

    return NULL;
}

void* div_func_struct(void* arg){

    struct operands* ops = (struct operands*) arg;

    printf("%d / %d = %f \n",ops->a,ops->b,(float)ops->a / ops->b);

    return NULL;
}

void* mul_func_struct(void* arg){

    struct operands* ops = (struct operands*) arg;

    printf("%d * %d = %d \n",ops->a,ops->b,ops->a * ops->b);

    return NULL;
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


    pthread_exit(0);
}