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

#ifndef ANPI_ROOT_BISECTION_HPP
#define ANPI_ROOT_BISECTION_HPP

namespace anpi {
  
  /**
   * Find the roots of the function funct looking for it in the
   * interval [xl,xu], using the bisection method.
   *
   * @param funct a std::function of the form "T funct(T x)"
   * @param xl lower interval limit
   * @param xu upper interval limit
   *
   * @return root found, or NaN if none could be found.
   *
   * @throws anpi::Exception if inteval is reversed or both extremes
   *         have same sign.
   */

  template<typename T>
  T rootBisection(const std::function<T(T)>& funct,T xl,T xu,const T eps) {
    
    const int maxi = std::numeric_limits<T>::digits;          //Numero maximo de iteraciones

    T xr = xl;                //Valor inicial de la raiz en el limite inferior
    T fl = funct(xl);         //Funcion evaluada en el extremo inferior del metodo. 

    T ea = T(0); //Casting de cero a tipo T

    //Loop que recortara los limites segun el signo de los limites evaluados con respecto al centro.
    for(int i=maxi;i>0;--i){
      T xrold = xr;          //Se almacena para el calculo del error
      xr = (xl+xu)/T(2);     //Calculo de la nueva raiz
      T fr = funct(xr);      //Raiz evaluada en el centro del intervalo

      //Evitar division por cero
      if(std::abs(xr) > std::numeric_limits<T>::epsilon()){
        ea = std::abs((xr-xrold)/xr)*T(100); //Calculo del nuevo error
      }
      T cond = fl*fr;//Negativo si el extremo izquierdo y el centro poseen signo contrario

      if(cond < T(0)){
        xu=xr;//Se itera con el lado izquierdo. Se modifica el extremo derecho con el centro.
      }else{
        if (cond > T(0)){//Se continua con el lado derecho de la funcion.
          xl=xr;         //Se cambia el extremo izquierdo por el centro.
          fl=fr;
        }else{          //Alguno de los bordes es cero
          ea = T(0);
          xr = (std::abs(fl) < std::numeric_limits<T>::epsilon()) ? xl : xr;
        }
      }

      if (ea < eps){ //Error menor al umbral.!
        return xr;
      }
    }

    //Si no existe un valor numerico para la raiz
    return std::numeric_limits<T>::quiet_NaN();
  }

}
  
#endif

