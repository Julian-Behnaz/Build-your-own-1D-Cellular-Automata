
#include <stdio.h>

#define CURRENT_RULE 30
#define ROW_LENGTH 80
int DATA[ROW_LENGTH * 2];

int* current_cell_states;
int* next_cell_states;
int* temp;

int stateBasedOnNeighbors (int rule, int left, int center, int right) {
	return (rule >> (left << 2 | center << 1 | right)) & 1;
}

int main (void) {
	current_cell_states = DATA;
	next_cell_states = DATA+ROW_LENGTH;

  /* Start with a 1 cell in the middle */
  current_cell_states[ROW_LENGTH/2] = 1;

	for (int t = 0; t < 1000; t++) {
    /* Display the current state */
		for (int i = 0; i < ROW_LENGTH; i++) {
      printf("%c", current_cell_states[i]? '#' : '.');
    }
    printf("\n");
		
    /* Calculate the next state */
		for (int i = 0; i < ROW_LENGTH; i++) {
		  int left = current_cell_states[((i - 1) + ROW_LENGTH) % ROW_LENGTH];
		  int curr = current_cell_states[i];
		  int right = current_cell_states[(i + 1) % ROW_LENGTH];
		
		  next_cell_states[i] = stateBasedOnNeighbors(CURRENT_RULE, left, curr, right);
		}
		
	  /* Set the current state equal to what was the next state */
		temp = current_cell_states;
		current_cell_states = next_cell_states;
		next_cell_states = temp;
	}

    return 0;
}
