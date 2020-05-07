/*
 * Copyright (c) 2004-2007 The Trustees of Indiana University and Indiana
 *                         University Research and Technology
 *                         Corporation.  All rights reserved.
 * Copyright (c) 2004-2020 The University of Tennessee and The University
 *                         of Tennessee Research Foundation.  All rights
 *                         reserved.
 * Copyright (c) 2004-2008 High Performance Computing Center Stuttgart,
 *                         University of Stuttgart.  All rights reserved.
 * Copyright (c) 2004-2005 The Regents of the University of California.
 *                         All rights reserved.
 * Copyright (c) 2015      Research Organization for Information Science
 *                         and Technology (RIST). All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 * $HEADER$
 */
#include "ompi_config.h"
#include <stdio.h>

#include "ompi/mpi/c/bindings.h"
#include "ompi/runtime/params.h"
#include "ompi/communicator/communicator.h"
#include "ompi/errhandler/errhandler.h"
#include "ompi/memchecker.h"

#if OMPI_BUILD_MPI_PROFILING
#if OPAL_HAVE_WEAK_SYMBOLS
#pragma weak MPI_Comm_free = PMPI_Comm_free
#endif
#define MPI_Comm_free PMPI_Comm_free
#endif

static const char FUNC_NAME[] = "MPI_Comm_free";


int MPI_Comm_free(MPI_Comm *comm)
{
    int ret;

    MEMCHECKER(
        memchecker_comm(*comm);
    );

    if ( MPI_PARAM_CHECK ) {
        OMPI_ERR_INIT_FINALIZE(FUNC_NAME);

        if ( NULL == *comm ||
             ompi_comm_invalid (*comm)) {
            return OMPI_ERRHANDLER_NOHANDLE_INVOKE(MPI_ERR_COMM,
                                          FUNC_NAME);
        } else if (MPI_COMM_WORLD == *comm ||
                   MPI_COMM_SELF == *comm) {
            return OMPI_ERRHANDLER_INVOKE(*comm, MPI_ERR_COMM,
                                          FUNC_NAME);
        }
    }

    OPAL_CR_ENTER_LIBRARY();

    ret = ompi_comm_free ( comm );
    OMPI_ERRHANDLER_CHECK(ret, *comm, ret, FUNC_NAME);

    OPAL_CR_EXIT_LIBRARY();
    return MPI_SUCCESS;
}
