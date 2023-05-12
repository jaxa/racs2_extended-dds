#ifndef _sample_sub_h_
#define _sample_sub_h_

/*
** Required header files.
*/
#include "cfe.h"
#include "cfe_error.h"
#include "cfe_evs.h"
#include "cfe_sb.h"
#include "cfe_es.h"

#include <string.h>
#include <errno.h>
#include <unistd.h>

/***********************************************************************/

#define SAMPLE_PIPE_DEPTH                     32

/************************************************************************
** Type Definitions
*************************************************************************/

/****************************************************************************/
/*
** Local function prototypes.
**
** Note: Except for the entry point (SAMPLE_AppMain), these
**       functions are not called from any other source module.
*/
void SAMPLE_AppMain(void);
void SAMPLE_AppInit(void);
void SAMPLE_SUB_ProcessCommandPacket(void);
void SAMPLE_SUB_ProcessGroundCommand(void);
void SAMPLE_SUB_ReportHousekeeping(void);
void SAMPLE_SUB_ResetCounters(void);

bool SAMPLE_SUB_VerifyCmdLength(CFE_SB_MsgPtr_t msg, uint16 ExpectedLength);

#endif /* _sample_sub_h_ */
