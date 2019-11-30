// Projet Yoté -- IATIC 3 ISTY
// See the authors in AUTHOR.md

#include "display.h"

// La surface de la fenêtre.
SDL_Surface *bg = NULL ;

// Initilise la SDL et charge les images
void initDisplay() {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_WM_SetCaption("ISTY - Yoté", NULL);

	bg = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE);
	fatal(bg, "launch SDL");
}

// Fatal if pt is NULL, print the message and the log of SDL
void fatal(void* pt, char ms[]) {
	if (pt == NULL) {
		fprintf(stderr, "Error %s: %s\n", ms, SDL_GetError());
		exit(1);
	}
}

// Affiche tout
void display() {
	displayBoard(FALSE);
	SDL_Flip(bg);
}

// Affiche que le plateau, si flip est vrai, alors
// le plateau est affiché.
void displayBoard(bool flip) {
	int x,y ;

	SDL_Surface* squareBg = SDL_LoadBMP("media/squareBg.bmp");
	fatal(squareBg, "load squareBg");
	
	SDL_Surface* pieceBlack = SDL_LoadBMP("media/pieceBlack.bmp");
	fatal(pieceBlack, "load pieceBlack");
	SDL_SetColorKey(pieceBlack,SDL_SRCCOLORKEY, SDL_MapRGB(pieceBlack->format,255,0,255));

	SDL_Surface* pieceWhite = SDL_LoadBMP("media/pieceWhite.bmp");
	fatal(pieceWhite, "Error load pieceWhite");
	SDL_SetColorKey(pieceWhite,SDL_SRCCOLORKEY, SDL_MapRGB(pieceWhite->format,255,0,255));

	for ( x = 0; x < 6; x++) {
		for(y=0;y<5;y++) {
			displaySquare(squareBg, x, y);
			switch (board[x][y].status) {
				// TODO: use the color format from the background
				case SELECTED:   displayStatus(0x00FF00, x, y); break;
				case ACCESSIBLE: displayStatus(0x0000FF, x, y); break;
				case CAPTURE:    displayStatus(0xFF0000, x, y); break;
			}
			switch (board[x][y].color) {
				case EMPTY:
					break;
				case WHITE:
					displaySquare(pieceWhite, x, y);
					break;
				case BLACK:
					displaySquare(pieceBlack, x, y);
					break;
			}
		}
	}
	if (flip) {
		SDL_Flip(bg);
	}
}

// Dessin un fond différent selon le fond
void displayStatus(Uint32 color, int x, int y) {
	int r = SDL_FillRect(bg, &(SDL_Rect){
		x: x*50,
		y: y*50,
		w: 50,
		h: 50,
	}, color);
	fatal(!r, "displayStatus()");
}

// x and y is the coord of a square
void displaySquare(SDL_Surface* square, int x, int y) {
	int r = SDL_BlitSurface(square, NULL, bg, &(SDL_Rect){
		x: x*50,
		y: y*50,
	});
	fatal(!r, "displaySquare()");
}


void displayTitle() {
	SDL_Surface* spriteTitre = SDL_LoadBMP("media/title.bmp");
	fatal(spriteTitre, "load titleSprite");

	SDL_BlitSurface(spriteTitre, NULL, bg, &(SDL_Rect){0,0});

	SDL_Flip(bg);
}


// Affiche les boutons du menu du jeu
void displayMenuButtons() {
	SDL_Surface* boutonPVP = SDL_LoadBMP("media/boutons/boutonPVP.bmp");
	SDL_Surface* boutonIA = SDL_LoadBMP("media/boutons/boutonIA.bmp");
	SDL_Surface* boutonRegles = SDL_LoadBMP("media/boutons/boutonRegles.bmp");
	SDL_Surface* boutonResultats = SDL_LoadBMP("media/boutons/boutonResultats.bmp");
	SDL_Surface* boutonQuitter = SDL_LoadBMP("media/boutons/boutonQuitter.bmp");

	SDL_BlitSurface(boutonPVP, NULL, bg, &(SDL_Rect){50, 200});
	SDL_BlitSurface(boutonIA, NULL, bg, &(SDL_Rect){260, 200});
	SDL_BlitSurface(boutonRegles, NULL, bg, &(SDL_Rect){50, 280});
	SDL_BlitSurface(boutonResultats, NULL, bg, &(SDL_Rect){260, 280});
	SDL_BlitSurface(boutonQuitter, NULL, bg, &(SDL_Rect){50, 360});

	SDL_Flip(bg);
}

// Affiche les règles du jeu
void displayRules(char* regles) {
	int i = 0;

	// Initialisation de SDL_ttf
	TTF_Init();
	TTF_Font* police = TTF_OpenFont("media/LifeCraft.ttf", 30);
	
	SDL_Surface* texte = NULL;

	char* separateur = "_";
	// Découpe une chaîne de caractères en sous-chaînes, en fonction d'un ou plusieurs séparateurs
	const char* ligne = strtok(regles, separateur);

	while (ligne != NULL) {
		texte = TTF_RenderUTF8_Shaded(police, ligne, (SDL_Color){255, 255, 255}, (SDL_Color){0,0,0});
		SDL_BlitSurface(texte, NULL, bg, &(SDL_Rect){0, i});
		i += 30;
		ligne = strtok(NULL, separateur);
	}

	SDL_Flip(bg);

	// Clotûre de la police et de SDL_ttf
	TTF_CloseFont(police);
	TTF_Quit();
}


// Affiche les derniers scores
void displayScores(char* scores) {
	// Coordonnées x dans la fenêtre
	int i = 150;
	// Coordonnées y dans la fenêtre
	int j = 100;
	// Compteur 
	int k = 0;

	TTF_Init();
	TTF_Font* police = NULL;
	SDL_Surface* texte = NULL;

	police = TTF_OpenFont("media/LifeCraft.ttf", 25);
	texte = TTF_RenderUTF8_Shaded(police, "REGLES DU JEU", (SDL_Color){255, 255, 255}, (SDL_Color){0,0,0});
	SDL_BlitSurface(texte, NULL, bg, &(SDL_Rect){(LARGEUR_FENETRE - texte->w)/2, 30});
	TTF_CloseFont(police);

	police = TTF_OpenFont("media/LifeCraft.ttf", 20);
	const char* separateurs = "\n|";
	char* ligne = strtok(scores, separateurs);

	while (ligne != NULL) {
		texte = TTF_RenderUTF8_Shaded(police, ligne, (SDL_Color){255, 255, 255}, (SDL_Color){0,0,0});
		SDL_BlitSurface(texte, NULL, bg, &(SDL_Rect){i, j});
		k++;

		// Si k % 2 = 0 alors on est en train d'écrire le score du premier joueur d'une partie
		// Sinon on est en train d'écrire le score du 2e joueur
		if (k % 2 == 0) {
			i = 150;
			j+= 30;
		}
		else {
			i = 250;
		}

		ligne = strtok(NULL, separateurs);
	}

	SDL_Flip(bg);

	TTF_CloseFont(police);
	TTF_Quit();
}