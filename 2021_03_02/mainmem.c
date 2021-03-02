#include <stdio.h>

int bss_var;
int data_var = 1;

int main(){
    //Vedo la locazione di memoria dove è localizzato il processo
    void *stack_var;
    stack_var = (void *) main;

    printf("Il programma sta eseguendo in: %p \n", stack_var);
    printf("Lo stack frame si trova a: %p \n", &stack_var);
    
    while(1);
    return 0;
}
