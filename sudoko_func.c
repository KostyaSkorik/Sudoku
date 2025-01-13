#include "sudoko_func.h"

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
      if (field[i][j] == 0) {
        printf("  ");
      } else {
        printf("%d ", field[i][j]);
      }
    }
    printf("\n");
  }
}

void generate_basic_field(int **field) {
  int num;
  for (int i = 0; i < SIZE; i++) {
    if (i % 3 != 0) {
      num = field[i - 1][3];
    } else if (i != 0) {
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
  int exclude[7] = {1, 2, 4, 5, 7, 8};
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

void shake_field(int **field) {
  int number_of_rep = generate_random_num(1000, 100000, NULL);
  for (int i = 0; i < number_of_rep; i++) {
    transposition(field);
    random_swap_row_and_colom(field);
  }
}

int is_contains_in_array(int num, const int array[]) {
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

int **make_field_for_players(int **field) {
  int **matrix = calloc(SIZE, sizeof(int *));
  for (int i = 0; i < SIZE; i++) {
    matrix[i] = calloc(SIZE, sizeof(int));
  }

  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      matrix[i][j] = field[i][j];
    }
  }

  return matrix;
}
void delete_cells(int **players_field, int hard_level) {
  int count_del_cells = hard_level * 20;
  while (count_del_cells > 0) {
    int x = generate_random_num(0, 8, NULL);
    int y = generate_random_num(0, 8, NULL);
    if (zero_in_square(players_field, x, y) <= hard_level ||
        (zero_in_row(players_field, x) + zero_in_colom(players_field, y) <=
         (hard_level * 2))) {
      players_field[x][y] = 0;
    }
    count_del_cells--;
  }
}

int zero_in_row(int **field, int ind) {
  int count_zero = 0;
  for (int i = 0; i < SIZE; i++) {
    if (field[ind][i] == 0) {
      count_zero++;
    }
  }
  return count_zero;
}
int zero_in_colom(int **field, int ind) {
  int count_zero = 0;
  for (int i = 0; i < SIZE; i++) {
    if (field[i][ind] == 0) {
      count_zero++;
    }
  }
  return count_zero;
}

int zero_in_square(int **field, int ind_i, int ind_j) {
  int start_i = 0;
  int start_j = 0;
  int count_zero = 0;

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

  int end_i = start_i + 3;
  int end_j = start_j + 3;
  for (int i = start_i; i < end_i; i++) {
    for (int j = start_j; j < end_j; j++) {
      if (field[i][j] == 0) {
        count_zero++;
      }
    }
  }
  return count_zero;
}

void play(int **field, int **players_field) {

  char player_say = 'r';

  while (player_say != 'q') {
    int x, y, n;
    char extra;
    printf("ENTERS ARE COORDINATES, WHERE YOU WANT TO STAY NUMBER AND "
           "NUMBER\n");
    scanf("%d%d%d%c", &x, &y, &n,&extra);
    if (field[x][y] == n && players_field[x][y] == 0) {
      printf("CURRECT\n");
      players_field[x][y] = n;
    } else {
      printf("FALSE\n");
    }
    output(players_field);

    printf("ENTER TO CONTINUE OR 'q' TO QUIT\n");
    scanf("%c", &player_say);
  }
}
