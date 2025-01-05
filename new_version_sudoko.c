#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 9
// printf("%ld\n",rand()%9);
int **make_field();
void free_mem(int **field);
void output(int **field);
int is_contains_in_array(int num, int array[]);
int check_square(int **field, int ind_i, int ind_j, long num);
int check_row(int **field, int ind, long num);
int generate_random_num(int start, int end, int exclude[]);
void regenerate_num(int **field, int *ind_i, int *ind_j, long *num);
int check_colom(int **field, int ind_j, long num);
int check_uniq(int **field);
void generate(int **field);
void make_zero_field(int **field);
void add_row(int exclude[], int **field, int ind_i);
void add_col(int exclude[], int **field, int ind_j);
void add_square(int exclude[], int **field, int ind_i, int ind_j);
void make_zero(int arr[], int from, int to);
int main() {
  int **field = make_field(SIZE);
  srand(time(NULL));
  generate(field);
  output(field);
  // printf("%d\n", generate_random_num(1, 1, 1));
  // printf("UNIQ is %d\n", check_uniq(field));
  // free_mem(field);
  return 0;
}
int generate_random_num(int start, int end, int exclude[]) {
  int num = (start + rand() % (end - start + 1));
  if ((exclude[0] != 0) && (start != end)) {
    while (is_contains_in_array(num, exclude)) {
      num = (start + rand() % (end - start + 1));
    }
  }

  return num;
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

void generate(int **field) {
  long r_num = 1;
  // int exclude = -1;
  for (int s = 0; s < SIZE; s++) {
    int exclude[20] = {0};
    int e = 0;
    for (int i = s / 3; i < SIZE; i += 3) {
      for (int j = s % 3; j < SIZE; j += 3) {
        add_square(&exclude[9], field, i, j);
        field[i][j] = generate_random_num(1, 9, exclude);
        exclude[e++] = field[i][j];
        make_zero(exclude, 9, 20);
        output(field);
        printf("\n");

      }
    }
  }
}
void make_zero(int arr[], int from, int to) {
  for (int i = from; i <= to; i++) {
    arr[i] = 0;
  }
}

int is_contains_in_array(int num, int array[]) {
  int flag = 0;
  for (int i = 0; i < 20; i++) {
    // printf("arr = %d\n",array[i]);
    if (array[i] == num) {
      flag = 1;
    }
  }
  return flag;
}

void add_square(int exclude[], int **field, int ind_i, int ind_j) {
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
  int e = 0;
  for (int i = start_i; i < end_i; i++) {
    for (int j = start_j; j < end_j; j++) {
      exclude[e++] = field[i][j];
    }
  }
  // printf("last el of squar = %d\n",exclude[2]);

  // printf("flag square = %d\n", flag);
}
// void add_row(int exclude[], int** field, int ind_i){
//   for (int j = 0; j < SIZE; j++) {
//     if (exclude[j] field[ind_i][j] == num) {
//       flag = 1;
//       break;
//     }
//   }
// }
// int check_row(int **field, int ind, long num) {
//   int flag = 0;
//   for (int i = 0; i < SIZE; i++) {
//     if (field[ind][i] == num) {
//       flag = 1;
//       break;
//     }
//   }
//   return flag;
// }
// int check_colom(int **field, int ind, long num) {
//   int flag = 0;
//   for (int i = 0; i < SIZE; i++) {
//     if (field[i][ind] == num) {
//       flag = 1;
//       break;
//     }
//   }
//   return flag;
// }

// int check_square(int **field, int ind_i, int ind_j, long num) {
//   int start_i = 0;
//   int start_j = 0;
//   int flag = 0;

//   if (ind_i >= 3 && ind_i <= 5) {
//     start_i = 3;
//   } else if (ind_i >= 6) {
//     start_i = 6;
//   }

//   if (ind_j >= 3 && ind_j <= 5) {
//     start_j = 3;
//   } else if (ind_j >= 6) {
//     start_j = 6;
//   }

//   // printf("start i = %d\n",start_i);
//   // printf("start j = %d\n",start_j);
//   int end_i = start_i + 3;
//   int end_j = start_j + 3;
//   for (int i = start_i; i < end_i; i++) {
//     for (int j = start_j; j < end_j; j++) {
//       if (field[i][j] == num) {
//         flag = 1;
//         return flag;
//       }
//     }
//   }
//   // printf("flag square = %d\n", flag);
//   return flag;
// }

// void regenerate_num(int **field, int *ind_i, int *ind_j, long *num) {
//   while (check_row(field, *ind_i, *num) || check_colom(field, *ind_j, *num)
//   ||
//          check_square(field, *ind_i, *ind_j, *num)) {
//     *num = (rand() % 10);
//     if (*num == 0) {
//       *num += 1;
//     }
//     *ind_i = 0;
//     *ind_j = 0;
//     // make_zero_field(field);
//     // printf("NUM = %ld\n", *num);
//     // generate(field);
//   }
// }

// int check_uniq(int **field) {
//   int flag = 1;
//   int num = field[0][0];
//   for (int i = 1; i < SIZE; i++) {
//     for (int j = 1; j < SIZE; j++) {
//       if (field[i][j] == num) {
//         flag = 0;
//         break;
//       }
//       num = field[i][j];
//     }
//   }
//   return flag;
// }

// void make_zero_field(int** field){
//   for(int i = 0; i < SIZE; i++){
//     for (int j = 0; j < SIZE; j++){
//       field[i][j] = 0;
//     }
//   }
// }