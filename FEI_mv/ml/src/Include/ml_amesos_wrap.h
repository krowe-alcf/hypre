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

/*!
 * \file ml_amesos_wrap.h
 *
 * \brief Interface to the Trilinos package Amesos.
 *
 * The ML/Amesos interface can be used to solve the coarse problem with some
 * of the sparse direct solvers supported by Amesos:
 * - KLU, a simple serial sparse solver, distributed with Amesos;
 * - UMFPACK, a serial sparse solver;
 * - SuperLU and SuperLU_DIST
 * - MUMPS, a multifrontal sparse direct solver.
 *
 * For serial solvers, Amesos will take care to redistribute all required data
 * to process 0, solve the linear system on process 0, then broadcast the
 * solution back to all the processes. 
 *
 * For parallel solvers (like SuperLU_DIST and MUMPS), the user can tell
 * Amesos how many processes should be used for the coarse solution. This
 * number can be:
 * - a positive number, that defines how many processes will be used (if
 *   available);
 * - the number -1, meaning that Amesos will estimate the "best" number of
 *   processes;
 * - the number -2, meaning that Amesos will use the square root of the
 *   available processes.
 *
 * In its current implementation, ML/Amesos converts the ML_Operator for the
 * coarse level to and Epetra matrix ("heavy conversion").
 * 
 * \note If \c ML_AMESOS_DEBUG is defined, some checks are performed to verify
 * that the linear system has been solved up to machine precision.
 *
 * \note We experienced some problems with \c out on TFLOPS. These problems
 * were solved by replacing \c cout with \c puts().
 *
 * \date Last update to Doxygen: 21-Jun-05
 *
 */

#ifndef _MLAMESOSWRAP_
#define _MLAMESOSWRAP_

#include "ml_include.h"

#ifndef ML_CPP
#ifdef __cplusplus
extern "C" {
#endif
#endif

  /** Generates the direct solver using Amesos. */
  /*! This function performs several operations:
    - wrap the ML_Operator for the given level to an Epetra_CrsMatrix
    - creates the Amesos object;
    - compute the symbolic and numeric factorzation.

    \param ml (InOut) : ML_Structure

    \param curr_level (In) : specifies the level for which we have to
    define the direct solver;

    \param choice (In) : integer variable, that can be ML_AMESOS_KLU,
    ML_AMESOS_UMFPACK, ML_AMESOS_SUPERLUDIST, ML_AMESOS_MUMPS,
    ML_AMESOS_SCALAPACK;

    \param MaxProcs (In) : integer defining the maximum number of
    processes to use in the coarse solution (only for some of the
    supported Amesos solvers);

    \param Amesos (In) : add the specified value to the diagonal
    elements of the matrix.

    \param Amesos_Handle (Out) : it will contain a pointer to the Amesos object (casted
    to void *).

    If the required solver is not avaiable, ML_Amesos_Gen will create 
    a KLU solver. KLU is distributed with Amesos, and is enabled by default.
    
  */
  int ML_Amesos_Gen(ML *ml, int curr_level, int choice, int MaxProcs, 
                    double AddToDiag, void **Amesos_Handle);

  /** Solves using Amesos, and the factorization computed by ML_Amesos_Gen. */
  int ML_Amesos_Solve( void *Amesos_Handle, double x[], double rhs[] ) ;

  /** Destroy the Amesos object. Prints out some timing. */
  void ML_Amesos_Destroy(void *Amesos_Handle);

  int ML_isKLUAvailable();
#ifndef ML_CPP
#ifdef __cplusplus
}
#endif
#endif

#endif
