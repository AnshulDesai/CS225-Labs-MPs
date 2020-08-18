#ifndef _MAZE_H_
#define _MAZE_H_

#include <cstdlib>
#include <vector>
#include <queue>
#include <time.h>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "dsets.h"
using namespace std;
using namespace cs225;

class SquareMaze
{
	public:
		SquareMaze();
		void makeMaze (int w, int h);
		bool canTravel (int x, int y, int dir) const;
		void setWall (int x, int y, int dir, bool exists);
		vector<int> solveMaze ();
		PNG * drawMaze () const;
		PNG * drawMazeWithSolution ();

	private:
		vector<vector<vector<bool>>> wallcheck;
		int width;
		int height;
		vector<int> checkAdj(int v) ;
		int checkDir(int p, int v) ;

};

#endif
