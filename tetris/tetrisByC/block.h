#include <stdio.h>
#include <stdlib.h>

int ran_block[7][4] ={ // 01 mean 0,1
	//0 is O block
	{03, 02, 12, 13},
	//1 is S block
	{03, 04, 12, 13},
	//2 is Z block
	{03, 02, 13, 14},
	//3 is L block
	{03, 04, 02, 12},
	//4 is J block
	{03, 02, 04, 14},
	//5 is I block 
	{03, 02, 04, 05},
	//6 is T block
	{03, 02, 04, 13}	
};

/*
@ brief: translate the number into x-coordinate, 03 -> 0
@ return: x-coordinate
@ parameter: number like 03, 02, 12
*/
int get_x_coordinate(int num) {
	return num/10;
}

/*
@ brief: translate the number into y-coordinate, 03 -> 3
@ return: y-coordinate
@ parameter: number like 03, 02, 12
*/
int get_y_coordinate(int num) {
	return num%10;
}

/*
@ brief: create random block, key_block is created in block_list[0][3]. toss the coordinate.
@ return: block in block_list
@ parameter: block_list
*/
int random_block(int block_list[16][10]) {
	int rand_blo = rand()%7;
	for(int i=0; i<4; i++) {
		block_list[get_x_coordinate(ran_block[rand_blo][i])][get_y_coordinate(ran_block[rand_blo][i])] = 1;
	}
	return 0;
}