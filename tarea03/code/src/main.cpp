/**
 * Copyright (C) 2018
 * Área Académica de Ingeniería en Computadoras, TEC, Costa Rica
 *
 * This file is part of the CE3102 Numerical Analysis lecture at TEC
 *
 * @Author: 
 * @Date  : 24.02.2018
 */

#include <cstdlib>
#include <iostream>

using namespace std;

template <class T>
struct funcion1 {
    T operator()(T x){
        return exp(-x) - abs(x);
    }
};

template <class T>
struct funcion2 {
    T operator()(T x){
        return exp((-((x-T(3))*(x-T(3))))/(T(3)))-exp((-(x*x)));;
    }
};

template <class T>
struct funcion3 {
    T operator()(T x){
        const T PI = std::atan(T(1))*T(4);
        return atan(x)*(T(180)/PI)-(x*x);
    }
};

template <class T>
struct funcion4 {
    T operator()(T x){
        return (x-T(2))*(x-T(2))*(x-T(2))+(T(1)/T(100))*(x-T(2));
    }
};


int main() {
    //Declaracion de las funciones..!!
    std::function<float(float)>   ff1 = funcion1<float>();
    std::function<double(double)> fd1 = funcion1<double>();
    std::function<float(float)>   ff2 = funcion2<float>();
    std::function<double(double)> fd2 = funcion2<double>();
    std::function<float(float)>   ff3 = funcion3<float>();
    std::function<double(double)> fd3 = funcion3<double>();
    std::function<float(float)>   ff4 = funcion4<float>();
    std::function<double(double)> fd4 = funcion4<double>();

    //Declaracion de los parametros..!!
    float  xlf,xuf,xif,xiif,epsf;
    double xld,xud,xid,xiid,epsd;

    //Loop del menu..!!
    while (true) {
        cout << endl << endl << "!!!-!!!-!!!-!!!-!!!-!!!-!!!-!!!-!!!-!!!-!!!" << endl <<endl;
        
        menu:cout << "Elegir método para obtener raíz: " << endl;

        cout << "   1) Metodo de Bisección." << endl;
        cout << "   2) Metodo de Interpolación lineal." << endl;
        cout << "   3) Metodo de Newton-Raphson." << endl;
        cout << "   4) Metodo de la Secante." << endl;
        cout << "   5) Metodo de Brent." << endl;
        cout << "   6) Metodo de Ridder." << endl;
        cout << "   7) Salir." << endl;

        int metodo;
        cout << endl << "Seleccione un metodo para correr: ";
        cin >> metodo;
    
        if (metodo > 7 || metodo < 1) {
            cout << "Intentar de nuevo: " << endl;
            goto menu;
        }
        else if (metodo == 7) {
            cout << "Saliendo..." << endl;
            break;
        }
    
        cout << "Elegir función para obtener raíz: " << endl;
        cout << "   1) |x| = exp(-x)" << endl;
        cout << "   2) exp(-x^2) = exp((-(x-3)^2)/3)" << endl;
        cout << "   3) x^2 = atan(x)" << endl;
        cout << "   4) (x-2)^3 + (1/100)*(x-2)" << endl;
        int funcion;
        cout << "Funcion a evaluar: ";
        cin >> funcion;
        /**
		xl = Valor inferior del intervalo de busqueda de metodos cerrados.
		xu = Valor superior del intervalo de busqueda en metodos cerrados.
		xi = Valor inicial en metodos abiertos.
		xii = Valor anterior al inicial en metodos abiertos secuenciales.
        eps = Tolerancia del error.
        */

        //Biseccion, Interpolacion o Brent (xl,xu)
        if ((metodo == 1)|| (metodo == 2)||(metodo == 5)){
            cout << endl << "Valores para double" << endl << endl;
            cout << " xl: ";
            cin >> xld;
            cout << " xu: ";
            cin >> xud;

            cout << endl << "Valores para float" << endl << endl;
            cout << " xl: ";
            cin >> xlf;
            cout << " xu: ";
            cin >> xuf;
        }else{ 
            if((metodo == 4)|| (metodo == 6)){ //Secante o Ridder (xi, xii)
                cout << endl << "Valores para double" << endl << endl;
                cout << " xi: ";
                cin >> xid;
                cout << " xii: ";
                cin >> xiid;

                cout << endl << "Valores para float" << endl << endl;
                cout << " xi: ";
                cin >> xif;
                cout << " xii: ";
                cin >> xiif;
            }else{   //Newton Raphson (xi)
                cout << endl << "Valores para double" << endl << endl;
                cout << " xi: ";
                cin >> xid;
                cout << endl << "Valores para float" << endl << endl;
                cout << " xi: ";
                cin >> xif;
            }
        }
        cout << endl << "Valores para double" << endl << endl;
        cout << " eps: ";
        cin >> epsd;
        cout << endl << "Valores para float" << endl << endl;
        cout << " eps: ";
        cin >> epsf;
	
        switch (metodo) {
            case 1:														//Algoritmo de biseccion
                switch (funcion) {
                    case 1:											//Funcion |x| = exp^(-x)
                        cout << "	Algoritmo de Biseccion:" << endl;
                        cout << "       Raiz tipo double: " << anpi::rootBisection(fd1,xld,xud,epsd) << endl;
                        cout << "       Raiz tipo float: " <<  anpi::rootBisection(ff1,xlf,xuf,epsf) << endl;
                        break;
                    case 2:											//Funcion exp^(-x^2) = exp^((-(x-3)^2)/3)
                        cout << "	Algoritmo de Biseccion:" << endl;
                        cout << "       Raiz tipo double: " << anpi::rootBisection(fd2,xld,xud,epsd) << endl;
                        cout << "       Raiz tipo float: " <<  anpi::rootBisection(ff2,xlf,xuf,epsf) << endl;
                        break;
                    case 3:											//Funcion x^2 = atan(x)
                        cout << "	Algoritmo de Biseccion:" << endl;
                        cout << "       Raiz tipo double: " << anpi::rootBisection(fd3,xld,xud,epsd) << endl;
                        cout << "       Raiz tipo float: " <<  anpi::rootBisection(ff3,xlf,xuf,epsf) << endl;
                        break;
                    case 4:											//Funcion (x-2)^3 + (1/100)(x-2)
                        cout << "	Algoritmo de Biseccion:" << endl;
                        cout << "       Raiz tipo double: " << anpi::rootBisection(fd4,xld,xud,epsd) << endl;
                        cout << "       Raiz tipo float: " <<  anpi::rootBisection(ff4,xlf,xuf,epsf) << endl;
                        break;
                    default:
                        cout << "Opción inválida." << endl;
                        break;
                }
                break;
            case 2:														//Algoritmo de Interpolacion Lineal
                switch (funcion) {
                    case 1:											//Funcion |x| = exp^(-x)
                        cout << "	Algoritmo de Interpolacion Lineal:" << endl;
                        cout << "       Raiz tipo double: " << anpi::rootInterpolation(fd1,xld,xud,epsd) << endl;
                        cout << "       Raiz tipo float: " <<  anpi::rootInterpolation(ff1,xlf,xuf,epsf) << endl;
                        break;
                    case 2:											//Funcion exp^(-x^2) = exp^((-(x-3)^2)/3)
                        cout << "	Algoritmo de Interpolacion Lineal:" << endl;
                        cout << "       Raiz tipo double: " << anpi::rootInterpolation(fd2,xld,xud,epsd) << endl;
                        cout << "       Raiz tipo float: " <<  anpi::rootInterpolation(ff2,xlf,xuf,epsf) << endl;
                        break;
                    case 3:											//Funcion x^2 = atan(x)
                        cout << "	Algoritmo de Interpolacion Lineal:" << endl;
                        cout << "       Raiz tipo double: " << anpi::rootInterpolation(fd3,xld,xud,epsd) << endl;
                        cout << "       Raiz tipo float: " <<  anpi::rootInterpolation(ff3,xlf,xuf,epsf) << endl;
                        break;
                    case 4:											//Funcion (x-2)^3 + (1/100)(x-2)
                        cout << "	Algoritmo de Interpolacion Lineal:" << endl;
                        cout << "       Raiz tipo double: " << anpi::rootInterpolation(fd4,xld,xud,epsd) << endl;
                        cout << "       Raiz tipo float: " <<  anpi::rootInterpolation(ff4,xlf,xuf,epsf) << endl;
                        break;
                    default:
                        cout << "Opción inválida." << endl;
                        break;
                }
                break;
            case 3:														//Algoritmo de Newton-Raphson
                switch (funcion) {
                    case 1:											//Funcion |x| = exp^(-x)
                        cout << "	Algoritmo de Newton-Raphson:" << endl;
                        cout << "       Raiz tipo double: " << anpi::rootNewtonRaphson(fd1,xid,epsd) << endl;
                        cout << "       Raiz tipo float: " <<  anpi::rootNewtonRaphson(ff1,xif,epsf) << endl;
                        break;
                    case 2:											//Funcion exp^(-x^2) = exp^((-(x-3)^2)/3)
                        cout << "	Algoritmo de Newton-Raphson:" << endl;
                        cout << "       Raiz tipo double: " << anpi::rootNewtonRaphson(fd2,xid,epsd) << endl;
                        cout << "       Raiz tipo float: " <<  anpi::rootNewtonRaphson(ff2,xif,epsf) << endl;
                        break;
                    case 3:											//Funcion x^2 = atan(x)
                        cout << "	Algoritmo de Newton-Raphson:" << endl;
                        cout << "       Raiz tipo double: " << anpi::rootNewtonRaphson(fd3,xid,epsd) << endl;
                        cout << "       Raiz tipo float: " <<  anpi::rootNewtonRaphson(ff3,xif,epsf) << endl;
                        break;
                    case 4:											//Funcion (x-2)^3 + (1/100)(x-2)
                        cout << "	Algoritmo de Newton-Raphson:" << endl;
                        cout << "       Raiz tipo double: " << anpi::rootNewtonRaphson(fd4,xid,epsd) << endl;
                        cout << "       Raiz tipo float: " <<  anpi::rootNewtonRaphson(ff4,xif,epsf) << endl;
                        break;
                    default:
                        cout << "Opción inválida." << endl;
                        break;
                }
                break;
            case 4:														//Algoritmo de la Secante
                switch (funcion) {
                    case 1:											//Funcion |x| = exp^(-x)
                        cout << "	Algoritmo de la Secante:" << endl;
                        cout << "       Raiz tipo double: " << anpi::rootSecant(fd1,xid,xiid,epsd) << endl;
                        cout << "       Raiz tipo float: " <<  anpi::rootSecant(ff1,xif,xiif,epsf) << endl;
                        break;
                    case 2:											//Funcion exp^(-x^2) = exp^((-(x-3)^2)/3)
                        cout << "	Algoritmo de la Secante:" << endl;
                        cout << "       Raiz tipo double: " << anpi::rootSecant(fd2,xid,xiid,epsd) << endl;
                        cout << "       Raiz tipo float: " <<  anpi::rootSecant(ff2,xif,xiif,epsf) << endl;
                        break;
                    case 3:											//Funcion x^2 = atan(x)
                        cout << "	Algoritmo de la Secante:" << endl;
                        cout << "       Raiz tipo double: " << anpi::rootSecant(fd3,xid,xiid,epsd) << endl;
                        cout << "       Raiz tipo float: " <<  anpi::rootSecant(ff3,xif,xiif,epsf) << endl;
                        break;
                    case 4:											//Funcion (x-2)^3 + (1/100)(x-2)
                        cout << "	Algoritmo de la Secante:" << endl;
                        cout << "       Raiz tipo double: " << anpi::rootSecant(fd4,xid,xiid,epsd) << endl;
                        cout << "       Raiz tipo float: " <<  anpi::rootSecant(ff4,xif,xiif,epsf) << endl;
                        break;
                    default:
                        cout << "Opción inválida." << endl;
                        break;
                }
                break;
            case 5:														//Algoritmo de Brent
                switch (funcion) {
                    case 1:											//Funcion |x| = exp^(-x)
                        cout << "	Algoritmo de Brent: " << endl;
                        cout << "       Raiz tipo double: " << anpi::rootBrent(fd1,xld,xud,epsd) << endl;
                        cout << "       Raiz tipo float: " <<  anpi::rootBrent(ff1,xlf,xuf,epsf) << endl;
                        break;
                    case 2:											//Funcion exp^(-x^2) = exp^((-(x-3)^2)/3)
                        cout << "	Algoritmo de Brent: " << endl;
                        cout << "       Raiz tipo double: " << anpi::rootBrent(fd2,xld,xud,epsd) << endl;
                        cout << "       Raiz tipo float: " <<  anpi::rootBrent(ff2,xlf,xuf,epsf) << endl;
                        break;
                    case 3:											//Funcion x^2 = atan(x)
                        cout << "	Algoritmo de Brent: " << endl;
                        cout << "       Raiz tipo double: " << anpi::rootBrent(fd3,xld,xud,epsd) << endl;
                        cout << "       Raiz tipo float: " <<  anpi::rootBrent(ff3,xlf,xuf,epsf) << endl;
                        break;
                    case 4:											//Funcion (x-2)^3 + (1/100)(x-2)
                        cout << "	Algoritmo de Brent: " << endl;
                        cout << "       Raiz tipo double: " << anpi::rootBrent(fd4,xld,xud,epsd) << endl;
                        cout << "       Raiz tipo float: " <<  anpi::rootBrent(ff4,xlf,xuf,epsf) << endl;
                        break;
                    default:
                        cout << "Opción inválida." << endl;
                        break;
                }
                break;
            case 6:													//Algoritmo de Ridder
                switch (funcion) {
                    case 1:											//Funcion |x| = exp^(-x)
                        cout << "	Algoritmo de Ridder: " << endl;
                        cout << "       Raiz tipo double: " << anpi::rootRidder(fd1,xid,xiid,epsd) << endl;
                        cout << "       Raiz tipo float: " <<  anpi::rootRidder(ff1,xif,xiif,epsf) << endl;
                        break;
                    case 2:											//Funcion exp^(-x^2) = exp^((-(x-3)^2)/3)
                        cout << "	Algoritmo de Ridder: " << endl;
                        cout << "       Raiz tipo double: " << anpi::rootRidder(fd2,xid,xiid,epsd) << endl;
                        cout << "       Raiz tipo float: " <<  anpi::rootRidder(ff2,xif,xiif,epsf) << endl;
                        break;
                    case 3:											//Funcion x^2 = atan(x)
                        cout << "	Algoritmo de Ridder: " << endl;
                        cout << "       Raiz tipo double: " << anpi::rootRidder(fd3,xid,xiid,epsd) << endl;
                        cout << "       Raiz tipo float: " <<  anpi::rootRidder(ff3,xif,xiif,epsf) << endl;
                        break;
                    case 4:											//Funcion (x-2)^3 + (1/100)(x-2)
                        cout << "	Algoritmo de Ridder: " << endl;
                        cout << "       Raiz tipo double: " << anpi::rootRidder(fd4,xid,xiid,epsd) << endl;
                        cout << "       Raiz tipo float: " <<  anpi::rootRidder(ff4,xif,xiif,epsf) << endl;
                        break;
                    default:
                        cout << "Opción inválida." << endl;
                        break;
                }
                break;
            default:
                break;
        }
    }
	return EXIT_FAILURE;
}
  
