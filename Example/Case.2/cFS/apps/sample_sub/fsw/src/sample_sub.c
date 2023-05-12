/*
**   Include Files:
*/

#include "sample_sub.h"
#include "sample_sub_perfids.h"
#include "sample_sub_msgids.h"
#include "sample_sub_msg.h"
#include "racs2_user_msg.h"
#include "sample_sub_events.h"
#include "sample_sub_version.h"
#include "RACS2Bridge_std_msgs.pb-c.h"

#include <std_msgs/msg/string.h>
#include <rclc/executor.h>
#include <rclc/rclc.h>

/*
** global data
*/

sample_hk_tlm_t SAMPLE_SUB_HkTelemetryPkt;
sample_hk_tlm_t SAMPLE_TalkerListenerPkt;
CFE_SB_PipeId_t SAMPLE_SUB_CommandPipe;
CFE_SB_MsgPtr_t SAMPLE_SUB_MsgPtr;
racs2_user_msg_t RACS2_UserMsgPkt;
CFE_SB_MsgPtr_t RACS2_UserMsgPkt_Ptr;

std_msgs__msg__String sub_msg;
const unsigned int PUB_MSG_CAPACITY = 32;

static CFE_EVS_BinFilter_t SAMPLE_EventFilters[] =
    {
        /* Event ID    mask */
        {SAMPLE_STARTUP_INF_EID, 0x0000},
        {SAMPLE_COMMAND_ERR_EID, 0x0000},
        {SAMPLE_COMMANDNOP_INF_EID, 0x0000},
        {SAMPLE_COMMANDRST_INF_EID, 0x0000},
};

/***************************** CALLBACK ***********************************/
void my_subscriber_callback(const void *msgin)
{
    const std_msgs__msg__String *msg = (const std_msgs__msg__String *)msgin;
    if (msg == NULL)
    {
        OS_printf("Error, callback msg NULL\n");
    }
    else
    {
        OS_printf("Subscribed message [%s]\n", msg->data.data);
    }
}

/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* SAMPLE_SUB_Main() -- Application entry point and main process loop         */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * *  * * * * **/
void SAMPLE_SUB_Main(void)
{
    int32 status;
    uint32 RunStatus = CFE_ES_RunStatus_APP_RUN;

    OS_printf("SAMPLE_SUB_Main starts.\n");

    CFE_ES_PerfLogEntry(SAMPLE_APP_PERF_ID);

    SAMPLE_SUB_Init();

    /*
    ** SAMPLE_SUB Runloop
    */
    while (CFE_ES_RunLoop(&RunStatus) == true)
    {
        CFE_ES_PerfLogExit(SAMPLE_APP_PERF_ID);

        /* Pend on receipt of command packet -- timeout set to 500 millisecs */
        status = CFE_SB_RcvMsg(&RACS2_UserMsgPkt_Ptr, SAMPLE_SUB_CommandPipe, 1000);

        CFE_ES_PerfLogEntry(SAMPLE_APP_PERF_ID);

        if (status == CFE_SUCCESS)
        {
            SAMPLE_SUB_ProcessCommandPacket();
        }
    }

    CFE_ES_ExitApp(RunStatus);

} /* End of SAMPLE_SUB_Main() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  */
/*                                                                            */
/* SAMPLE_SUB_Init() --  initialization                                       */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
void SAMPLE_SUB_Init(void)
{
    int32 status;
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
    rc = rclc_node_init_default(&my_node, "sample_sub", "", &support);
    if (rc != RCL_RET_OK)
    {
        OS_printf("Error in rclc_node_init_default\n");
        return;
    }
    //-------------------------------------------------

    //-------------------------------------------------
    const char *topic_name = "RACS2DDS";
    const rosidl_message_type_support_t *my_type_support =
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, String);
    //-------------------------------------------------

    //-------------------------------------------------
    // assign message to publisher
    std_msgs__msg__String__init(&sub_msg);
    sub_msg.data.data = malloc(PUB_MSG_CAPACITY);
    sub_msg.data.capacity = PUB_MSG_CAPACITY;
    //-------------------------------------------------

    //-------------------------------------------------
    // create subscription
    rcl_subscription_t my_sub = rcl_get_zero_initialized_subscription();
    rc = rclc_subscription_init_default(
        &my_sub,
        &my_node,
        my_type_support,
        topic_name);
    if (rc != RCL_RET_OK)
    {
        OS_printf("Failed to create subscriber %s.\n", topic_name);
        return -1;
    }
    else
    {
        OS_printf("Created subscriber %s:\n", topic_name);
    }
    std_msgs__msg__String__init(&sub_msg);
    //-------------------------------------------------

    //-------------------------------------------------
    // Configuration of RCL Executor
    rclc_executor_t executor;
    executor = rclc_executor_get_zero_initialized_executor();
    unsigned int num_handles = 1 + 1;
    rclc_executor_init(&executor, &support.context, num_handles, &allocator);

    // add subscription to executor
    rc = rclc_executor_add_subscription(
        &executor, &my_sub, &sub_msg, &my_subscriber_callback,
        ON_NEW_DATA);
    if (rc != RCL_RET_OK)
    {
        OS_printf("Error in rclc_executor_add_subscription. \n");
    }

    if (rc != RCL_RET_OK)
    {
        OS_printf("Error in rclc_executor_add_timer.\n");
    }

    // Start Executor
    rclc_executor_spin(&executor);
    //-------------------------------------------------

    /*
    ** Create the Software Bus command pipe and subscribe to housekeeping
    **  messages
    */
    status = CFE_SB_CreatePipe(&SAMPLE_SUB_CommandPipe, SAMPLE_PIPE_DEPTH, "TO_LISTENER");
    if (status != CFE_SUCCESS)
    {
        OS_printf("SAMPLE_SUB: failed to create SB pipe, status = 0x%x\n", status);
    }
    status = CFE_SB_Subscribe(SAMPLE_SUB_MID, SAMPLE_SUB_CommandPipe);
    if (status != CFE_SUCCESS)
    {
        OS_printf("SAMPLE_SUB: failed to subscribe MsgID[0x%x], status = 0x%x\n", SAMPLE_SUB_MID, status);
    }
    SAMPLE_SUB_ResetCounters();

    CFE_SB_InitMsg(&SAMPLE_SUB_HkTelemetryPkt,
                   SAMPLE_SUB_HK_TLM_MID,
                   SAMPLE_APP_HK_TLM_LNGTH, true);

    CFE_EVS_SendEvent(SAMPLE_STARTUP_INF_EID, CFE_EVS_EventType_INFORMATION,
                      "SAMPLE_SUB App Initialized. Version %d.%d.%d.%d",
                      SAMPLE_APP_MAJOR_VERSION,
                      SAMPLE_APP_MINOR_VERSION,
                      SAMPLE_APP_REVISION,
                      SAMPLE_APP_MISSION_REV);

} /* End of SAMPLE_SUB_Init() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  SAMPLE_SUB_ProcessCommandPacket                                    */
/*                                                                            */
/*  Purpose:                                                                  */
/*     This routine will process any packet that is received on the SAMPLE_SUB*/
/*     command pipe.                                                          */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
void SAMPLE_SUB_ProcessCommandPacket(void)
{
    CFE_SB_MsgId_t MsgId;

    MsgId = CFE_SB_GetMsgId(RACS2_UserMsgPkt_Ptr);

    uint8 *tmpPtr;

    switch (MsgId)
    {
    case SAMPLE_SUB_CMD_MID:
        SAMPLE_SUB_ProcessGroundCommand();
        break;

    case SAMPLE_SUB_SEND_HK_MID:
        SAMPLE_SUB_ReportHousekeeping();
        break;

    case SAMPLE_SUB_MID:
        tmpPtr = RACS2_UserMsgPkt_Ptr;
        OS_printf("SAMPLE_SUB: received sample message from talker, MID = [0x%x].\n",
                  MsgId);
        char buffer[1024];
        int len = 0;

        RACS2DDSStdMsgs *message;
        message = racs2_dds_std_msgs__unpack(NULL, len, tmpPtr + 12 + 32 + 1);
        if (message)
        {
            OS_printf("SAMPLE_SUB: deserialization failed\n");
            break;
        }
        // OS_printf("len = %d\n", len);

        if (message->string_data)
        {
            OS_printf("SAMPLE_SUB: %s\n", message->string_data);
        }
        else
        {
            OS_printf("SAMPLE_SUB: data is empty\n");
        }

        racs2_dds_std_msgs__free_unpacked(message, NULL);
        break;

    default:
        SAMPLE_SUB_HkTelemetryPkt.sample_command_error_count++;
        CFE_EVS_SendEvent(SAMPLE_COMMAND_ERR_EID, CFE_EVS_EventType_ERROR,
                          "SAMPLE_SUB: invalid command packet,MID = 0x%x", MsgId);
        break;
    }

    return;

} /* End SAMPLE_SUB_ProcessCommandPacket */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* SAMPLE_SUB_ProcessGroundCommand() -- SAMPLE_SUB ground commands            */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

void SAMPLE_SUB_ProcessGroundCommand(void)
{
    uint16 CommandCode;

    // CommandCode = CFE_SB_GetCmdCode(SAMPLE_SUB_MsgPtr);
    CommandCode = CFE_SB_GetCmdCode(RACS2_UserMsgPkt_Ptr);

    /* Process "known" SAMPLE_SUB app ground commands */
    switch (CommandCode)
    {
    case SAMPLE_APP_NOOP_CC:
        SAMPLE_SUB_HkTelemetryPkt.sample_command_count++;
        CFE_EVS_SendEvent(SAMPLE_COMMANDNOP_INF_EID,
                          CFE_EVS_EventType_INFORMATION,
                          "SAMPLE_SUB: NOOP command");
        break;

    case SAMPLE_APP_RESET_COUNTERS_CC:
        SAMPLE_SUB_ResetCounters();
        break;

    /* default case already found during FC vs length test */
    default:
        break;
    }
    return;

} /* End of SAMPLE_SUB_ProcessGroundCommand() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  SAMPLE_SUB_ReportHousekeeping                                      */
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function is triggered in response to a task telemetry request */
/*         from the housekeeping task. This function will gather the Apps     */
/*         telemetry, packetize it and send it to the housekeeping task via   */
/*         the software bus                                                   */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
void SAMPLE_SUB_ReportHousekeeping(void)
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t *)&SAMPLE_SUB_HkTelemetryPkt);
    CFE_SB_SendMsg((CFE_SB_Msg_t *)&SAMPLE_SUB_HkTelemetryPkt);
    return;

} /* End of SAMPLE_SUB_ReportHousekeeping() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  SAMPLE_SUB_ResetCounters                                           */
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function resets all the global counter variables that are     */
/*         part of the task telemetry.                                        */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
void SAMPLE_SUB_ResetCounters(void)
{
    /* Status of commands processed by the SAMPLE_SUB App */
    SAMPLE_SUB_HkTelemetryPkt.sample_command_count = 0;
    SAMPLE_SUB_HkTelemetryPkt.sample_command_error_count = 0;

    CFE_EVS_SendEvent(SAMPLE_COMMANDRST_INF_EID, CFE_EVS_EventType_INFORMATION,
                      "SAMPLE_SUB: RESET command");
    return;

} /* End of SAMPLE_SUB_ResetCounters() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* SAMPLE_SUB_VerifyCmdLength() -- Verify command packet length               */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
bool SAMPLE_SUB_VerifyCmdLength(CFE_SB_MsgPtr_t msg, uint16 ExpectedLength)
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
        SAMPLE_SUB_HkTelemetryPkt.sample_command_error_count++;
    }

    return (result);

} /* End of SAMPLE_SUB_VerifyCmdLength() */
