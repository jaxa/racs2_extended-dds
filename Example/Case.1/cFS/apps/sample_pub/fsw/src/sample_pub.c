/*
**   Include Files:
*/

#include "sample_pub.h"
#include "sample_pub_perfids.h"
#include "sample_pub_msgids.h"
#include "sample_pub_msg.h"
#include "racs2_user_msg.h"
#include "sample_pub_events.h"
#include "sample_pub_version.h"
#include "RACS2Brdige_std_msgs.pb-c.h"

#include <std_msgs/msg/string.h>
#include <rclc/executor.h>
#include <rclc/rclc.h>

/*
** global data
*/

sample_hk_tlm_t SAMPLE_PUB_HkTelemetryPkt;
racs2_user_msg_t RACS2_UserMsgPkt;
CFE_SB_PipeId_t SAMPLE_PUB_CommandPipe;
CFE_SB_MsgPtr_t SAMPLE_PUB_MsgPtr;

rcl_publisher_t my_pub;
std_msgs__msg__String pub_msg;
const unsigned int PUB_MSG_CAPACITY = 32;

static CFE_EVS_BinFilter_t SAMPLE_EventFilters[] =
    {
        /* Event ID    mask */
        {SAMPLE_STARTUP_INF_EID, 0x0000},
        {SAMPLE_COMMAND_ERR_EID, 0x0000},
        {SAMPLE_COMMANDNOP_INF_EID, 0x0000},
        {SAMPLE_COMMANDRST_INF_EID, 0x0000},
};

/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* SAMPLE_PUB_Main() -- Application entry point and main process loop         */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * *  * * * * **/
void SAMPLE_PUB_Main(void)
{
    int32 status;
    uint32 RunStatus = CFE_ES_RunStatus_APP_RUN;

    OS_printf("SAMPLE_PUB_Main starts.\n");

    CFE_ES_PerfLogEntry(SAMPLE_APP_PERF_ID);

    SAMPLE_PUB_Init();

    /*
    ** SAMPLE_PUB Runloop
    */
    int count = 0;
    while (CFE_ES_RunLoop(&RunStatus) == true)
    {
        CFE_ES_PerfLogExit(SAMPLE_APP_PERF_ID);

        // /* Pend on receipt of command packet -- timeout set to 500 millisecs */
        // status = CFE_SB_RcvMsg(&SAMPLE_PUB_MsgPtr, SAMPLE_PUB_CommandPipe, 500);

        CFE_ES_PerfLogEntry(SAMPLE_APP_PERF_ID);

        // if (status == CFE_SUCCESS)
        // {
        //     SAMPLE_PUB_ProcessCommandPacket();
        // }
        sleep(2);

        // ------------------------------------------------------------
        // send message
        rcl_ret_t rc;
        char *buf[PUB_MSG_CAPACITY];
        sprintf(buf, "Message To ROS2 :%5d", count);
        strncpy(pub_msg.data.data, buf, PUB_MSG_CAPACITY);
        pub_msg.data.size = strlen(pub_msg.data.data);

        rc = rcl_publish(&my_pub, &pub_msg, NULL);
        if (rc == RCL_RET_OK)
        {
            OS_printf("Published message [%s]\n", pub_msg.data.data);
        }
        else
        {
            OS_printf("Error publishing message %s\n", pub_msg.data.data);
        }
        // ------------------------------------------------------------

        count++;
    }

    CFE_ES_ExitApp(RunStatus);

} /* End of SAMPLE_PUB_Main() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  */
/*                                                                            */
/* SAMPLE_PUB_Init() --  initialization                                       */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
void SAMPLE_PUB_Init(void)
{
    /*
    ** Register the app with Executive services
    */
    CFE_ES_RegisterApp();

    /*
    ** Register the events
    */
    CFE_EVS_Register(SAMPLE_EventFilters,
                     sizeof(SAMPLE_EventFilters) / sizeof(CFE_EVS_BinFilter_t),
                     CFE_EVS_EventFilter_BINARY);

    //-------------------------------------------------
    // rclc init options
    rcl_allocator_t allocator = rcl_get_default_allocator();
    rclc_support_t support;
    rcl_ret_t rc;
    rc = rclc_support_init(&support, 0, NULL, &allocator);
    if (rc != RCL_RET_OK)
    {
        OS_printf("Error rclc_support_init.\n");
        return;
    }
    //-------------------------------------------------

    //-------------------------------------------------
    // create rclc node
    rcl_node_t my_node = rcl_get_zero_initialized_node();
    rc = rclc_node_init_default(&my_node, "sample_pub", "", &support);
    if (rc != RCL_RET_OK)
    {
        OS_printf("Error in rclc_node_init_default\n");
        return;
    }
    //-------------------------------------------------

    //-------------------------------------------------
    // create a publisher to publish topic 'RACS2DDS'
    const char *topic_name = "RACS2DDS";
    const rosidl_message_type_support_t *my_type_support =
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, String);

    rc = rclc_publisher_init_default(
        &my_pub,
        &my_node,
        my_type_support,
        topic_name);
    if (RCL_RET_OK != rc)
    {
        OS_printf("Error in rclc_publisher_init_default %s.\n", topic_name);
        return -1;
    }
    //-------------------------------------------------

    //-------------------------------------------------
    // assign message to publisher
    std_msgs__msg__String__init(&pub_msg);
    pub_msg.data.data = malloc(PUB_MSG_CAPACITY);
    pub_msg.data.capacity = PUB_MSG_CAPACITY;
    //-------------------------------------------------

    // /*
    // ** Create the Software Bus command pipe and subscribe to housekeeping
    // **  messages
    // */
    // CFE_SB_CreatePipe(&SAMPLE_PUB_CommandPipe, SAMPLE_PIPE_DEPTH, "TO_TALKER");
    // CFE_SB_Subscribe(SAMPLE_PUB_CMD_MID, SAMPLE_PUB_CommandPipe);
    // CFE_SB_Subscribe(SAMPLE_PUB_SEND_HK_MID, SAMPLE_PUB_CommandPipe);

    SAMPLE_PUB_ResetCounters();

    CFE_SB_InitMsg(&SAMPLE_PUB_HkTelemetryPkt,
                   SAMPLE_PUB_HK_TLM_MID,
                   SAMPLE_APP_HK_TLM_LNGTH, true);

    CFE_SB_InitMsg(&RACS2_UserMsgPkt, RACS2_DDS_MID, RACS2_USER_MSG_LNGTH, false);

    CFE_EVS_SendEvent(SAMPLE_STARTUP_INF_EID, CFE_EVS_EventType_INFORMATION,
                      "SAMPLE_PUB App Initialized. Version %d.%d.%d.%d",
                      SAMPLE_APP_MAJOR_VERSION,
                      SAMPLE_APP_MINOR_VERSION,
                      SAMPLE_APP_REVISION,
                      SAMPLE_APP_MISSION_REV);

} /* End of SAMPLE_PUB_Init() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  SAMPLE_PUB_ProcessCommandPacket                                    */
/*                                                                            */
/*  Purpose:                                                                  */
/*     This routine will process any packet that is received on the SAMPLE_PUB*/
/*     command pipe.                                                          */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
void SAMPLE_PUB_ProcessCommandPacket(void)
{
    CFE_SB_MsgId_t MsgId;

    MsgId = CFE_SB_GetMsgId(SAMPLE_PUB_MsgPtr);

    switch (MsgId)
    {
    case SAMPLE_PUB_CMD_MID:
        SAMPLE_PUB_ProcessGroundCommand();
        break;

    case SAMPLE_PUB_SEND_HK_MID:
        SAMPLE_PUB_ReportHousekeeping();
        break;

    default:
        SAMPLE_PUB_HkTelemetryPkt.sample_command_error_count++;
        CFE_EVS_SendEvent(SAMPLE_COMMAND_ERR_EID, CFE_EVS_EventType_ERROR,
                          "SAMPLE_PUB: invalid command packet,MID = 0x%x", MsgId);
        break;
    }

    return;

} /* End SAMPLE_PUB_ProcessCommandPacket */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* SAMPLE_PUB_ProcessGroundCommand() -- SAMPLE_PUB ground commands            */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

void SAMPLE_PUB_ProcessGroundCommand(void)
{
    uint16 CommandCode;

    CommandCode = CFE_SB_GetCmdCode(SAMPLE_PUB_MsgPtr);

    /* Process "known" SAMPLE_PUB app ground commands */
    switch (CommandCode)
    {
    case SAMPLE_APP_NOOP_CC:
        SAMPLE_PUB_HkTelemetryPkt.sample_command_count++;
        CFE_EVS_SendEvent(SAMPLE_COMMANDNOP_INF_EID,
                          CFE_EVS_EventType_INFORMATION,
                          "SAMPLE_PUB: NOOP command");
        break;

    case SAMPLE_APP_RESET_COUNTERS_CC:
        SAMPLE_PUB_ResetCounters();
        break;

    /* default case already found during FC vs length test */
    default:
        break;
    }
    return;

} /* End of SAMPLE_PUB_ProcessGroundCommand() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  SAMPLE_PUB_ReportHousekeeping                                      */
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function is triggered in response to a task telemetry request */
/*         from the housekeeping task. This function will gather the Apps     */
/*         telemetry, packetize it and send it to the housekeeping task via   */
/*         the software bus                                                   */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
void SAMPLE_PUB_ReportHousekeeping(void)
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t *)&SAMPLE_PUB_HkTelemetryPkt);
    CFE_SB_SendMsg((CFE_SB_Msg_t *)&SAMPLE_PUB_HkTelemetryPkt);
    return;

} /* End of SAMPLE_PUB_ReportHousekeeping() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  SAMPLE_PUB_ResetCounters                                           */
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function resets all the global counter variables that are     */
/*         part of the task telemetry.                                        */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
void SAMPLE_PUB_ResetCounters(void)
{
    /* Status of commands processed by the SAMPLE_PUB App */
    SAMPLE_PUB_HkTelemetryPkt.sample_command_count = 0;
    SAMPLE_PUB_HkTelemetryPkt.sample_command_error_count = 0;

    CFE_EVS_SendEvent(SAMPLE_COMMANDRST_INF_EID, CFE_EVS_EventType_INFORMATION,
                      "SAMPLE_PUB: RESET command");
    return;

} /* End of SAMPLE_PUB_ResetCounters() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* SAMPLE_PUB_VerifyCmdLength() -- Verify command packet length               */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
bool SAMPLE_PUB_VerifyCmdLength(CFE_SB_MsgPtr_t msg, uint16 ExpectedLength)
{
    bool result = true;

    uint16 ActualLength = CFE_SB_GetTotalMsgLength(msg);

    /*
    ** Verify the command packet length.
    */
    if (ExpectedLength != ActualLength)
    {
        CFE_SB_MsgId_t MessageID = CFE_SB_GetMsgId(msg);
        uint16 CommandCode = CFE_SB_GetCmdCode(msg);

        CFE_EVS_SendEvent(SAMPLE_LEN_ERR_EID, CFE_EVS_EventType_ERROR,
                          "Invalid msg length: ID = 0x%X,  CC = %d, Len = %d, Expected = %d",
                          MessageID, CommandCode, ActualLength, ExpectedLength);
        result = false;
        SAMPLE_PUB_HkTelemetryPkt.sample_command_error_count++;
    }

    return (result);

} /* End of SAMPLE_PUB_VerifyCmdLength() */
