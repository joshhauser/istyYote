// Projet Yoté -- IATIC 3 ISTY
// See the authors in AUTHOR.md

#include "mod.h"

// Initialise le plateau
void initBoard() {
	int x,y ;
	for ( x = 0; x < 6; x++) {
		for(y=0;y<5;y++) {
			board[x][y].color = EMPTY ;
			board[x][y].status = DEFAULT ;
		}
	}

	// valeur pour le développement
	board[1][1] = (square){
		color: BLACK,
	};
	board[2][1] = (square){
		color: WHITE,
		status: ACCESSIBLE,
	};
	board[1][2] = (square){
		color: BLACK,
		status: CAPTURE,
	};
	board[2][2] = (square){
		color: WHITE,
		status: SELECTED,
	};
}
