#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_STUDENTS 5

pthread_t thread_id[MAX_STUDENTS];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
int pizza = 0;
int S = 8;
int slices = 0;
bool firstToSee = true;
int errno;

sem_t sem;

void * student(void * arg){

  int stid = (int)arg + 1;
    sem_wait(&sem);
    
    if(slices > 0){
      slices--;
      printf("Student %d took slice %d of pizza from pizza %d\n", stid, (S - slices), pizza);
    }else{
    
      if(slices == 0 && firstToSee == true && pizza < 13){
      
        printf("Out of pizza. Student %d is calling Seasons for pizza %d.\n", stid, (pizza + 1));
        printf("The students are sleeping now.\n");
        sleep(rand() % 3);
        
        firstToSee = false;
        slices = S;
        pizza++;
        
        printf("Pizza %d delivered.\n", pizza);
        firstToSee = true;
        printf("Waking up sleeping students\n");
        
      }
      if(slices == 0 && pizza >= 13){
      
        printf("The students are finished studying and eating pizza.\n");
        exit(0);
        
      }
    }
    sem_post(&sem);
    sleep(rand() % 3);
}

int main(){
  sem_init(&sem, 0, 1);
  int students;
  printf("Enter number of students (2-5): ");
  scanf("%d", &students);
  if((students < 2) || (students > 5)){
    printf("Invalid input. Exiting program.\n");
    exit(0);
  }
  while(pizza < 14){
    for(int i = 0; i < students; i++){
      sem_wait(&sem);
      thread_id[i] = i;
      errno = pthread_create(&thread_id[i], NULL, student, (void*)i);
      if(errno != 0){
        fprintf(stderr, "pthread_create failed with i = %d. errno = %d, %s\n", i, errno, strerror(errno));
      }
      sem_post(&sem);
    }
  }
  sem_destroy(&sem);
  exit(0);
}
