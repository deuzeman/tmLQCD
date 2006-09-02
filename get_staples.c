/* $Id$ */

#ifdef HAVE_CONFIG_H
# include<config.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "global.h"
#include "su3.h"
#include "su3adj.h"
#include "start.h"
#include "get_staples.h"

#if ((defined BGL_notchecked) && (defined XLC))

su3 get_staples(int x, int mu) {
  /* We have 32 registers */
  double _Complex u00, u01, u02, u10, u11, u12, u20;
  double _Complex v00, v01, v02, v10, v11, v12, v20, v21, v22;
  double _Complex w00, w01, w02, w10, w11, w12, w20;
  double _Complex reg00, reg01, reg02, reg10, reg11, reg12, reg20, reg21, reg22;
  int k, iy;
  static su3 v;
  su3 *w1 ALIGN;
  su3 *w2 ALIGN;
  su3 *w3 ALIGN;

  v00 = __cmplx(0.,0.);
  v01 = __cmplx(0.,0.);
  v02 = __cmplx(0.,0.);
  v10 = __cmplx(0.,0.);
  v11 = __cmplx(0.,0.);
  v12 = __cmplx(0.,0.);
  v20 = __cmplx(0.,0.);
  v21 = __cmplx(0.,0.);
  v22 = __cmplx(0.,0.);


#pragma unroll(4)
  for(k = 0; k < 4; k++) {
    if(k!=mu){
      w1=&g_gauge_field[x][k];
      w2=&g_gauge_field[g_iup[x][k]][mu];
      w3=&g_gauge_field[g_iup[x][mu]][k];

      /* st = w2 * w3^d */
      _su3_times_su3d(st,*w2,*w3);
      /* v = v + w1 * st */
      _su3_times_su3_acc(v,*w1,st); 

      iy=g_idn[x][k];
      w1=&g_gauge_field[iy][k];
      w2=&g_gauge_field[iy][mu];
      w3=&g_gauge_field[g_iup[iy][mu]][k];
      /* st = w2 * w3 */
      /* v = v + w1^d * st */
      _bgl_su3_times_su3(*w2, *w3);
      _bgl_su3_times_su3_acc(*w1);
    }
  }

  _bgl_store_vxx(v);
  return(v);
}
#else
su3 get_staples(int x, int mu) {

  int k,iy;
  static su3 v,st;
  su3 *w1,*w2,*w3;
#pragma pomp inst begin(staples)
  
  _su3_zero(v);
  for(k=0;k<4;k++) {
    if(k!=mu){
      w1=&g_gauge_field[x][k];
      w2=&g_gauge_field[g_iup[x][k]][mu];
      w3=&g_gauge_field[g_iup[x][mu]][k];
      /* st = w2 * w3^d */
      _su3_times_su3d(st,*w2,*w3);
      /* v = v + w1 * st */
      _su3_times_su3_acc(v,*w1,st); 

      iy=g_idn[x][k];
      w1=&g_gauge_field[iy][k];
      w2=&g_gauge_field[iy][mu];
      w3=&g_gauge_field[g_iup[iy][mu]][k];
      /* st = w2 * w3 */
      _su3_times_su3(st,*w2,*w3);
      /* v = v + w1^d * st */
      _su3d_times_su3_acc(v,*w1,st);
    }
  }
  return v;
#pragma pomp inst end(staples)
}

#endif

