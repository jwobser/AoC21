// https://www.reddit.com/r/adventofcode/comments/r9824c/comment/hnav2mt/?utm_source=share&utm_medium=web2x&context=31
#include <stdio.h>

char points[1024][1024];

short cmp (short a, short b)
{
	return (b < a) - (a < b);
}

int main (void)
{
	int ans = 0;
	for (short x,y,xx,yy; scanf("%hd,%hd%*s%hd,%hd", &x, &y, &xx, &yy) == 4; ) {
		short dx = cmp(xx, x), dy = cmp(yy, y);
        // if(dx && dy) continue;
		for (xx += dx, yy += dy; x != xx || y != yy; x += dx, y += dy)
			ans += ++points[x][y] == 2;
	}
	printf("%d", ans);
}