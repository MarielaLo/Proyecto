#include <complex>
#include <iostream>
#include <valarray>
#include <time.h>
#include <fstream>

using namespace std;

int n = 8;


typedef complex<double> Complex;

typedef valarray<Complex> CArray;

double funcion(double);


template <class T>  //identificador de tipo: T
void obtener_datos(T data[])
{
    for (int i = 0; i < n; i++)
    {
        data[i] = funcion(i);
    }
}


void FFT(CArray &);

int main()
{
    cout << "num. maximo n = " ;
    long long int NN;
    cin >> NN;
    fstream myfile;
    myfile.open("FFT.txt", fstream::out);
    clock_t t;

    for (long int j = 4; j <= NN; j *= 2)
    {
        n = j;
        Complex *test = new Complex[n];
        obtener_datos(test);
        CArray data(test, n);

        t = clock();
        FFT(data);
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

// Definimos la estructura de la funcion FFT.

void FFT(CArray &x)
{
    const size_t n = x.size();
    if (n <= 1)
        return;

    
    CArray even = x[slice(0, n / 2, 2)];
    CArray odd = x[slice(1, n / 2, 2)];

    // Recurcividad
    FFT(even);
    FFT(odd);

    // Combinamos
    for (size_t k = 0; k < n / 2; ++k)
    {
        Complex t = polar(1.0, -2 * M_PI * k / n) * odd[k];
        x[k] = even[k] + t;
        x[k + n / 2] = even[k] - t;
    }
}
