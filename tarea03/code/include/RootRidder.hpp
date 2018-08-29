/**
 * Copyright (C) 2018
 * Área Académica de Ingeniería en Computadoras, ITCR, Costa Rica
 *
 * This file is part of the numerical analysis lecture CE3102 at TEC
 *
 * @Author: Pablo Alvarado
 * @Date  : 04.08.2018
 */

#include <cmath>
#include <limits>
#include <functional>

#include "Exception.hpp"

#ifndef ANPI_ROOT_RIDDER_HPP
#define ANPI_ROOT_RIDDER_HPP

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
  T rootRidder(const std::function<T(T)>& funct,T xi,T xii,const T eps) {
    const int maxi = std::numeric_limits<T>::digits;           //Numero maximo de iteraciones
    T fl = funct(xi); //Valor de la funcion en xi = Limite inferior.
    T fh = funct(xii); //Valor de la funcion en xu = Limite superior.
    if((fl > T(0) &&  fh < T(0)) || (fl < T(0) &&  fh > T(0))){ //En caso de encontrar un cambio de signo en los
      T xl = xi;                                              //limites, aseguramos una raiz dentro del intervalo.
      T xh = xii; 
      T ans = -9.99e99;
      for (int i=maxi;i>0;i--){     //Loop iterativo para el calculo de la raiz.
        T xm = 0.5*(xl+xh);     //Calculo del punto medio.
        T fm = funct(xm);
        T s  = std::sqrt(fm*fm-fl*fh);
        if (s == T(0)){
          return ans;
        }
        T xnew = xm + (xm - xl)*((fl > fh ? T(1) : T(-1))*fm/s); //Calculo de la nueva raiz (x4 || xr)
        if ((std::abs(xnew-ans)/xnew)*T(100) < eps){
          return ans;
        }
        ans = xnew;       //Se asigna la raiz a ans
        T fnew = funct(ans);    //Se evalua la funcion en xnew
        if (fnew == T(0)){    //En caso de ser la solucion exacta se retorna la raiz (ans || xnew)
          return ans;
        }
        if(fm*fnew < T(0)){
          xl = xm;
          fl = fm;
          xh = ans;
          fh = fnew;
        }else{
          if (fl*fnew < T(0)){
            xh = ans;
            fh = fnew;
          }else{
            if (fh*fm < T(0)){
              xl = ans;
              fl = fnew;
            }else{
              return std::numeric_limits<T>::quiet_NaN();
            }
          }
        }
     }
     // Retorna un NaN si no encontro  ninguna raiz
     return std::numeric_limits<T>::quiet_NaN();
    }else{

      if (fl == T(0)){
        return xi;
      }
      if (fh == T(0)){
        return xii;
      }
    }
     
   }
}
  
#endif

