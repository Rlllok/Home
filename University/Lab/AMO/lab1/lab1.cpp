#include <stdio.h>
#include <iostream>
#include <cmath>
#include <math.h>


int main()
{
// exp^x = sum(Uk(x))
// Uk(x) = (x / k) * 1

    double U = 1;
    double e = 1;
    int n = 2;
    int n_task2;
    double a = -11.4;
    double b = 2.5;
    double x = (a + b) / 2;
    // double eps = 1e-5;


    // for (int i = 1; i <= n; i++) {
    //     U *= (x / i);
    //     e += U;
    // }

    std::cout << "EPX(" << x << ") = " << exp(x) << std::endl << std::endl;

    for (double eps = 1e-2; eps > 1e-14; eps *= 1e-3) {
        int k = 1;
        e = 1;
        U = 1;
        while(abs(U) >= eps) {
            U *= (x / k);
            e += U;
            k++;
        }
        n = k - 1;
        if (eps == 1e-8) n_task2 = n;
        std::cout << "e(" << x << ") = ";
        std::cout.precision(20);
        std::cout << e << std::endl;
        std::cout.precision(6);
    }

    std::cout << std::endl << std::endl;

    double h = (b - a) / 10;
    for (int i = 0; i <= 10; i++) {
        x = a + h*i;
        e = 1;
        U = 1;
        for(int k = 1; k < n_task2; k++) {
            U *= (x / k);
            e += U;
            k++;
        }


        std::cout << i << ") " << "e(" << x << ") = ";
        std::cout.precision(20);
        std::cout << e << std::endl;
        std::cout << "EPX(" << x << ") = " << exp(x) << std::endl << std::endl;
        std::cout.precision(6);
    }



    return 0;
}