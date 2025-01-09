#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 9
// printf("%ld\n",rand()%9);
int **make_field();
void free_mem(int **field);
void output(int **field);
int generate_random_num(int start, int end, int exclude[]);
int is_contains_in_array(int num, int array[]);
void transposition(int **field);
void random_swap_row_and_colom(int **field);
void shake_field(int** field);
void generate_basic_field(int **field);

int check_square(int **field, int ind_i, int ind_j, long num);
int check_row(int **field, int ind, long num);
void regenerate_num(int **field, int *ind_i, int *ind_j, long *num);
int check_colom(int **field, int ind_j, long num);
int check_uniq(int **field);
void make_zero_field(int **field);

int main() {
  srand(time(NULL));
  int **field = make_field(SIZE);
  generate_basic_field(field);
  shake_field(field);  
  output(field);
  free_mem(field);
  return 0;
}

void output(int **field) {
  for (int i = 0; i < SIZE; i++) {
    int flag_line = 0;
    for (int j = 0; j < SIZE; j++) {
      if (i % 3 == 0 && i != 0 && flag_line != 1) {
        flag_line = 1;
        for (int k = 0; k < SIZE + 10; k++) {

          printf("-");
        }
        printf("\n");
      }

      if (j % 3 == 0 && j != 0) {
        printf("|");
      }

      printf("%d ", field[i][j]);
    }
    printf("\n");
  }
}

void generate_basic_field(int **field) {
  int num;
  for (int i = 0; i < SIZE; i++) {
    if (i % 3 != 0) {
      num = field[i - 1][3];
    } else if (i % 3 == 0 && i != 0) {
      num = field[i - 3][1];
    } else {
      num = generate_random_num(1, 9, NULL);
      // num = 8;
    }
    for (int j = 0; j < SIZE; j++) {
      field[i][j] = num;
      num++;
      if (num == 10) {
        num = 1;
      }
    }
  }
}

int generate_random_num(int start, int end, int exclude[]) {
  int num = (start + rand() % (end - start + 1));
  if (exclude != NULL && (exclude[0] != 0) && (start != end)) {
    while (is_contains_in_array(num, exclude)) {
      num = (start + rand() % (end - start + 1));
    }
  }

  return num;
}

void transposition(int **field) {
  for (int i = 0; i < SIZE; i++) {
    for (int j = i; j < SIZE; j++) {
      int temp = field[i][j];
      field[i][j] = field[j][i];
      field[j][i] = temp;
    }
  }
}

void random_swap_row_and_colom(int **field) {
  int exclude[6] = {1, 2, 4, 5, 7, 8};
  int first_i = generate_random_num(0, 6, exclude);
  int plus_num = generate_random_num(1, 2, NULL);
  int second_i = first_i + plus_num;
  int temp;
  for (int j = 0; j < SIZE; j++) {
    temp = field[second_i][j];
    field[second_i][j] = field[first_i][j];
    field[first_i][j] = temp;
  }
  for (int j = 0; j < SIZE; j++) {
    temp = field[j][second_i];
    field[j][second_i] = field[j][first_i];
    field[j][first_i] = temp;
  }
}

void shake_field(int** field){
  int number_of_rep = generate_random_num(1, 100000,NULL);
  for ( int i = 0; i < number_of_rep; i++){
    transposition(field);
    random_swap_row_and_colom(field);
  
  }
}


int is_contains_in_array(int num, int array[]) {
  int flag = 0;
  for (int i = 0; i < 20; i++) {
    if (array[i] == num) {
      flag = 1;
    }
  }
  return flag;
}

int **make_field() {
  int **matrix = malloc(SIZE * sizeof(int *));

  for (int i = 0; i < 9; i++) {
    matrix[i] = calloc(SIZE, sizeof(int));
  }
  return matrix;
}

void free_mem(int **field) {
  for (int i = 0; i < SIZE; i++) {
    free(field[i]);
  }
  free(field);
}

int check_row(int **field, int ind, long num) {
  int flag = 0;
  for (int i = 0; i < SIZE; i++) {
    if (field[ind][i] == num) {
      flag = 1;
      break;
    }
  }
  return flag;
}
int check_colom(int **field, int ind, long num) {
  int flag = 0;
  for (int i = 0; i < SIZE; i++) {
    if (field[i][ind] == num) {
      flag = 1;
      break;
    }
  }
  return flag;
}

int check_square(int **field, int ind_i, int ind_j, long num) {
  int start_i = 0;
  int start_j = 0;
  int flag = 0;

  if (ind_i >= 3 && ind_i <= 5) {
    start_i = 3;
  } else if (ind_i >= 6) {
    start_i = 6;
  }

  if (ind_j >= 3 && ind_j <= 5) {
    start_j = 3;
  } else if (ind_j >= 6) {
    start_j = 6;
  }

  // printf("start i = %d\n",start_i);
  // printf("start j = %d\n",start_j);
  int end_i = start_i + 3;
  int end_j = start_j + 3;
  for (int i = start_i; i < end_i; i++) {
    for (int j = start_j; j < end_j; j++) {
      if (field[i][j] == num) {
        flag = 1;
        return flag;
      }
    }
  }
  // printf("flag square = %d\n", flag);
  return flag;
}

void regenerate_num(int **field, int *ind_i, int *ind_j, long *num) {
  while (check_row(field, *ind_i, *num) || check_colom(field, *ind_j, *num) ||
         check_square(field, *ind_i, *ind_j, *num)) {
    *num = (rand() % 10);
    if (*num == 0) {
      *num += 1;
    }
    *ind_i = 0;
    *ind_j = 0;
    // make_zero_field(field);
    // printf("NUM = %ld\n", *num);
    // generate(field);
  }
}

int check_uniq(int **field) {
  int flag = 1;
  int num = field[0][0];
  for (int i = 1; i < SIZE; i++) {
    for (int j = 1; j < SIZE; j++) {
      if (field[i][j] == num) {
        flag = 0;
        break;
      }
      num = field[i][j];
    }
  }
  return flag;
}

void make_zero_field(int **field) {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      field[i][j] = 0;
    }
  }
}