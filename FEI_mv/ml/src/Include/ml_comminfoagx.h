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

/* ******************************************************************** */
/* See the file COPYRIGHT for a complete copyright notice, contact      */
/* person and disclaimer.                                               */
/* ******************************************************************** */

/* ******************************************************************** */
/* Data structure to hold the send and receive information for grid     */
/* interpolation queries.                                               */
/* ******************************************************************** */
/* Author        : Charles Tong (LLNL)                                  */
/* Date          : February, 1999                                       */
/* ******************************************************************** */

#ifndef _MLCOMMINFOAGX_
#define _MLCOMMINFOAGX_

#include <stdio.h>
#include "ml_common.h"
#include "ml_defs.h"
#include "ml_memory.h"

/* ******************************************************************** */
/*  send_cur  : keeps track of how many send sublist has been loaded    */
/*  send_cnt  : total number of send sublists to be loaded              */
/*  send_proc : a list of processor numbers for send                    */
/*  send_ia   : send_ia[i] to send_ia[i-1] point to the locations in    */
/*  send_list : send_list for indices to send to send_proc[i]           */
/*  recv_cur  : keeps track of how many recv sublist has been loaded    */
/*  recv_cnt  : total number of recv sublists to be loaded              */
/*  recv_proc : a list of processor numbers for recv                    */
/*  recv_ia   : recv_ia[i] to recv_ia[i-1] point to the locations in    */
/*  recv_list : recv_list for indices to recv from recv_proc[i]         */
/*  recv_xyz  : storing coordinate information to be received.          */
/* -------------------------------------------------------------------- */

typedef struct ML_CommInfoAGX_Struct
{
   int    ML_id;
   int    proc_id;
   int    send_cur;
   int    send_cnt;
   int    *send_proc;
   int    *send_ia;
   ml_big_int    *send_list;
   int    recv_cur;
   int    recv_cnt;
   int    *recv_proc;
   int    *recv_ia;
   ml_big_int    *recv_list;
   double *recv_xyz;

} ML_CommInfoAGX;

/* ******************************************************************** */
/* functions to manipulate the ML_CommInfoAGX structure                 */
/* -------------------------------------------------------------------- */

#ifndef ML_CPP
#ifdef __cplusplus
extern "C"
{
#endif
#endif

extern int ML_CommInfoAGX_Create(ML_CommInfoAGX **);
extern int ML_CommInfoAGX_Setup_Send(ML_CommInfoAGX *, int, int);
extern int ML_CommInfoAGX_Load_SendList(ML_CommInfoAGX *, int, int, ml_big_int*);
extern int ML_CommInfoAGX_Get_SendList(ML_CommInfoAGX *,int,int*,int*,ml_big_int**);
extern int ML_CommInfoAGX_Setup_Recv(ML_CommInfoAGX *, int, int);
extern int ML_CommInfoAGX_Load_RecvInfo(ML_CommInfoAGX *, int, int);
extern int ML_CommInfoAGX_Load_RecvData(ML_CommInfoAGX*,int,ml_big_int*,double*,
                                        double*, double*);
extern int ML_CommInfoAGX_Get_RecvList(ML_CommInfoAGX *,int,int*,int*,ml_big_int**);
extern int ML_CommInfoAGX_Destroy(ML_CommInfoAGX **);
extern int ML_CommInfoAGX_Print(ML_CommInfoAGX *);

#ifndef ML_CPP
#ifdef __cplusplus
}
#endif
#endif

#endif

