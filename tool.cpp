#include "tool.h"

tool::tool(){xloc=0;yloc=0;}
tool::tool(int a){xloc=a;yloc=a;}
void tool::GetBasicConfig(){
		initscr(); 
		cbreak(); 
		noecho(); 
		keypad(stdscr,TRUE);
        	nodelay(stdscr,TRUE);   
                start_color();
}

void tool::GetBlock(int x0,int x1, int y0, int y1){
	xloc=x0;yloc=y0;
	for (int i=x0;i<x1;i++ ){
		for(int j=y0;j<y1;j++){
			mvaddstr(j,i," ");
		}
	}
}	


