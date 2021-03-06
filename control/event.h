// Projet Yoté -- IATIC 3 ISTY
// See the authors in AUTHOR.md

#ifndef CONTROL_EVENT
	#define CONTROL_EVENT 1

	#include "../main.h"

	// Fonction de filtre: prend un SDL_Event et renvoie un booléen.
	typedef void (*typeFilter(SDL_Event))(bool) ;
	// Fonction qui fait vraiment quelque chose. Prend un SDL_Event en entré et
	// ne renvoie rien.
	typedef void (*typeActuator(SDL_Event))(void) ;

	typedef struct {
		SDL_EventType event;
		typeFilter * filter;
		typeActuator * actuator;
	} handler ;

	typedef struct {
		handler * list ;
		int len ;
		int cap ;
		bool stop ;
	} typeHandlers ;

	void handlersAdd(typeHandlers * h, SDL_EventType e, typeFilter * f, typeActuator * a);
	void handlersRun(typeHandlers * h);
	void handlersFree(typeHandlers * h);

	bool filterTrue(SDL_Event event);

	bool filterKeyReturn(SDL_Event key);
	bool filterKeyBackspace(SDL_Event key);
	bool filterKeyLetter(SDL_Event key);

#endif
