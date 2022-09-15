#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <errno.h>

#define NUM 10

/*
 This union has been commented in the latest <sys/sem.h>.
 Although it is in man page of "semctl", the comment shows: user should create this union manually.
*/
union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *__buf;
};


/* get semnum from local. */
int get_local_semval(int sid, int semnum)
{
	return semctl(sid, semnum, GETVAL, 0);

}


void Test_sem()
{
	int i = 0, sem_id = 0, pid = 0, ret = 0;
	struct sembuf sem_op;		// sem-union
	union semun sem_val;		// sem-value

	/* 
	 semget() : Set up semaphore set
	 IPC_PRIVATE : only for this process use
	 IPC_CREAT : Create a new semaphore set.
	 1 : The set contains 1 semaphore.
	 0600 : permission of this semaphore.
	contains 1 semaphore
	*/
	sem_id = semget(IPC_PRIVATE, 1, IPC_CREAT | 0600);

	if(sem_id == -1){
		printf("Create Sem Error!\n");
		exit(1);
	}
	printf("Create %d Sem in success!\n", sem_id);

	/* Initialize the value of semaphore. */
	sem_val.val = 1;
	ret = semctl(sem_id, 0, SETVAL, sem_val);

	if(ret < 0){
		printf("Initiliza Sem Error!\n");
		exit(1);
	}
	/* Fork a process */
	if((pid = fork()) < 0){
		printf("Fork Error!\n");
		exit(1);
	}
	if(pid == 0){
		for(i = 0; i < NUM; i++){
			sem_op.sem_num = 0;
			sem_op.sem_op = -1;		// Operate --> semval-1 every loop.
			sem_op.sem_flg = 0;
			semop(sem_id, &sem_op, 1);
			printf("%d user: %d\n", i, get_local_semval(sem_id, 0));
		}
	}else{
		for(i = 0; i < NUM; i++){
			sem_op.sem_num = 0;
			sem_op.sem_op = 1;		// Operate --> semval+1 every loop.
			sem_op.sem_flg = 0;
			semop(sem_id, &sem_op, 1);
			printf("%d provider: %d\n", i, get_local_semval(sem_id, 0));
		}
	}
	exit(0);
}

int main()
{
	Test_sem();

	return 0;
}

