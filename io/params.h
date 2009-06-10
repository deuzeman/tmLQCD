/***********************************************************************
 * $Id$
 * Copyright (C) 2002,2003,2004,2005,2006,2007,2008 Carsten Urbach
 *
 * This file is part of tmLQCD.
 *
 * tmLQCD is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * tmLQCD is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with tmLQCD.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************/

#ifndef _PARAMS_H
#define _PARAMS_H

typedef struct
{
  char   date[64];
  char   package_version[32];

  double epssq;
  double epsbar;
  double kappa;
  double mu;
  double mu_bar;
  double mu_inverted;
  double mu_lowest;

  double *extra_masses;

  int    mms;
  int    iter;
  int    heavy;

  long int time;
}
paramsInverterInfo;

typedef struct
{
  int    flavours;
  int    prec;
  int    nx;
  int    ny;
  int    nz;
  int    nt;
}
paramsPropagatorFormat;

typedef struct
{
  int    colours;
  int    flavours;
  int    prec;
  int    nx;
  int    ny;
  int    nz;
  int    nt;
  int    spins;
}
paramsSourceFormat;

typedef struct
{
  char   date[64];
  char   package_version[32];

  double beta;
  double c2_rec;
  double epsilonbar;
  double kappa;
  double mu;
  double mubar;
  double plaq;

  int    counter;

  long int time;
}
paramsXlfInfo;

typedef struct
{
  int    nx;
  int    ny;
  int    nz;
  int    nt;
  int    prec;
}
paramsIldgFormat;

paramsIldgFormat       *construct_paramsIldgFormat(int const prec);
paramsPropagatorFormat *construct_paramsPropagatorFormat(int const prec, int const flavours);
paramsSourceFormat     *construct_paramsSourceFormat(int const prec, int const flavours, int const spins, int const sources);
paramsXlfInfo          *construct_paramsXlfInfo(double const plaq, int const counter);

#endif