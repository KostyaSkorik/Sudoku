#include "sudoko_func.h"
int main() {
  srand(time(NULL));
  int **field = make_field(SIZE);
  generate_basic_field(field);
  shake_field(field);

  int **players_field = make_field_for_players(field);
  int hard_level;
  printf("\t\t\t choose hard level:\n 1 - basik\n 2 - easy\n 3 - medium\n 4 - "
         "hard\n");
  scanf("%d", &hard_level);
  delete_cells(players_field, hard_level);
  output(players_field);
  play(field, players_field);

  free_mem(field);
  free_mem(players_field);
  return 0;
}