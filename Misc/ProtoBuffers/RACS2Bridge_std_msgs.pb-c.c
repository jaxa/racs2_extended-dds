/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: RACS2Bridge_std_msgs.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "RACS2Bridge_std_msgs.pb-c.h"
void   racs2_bridge_std_msgs__init
                     (RACS2BridgeStdMsgs         *message)
{
  static const RACS2BridgeStdMsgs init_value = RACS2_BRIDGE_STD_MSGS__INIT;
  *message = init_value;
}
size_t racs2_bridge_std_msgs__get_packed_size
                     (const RACS2BridgeStdMsgs *message)
{
  assert(message->base.descriptor == &racs2_bridge_std_msgs__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t racs2_bridge_std_msgs__pack
                     (const RACS2BridgeStdMsgs *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &racs2_bridge_std_msgs__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t racs2_bridge_std_msgs__pack_to_buffer
                     (const RACS2BridgeStdMsgs *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &racs2_bridge_std_msgs__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
RACS2BridgeStdMsgs *
       racs2_bridge_std_msgs__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (RACS2BridgeStdMsgs *)
     protobuf_c_message_unpack (&racs2_bridge_std_msgs__descriptor,
                                allocator, len, data);
}
void   racs2_bridge_std_msgs__free_unpacked
                     (RACS2BridgeStdMsgs *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &racs2_bridge_std_msgs__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor racs2_bridge_std_msgs__field_descriptors[14] =
{
  {
    "bool_data",
    1,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_BOOL,
    offsetof(RACS2BridgeStdMsgs, has_bool_data),
    offsetof(RACS2BridgeStdMsgs, bool_data),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "float_data",
    2,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_FLOAT,
    offsetof(RACS2BridgeStdMsgs, has_float_data),
    offsetof(RACS2BridgeStdMsgs, float_data),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "double_data",
    3,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_DOUBLE,
    offsetof(RACS2BridgeStdMsgs, has_double_data),
    offsetof(RACS2BridgeStdMsgs, double_data),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "int32_data",
    4,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_INT32,
    offsetof(RACS2BridgeStdMsgs, has_int32_data),
    offsetof(RACS2BridgeStdMsgs, int32_data),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "int64_data",
    5,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_INT64,
    offsetof(RACS2BridgeStdMsgs, has_int64_data),
    offsetof(RACS2BridgeStdMsgs, int64_data),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "string_data",
    6,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(RACS2BridgeStdMsgs, string_data),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "uint32_data",
    7,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_UINT32,
    offsetof(RACS2BridgeStdMsgs, has_uint32_data),
    offsetof(RACS2BridgeStdMsgs, uint32_data),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "uint64_data",
    8,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_UINT64,
    offsetof(RACS2BridgeStdMsgs, has_uint64_data),
    offsetof(RACS2BridgeStdMsgs, uint64_data),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "float32_array_data",
    9,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_FLOAT,
    offsetof(RACS2BridgeStdMsgs, n_float32_array_data),
    offsetof(RACS2BridgeStdMsgs, float32_array_data),
    NULL,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_PACKED,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "float64_array_data",
    10,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_DOUBLE,
    offsetof(RACS2BridgeStdMsgs, n_float64_array_data),
    offsetof(RACS2BridgeStdMsgs, float64_array_data),
    NULL,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_PACKED,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "int32_array_data",
    11,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_INT32,
    offsetof(RACS2BridgeStdMsgs, n_int32_array_data),
    offsetof(RACS2BridgeStdMsgs, int32_array_data),
    NULL,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_PACKED,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "int64_array_data",
    12,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_INT64,
    offsetof(RACS2BridgeStdMsgs, n_int64_array_data),
    offsetof(RACS2BridgeStdMsgs, int64_array_data),
    NULL,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_PACKED,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "uint32_array_data",
    13,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_UINT32,
    offsetof(RACS2BridgeStdMsgs, n_uint32_array_data),
    offsetof(RACS2BridgeStdMsgs, uint32_array_data),
    NULL,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_PACKED,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "uint64_array_data",
    14,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_UINT64,
    offsetof(RACS2BridgeStdMsgs, n_uint64_array_data),
    offsetof(RACS2BridgeStdMsgs, uint64_array_data),
    NULL,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_PACKED,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned racs2_bridge_std_msgs__field_indices_by_name[] = {
  0,   /* field[0] = bool_data */
  2,   /* field[2] = double_data */
  8,   /* field[8] = float32_array_data */
  9,   /* field[9] = float64_array_data */
  1,   /* field[1] = float_data */
  10,   /* field[10] = int32_array_data */
  3,   /* field[3] = int32_data */
  11,   /* field[11] = int64_array_data */
  4,   /* field[4] = int64_data */
  5,   /* field[5] = string_data */
  12,   /* field[12] = uint32_array_data */
  6,   /* field[6] = uint32_data */
  13,   /* field[13] = uint64_array_data */
  7,   /* field[7] = uint64_data */
};
static const ProtobufCIntRange racs2_bridge_std_msgs__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 14 }
};
const ProtobufCMessageDescriptor racs2_bridge_std_msgs__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "RACS2Bridge_std_msgs",
  "RACS2BridgeStdMsgs",
  "RACS2BridgeStdMsgs",
  "",
  sizeof(RACS2BridgeStdMsgs),
  14,
  racs2_bridge_std_msgs__field_descriptors,
  racs2_bridge_std_msgs__field_indices_by_name,
  1,  racs2_bridge_std_msgs__number_ranges,
  (ProtobufCMessageInit) racs2_bridge_std_msgs__init,
  NULL,NULL,NULL    /* reserved[123] */
};
