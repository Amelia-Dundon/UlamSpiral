#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
typedef struct _spiral spiral;
typedef struct _spiral {
    int n;
    int* s;
};
void setElement(spiral* s, int row, int col, int val) {
    int k = (col - 1) * (s->n) + row;
    s->s[k] = val;
    //printf("1-D position:(%d-1)*(%d)+%d = %d\n",row,s->n,col,k);
}
int getElement(spiral* s, int row, int col) {
    int k = (col - 1) * (s->n) + row;
    return k;
}
spiral* newSpiral(int n) {
    spiral* s = (spiral*)(malloc(sizeof(spiral)));
    s->n = n;
    s->s = (int*)(malloc(n * n * sizeof(int)));
    return s;
}
int prime(int n) {
    if (n == 2 || n == 5) {
        return 1;
    }
    if (n % 10 == 2 || n % 10 == 4 || n % 10 == 5 || n % 10 == 6 || n % 10 == 8 || n % 10 == 0) {
        return 0;
    }
    if (n == 1) {
        return 0;
    }
    for (int i = 2; i < n - 1; i++) {
        if (n % i == 0) { return 0; }
    }
    return 1;
}
spiral* UlamSpiral(int n) {
    spiral* s = newSpiral(n);
    int x = n / 2 + 1;
    int y = n / 2 + 1;
    int i = 0;
    int square = 1;
    int part = 1;
    while (i < n * n) {
        i = i + 1;
        setElement(s, x, y, i);
        //printf("(x,y):(%d,%d)- i:%d square:%d square^2:%d\n" , x,y,i,square,square*square);
        int c[4] = { (square * square) - (square - 1) * 3,(square * square) - (square - 1) * 2,(square * square) - (square - 1),(square * square) };
        //printf("%d,%d,%d,%d, i:%d\n", c[0], c[1], c[2], c[3],i);
        if (i == square * square) {
            x++;
            square += 2;
            part = 1;
        }
        else {
            //coordinate check
            if (i == c[0]) {
                part = 2;
            }
            else if (i == c[1]) {
                part = 3;
            }
            else if (i == c[2]) {
                part = 4;
            }
            else if (i == c[3]) {
                part = 1;
            }

            //coordinate change
            if (part == 1) {
                y--;
            }
            else if (part == 2) {
                x--;
            }
            else if (part == 3) {
                y++;
            }
            else if (part == 4) {
                x++;
            }
        }
    }
    return s;
}
