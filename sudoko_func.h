#ifndef SUDOKO
#define SUDOKO

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 9
int **make_field();
int **make_field_for_players(int **field);
void free_mem(int **field);
void output(int **field);
int generate_random_num(int start, int end, int exclude[]);
int is_contains_in_array(int num, const int array[]);
void transposition(int **field);
void random_swap_row_and_colom(int **field);
void shake_field(int **field);
void generate_basic_field(int **field);
void delete_cells(int **players_field, int hard_level);
int zero_in_square(int **field, int ind_i, int ind_j);
int zero_in_row(int **field, int ind);
int zero_in_colom(int **field, int ind_j);
void play(int **field, int **players_field);

#endif