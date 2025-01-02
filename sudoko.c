#include <stdio.h>
#include <stdlib.h>
#define SIZE 9
// printf("%ld\n",rand()%9);
int** make_field();
void free_mem(int** field);
void output(int** field);

int check_square(int** field,int ind_i, int ind_j, long num);
int check_row(int** field, int ind, long num);
void regenerate_num(int** field, int ind_i, int ind_j, long* num);
int check_colom(int** field, int ind_j,long num);
int check_uniq(int** field);


void generate(int** field);
int main() {
  int** field = make_field(SIZE);
  generate(field);
  output(field);
  printf("UNIQ is %d\n",check_uniq(field));
  free_mem(field);
  return 0;
}

int** make_field() {
  int** matrix = malloc(SIZE * sizeof(int*));

  for (int i = 0; i < 9; i++) {
    matrix[i] = calloc(SIZE, sizeof(int));
  }
  return matrix;
}

void free_mem(int** field) {
  for (int i = 0; i < SIZE; i++) {
    free(field[i]);
  }
  free(field);
}

void output(int** field) {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      if ((j + 1) % 3 == 0) {
        printf("%d|", field[i][j]);
      }

      else {
        printf("%d ", field[i][j]);
      }
    }
    printf("\n");
  }
}

void generate(int** field) {
  long r_num = (rand() % 10);
  if (r_num == 0) {
    r_num += 1;
  }
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      regenerate_num(field, i, j, &r_num);
      field[i][j] = r_num;
      output(field);
    }
  }
}

int check_row(int** field, int ind, long num) {
  int flag = 0;
  for (int i = 0; i < SIZE; i++) {
    if (field[ind][i] == num) {
      flag = 1;
      break;
    }
  }
  return flag;
}
int check_colom(int** field, int ind, long num) {
  int flag = 0;
  for (int i = 0; i < SIZE; i++) {
    if (field[i][ind] == num) {
      flag = 1;
      break;
    }
  }
  return flag;
}

int check_square(int** field,int ind_i, int ind_j, long num){
  int start_i = 0;
  int start_j = 0;
  int flag = 0;

  if (ind_i>=3 && ind_i<=5){
    start_i = 3;
  }else if (ind_i>=6){
    start_i = 6;
  }

  if (ind_j>=3 && ind_j<=5){
    start_j = 3;
  }else if (ind_j>=6){
    start_j = 6;
  }


  // printf("start i = %d\n",start_i);
  // printf("start j = %d\n",start_j);
  int end_i = start_i + 3;
  int end_j = start_j + 3;
  for (int i = start_i;i< end_i; i++){
    for (int j = start_j;j< end_j; j++){
      if (field[i][j] == num){
        flag = 1;
        return flag;
      }
    }
    
  }
  printf("flag square = %d\n",flag);
  return flag;
  
}

void regenerate_num(int** field, int ind_i, int ind_j, long* num) {
  while (check_row(field, ind_i, *num) || check_colom(field,ind_j,*num) || check_square(field,ind_i,ind_j,*num)){
    *num = (rand() % 10);
    if (*num == 0) {
      *num += 1;
    }
    // printf("NUM = %ld\n", *num);
    // generate(field);
  }
}

int check_uniq(int** field){
  int flag = 1;
  int num = field[0][0];
  for (int i = 1; i < SIZE; i++){
    for (int j = 1; j < SIZE; j++){
      if (field[i][j] == num){
        flag = 0;
        break;
      }
      num = field[i][j];
    }
  }
  return flag;
}

