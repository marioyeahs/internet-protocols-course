#include <stdio.h>
#include <stdlib.h>

int main(){

    int num[4];
    int ans=0;
    char buffer[256];              // Data buffer


    // while(ans<500){
    //     for(int i=0; i<4;i++){
    //         printf("Dame un número:");
    //         scanf("%d",&num[i]);
    //     }
    //     ans = (num[0]+num[1])*num[2]-num[3];
    //     if (ans < 500)
    //         printf("Total: %d, por favor vuelve a intentarlo.\n", ans);
    // }
    // printf("Bien, %d es mayor a 500\n", ans);
    printf("Cadena:");
    scanf("%c",*&buffer);
    printf("\nLa cadena es %c.", *buffer);
    return 0;
}