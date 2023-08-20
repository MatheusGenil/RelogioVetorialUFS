/**
 * Código base (incompleto) para implementação de relógios vetoriais.
 * Meta: implementar a interação entre três processos ilustrada na figura
 * da URL: 
 * 
 * https://people.cs.rutgers.edu/~pxk/417/notes/images/clocks-vector.png
 * 
 * Compilação: mpicc -o rvet rvet.c
 * Execução:   mpiexec -n 3 ./rvet
 */
 
#include <stdio.h>
#include <string.h>  
#include <mpi.h>     


typedef struct Clock { 
   int p[3];
} Clock;


void Event(int pid, Clock *clock){
   clock->p[pid]++;   
}


void Send(int pid, Clock *clock){
}

void Receive(int pid, Clock *clock){
   // TO DO

}


// Representa o processo de rank 0
void process0(){
   Clock clock = {{0,0,0}};
   Clock received_clock;
   
   //-------------------------------
   Event(0, &clock); // (1,0,0)
   printf("Process: %d, Clock: (%d, %d, %d)\n", 0, clock.p[0], clock.p[1], clock.p[2]);
   
   //-------------------------------
   Event(0, &clock); // (2,0,0)
   printf("Process: %d, Clock: (%d, %d, %d)\n", 0, clock.p[0], clock.p[1], clock.p[2]);
   MPI_Send(&clock, sizeof(Clock), MPI_BYTE, 1, 0, MPI_COMM_WORLD);
   
   //-------------------------------
   Event(0, &clock); // (3,0,0)
   MPI_Recv(&received_clock, sizeof(Clock), MPI_BYTE, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
   
   if (received_clock.p[0] > clock.p[0]){
      clock.p[0] = received_clock.p[0];
   }
   if (received_clock.p[1] > clock.p[1]){
      clock.p[1] = received_clock.p[1];
   }
   if (received_clock.p[2] > clock.p[2]){
      clock.p[2] = received_clock.p[2];
   }
   printf("Process: %d, Clock: (%d, %d, %d)\n", 0, clock.p[0], clock.p[1], clock.p[2]);
   
   //-------------------------------
   Event(0, &clock); // (4,0,0)
   printf("Process: %d, Clock: (%d, %d, %d)\n", 0, clock.p[0], clock.p[1], clock.p[2]);
   MPI_Send(&clock, sizeof(Clock), MPI_BYTE, 2, 0, MPI_COMM_WORLD);
   
   //-------------------------------
   Event(0, &clock); // (5,0,0)
   MPI_Recv(&received_clock, sizeof(Clock), MPI_BYTE, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
   
   if (received_clock.p[0] > clock.p[0]){
      clock.p[0] = received_clock.p[0];
   }
   if (received_clock.p[1] > clock.p[1]){
      clock.p[1] = received_clock.p[1];
   }
   if (received_clock.p[2] > clock.p[2]){
      clock.p[2] = received_clock.p[2];
   }
   printf("Process: %d, Clock: (%d, %d, %d)\n", 0, clock.p[0], clock.p[1], clock.p[2]);
   
   //-------------------------------
   Event(0, &clock); // (6,0,0)
   printf("Process: %d, Clock: (%d, %d, %d)\n", 0, clock.p[0], clock.p[1], clock.p[2]);
   MPI_Send(&clock, sizeof(Clock), MPI_BYTE, 1, 0, MPI_COMM_WORLD);
   
   //-------------------------------
   Event(0, &clock); // (7,0,0)
   printf("Process: %d, Clock: (%d, %d, %d)\n", 0, clock.p[0], clock.p[1], clock.p[2]);
   

}

// Representa o processo de rank 1
void process1(){
   Clock clock = {{0,0,0}};
   Clock received_clock;
   
   Event(1, &clock);
   printf("Process: %d, Clock: (%d, %d, %d)\n", 1, clock.p[0], clock.p[1], clock.p[2]);
   MPI_Send(&clock, sizeof(Clock), MPI_BYTE, 0, 0, MPI_COMM_WORLD);
   
   Event(1, &clock);
   MPI_Recv(&received_clock, sizeof(Clock), MPI_BYTE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
   if (received_clock.p[0] > clock.p[0]){
      clock.p[0] = received_clock.p[0];
   }
   if (received_clock.p[1] > clock.p[1]){
      clock.p[1] = received_clock.p[1];
   }
   if (received_clock.p[2] > clock.p[2]){
      clock.p[2] = received_clock.p[2];
   }
   printf("Process: %d, Clock: (%d, %d, %d)\n", 1, clock.p[0], clock.p[1], clock.p[2]);
   
   
   Event(1, &clock);
   MPI_Recv(&received_clock, sizeof(Clock), MPI_BYTE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
   if (received_clock.p[0] > clock.p[0]){
      clock.p[0] = received_clock.p[0];
   }
   if (received_clock.p[1] > clock.p[1]){
      clock.p[1] = received_clock.p[1];
   }
   if (received_clock.p[2] > clock.p[2]){
      clock.p[2] = received_clock.p[2];
   }
   printf("Process: %d, Clock: (%d, %d, %d)\n", 1, clock.p[0], clock.p[1], clock.p[2]);
   
}

// Representa o processo de rank 2
void process2(){
   Clock clock = {{0,0,0}};
   Clock received_clock;
   
   Event(2, &clock);
   printf("Process: %d, Clock: (%d, %d, %d)\n", 2, clock.p[0], clock.p[1], clock.p[2]);
   
   Event(2, &clock);
   printf("Process: %d, Clock: (%d, %d, %d)\n", 2, clock.p[0], clock.p[1], clock.p[2]);
   MPI_Send(&clock, sizeof(Clock), MPI_BYTE, 0, 0, MPI_COMM_WORLD);
   
   Event(2, &clock);
   MPI_Recv(&received_clock, sizeof(Clock), MPI_BYTE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
   if (received_clock.p[0] > clock.p[0]){
      clock.p[0] = received_clock.p[0];
   }
   if (received_clock.p[1] > clock.p[1]){
      clock.p[1] = received_clock.p[1];
   }
   if (received_clock.p[2] > clock.p[2]){
      clock.p[2] = received_clock.p[2];
   }
   printf("Process: %d, Clock: (%d, %d, %d)\n", 2, clock.p[0], clock.p[1], clock.p[2]);

}

int main(void) {
   int my_rank;               

   MPI_Init(NULL, NULL); 
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 

   if (my_rank == 0) { 
      process0();
   } else if (my_rank == 1) {  
      process1();
   } else if (my_rank == 2) {  
      process2();
   }

   /* Finaliza MPI */
   MPI_Finalize(); 

   return 0;
}  /* main */