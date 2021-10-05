#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>


// A 3D multivector has 8 elements
// a scalar, a three dimensional vector, a three dimensional bivector, and a trivector
// [ s x y z xy yz zx xyz ]
// [ e0 e1 e2 e3 e12 e23 e31 e123 ]

// 3D geometric product
void multiply_multivectors(double* a, double* b, double* c)
{

    // multivector product in R3
    // c.e0     =   +a.e0*b.e0  +a.e1*b.e1  +a.e2*b.e2  +a.e3*b.e3  -a.e12*b.e12 -a.e23*b.e23 -a.e31*b.e31 -a.e123*b.e123;
    // c.e1     =   +a.e0*b.e1  +a.e1*b.e0  -a.e2*b.e12  +a.e3*b.e31  +a.e12*b.e2 -a.e23*b.e123 -a.e31*b.e3 -a.e123*b.e23;
    // c.e2     =   +a.e0*b.e2  +a.e1*b.e12  +a.e2*b.e0  -a.e3*b.e23  -a.e12*b.e1 +a.e23*b.e3 -a.e31*b.e123 -a.e123*b.e31;
    // c.e3     =   +a.e0*b.e3  -a.e1*b.e31  +a.e2*b.e23  +a.e3*b.e0  -a.e12*b.e123 -a.e23*b.e2 +a.e31*b.e1 -a.e123*b.e12;
    // c.e12    =   +a.e0*b.e12  +a.e1*b.e2  -a.e2*b.e1  +a.e3*b.e123  +a.e12*b.e0 -a.e23*b.e31 +a.e31*b.e23 +a.e123*b.e3;
    // c.e23    =   +a.e0*b.e23  +a.e1*b.e123  +a.e2*b.e3  -a.e3*b.e2  +a.e12*b.e31 +a.e23*b.e0 -a.e31*b.e12 +a.e123*b.e1;
    // c.e31    =   +a.e0*b.e31  -a.e1*b.e3  +a.e2*b.e123  +a.e3*b.e1  -a.e12*b.e23 +a.e23*b.e12 +a.e31*b.e0 +a.e123*b.e2;
    // c.e123   =   +a.e0*b.e123  +a.e1*b.e23  +a.e2*b.e31  +a.e3*b.e12  +a.e12*b.e3 +a.e23*b.e1 +a.e31*b.e2 +a.e123*b.e0;    

    // "All the pieces matter" - Lester Freamon

    c[0]   =   +a[0]*b[0]  +a[1]*b[1]  +a[2]*b[2]  +a[3]*b[3]  -a[4]*b[4] -a[5]*b[5] -a[6]*b[6] -a[7]*b[7];
    c[1]   =   +a[0]*b[1]  +a[1]*b[0]  -a[2]*b[4]  +a[3]*b[6]  +a[4]*b[2] -a[5]*b[7] -a[6]*b[3] -a[7]*b[5];
    c[2]   =   +a[0]*b[2]  +a[1]*b[4]  +a[2]*b[0]  -a[3]*b[5]  -a[4]*b[1] +a[5]*b[3] -a[6]*b[7] -a[7]*b[6];
    c[3]   =   +a[0]*b[3]  -a[1]*b[6]  +a[2]*b[5]  +a[3]*b[0]  -a[4]*b[7] -a[5]*b[2] +a[6]*b[1] -a[7]*b[4];
    c[4]   =   +a[0]*b[4]  +a[1]*b[2]  -a[2]*b[1]  +a[3]*b[7]  +a[4]*b[0] -a[5]*b[6] +a[6]*b[5] +a[7]*b[3];
    c[5]   =   +a[0]*b[5]  +a[1]*b[7]  +a[2]*b[3]  -a[3]*b[2]  +a[4]*b[6] +a[5]*b[0] -a[6]*b[4] +a[7]*b[1];
    c[6]   =   +a[0]*b[6]  -a[1]*b[3]  +a[2]*b[7]  +a[3]*b[1]  -a[4]*b[5] +a[5]*b[4] +a[6]*b[0] +a[7]*b[2];
    c[7]   =   +a[0]*b[7]  +a[1]*b[5]  +a[2]*b[6]  +a[3]*b[4]  +a[4]*b[3] +a[5]*b[1] +a[6]*b[2] +a[7]*b[0];    

}

void print_multivector(double *c)
{
    printf("[");
    if ( c[0] != 0 ) printf(" %+.2f", c[0] );
    if ( c[1] != 0 ) printf(" %+.2fx", c[1] );
    if ( c[2] != 0 ) printf(" %+.2fy", c[2] );
    if ( c[3] != 0 ) printf(" %+.2fz", c[3] );
    if ( c[4] != 0 ) printf(" %+.2fxy", c[4] );
    if ( c[5] != 0 ) printf(" %+.2fyz", c[5] );
    if ( c[6] != 0 ) printf(" %+.2fzx", c[6] );
    if ( c[7] != 0 ) printf(" %+.2fxyz", c[7] );
    printf(" ]");
    // printf("[ %.1f + (%.1fx + %.1fy + %.1fz) + (%.1fxy + %.1fyz + %.1fzx) + %.1fxyz ]", c[0],c[1],c[2],c[3],c[4],c[5],c[6],c[7] );
}

void make_vector_in_spherical_coordinates(double r, double theta, double phi, double *mv)
{
    // Spherical coordinates
    // x = cos(theta)*sin(phi); y = cos(theta-90)*sin(phi); z = cos(phi); 
    mv[0] = 0;
    mv[1] = r*cos(theta)*sin(phi);
    mv[2] = r*sin(theta)*sin(phi);
    mv[3] = r*cos(phi);
    mv[4] = 0;
    mv[5] = 0;
    mv[6] = 0;
    mv[7] = 0;
}

#define MUL(a,b,c) \
{\
    multiply_multivectors(a,b,c);\
    print_multivector(a); printf(" * ");\
    print_multivector(b); printf(" = ");\
    print_multivector(c); printf("\n"); \
}\


int multivector_demo() // int argc, char **argv)
{
    #define TWOPI 6.28318530718

    double x[8] = { 0, 1,0,0 };
    double y[8] = { 0, 0,1,0 };
    double xy[8];
    double temp[8];

    // To multiply multivectors
    // xy = x*y
    multiply_multivectors(x,y,xy);
    print_multivector(xy);
    

    MUL(x,y,xy);
    MUL(x,xy,temp);
    MUL(y,xy,temp);
    MUL(xy,xy,temp);


    double a[8] = { 0, 2,3,8,  4,8,15, 1};
    double b[8] = { 0, 2,3,8,  4,8,15, 1};
    MUL(a,b,temp);

    // double c[8],d[8];
    // make_vector_in_spherical_coordinates(1,TWOPI/8,TWOPI/8, c);
    // MUL(x,c,d)

    return 0;

}



int main()
{
    multivector_demo();
}





// double* multivector_rotate(double* v, double* a, double* b)
// {
//     // Rotate v by twice the angle between a and b;
//     // return multivector_mul(5, b,a,v,a,b);
// }

// double* multivector_vector_spherical(double r, double theta, double phi)
// {
//     // Spherical coordinates
//     // x = cos(theta)*sin(phi); y = cos(theta-90)*sin(phi); z = cos(phi); 
//     return multivector_vector(
//         r*cos(theta)*sin(phi), 
//         r*sin(theta)*sin(phi), 
//         r*cos(phi)
//     );
// }


