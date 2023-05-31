#include "board.h"
#include "ai.h"

#include <iostream>

Board make_board(){
int size, to_win;
char pl_symbol, start;
bool turn;
std::cout <<"+"<< std::string(30,'-')<<"+"<<std::endl;
std::cout << "| Ustawienia rozmiaru planszy: |"<<std::endl;
std::cout <<"+"<< std::string(30,'-')<<"+"<<std::endl;

std::cout << "Rozmiar planszy: ";
std::cin >> size;
if(size<3){
	size=3;
	std::cout <<"Najmniejszy rozmiar planszy to: 3x3. Automatycznie ustawiono najmniejszą tablicę.\n";
}

std::cout << "Ilość znaków do wygranej: ";
std::cin >> to_win;
if(to_win<3){
	std::cout << "Minimalna liczba znaków w linii to 3. Automatycznie ustawiono najmnniejszą liczbę znaków.\n";
	to_win = 3;
}else if(to_win >size){
	std::cout << "Liczba znaków w linii nie może przekraczać rozmiaru tablicy. Ustawiono liczbę równą rozmiarowi tablicy\n";
	to_win = size;
}
std::cout <<std::endl;


std::cout <<"+"<< std::string(17,'-')<<"+"<<std::endl;
std::cout << "| Ustawienia gry: |"<<std::endl;
std::cout <<"+"<< std::string(17,'-')<<"+"<<std::endl;

do{
	std::cout << "Znak gracza (x/o): ";
	std::cin >> pl_symbol;
	if(!(pl_symbol =='x'||pl_symbol=='o'))
		std::cout << "Proszę wpisać 'x' lub 'o'.\n";
}while(!(pl_symbol =='x'||pl_symbol=='o'));


Board tic_tac_toe(size, to_win, pl_symbol);
return tic_tac_toe;
}

ai make_ai(){
	int max_depth;
	do{
		std::cout << "Maksymalna głębokość rekursji: ";
		std::cin >> max_depth;
		if(max_depth<=0)
			std::cout << "Minimalna głębokość rekursji wynosi 1. Podaj jeszcze raz. \n";
	}while(max_depth<=0);
	ai Ai(max_depth);
	return Ai;
}


int main(){
	Board table=make_board();
	ai Ai=make_ai();

	int max_moves = table.get_size();

	table.reset();
	table.print();       

    
	while(table.game_result()==0 && !table.full_board()){

		if(table.player_turn()){
			int x,y;
			std::cout << "Twój ruch.\n";
		
			do{
				do{
					std::cout << "Wybierz x z przedziału (1, " << table.get_size() << ")\n";
					std::cin >> x;

					std::cout << "Wybierz y z przedziału (1, " << table.get_size() << ")\n";
					std::cin >> y;
					std::cout << std::endl;

				}while(x<1 || x>table.get_size() || y<1 || y>table.get_size());
				if(table.occupied(x,y)|| x < 1 || x > max_moves || y < 1 || y > max_moves){
					std::cout <<"Wybrane pole (" <<x << "," <<y <<") jest zajęte. Wybierz inne pole!\n";
				}
			}while (table.occupied(x,y));
			table.set(x,y);
            table.change_turn(0);
		}else{
            std::cout << "komputer wykonuje ruch... \n";
            Ai.move(table);
			table.set(Ai.getx(),Ai.gety());
            table.change_turn(1);
        }

        table.print();
		
		
	}
	std::cout << "Brawo wygrałeś!!" <<std::endl;
}