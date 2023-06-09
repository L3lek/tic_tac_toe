#include "board.h"

#include <iomanip>
#include <iostream>



Board::Board(int size, int max_row, char player):size(size),max_row(max_row),pl_symbol(player), area(size, std::vector<char>(size)){

for(int i=0;i<size;i++){
	for(int j=0;j<size;j++){
		area[i][j]=0;
	}
}

if(player=='x'){
	ai_symbol='o';
}else if(player=='o'){
	ai_symbol='x';
}else{
	pl_symbol='x';
	ai_symbol='o';
}
}

void Board::print() const{
	system("clear");

	//poziome oznaczenia
	std::cout << std::string(4, ' ');
	for(int i=0; i<size; i++){
		 
		if(i<9)
			std::cout<<std::setw(1)<<i+1<<"   ";
		else
			std::cout<<std::setw(2)<<i+1<<"  ";
	}
	std::cout<<std::endl;

	//rysowanie planszy

	for (int y = 0; y < size; y++) {
        // oznaczenia wierszy, linie pionowe i znaki
        std::cout << std::setw(2) << y + 1 << "  ";
        for (int x = 0; x < size; x++) {
            if (area[x][y] == 0)
                std::cout << ' ';
            else
                std::cout << area[x][y];
            if (x < size - 1)
                std::cout << " | ";
        }
        std::cout << "  " << y + 1;

        // linie poziome
        if (y < size - 1) {
            std::cout << "\n   ";
            for (int i = 0; i < size - 1; i++)
                std::cout << std::string(3, '-') << '+';
            std::cout << std::string(3, '-');
        }
        std::cout << std::endl;
    }
		std::cout << std::string(4, ' ');
	for(int i=0; i<size; i++){
		 
		if(i<9)
			std::cout<<std::setw(1)<<i+1<<"   ";
		else
			std::cout<<std::setw(2)<<i+1<<"  ";
	}
	std::cout<<std::endl;
}


void Board::set(int x, int y) {
    if (x >= 1 && x <= size && y >= 1 && y <= size) {
        if (player_turn())
            area[x - 1][y - 1] = pl_symbol;
        else
            area[x - 1][y - 1] = ai_symbol;
    }
}

void Board::remove(int x, int y){
    if (x >= 1 && x <= size && y >= 1 && y <= size)
            area[x - 1][y - 1] = 0;
}

void Board::reset(){
	for(int y=0;y<size;y++){
		for(int x=0; x<size; x++){
			area[x][y]=0;
		}
	}
}

int Board::get_size(){
	return this->size;
}


int Board::game_result()const{
       
int pl_counter, ai_counter;

//pion
    for (int x = 0; x < size; x++) {
        pl_counter = ai_counter = 1;
        for (int y = 0; y < size - 1; y++) {
            if (area[x][y] == area[x][y + 1]) {
                if (area[x][y] == pl_symbol)
                    pl_counter++;
                else if (area[x][y] == ai_symbol)
                    ai_counter++;
                if (pl_counter == max_row)
                    return 1;
                if (ai_counter == max_row)
                    return -1;
            }
        }
    }
//poziom
  for (int y = 0; y < size; y++) {
        pl_counter = ai_counter = 1;
        for (int x = 0; x < size - 1; x++) {
            if (area[x][y] == area[x + 1][y]) {
                if (area[x][y] == pl_symbol)
                    pl_counter++;
                else if (area[x][y] == ai_symbol)
                    ai_counter++;
                if (pl_counter == max_row)
                    return 1;
                if (ai_counter == max_row)
                    return -1;
            }
        }
    }

//na skos

//lewa góra w dół
for(int y=0;y<size-max_row+1;y++){
	pl_counter=ai_counter=1;
	for(int x=0;x<(size-y-1);x++){
		if(area[x][x+y]==area[x+1][y+x+1]){
			if(area[x][x+y]==pl_symbol)
				pl_counter++;
			else if(area[x][x+y]==ai_symbol)
				ai_counter++;
			if(pl_counter==max_row)
				return 1;
			if(ai_counter==max_row)
				return -1;
		}	
	}
}

for(int y=1;y<size-max_row+1;y++){
	pl_counter=ai_counter=1;
	for(int x=0;x<(size-y-1);x++){
		if(area[x+y][x]==area[x+y+1][x+1]){
			if(area[x+y][x]==pl_symbol)
				pl_counter++;
			else if(area[x+y][x]==ai_symbol)
				ai_counter++;
			if(pl_counter==max_row)
				return 1;
			if(ai_counter==max_row)
				return -1;
		}
	}
}


for(int y=0;y<size-max_row+1;y++){
	pl_counter=ai_counter=1;
	for(int x=0;x<size-y-1;x++){
		if(area[size-x-1][x+y]==area[size-x-2][x+y+1]){
			if(area[size-x-1][x+y]==pl_symbol)
				pl_counter++;
			else if(area[size-x-1][x+y]==ai_symbol)
				ai_counter++;
			if(pl_counter==max_row)
				return 1;
			if(ai_counter==max_row)
				return -1;
		}
	}
}

for(int y=1;y<size-max_row+1;y++){
	pl_counter=ai_counter=1;
	for(int x=0;x<size-y-1;x++){
		if(area[size-x-y-1][x]==area[size-x-y-2][x+1]){
			if(area[size-x-y-1][x]==pl_symbol)
				pl_counter++;
			else if(area[size-x-y-1][x]==ai_symbol)
				ai_counter++;
			if(pl_counter==max_row)
				return 1;
			if(ai_counter==max_row)
				return -1;
		}
	}	
}

    return 0;
}



bool Board::full_board(){
	for(int x=1;x<size+1;x++){
		for(int y=1;y<size+1;y++){
			if(!occupied(x,y)){
				return false;
			}
		}
	}
	return true;
}

bool Board::occupied(int x, int y){
	if(area[x-1][y-1]==0){
		return false;
	}
	return true;
}