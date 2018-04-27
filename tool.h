#include <ncurses/curses.h>
using namespace std;

class tool{
	public:	
		tool();
		tool(int a);
		void GetBasicConfig();
		void GetBlock(int x0,int x1,int y0,int y1);
		
	private:
		int xloc;
		int yloc;


};
