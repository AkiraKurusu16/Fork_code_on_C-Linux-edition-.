#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
 
int calcoli_figlio1(int y){
  int k;
  printf("1.1 elab. parallela processo figlio 1 \n");
  k = 5 + y;
 return k; 
} 

int calcoli_figlio2(int z){
  int k;
  sleep(1);
  printf("1.2 elab. parallela processo figlio 2 \n");
  k = 7 * z + 3;
  printf("-> z = %d\n", k);
  return k; 
}

int calcoli_padre1(){
  int k, x;
  printf("1 elab. parallela processo padre \n");
  printf ("inserisci valore per la variabile x :");
  scanf ("%d", &x);
  k = 3 + x ;
  return k; 
} 

int calcoli_padre2(int a, int b, int c){
  int k;
  printf("2 elab. finale padre \n");
  k = (a - b * c);
  return k; 
} 
  
int main(){ 
  int x, y, z, ris, retv1, retv2;
  pid_t pid1, pid2;
  printf ("inserisci valore per la variabile y :");
  scanf ("%d", &y);
  printf ("inserisci valore per la variabile z :");
  scanf ("%d", &z);

  pid1 = fork();                        // fork per prendere la B.
  if (pid1 == 0){    
    y = calcoli_figlio1(y);             // check del pid per creare la C ed esecuzione parallela calcoli figlio
    exit(y);                            // termina processo figlio 
  }
  else{
    pid2 = fork();                      //inizio elaborazione parallela 
    if (pid2 == 0){    
      z = calcoli_figlio2(z);           // esecuzione parallela calcoli figlio
      exit(z);                          // termina processo figlio 
    }
    else
      x = calcoli_padre1();             // esecuzione parallela calcoli padre
  }
  printf(".. join: padre aspetta \n");
 
  waitpid(pid1, &retv1, 0);              // join : il padre aspetta il figlio pid1 
  y = WEXITSTATUS(retv1);                // prende il risultato del figlio
  printf("-> y = %d \n", y);
  // printf("-> y = %d \n", retv1>>8);
 
  waitpid(pid2, &retv2, 0);              // join : il padre aspetta il figlio pid2 
  z = WEXITSTATUS(retv2);                // prende il risultato del figlio
  printf("-> z = %d\n", z);
  // printf("-> z = %d \n", retv2>>8);
 
  ris = calcoli_padre2(x, y, z);        // esegue gli ultimi calcoli 
  printf("-> risultato finale ris = %d\n", ris);
}

Visualizzazione di ese_forkjoin1Sol.c.