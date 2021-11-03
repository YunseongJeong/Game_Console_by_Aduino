#include <stdio.h>


int what_height(int map[16][10]){
	// brief: return the highest height of map. 
	// return: height.
	// parameter : game map.
	for(int i = 15; i>=0; i--){
		for(int j=0; j<10; j++){
			if(map[i][j]) break;
			else return(i);
		}
	}
}

/*
@ brief: block stacks over the height of the map, return -1, to lose that game.
@ return: -1 if lose, 1 if no situation.
@ parameter: map
*/
int win_lose(int map[16][10]) {
	int i = 15;
	for(int j=0; j<10; j++) {
		if(map[i][j]) return -1;
	}
	return 1;
}