#include <ncurses/curses.h>
#include <ctime>
#include <iostream>
#include <vector>
#include <cstring>
#include "stdlib.h"
#include <cmath>
#include <unistd.h>
#include <algorithm>
#include "timer.h"
#include "tool.h"

using namespace std;


struct UserData{              				//for socreboard
	string Name;
	int Points;
};


bool cmp(const UserData &a, const UserData &b){
	return a.Points < b.Points;
}
							// sorting priciple					

int main(){
	int player_number = 1;
	Timer clk(time(NULL));
	tool toolman(0);
	bool cont_play = 1;
	vector<UserData> UserIn(100);
	int locx1=20,locx2=20,locy1=20,locy2=20;
	while (cont_play){
 	 	int width,height; double u,v,x,y; int c,go_on;
  		u=2;v=0; x=20;y=20; go_on=1;

		//intialize the curses screen
		for (int idxx = 0; idxx<width; idxx++){
			for (int idyy = 0; idyy < height; idyy++){
				mvaddstr(idyy,idxx," ");
			}
		}
		toolman.GetBasicConfig();
                getmaxyx(stdscr,height,width);
                init_pair(1,7,1);
		attrset(A_BOLD|A_REVERSE|COLOR_PAIR(1));
		mvaddstr(0,20,"Greedyyyyyyyyyyyy snake Game");
		mvaddstr(2,0,"__________________________your game_______________________________________");
		//set block on the screen
		toolman.GetBlock(0,25,10,12);
		toolman.GetBlock(25,53,30,33);
		toolman.GetBlock(45,62,45,57);
		attrset(A_NORMAL);

  		int index = 0 ;			//for socre and timer 
		bool incredible = 0 ;
  		vector<time_t> timer(2);
		int score = 0;
		timer[index] = time(NULL); //initialize
		int pty = 0;  //for some score ++ policy
		int ptx = 0;
		int deady = height;	
		int deadx = width;
		int ran_effy = 0;
		int ran_effx = 0;
		int i;
		time_t passed_time;		

		//initialize
		time_t clock1 = time(NULL);
		time_t clock2 = time(NULL);
		int size = 3;
		time_t clock3 = time(NULL);
		time_t clock4 = time(NULL);

		vector<int> SnakeBodyx	;
		vector<int> SnakeBodyy	;	//for snake
		SnakeBodyx.push_back(x);
		SnakeBodyy.push_back(y);
		SnakeBodyx.push_back(x-1);
		SnakeBodyy.push_back(y);           		//initial setting for the snake
 		SnakeBodyx.push_back(x-2);
		SnakeBodyy.push_back(y);
        
		attrset(A_REVERSE);										
		for(i = 0 ; i < SnakeBodyx.size() ; i++ ){
 			mvaddstr(SnakeBodyy.at(i),SnakeBodyx.at(i),"-"); 
		}
		attrset(A_NORMAL);
		move(y,x);
		clk.getStart();
       	 	while (go_on){		
            		while ((c=getch()) == ERR){ //while nothing entered
				// for boundary condition setting
				attrset(A_BOLD|A_REVERSE|COLOR_PAIR(1));
				mvprintw(4,0,"your size is %d",size);
                		attrset(A_NORMAL);
				locx1 = x; locy1=y;
  				x += u/20000;
  				y += v/20000;
  					while (x<0) x+=width;
  					while (x>=width) x-=width;
  					while (y<5) y+=(height-5);
					while (y>=height) y-=(height-5);
				locx2=x;locy2 =y;	
				//end condition for the block
				attrset(A_REVERSE);
				if (incredible) attrset(A_BLINK);
				for (int i=0;i<SnakeBodyx.size()-2;i++){
					mvaddstr(SnakeBodyy[i],SnakeBodyx[i],"-");
				}
				move(y,x);
				attrset(A_NORMAL);
				srand(time(NULL));
			
				clock2 = time(NULL);
			
				if( (clock2 - clock4) == 5 ) { incredible =0; mvaddstr(3,80,"incredible has gone...");attrset(A_NORMAL);}

				//as time passed , increase the length of the snake nd speed
				
				if ( (passed_time%6 == 4) && (( clock2 - clock1) > 3 ) ){ 
					(u==0) ?    ((v>0)? ({v+=3;}): ({v-=3;}) )   :   ((u>0)?({u+=3;}) : ({u-=3;}) )  ;

					score+=15;
					size+=2;
					for (i=0;i<2;i++){SnakeBodyx.push_back(x);SnakeBodyy.push_back(0);}
						clock1 = time(	NULL);
				}

				// bite your self and gameover setting & intense setting

				if( abs(locx1-locx2)>=1 || abs(locy1-locy2)>=1 ){
					mvaddstr(SnakeBodyy.at(SnakeBodyy.size()-1) ,SnakeBodyx.at(SnakeBodyx.size()-1) ," ");
        				move(y,x);
					for (i = SnakeBodyx.size()-1 ; i > 0 ; i--){
						SnakeBodyx.at(i) = SnakeBodyx.at(i-1);
						SnakeBodyy.at(i) = SnakeBodyy.at(i-1);
					} //update the snakebod
				
					if(x<0) SnakeBodyx[0] = x+width;	else SnakeBodyx[0] = x;
					if(y<5) SnakeBodyy[0] = y+height-5; 	else SnakeBodyy[0] = y;
				}// check validity
								 
					for (int i = 1; i<SnakeBodyx.size(); i++){
					if(SnakeBodyx[0] == SnakeBodyx[i] && SnakeBodyy[0] == SnakeBodyy[i]) {endwin();go_on = 0;}
					}//bite yourself and gameover

			 	//for time&score  calculation
				time_t t = time(NULL);
				index = 1;
				timer[index] = t;
      				passed_time = timer[index] - timer[0];
      				mvprintw(3,20,"the elapased time is %d seconds",passed_time);
				mvprintw(4,20,"your scores are %d pts",score);
				clk.getElapsedTime();
			
				// for some ++socre and --score policy
				if  ( (passed_time%10 == 4) && (( clock2 - clock1) > 3 )){
                                pty = rand()%height;
                                ptx = rand()%width;
				init_pair(2,2,0);
				attrset(COLOR_PAIR(2));
                                mvaddstr(pty,ptx,"$");
				attrset(A_NORMAL);
                        	}


				if  ( (passed_time%10 == 4) && (( clock2 - clock1) > 3 )){
					mvaddstr(deady,deadx," ");
					deady = rand()%height;
					deadx = rand()%width;
					init_pair(3,1,0);
					attrset(COLOR_PAIR(3));
					mvaddstr(deady,deadx,"$");
					attrset(A_NORMAL);
				}

				if  ( (passed_time%10 == 4) && (( clock2 - clock1) > 3 )){
					ran_effy = rand()%height;
					ran_effx = rand()%width;
					init_pair(4,4,0);
					attrset(COLOR_PAIR(4));
					mvaddstr(ran_effy,ran_effx,"?");
					attrset(A_NORMAL);
				}
				
			
				// some effect for getting object on the screen
				clock3 = time (NULL);
				if  ( ( abs(x-ptx<2 ) ) && ( abs(y-pty)<2 ) && ( (clock3-clock4) >3 ) ){
					clock4 = time(NULL);
					score+=50;
					for (i=0;i<1;i++){SnakeBodyx.push_back(x);SnakeBodyy.push_back(0);}
				}
				else if ( ( abs(x-deadx<2 ) ) && ( abs(y-deady)<2 ) && ( (clock3-clock4) >3 ) ){
					go_on = 0;
				}
				else if ( ( abs(x-ran_effx<2 ) ) && ( abs(y-ran_effy)<2 ) && ( (clock3-clock4) >3 ) ){
					clock4 = time (NULL);
					if (time(NULL)%2==1){
					       	size+=5;
						for (i=0;i<5;i++){
						SnakeBodyx.push_back(x);SnakeBodyy.push_back(0);
						}
					} 
					else	{ incredible = 1;
						  mvaddstr(3,80,"incredible time !!     ");		
					}	
				}
			
			
				if (incredible == 1){continue; }  //incredible option 
				if ( ((y<13)&&(y>9) )&&( (x>0)&&(x<24)) )   {endwin();go_on = 0;}
				if ( ((y<58)&&(y>44) )&&( (x>59)&&(x<78)) ) {endwin();go_on = 0;}
				if ( ((y<34)&&(y>29) )&&( (x>24)&&(x<54)) ) {endwin();go_on = 0;}
			 

                	} //while ( c =getch() ==ERR )
               

                	switch (c) {
				case KEY_LEFT: u = -abs(u+v) ;v = 0 ;break;
                 		case KEY_RIGHT:  u =  abs(u+v); v = 0 ;break;
                        	case KEY_UP: v = -abs (u+v); u = 0 ;break;
                        	case KEY_DOWN:v =  abs(u+v); u = 0 ;break;
                        	default: go_on = 1;
                	} //switch(c)
		} //while (go_on)

       		endwin();
		cout << "game over \n input your name and see the scoreboard \n" ;
		cin >>UserIn[player_number].Name;
		UserIn[player_number].Points = score;
		vector<UserData> show = UserIn;
		sort(show.begin(),show.end(),cmp);

		cout << "___________________________________________________ \n";
		cout <<	"|"<<"Name ______"<<"__|"<<"____score____"<<"___|\n";                  
		cout <<	"|"<<show[99].Name<<"________|"<<show[99].Points<<"_________|\n";
		cout <<	"|"<<show[98].Name<<"________|"<<show[98].Points<<"_________|\n";
		cout <<	"|"<<show[97].Name<<"________|"<<show[97].Points<<"_________|\n";
		cout <<	"|"<<show[96].Name<<"________|"<<show[96].Points<<"_________|\n";
		cout <<	"|"<<show[95].Name<<"________|"<<show[95].Points<<"_________|\n";
		cout <<	"|"<<show[94].Name<<"________|"<<show[94].Points<<"_________|\n";
		cout <<	"|"<<show[93].Name<<"________|"<<show[93].Points<<"_________|\n";
		cout <<	"|"<<show[92].Name<<"________|"<<show[92].Points<<"_________|\n";
		cout <<	"|"<<show[91].Name<<"________|"<<show[91].Points<<"_________|\n";
		cout <<	"|"<<show[90].Name<<"________|"<<show[90].Points<<"_________|\n";
		cout << "_"<<"___________"<<"__|"<<"_____________"<<"___|\n";

		cout << "would u like to play again ? \nenter any button to continue if not just enter number 0 \n ";
		cin >> cont_play;
		sleep(1);

		player_number++;
	}//while cont_play end
        return 0;
}




