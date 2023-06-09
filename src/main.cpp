#include "board.h"
#include "ai.h"

#include <iostream>
#include <string>
#include <vector>

Board make_board(){
int size, to_win;
char pl_symbol, start;


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

std::vector<int> pl_choise(Board table){
	int x,y;
			do{
				do{
					std::cout << "Wybierz x z przedziału (1, " << table.get_size() << ")\n";
					std::cin >> x;

					std::cout << "Wybierz y z przedziału (1, " << table.get_size() << ")\n";
					std::cin >> y;
					std::cout << std::endl;

				}while(x<1 || x>table.get_size() || y<1 || y>table.get_size());
				if(table.occupied(x,y)|| x < 1 || x > table.get_size() || y < 1 || y > table.get_size()){
					std::cout <<"Wybrane pole (" <<x << "," <<y <<") jest zajęte. Wybierz inne pole!\n";
				}
			}while (table.occupied(x,y));
	std::vector<int> coords;
	coords.push_back(x);
	coords.push_back(y);
	return coords;
}

void win_condition(Board table){
if (table.full_board() && table.game_result() == 0)
    std::cout << "remis!\n";
else if (table.game_result() != 0) {
	std::cout << "koniec gry! wygrywa ";
	if (!table.player_turn())
		std::cout << "gracz (" << table.get_pl_symbol() << ")\n";
	else
		std::cout << "komputer (" << table.get_ai_symbol() << ")\n";
	}
	std::cout << '\n';
}

void game_ai(Board table){
	std::string turn_choise;
	std::vector<int> coords;

	ai Ai=make_ai();

	do{
	std::cout << "Kto zaczyna? Pl - gracz/ Ai - komputer. ";
	std::cin >> turn_choise;
	if(turn_choise =="Pl" || turn_choise =="PL"|| turn_choise =="pl"|| turn_choise =="pL")
		table.set_turn(1);
	else if(turn_choise =="Ai" || turn_choise =="AI"|| turn_choise =="ai"|| turn_choise =="aI")
		table.set_turn(0);
	else
		std::cout << "Wpisano nieprawidłowy wybór. Wpisz \"Ai\" lub \"Pl\"\n";
	}while(!((turn_choise =="Pl" || turn_choise =="PL"|| turn_choise =="pl"|| turn_choise =="pL" || turn_choise =="Ai" || turn_choise =="AI"|| turn_choise =="ai"|| turn_choise =="aI")));

	table.reset();
	table.print();       

    
	while(table.game_result()==0 && !table.full_board()){

		if(table.player_turn()){
			
			std::cout << "Twój ruch.\n";
			coords=pl_choise(table);
			table.set(coords[0],coords[1]);
            table.change_turn(0);
		}else {
                std::cout << "komputer wykonuje ruch... \n";
                Ai.move(table);
                table.set(Ai.getx(), Ai.gety());
                table.change_turn(1);
            }

        table.print();

		win_condition(table);
        }

}

void game_2pl(Board table){
	std::vector<int> coords;

	table.set_turn(1);

	table.reset();
	table.print();       

    
	while(table.game_result()==0 && !table.full_board()){

		if(table.player_turn()){
			
			std::cout << "Gracz 1.\n";
			coords=pl_choise(table);
			table.set(coords[0],coords[1]);
            table.change_turn(0);
		}else {
            std::cout << "Gracz 2.\n";
			coords=pl_choise(table);
			table.set(coords[0],coords[1]);
            table.change_turn(1);
            }

        table.print();

		win_condition(table);
        }
}


int main(){
	Board table=make_board();
	int choise;

	do{
		std::cout<<"\nWybierz tryb gry: \n 1. Gracz vs Gracz.\n 2. Gracz vs Komputer.\n";
		std::cin >> choise;
		if(choise!=1 && choise != 2){
			std::cout << "Wybrano złą opcję.\n";
		}
	}while (choise!=1 && choise !=2);
	
	std::cout<<std::endl;
		if(choise==1){
			game_2pl(table);
		}else if(choise==2){
			game_ai(table);
	
		}
}