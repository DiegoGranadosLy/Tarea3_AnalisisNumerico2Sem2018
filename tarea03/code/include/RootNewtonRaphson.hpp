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

#ifndef ANPI_NEWTON_RAPHSON_HPP
#define ANPI_NEWTON_RAPHSON_HPP

namespace anpi {

    /**
  * Calcula la derivada en un punto 
  * utilizando la diferenciacion centrada.
  * Utiliza un delta equivalente a 1 epsilon.
  * Parametros:
  * funct : Funcion a evaluar
  * xi : Parametro inicial
  */
  template<typename T>
  T derivate(const std::function<T(T)>& funct,T xi) {
    T delta = std::numeric_limits<T>::epsilon(); //Tamano minimo de paso
    T xl  = xi - 50*delta;                       // x_(i-1)
    T xu  = xi + 50*delta;                       // x_(i+1)
    T fxl = funct(xl);                           // f(x_(i-1))
    T fxu = funct(xu);                           // f(x_(i+1))
    return (fxu-fxl)/(100*delta);                //Derivada por aproximacion centrada.
  }

  
  /**
   * Find the roots of the function funct looking by means of the
   * Newton-Raphson method
   *
   * @param funct a functor of the form "T funct(T x)"
   * @param xi initial root guess
   * 
   * @return root found, or NaN if none could be found.
   *
   * @throws anpi::Exception if interval is reversed or both extremes
   *         have same sign.
   */
  template<typename T>
  T rootNewtonRaphson(const std::function<T(T)>& funct,T xi,const T eps) {

    const int maxi = std::numeric_limits<T>::digits;    //Numero maximo de iteraciones
    T x_new = xi;                                       //Nueva raiz por iteracion
    T fxi = funct(xi);                                  //Valor de la funcion en xi
    T fxi_prime = derivate(funct,xi);                   //Derivada en xi
    T ea;                                               //Error de parada
    for(int i= maxi;i>=0;--i){                          //Loop para iterar
      x_new = xi - (fxi)/(fxi_prime);                   //Calculo de la nueva raiz
      fxi = funct(x_new);                               //Calculo del nuevo valor en la raiz
      T fxi_prime = derivate(funct,x_new);              //calculo de la nueva derivada en la raiz
      
      //Evitar division por cero
      if(std::abs(x_new) > std::numeric_limits<T>::epsilon()){
        ea = std::abs((x_new-xi)/x_new)*T(100);         //Calculo del nuevo error
      }
      xi = x_new;                                       //Actualizacion de xi por la nueva raiz
      if (ea < eps){ //Error menor al umbral.!          //Condicion de parada cuando se pasa el umbral.
        return x_new;
      }
    }

    //Si no existe un valor numerico para la raiz
    return std::numeric_limits<T>::quiet_NaN();
  }
}
  
#endif
