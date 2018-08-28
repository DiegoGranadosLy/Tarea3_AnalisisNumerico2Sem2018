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

#ifndef ANPI_ROOT_INTERPOLATION_HPP
#define ANPI_ROOT_INTERPOLATION_HPP

namespace anpi {
  
  /**
   * Find the roots of the function funct looking for it in the
   * interval [xl,xu], by means of the interpolation method.
   *
   * @param funct a functor of the form "T funct(T x)"
   * @param xl lower interval limit
   * @param xu upper interval limit
   *
   * @return root found, or NaN if none could be found.
   *
   * @throws anpi::Exception if inteval is reversed or both extremes
   *         have same sign.
   */
  template<typename T>
  T rootInterpolation(const std::function<T(T)>& funct,T xl,T xu,const T eps) {
    const int maxi = std::numeric_limits<T>::digits;           //Numero maximo de iteraciones
     T xr = xl;  //Valor de inicio para la raiz
     T fl = funct(xl); //Extremo izquierdo evaluado en la funcion.
     T fu = funct(xu); //Extremo derecho evaluado en la funcion.

     T ea = T(0); //Error de inicio

     int iu = 0; //Contadores para evitar atascamiento en un extremo.
     int il = 0;

     for (int i=maxi;i>0;i--){
      T xrold = xr;               //Para el calculo de error.
      xr = xu-fu*(xl-xu)/(fl-fu); //Nueva raiz
      T fr = funct(xr);           //Raiz evaluada en la funcion.

      //Para evitar una division por cero.
      if (std::abs(xr) > std::numeric_limits<T>::epsilon()){
        ea = std::abs((xr-xrold)/xr)*T(100);
      }

      T cond = fl*fr;

      if(cond < T(0)){//Extremo izquierdo cumple cambio de signo.
        xu = xr; //Se cambia el extremo superior
        fu = fr; //Se modifica el valor de la funcion evaluada en el limite.
        iu = 0;  //Se setea el contador del lado derecho.
        il++;
        if (il >= 2){ //En caso de que se repita dos veces por el mismo extremo recortamos la funcion.
          fl = fl/T(2);
        }
      }else 
        if(cond > T(0)){ //Se cumple la condicion para el extremo derecho
          xl = xr; //Se modifica el limite izquierdo por el de la raiz.
          fl = fr; //Se modifica el valor evaluado de la funcion.
          il = 0;  //Se setea el contador izquierdo en cero.
          iu++;    //Se incrementa el contador derecho.
          if (iu >= 2){ //En caso de que hayan pasado dos iteraciones seguidas sobre el lado derecho. 
            fu = fu/T(2);  //Se recorta el valor de la funcion.
          }
        }else{ //Hay una raiz en uno de los limites (izquierdo o derecho). Se Verifica y se asigna a xr
          ea = T(0);
          xr = (fl == T(0)) ? xl : xu;
        }

        if (ea < eps){
          return xr;
        }
     }
     
     // Retorna un NaN si no encontro  ninguna raiz
     return std::numeric_limits<T>::quiet_NaN();
   }
 }
  
#endif

