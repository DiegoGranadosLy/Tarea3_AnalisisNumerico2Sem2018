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

#ifndef ANPI_ROOT_BRENT_HPP
#define ANPI_ROOT_BRENT_HPP

namespace anpi {
  
  /**
   * Find the roots of the function funct looking for it in the
   * interval [xl,xu], using the Brent's method.
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
  T rootBrent(const std::function<T(T)>& funct,T x1,T x2,const T eps) {
    const T EPS=std::numeric_limits<T>::epsilon();
    const int maxi = std::numeric_limits<T>::digits;          //Numero maximo de iteraciones
    T a=x1,b=x2,c=x2,d,e,fa=funct(a),fb=funct(b),fc,p,q,r,s,tol1,xm;

    if ((fa > T(0) && fb > T(0)) || ((fa < T(0) && fb < T(0)))) {
      return std::numeric_limits<T>::quiet_NaN(); //No hay raiz ya que los limites poseen mismo signo.
    }
    fc = fb;
    for(int i=maxi;i>=0;--i){
      if ((fb > T(0) && fc > T(0)) || (fb < T(0) && fc < T(0))){
        c=a;
        fc = fa;
        e=d=b-a;
      }
      if(std::abs(fc) < std::abs(fb)){
        a=b;
        b=c;
        c=a;
        fa=fb;
        fb=fc;
        fc=fa;
      }
      tol1 = T(2)*EPS*std::abs(b)+0.5*eps;  //Check de convergencia.
      xm = 0.5*(c-b);
      if (std::abs(xm) <= tol1 || fb == T(0)){return b;}
      if (std::abs(e) <= tol1 && std::abs(fa) > std::abs(fb)){
        s= fb/fa;
        if(a == c){
          p = T(2)*xm*s;
          q = T(1)-s;
        }else{
          q = fa/fc;
          r = fb/fc;
          p = s*(T(2)*xm*q*(q-r)-(b-a)*(r-T(1)));
          q = (q-T(1))*(r-T(1))*(s-T(1));
        }
        if(p > T(0)){ q = -q; }
        p = std::abs(p);
        T min1 = T(3)*xm*q-std::abs(tol1*q);
        T min2 = std::abs(e*q);

        if(T(2)*p < (min1 < min2 ? min1 : min2)){
          e=d;
          d=p/q;
        }else{
          d=xm;
          e=d;
        }
      }else{
        d=xm;
        e=d;
      }
      a=b;
      fa=fb;
      if(std::abs(d) > tol1){ b+=d;}
      else {b+=(tol1 > xm ? 1 : 0);}
      fb = funct(b);
    }
    return std::numeric_limits<T>::quiet_NaN();
  }
}
  
#endif