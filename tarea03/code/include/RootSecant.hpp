/**
 * Copyright (C) 2018
 * Área Académica de Ingeniería en Computadoras, ITCR, Costa Rica
 *
 * This file is part of the numerical analysis lecture CE3102 at TEC
 *
 * @Author: Pablo Alvarado
 * @Date  : 10.02.2018
 */

#include <cmath>
#include <limits>
#include <functional>

#include "Exception.hpp"

#ifndef ANPI_ROOT_SECANT_HPP
#define ANPI_ROOT_SECANT_HPP

namespace anpi {
  
  /**
   * Find a root of the function funct looking for it starting at xi
   * by means of the secant method.
   *
   * @param funct a functor of the form "T funct(T x)"
   * @param xi initial position
   * @param xii second initial position 
   *
   * @return root found, or NaN if no root could be found
   */
  template<typename T>
  T rootSecant(const std::function<T(T)>& funct,T xi,T xii,const T eps) {
    
    const int maxi = std::numeric_limits<T>::digits;

    //Declaracion de variables
    T fxi = funct(xi);      //Funcion evaluada en xi
    T fxii = funct(xii);    //Funcion evaluada en xii
    T xr;                   //Raiz estimada 
    T fr;                   //Funcion evaluada en raiz xr
    T xii_old = xii;        //Respaldo de xii 

    T ea;                   //Error de parada.


    //Proceso de iteracion para el calculo
    for (int i=0; i <= maxi; ++i) {
      //Calculo de raiz
      xr = xi - (fxi*(xii-xi))/(fxii-fxi);
      fr = funct(xr); //Evalua raiz en funcion
        
      if (std::abs(xr) > std::numeric_limits<T>::epsilon()){
        ea = std::abs((xr-xii_old)/xr)*T(100);
      }
        
      //Intercambia puntos de referencia
      xi  = xii;
      fxi = fxii;

      xii_old = xii;
      xii = xr;
      fxii = fr;

      if (ea < eps){
          return xr;
        }
    }

    // Retorna un NaN si no encontro  ninguna raiz
     return std::numeric_limits<T>::quiet_NaN();
    }
}
  
#endif

