#include <iostream>
#include <cstdlib> 
#include <ctime>
#include "TXLib.h"

const int SizeX_of_Window = 950;                     
const int SizeY_of_Window = 600;

const int SizeX_of_Rectangle = 350;
const int SizeY_of_Rectangle = 500; 

const int Radius = 4;



class CoordSys {

public:    
	int x = 0, y = 0, scaleX = 0, scaleY = 0,
		x0 = 0, y0 = 0, x1 = 0, y1 = 0;
        
	int ToPixelsX() {
        return (x0 + scaleX * x);
    }

	int ToPixelsY() {
        return (y1 - scaleY * y);
    }
    
    void Coordinate_Grid() {
        
        txSetColor(TX_BLACK);

        for (int i = 0; i < ((x1 - x0) / 15); i++) 
            txLine(x0 + i * 15, y0, x0 + i * 15, y1);

        for (int j = 0; j < ((y1 - y0) / 15); j++)
            txLine(x0, y0 + j * 15, x1, y0 + j * 15);

        txSetFillColor(TX_BLACK);
        POINT arrow1[3] = { {x0, y0}, {x0 + 3, y0 + 10}, {x0 - 3, y0 + 10} };
        txPolygon(arrow1, 3);

        POINT arrow2[3] = { {x1, y1}, {x1 - 10, y1 + 3}, {x1 - 10, y1 - 3} };
        txPolygon(arrow2, 3);

        txSelectFont("Arial", 15);
        txTextOut(x0 - 10, y1 + 2, "0");
        txTextOut(x1 - 80, y1 + 10, "amount of elements");
    }
};


int bubbleSort(int Amount_Elements, int* massive, CoordSys* coordinate_comparisons, CoordSys* coordinate_exchanges);
int Random_Array(int* massive, int i);

int main() {
	int N = 0;
    int Indent = 50;
    
	std::cout << "Please enter maximum amount of elements" << std::endl;
    std::cin >> N;
    int* massive = new int[N];

	CoordSys coordinate_comparisons;
	CoordSys coordinate_exchanges;

	coordinate_comparisons.scaleX = 300 / N;
	coordinate_comparisons.scaleY = coordinate_comparisons.scaleX / 5;
	coordinate_exchanges.scaleX = 300 / N;
	coordinate_exchanges.scaleY = coordinate_exchanges.scaleX / 5;

	txCreateWindow(SizeX_of_Window, SizeY_of_Window);
    txSetFillColor(TX_ORANGE);
	txClear();

	txSetFillColor(TX_GREY);
    txSetColor(TX_BLACK);
	txRectangle(Indent, Indent, Indent + SizeX_of_Rectangle, Indent + SizeY_of_Rectangle);
	txRectangle(2 * Indent + SizeX_of_Rectangle, Indent, 2 * Indent + 2 * SizeX_of_Rectangle, Indent + SizeY_of_Rectangle);
    
    txSelectFont("", 30);
	txTextOut(300, 2, "Bubble sort characteristic");

	coordinate_comparisons.x0 = Indent;
	coordinate_comparisons.y0 = Indent;
	coordinate_comparisons.x1 = Indent + SizeX_of_Rectangle;
	coordinate_comparisons.y1 = Indent + SizeY_of_Rectangle;

	coordinate_exchanges.x0 = 2 * Indent + SizeX_of_Rectangle;
	coordinate_exchanges.y0 = Indent;
	coordinate_exchanges.x1 = 2 * Indent + 2 * SizeX_of_Rectangle;
	coordinate_exchanges.y1 = Indent + SizeY_of_Rectangle;
    
    coordinate_comparisons.Coordinate_Grid();
    coordinate_exchanges.Coordinate_Grid();
    txSelectFont("Arial", 15);
    txTextOut(coordinate_comparisons.x0 - 45, coordinate_comparisons.y0 - 20, "amount of comparisons");
    txTextOut(coordinate_exchanges.x0 - 45, coordinate_exchanges.y0 - 20, "amount of exchanges");
    
    txSetFillColor(TX_BLACK);
    txSetColor(TX_WHITE);
    txCircle(53, 550, Radius);
    txCircle(453, 550, Radius);

    for (int i = 0; i < N; i++) {
        Random_Array(massive, i + 1);
        coordinate_comparisons.x = i;
        coordinate_exchanges.x = i;
        bubbleSort(i + 1, massive, &coordinate_comparisons, &coordinate_exchanges);

        int X_comparisons = coordinate_comparisons.ToPixelsX(), Y_comparisons = coordinate_comparisons.ToPixelsY(),
        X_exchanges = coordinate_exchanges.ToPixelsX(), Y_exchanges = coordinate_exchanges.ToPixelsY();
        
        txSetFillColor(TX_BLACK);
        txSetColor(TX_WHITE);

        if ((X_comparisons + Radius <= coordinate_comparisons.x1) && (Y_comparisons - Radius >= coordinate_comparisons.y0)
            && (X_comparisons - Radius >= coordinate_comparisons.x0) && (Y_comparisons + Radius <= coordinate_comparisons.y1))
        txCircle(X_comparisons, Y_comparisons, Radius);

        if ((X_exchanges + Radius <= coordinate_exchanges.x1) && (Y_exchanges - Radius >= coordinate_exchanges.y0)
            && (X_exchanges - Radius >= coordinate_exchanges.x0) && (Y_exchanges + Radius <= coordinate_exchanges.y1))
        txCircle(X_exchanges, Y_exchanges, Radius);
    }
    
    
    
    if ((txMouseButtons() && 1)) { //&& (txMouseX() <= 920) && (txMouseX() >= 820) && (txMouseY() <= 400) && (txMouseY() >= 300)) {
        txSelectFont("Arial", 100);
        txTextOut(820, 450, "DIMA");
    }
    return 0;
}

int bubbleSort(int size, int* massive, CoordSys* coordinate_comparisons, CoordSys* coordinate_exchanges) {
    
	int Counter_Comparisons = 0, Counter_Exchanges = 0;

	for (int i = 0; i < size; i++) {
		for (int j = size - 1; j > i; j--) {
			Counter_Comparisons++;
			if (massive[j - 1] > massive[j]) {
				int temp = massive[j - 1];
				massive[j - 1] = massive[j];
				massive[j] = temp;
				Counter_Exchanges ++;
			}
		}
	}

	coordinate_comparisons->y = Counter_Comparisons;
	coordinate_exchanges->y = Counter_Exchanges;

	return 0;
}

int Random_Array(int* massive, int i) {
    
    srand(time(0));
	for (int j = 0; j < i; j++)
	{
		massive[j] = rand();
	}
	return *massive;
}
