#include "SVGdraw.h"
#include <cmath>
#include <iostream>


struct bod {
    double x, y;
};

// Generate point
void generujBod(bod &k, double x, double y) {
    k.x = x;
    k.y = y;
}

// Counts distance between two points
double dlzka(bod &bod1, bod &bod2) {
    double dx = bod1.x - bod2.x;
    double dy = bod1.y - bod2.y;
    return sqrt(dx * dx + dy * dy);
}

// Takes the coordinates of a point and finds the nearest post office from the array
int najbliz(bod &bod1, bod a[], int num) {
    double res[num];
    for (int i = 0; i < num; i++) {
        res[i] = dlzka(bod1, a[i]);
    }
    int index = 0;

    for (int i = 0; i < num; i++) {
        if (res[i] < res[index]) {
            index = i;
        }

    }
    return index;
}

// Checks if number is in array
bool findTarget(int a[], int target, int size) {
    for (int i = 0; i < size; i++) {
        if (a[i] == target) {
            return true;
        }
    }
    return false;
}

// Counts houses for each post office
int pocetDomov(int a[], int len, int target) {
    int count = 0;
    for (int i = 0; i < len; i++) {
        if (a[i] == target) {
            count++;
        }
    }
    return count;
}

int main() {
    // Sets the number of houses and post offices and initializes an array with colors
    int d, p;
    cin >> d >> p;
    const int MAXP = 10;
    const char *farby[MAXP] = {"red", "green", "blue", "white", "black", "gray",
                               "yellow", "brown", "orange", "purple"};

    // Initializes arrays of houses and post offices
    bod body1[d];
    bod body2[p];

    // Puts houses in the array
    for (int i = 0; i < d; i++) {
        double x, y;
        cin >> x >> y;
        generujBod(body1[i], x, y);
    }

    // Puts post offices in the array
    for (int i = 0; i < p; i++) {
        double x, y;
        cin >> x >> y;
        generujBod(body2[i], x, y);
    }

    // Initializes a drawing and accepts canvas and shape sizes
    int sirka, vyska, polomer;
    cin >> sirka >> vyska >> polomer;

    SVGdraw drawing(sirka, vyska, "posty.svg");

    int total[d];

    // Shows the nearest post office for each house and draws a line between them
    for (int i = 0; i < d; i++) {
        int idx = najbliz(body1[i], body2, p);
        total[i] = idx;
        cout << "dom " << i << " posta " << idx << endl;
        drawing.drawLine(body1[i].x, body1[i].y, body2[idx].x, body2[idx].y);
    }

    // Outputs number of houses for each post office
    for (int i = 0; i < p; i++) {
         bool exists = findTarget(total, i, d);
         if (exists) {
            cout << "posta " << i << " pocet domov " << pocetDomov(total, d, i) << endl;
         }
         else {
            cout << "posta " << i << " pocet domov " << 0 << endl;
         }
    }

    // Draws the figures of houses and post offices on the canvas in the desired color
    for (int i = 0; i < p; i++) {
        drawing.setFillColor(farby[i]);
        drawing.drawRectangle(body2[i].x, body2[i].y, polomer, polomer);
        for (int j = 0; j < d; j++) {
            if (najbliz(body1[j], body2, p) == i) {
                drawing.drawEllipse(body1[j].x, body1[j].y, polomer, polomer);
            }
        }
    }

    // Finishes the drawing
    drawing.finish();
}