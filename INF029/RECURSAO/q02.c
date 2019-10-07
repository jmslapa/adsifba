#include <stdio.h>
#include <stdlib.h>

int fibo(int n);

int main(void){
	
	int n, i;
	
	puts("Informe um Numero");
	scanf("%d", &n);

	printf("%dº termo da sequencia fibonacci:", n);   
   
    printf(" %d\n", fibo(n)); 
    
    return 0;
}

int fibo(int n){
    
    if(n == 1)
        return 0;
    
    if(n == 2 || n == 3)
        return 1;
    
    return fibo(n-1) + fibo(n-2);      
}
