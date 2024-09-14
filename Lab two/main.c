#include <stdlib.h>
#include <stdio.h>
#include "leak_detector_c.h"

typedef struct student
{
  char *lname; //this will require DMA to store a string
  int assignment;
  int finalExam;
  int total;
  int *quizzes;//this will require DMA to store quizzes
}student;

student** readCourses(int *C, int *N, int *M){
  scanf("%d %d %d", C, N, M);
  student **studentList;
  studentList = (student**)calloc(*C, sizeof(student*));

  for(int i = 0; i<*C; i++){
    studentList[i] = (student*)calloc(*N, sizeof(student));
    
    for(int n = 0; n<*N; n++){
      studentList[i][n].lname = (char*)calloc(30, sizeof(char));
      studentList[i][n].quizzes = (int*)calloc(*M, sizeof(int));
      studentList[i][n].total = 0;

      scanf("%s", studentList[i][n].lname);
      scanf("%d", &studentList[i][n].assignment);
      studentList[i][n].total += studentList[i][n].assignment;
      for(int k = 0; k<*M; k++){
        scanf("%d", &studentList[i][n].quizzes[k]);
        studentList[i][n].total += studentList[i][n].quizzes[k];
      }
      scanf("%d", &studentList[i][n].finalExam);
      studentList[i][n].total += studentList[i][n].finalExam;
    }
  }

  return studentList;
}

void printHighestTotal(student **stList, int C, int N, int M){
  int max = stList[0][0].total;
  int maxCourse = 0;
  int maxStudent = 0;

  for(int i = 0; i<C; i++){
    for(int n = 0; n<N; n++){
      if(stList[i][n].total > max){
        max = stList[i][n].total;
        maxCourse = i;
        maxStudent = n;
      }
    }
  }
  printf("Name: %s\n", stList[maxCourse][maxStudent].lname);
  printf("Assignment: %d\n", stList[maxCourse][maxStudent].assignment);
  printf("Quizzes: ");
  for(int i = 0; i<M; i++){
    printf("%d ", stList[maxCourse][maxStudent].quizzes[i]);
  }
  puts("");
  printf("Final exam: %d\n", stList[maxCourse][maxStudent].finalExam);
  printf("Total: %d\n", stList[maxCourse][maxStudent].total);
  printf("Course number: %d", maxCourse + 1);
}

void release_memory(student **st, int C, int N, int M){
  for(int i = 0; i<C; i++){
    for(int n = 0; n<N; n++){
      free(st[i][n].lname);
      free(st[i][n].quizzes);
    }
    free(st[i]);
  }
  free(st);
}

int main(void) {
  atexit(report_mem_leak);
  student **courseList;
  int i, j, C, N, M;
  
  courseList = readCourses(&C, &N, &M);

  printHighestTotal(courseList, C, N, M);

  release_memory(courseList, C, N, M);
  
  return 0;
}