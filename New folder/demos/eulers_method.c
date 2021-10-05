#include <stdio.h>
#include <math.h>

// float f_dash(float x, float y, float *dx, float *dy) { return y; }

int eulers_method_main()
{
    // Euler's Method for solving a differential equation
    // ---------------------------------------------------
    // start at a point.  calculate the slope
    // follow the slope to the next point
    // repeat

    // y1 = dydx(x0,y0) * delta_x + y0;
    // x1 = x0 + delta_x;

    // khan https://www.youtube.com/watch?v=q87L9R9v274



    if (0) {
        // Example: Draw the line y = e^x from its vector field 
        // dy_dx = y, y(0) = 1

        float x = 0;
        float y = 1;
        float slope = y; 
        float delta_x = 0.0001;

        for (int i = 0; i < 1.0/delta_x; i += 1)
        {

            slope = y;
            y = y + slope * delta_x;
            x = x + delta_x;
            printf("x, y, slope: [ %f %f %f ]\n", x, y, slope);
        }
        // output 
        // x, y, slope: [ 1.0000 2.7181 2.7179 ]
        // yahoo!!
    }



    {   
        // Example: Draw a circle using the vector field < -y, x >

        float x = 1;
        float y = 0;
        float dx = -y;
        float dy = x;
        float step = 0.0001;
        #define TWOPI 6.28318530718

        printf("Euler's Method for solving differential equations and vector fields\n");
        printf("---------------------------------------------------------------------\n");
        printf("Drawing a circle using the vector field < -y, x >\n");
        printf("Starting point\n");
        printf("x, y, dx, dy: [ %f %f %f %f %f ]\n", x, y, dx, dy, step);

        for (int i = 0; i < TWOPI/step; i += 1)
        {
            dx = -y;
            dy = x;

            y = y + dy * step;
            x = x + dx * step;
            // printf("x, y, dx, dy: [ %f %f %f %f %f ]\n", x, y, dx, dy, step);
        }
        printf("End point\n");
        printf("x, y, dx, dy: [ %f %f %f %f %f ]\n", x, y, dx, dy, step);

        // output 
        // using float
        // x, y, dx, dy: [ 1.000314 0.000015 0.000085 1.000314 0.000100 ]
        // using double
        // x, y, dx, dy: [ 1.000316 0.000015 0.000085 1.000316 0.000100 ]


    }




    // Conservative Vector Fields
    // -----------------------------------------

    // A conservative vector field is one that has an associated scalar field.
    // that can be found by integrating all of the partial derivative equations

    // Here's a scalar field
    // f(x,y) = 1/4 x4y4 + 1/2 x2 + 1/2 y2 ) + c

    // The associated vector field is the gradient of f 
    // grad f(x,y) = dfdx(x,y) i  + dfdy(x,y) j 

    // let fx be dfdx and fy be dfdy

    // fx = x3y4 + x
    // fy = x4y3 + y


    // A vector field is conservative if you can integrate all of the gradient
    // components into the same scalar field
    // of if you take several derivatives with respect to the different variables
    // in all the different orders and they're all the same.



    return 0;
}


// int main()
// {
//     eulers_method_main();
// }





int newtons_method_main()
{

    // Newton's Method for solving an equation of one variable
    // ---------------------------------------

    // x1 = x0 - f(x0)/f'(x0)

    // This can solve any equation of the form f(x) = some_number.
    // You do need to give it a good initial x position, specially if it's a higher
    // order equation.

    // Simply 
    // 1. Put the equation into homogenous form f(x) = 0
    // 2. set the initial x value
    // 3. Run the algorithm for a certain number of iterations

    // The technique is to calculate the height and derivative at the current x value
    // and follow them down to the next x value at the x-axis.
    
    // The way that polynomials curve means that this technique should bring you 
    // closer and closer to one of the closest roots of the equation.


    // set x to some value, say 0.
    // x = x - ( f(x) / f'(x) )
    float x = 0;
    for (int i=0; i<10; ++i) {
        x = x - ( (x*x + 5*x -20) / (2*x + 5) );
    }
    printf("newton's method x: %f\n", x);
    
    return 0;
}


int main()
{
    eulers_method_main();
}