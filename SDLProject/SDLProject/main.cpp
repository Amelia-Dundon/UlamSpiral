#include "UlamSpiral.h"
#include <SDL.h>
#include <cmath>
#include <iostream>
int printSpeed = 10;
void renderSpiral(spiral* s) {
    int x = s->n / 2 + 1;
    int y = s->n / 2 + 1;
    int i = 0;
    int square = 1;
    int part = 1;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    //Creating Screen and Background
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(s->n * 4, s->n * 4, 0, &window, &renderer);
    SDL_RenderSetScale(renderer, 4, 4);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    //center for testing
    SDL_SetRenderDrawColor(renderer, 0,255, 0, 0);
    SDL_RenderDrawPoint(renderer, s->n / 2, s->n / 2);
    SDL_RenderPresent(renderer);
    SDL_Delay(10);
    while (i < s->n * s->n) {
        
        i = i + 1;
        if (prime(i)) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawPoint(renderer, (x-1), (y-1));
            SDL_RenderPresent(renderer);
            SDL_Delay(printSpeed);
        }
        int c[4] = { (square * square) - (square - 1) * 3,(square * square) - (square - 1) * 2,(square * square) - (square - 1),(square * square) };
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
    SDL_Event e;
    int running = 1;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = 0;
                break;
            }
            SDL_Delay(10);
        }
    }
    SDL_RenderPresent(renderer);
}
int main(int argc, char** argv) {
	int n;
	if (argc < 2) {
		fprintf(stdout, "use -h for the how to use function, otherwise enter an odd integer\n");
	}else if (argv[1][0] == '-' && argv[1][1] == 'h') {
		fprintf(stdout, "Enter an odd interger n and the program will print a UlamSpiral of size n^2. If you enter a even number it will round up to the next odd number. To change the print speed, enter the -i modifier followed by the speed in milliseconds between each printed pixel then followed by the print size. Speed will otherwise default to 100.\n");
    }
    else if (argv[1][0] == '-' && argv[1][1] == 'i') {
        if (argc <= 3) {
            fprintf(stdout, "Improper Inputs, after -i please enter the print speed and then the size n.");
        }else {
            printSpeed = atoi(argv[2]);
            n = atoi(argv[3]);
            if (n) {
                if (n % 2 == 0) { n++; }
                spiral* s = UlamSpiral(n);
                renderSpiral(s);
            }
        }
        
    }
    else if (atoi(argv[1])) {
        n = atoi(argv[1]);
        if(n%2==0){ n++;}
		spiral* s = UlamSpiral(n);
		renderSpiral(s);
	}
    n = 9;
	return 0;
}