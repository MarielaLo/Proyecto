#include <complex>
#include <iostream>
#include <valarray>
#include <time.h>
#include<fstream> 

using namespace std;


int n = 0;

//se utilizo complex
typedef complex<double> Complex;

typedef valarray<Complex> CArray;


double funcion(double);


template <class TI>
void obtener_datos(TI data[])
{
    for (int i = 0; i < n; i++)
    {
        data[i] = funcion(i);
    }
}

// la función DFT.
void DFT(CArray &, Complex[]);

int main()
{
    cout << "El numero maximo n = " ;
    int p;
    cin >> p;
    fstream myfile;
    myfile.open("DFT_I.txt", fstream::out);
    clock_t t;
    for (int j = 4; j <= p; j *=2)
    
    {
        n = j;
        Complex *test = new Complex[n];
        obtener_datos(test);
        CArray data(test, n);
        t = clock();
        DFT(data, test);
        t = clock() - t;
        cout << "n = " << n << "  ,  t = " << ((float)t) / CLOCKS_PER_SEC << endl;
        myfile << "{" << n << ", " << ((float)t) / CLOCKS_PER_SEC << " } , ";
        delete []test;
    }
    myfile.close();

    return 0;
}

double funcion(double x)
{
    return 2 * sin(2 * M_PI / n * x) + 5 * cos(2 * M_PI / n * x);
}


void DFT(CArray &x, Complex test[])
{
   
    for (int i = 0; i < n; i++)
    {
        double suma_R = 0;
        double suma_i = 0;
        for (int k = 0; k < n; k++)
        {
            suma_R += test[k].real() * cos(2 * M_PI / n * k * i);
            suma_i -= test[k].real() * sin(2 * M_PI / n * k * i);
        }
        x[i].real(suma_R);
        x[i].imag(suma_i);
    }
}
