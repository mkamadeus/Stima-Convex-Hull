#include "koolplot.h"
#include<iostream>

int main()
{
    Plotdata x(-3.0, 3.0), y = sin(x) - 0.5*x;
    plot(x, y);
    return 0;
}


