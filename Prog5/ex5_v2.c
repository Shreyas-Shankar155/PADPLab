#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSG_SIZE 100
char messages[5][MSG_SIZE] = {"Hello", "CSE", "RVCE","Daydream", "Random"};

int main(int argc, char *argv[])
	{
	int rank, num_processes;
//	char name[MPI_MAX_PROCESSOR_NAME]; 
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); //find rank of current process
	MPI_Comm_size(MPI_COMM_WORLD, &num_processes); //returns number of processes executing
	
	
	if(num_processes>6)
		{
		if(rank==0)
			printf("Number of processes>4. Exiting...\n");
		
		MPI_Finalize();
		exit(1);
		}	
	
	//printf("Hello from rank %d\n",rank);

	if(rank==0)
		{
		MPI_Status status;
		char msg[MSG_SIZE];
		for(int i=1; i<num_processes; i++)
			{
			MPI_Recv(&msg, MSG_SIZE, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status ); 
				//message buffer, message size, datatype, sender's rank, tag, comm, status
			printf("Message received from process %d:\t%s\n",status.MPI_SOURCE ,msg);
			
			}
		}
	else	{
		char temp_msg[MSG_SIZE];
		strcpy(temp_msg , messages[rank-1]);
		
		MPI_Send(&temp_msg, strlen(temp_msg)+1, MPI_CHAR, 0, 0, MPI_COMM_WORLD); 
		//IMPORTANT: sending length = string length + 1 to account for null character
		}
	
	MPI_Finalize(); //terminate the MPI execution environment
	
	return 0;
	}
