#include "maze.h"
#include <stdio.h>
#include <math.h>

SquareMaze::SquareMaze () {
}

void SquareMaze::makeMaze(int w, int h) {
	width = w;
	height = h;
	wallcheck = vector<vector<vector<bool>>>(width);
	for (int x = 0; x < width; x++) {
		wallcheck[x] = vector<vector<bool>>(height);
		for (int y = 0; y < height; y++) {
			wallcheck[x][y] = vector<bool>(2);
			wallcheck[x][y][0] = true;
			wallcheck[x][y][1] = true;
		}
	}

	DisjointSets lit;
	lit.addelements(width * height);
	int yikes = (width * height);

	while (yikes > 1) {
		int xr = rand() % width;
		int yr = rand() % height;
		int dr = rand() % 2;
		if (wallcheck[xr][yr][dr]) {
      if (dr == 0 && xr < width - 1) {
				if (lit.find((xr * height) + yr) != lit.find(((xr + 1) * height) + yr)) {
					yikes--;
					lit.setunion((xr * height) + yr, ((xr + 1) * height) + yr);
					wallcheck[xr][yr][dr] = false;
				}
			}
			else if (dr == 1 && yr < height - 1) {
				if (lit.find((xr * height) + yr) != lit.find((xr * height) + (yr + 1))) {
					yikes--;
					lit.setunion((xr * height) + yr, (xr * height) + (yr + 1));
					wallcheck[xr][yr][dr] = false;
				}
			}
		}
	}

}

bool SquareMaze::canTravel(int x, int y, int dir) const {
	if (!((x >= 0) && (x < width) && (y >= 0) && (y < height))) {
    return false;
  }
	if (dir == 0 && (x + 1 >= 0) && (x + 1 < width) && (y >= 0) && (y < height) && wallcheck[x][y][0]==false) {
    return true;
  }
	else if (dir == 1 && (x >= 0) && (x < width) && (y + 1 >= 0) && (y + 1 < height) && wallcheck[x][y][1]==false) {
    return true;
  }
	else if (dir == 2 && (x - 1 >= 0) && (x - 1 < width) && (y >= 0) && (y < height) && wallcheck[x-1][y][0]==false) {
    return true;
  }
	else if (dir == 3 && (x >= 0) && (x < width) && (y - 1 >= 0) && (y - 1 < height) && wallcheck[x][y-1][1]==false) {
    return true;
  }
	return false;
}


void SquareMaze::setWall(int x, int y, int dir, bool exists) {
	if ((x >= 0) && (x < width) && (y >= 0) && (y < height))
	{
		wallcheck[x][y][dir] = exists;
	}
}

vector<int> SquareMaze::solveMaze() {
	vector<int> dm = vector<int>(width*height, 0);
	vector<int> pm = vector<int>(width*height, 0);
	vector<bool> vm = vector<bool>(width*height, false);
	queue<int> q;
	vm[0] = true;
	q.push(0);
	while (!q.empty())
	{
		int vertex = q.front();
		q.pop();
		for (auto & sauce : checkAdj(vertex)) {
			if (!vm[sauce])
			{
				vm[sauce] = true;
				q.push(sauce);
				dm[sauce] = dm[vertex] + 1;
				pm[sauce] = vertex;
			}
		}
	}
  int y = height - 1;
	int pos = y;
	for (int x=0; x<width; x++) {
		int lol = (x * height) + y;
		if (dm[lol] > dm[pos]) {
			pos = lol;
		}
	}
	int vend = pos;
	vector<int> path;
	while (pm[vend] != vend)
	{
		int dir = checkDir(pm[vend], vend);
		path.push_back(dir);
		vend = pm[vend];
	}
	std::reverse(path.begin(),path.end());
	return path;
}

PNG * SquareMaze::drawMaze() const {
	PNG* mazeImage = new PNG(width * 10 + 1, height * 10 + 1);

	HSLAPixel black(0, 0, 0);

	for (int i = 0; i< width * 10 + 1; i++) {
		if (i<1 || i>9) {
			HSLAPixel & pixel = mazeImage->getPixel(i, 0);
			pixel.s = black.s;
			pixel.h = black.h;
			pixel.l = black.l;
		}
	}
	for (int i = 0; i < height * 10 + 1; i++) {
		HSLAPixel & pixel = mazeImage->getPixel(0, i);
		pixel.s = black.s;
		pixel.h = black.h;
		pixel.l = black.l;
	}
	for (int a = 0; a < width; a++) {
		for (int b = 0; b < height; b++) {
			if (wallcheck[a][b][0]) {
				for (int c = 0; c <= 10; c++) {
					HSLAPixel & pixel = mazeImage->getPixel((a+1)*10, b*10+c);
					pixel.s = black.s;
					pixel.h = black.h;
					pixel.l = black.l;
				}
			}
			if (wallcheck[a][b][1]) {
				for (int c = 0; c <= 10; c++) {
					HSLAPixel & pixel = mazeImage->getPixel(a*10+c, (b+1)*10);
					pixel.s = black.s;
					pixel.h = black.h;
					pixel.l = black.l;
				}
			}
		}
	}
	return mazeImage;
}

PNG * SquareMaze::drawMazeWithSolution () {
	PNG* mazeImage = drawMaze();

	HSLAPixel red(0,1,0.5,1);

	vector<int> path = solveMaze();
	int mark = 5;
	int mark2 = 5;
	for (int yeet = 0; yeet < (int)path.size(); yeet++) {
		if (path[yeet]==0) {
			for (int i = 0; i <= 10; i++) {
				HSLAPixel & pixel = mazeImage -> getPixel(mark + i, mark2);
				pixel.s = red.s;
				pixel.h = red.h;
				pixel.l = red.l;
			}
			mark += 10;
		}
		else if (path[yeet] == 1) {
			for (int i = 0; i <= 10; i++) {
				HSLAPixel & pixel = mazeImage -> getPixel(mark, mark2 + i);
				pixel.s = red.s;
				pixel.h = red.h;
				pixel.l = red.l;
			}
			mark2 += 10;
		}
		else if (path[yeet]==2) {
			for (int i = 0; i <= 10; i++) {
				HSLAPixel & pixel = mazeImage -> getPixel(mark - i, mark2);
				pixel.s = red.s;
				pixel.h = red.h;
				pixel.l = red.l;
			}
			mark -= 10;
		}
		else if (path[yeet]==3) {
			for (int i = 0; i <= 10; i++) {
				HSLAPixel & pixel = mazeImage -> getPixel(mark, mark2 - i);
				pixel.s = red.s;
				pixel.h = red.h;
				pixel.l = red.l;
			}
			mark2 -= 10;
		}
	}
	mark -= 5;
	mark2 += 5;
	for (int i = 1; i < 10; i++) {
		HSLAPixel & pixel = mazeImage -> getPixel(mark+i, mark2);
		pixel.l = 1;
	}
	return mazeImage;
}

vector<int> SquareMaze::checkAdj(int v) {
	vector<int> yeet;
	pair<int,int> coord = pair<int,int>(v / height , v % height);
	int x = coord.first;
	int y = coord.second;
	if ((x - 1 >= 0) && (x - 1 < width) && (y >= 0) && (y < height) && !wallcheck[x-1][y][0]) {
		yeet.push_back(((x-1)*height)+y);
	}
	if ((x + 1 >= 0) && (x + 1 < width) && (y >= 0) && (y < height) && !wallcheck[x][y][0]) {
		yeet.push_back(((x+1)*height)+y);
	}
	if ((x >= 0) && (x < width) && (y - 1 >= 0) && (y - 1 < height) && !wallcheck[x][y-1][1]) {
		yeet.push_back((x*height) + y - 1);
	}
	if ((x >= 0) && (x < width) && (y + 1 >= 0) && (y + 1 < height) && !wallcheck[x][y][1]) {
		yeet.push_back((x*height) + y + 1);
	}
	return yeet;
}

int SquareMaze::checkDir(int p, int v) {
	pair<int,int> coordp = pair<int,int>( p / height , p % height );
	int xp = coordp.first;
	int yp = coordp.second;
	pair<int,int> coordv = pair<int,int>(v / height , v % height);
	int xv = coordv.first;
	int yv = coordv.second;
	if (xp == xv - 1) {
    return 0;
  }
  if (yp == yv - 1) {
    return 1;
  }
	if (xp == xv + 1) {
    return 2;
  }
	if (yp == yv + 1) {
    return 3;
  }
	return int();
}
