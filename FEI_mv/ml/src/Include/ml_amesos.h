/*BHEADER**********************************************************************
 * Copyright (c) 2006   The Regents of the University of California.
 * Produced at the Lawrence Livermore National Laboratory.
 * Written by the HYPRE team <hypre-users@llnl.gov>, UCRL-CODE-222953.
 * All rights reserved.
 *
 * This file is part of HYPRE (see http://www.llnl.gov/CASC/hypre/).
 * Please see the COPYRIGHT_and_LICENSE file for the copyright notice, 
 * disclaimer and the GNU Lesser General Public License.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License (as published by the Free
 * Software Foundation) version 2.1 dated February 1999.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the IMPLIED WARRANTY OF MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the terms and conditions of the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * $Revision$
 ***********************************************************************EHEADER*/

/* ************************************************************************* */
/* See the file COPYRIGHT for a complete copyright notice, contact person,   */
/* and disclaimer.                                                           */
/* ************************************************************************* */

#ifndef __ML_AMESOS_H__
#define __ML_AMESOS_H__

#include <stdlib.h>
#include <assert.h>
#include "ml_struct.h"

#define ML_AMESOS_LAPACK        -1
#define ML_AMESOS_KLU            0
#define ML_AMESOS_UMFPACK        1
#define ML_AMESOS_SUPERLUDIST    2
#define ML_AMESOS_MUMPS          3
#define ML_AMESOS_SCALAPACK      4
#define ML_AMESOS_SUPERLU        5

#ifndef ML_CPP
#ifdef __cplusplus
extern "C" {
#endif
#endif

  /** Applies the Amesos direct solver to the given vector. */
  extern int ML_Smoother_Amesos(ML_Smoother *sm,int inlen,double x[],int outlen,
				double rhs[]);

  /** Clean memory associated to Amesos_Handle. */
  void ML_Smoother_Clean_Amesos(void *Amesos_Handle);
  
  /** Generates the coarse solver using Amesos. */
  /*! Generates the coarse solver using one of the Amesos supported
    direct solvers.

    \param ml (InOut) - ML_Structure;

    \param nl (In) - level for which we have to define the coarse solver;

    \param AmesosSolver (In) - integer variable, that can be ML_AMESOS_KLU,
    ML_AMESOS_UMFPACK, ML_AMESOS_SUPERLUDIST, ML_AMESOS_MUMPS,
    ML_AMESOS_SCALAPACK;

    \param MaxProcs (In) - integer defining the maximum number of
    processes to use in the coarse solution (only for some of the
    supported Amesos solvers).

    \param AddToDiag (In) - add the specified value to the 
    diagonals of the matrix.
  */
  
int ML_Gen_Smoother_Amesos(ML *ml, int nl, int AmesosSolver, 
                           int MaxProcs, double AddToDiag);


#ifndef ML_CPP
#ifdef __cplusplus
   }
#endif
#endif

#endif /* #ifndef __ML_AMESOS_H__ */
