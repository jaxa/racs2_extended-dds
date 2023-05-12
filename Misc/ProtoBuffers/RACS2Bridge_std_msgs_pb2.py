# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: RACS2Bridge_std_msgs.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='RACS2Bridge_std_msgs.proto',
  package='',
  syntax='proto2',
  serialized_options=None,
  serialized_pb=_b('\n\x1aRACS2Bridge_std_msgs.proto\"\xf3\x02\n\x14RACS2Bridge_std_msgs\x12\x11\n\tbool_data\x18\x01 \x01(\x08\x12\x12\n\nfloat_data\x18\x02 \x01(\x02\x12\x13\n\x0b\x64ouble_data\x18\x03 \x01(\x01\x12\x12\n\nint32_data\x18\x04 \x01(\x05\x12\x12\n\nint64_data\x18\x05 \x01(\x03\x12\x13\n\x0bstring_data\x18\x06 \x01(\t\x12\x13\n\x0buint32_data\x18\x07 \x01(\r\x12\x13\n\x0buint64_data\x18\x08 \x01(\x04\x12\x1e\n\x12\x66loat32_array_data\x18\t \x03(\x02\x42\x02\x10\x01\x12\x1e\n\x12\x66loat64_array_data\x18\n \x03(\x01\x42\x02\x10\x01\x12\x1c\n\x10int32_array_data\x18\x0b \x03(\x05\x42\x02\x10\x01\x12\x1c\n\x10int64_array_data\x18\x0c \x03(\x03\x42\x02\x10\x01\x12\x1d\n\x11uint32_array_data\x18\r \x03(\rB\x02\x10\x01\x12\x1d\n\x11uint64_array_data\x18\x0e \x03(\x04\x42\x02\x10\x01')
)




_RACS2BRIDGE_STD_MSGS = _descriptor.Descriptor(
  name='RACS2Bridge_std_msgs',
  full_name='RACS2Bridge_std_msgs',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='bool_data', full_name='RACS2Bridge_std_msgs.bool_data', index=0,
      number=1, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='float_data', full_name='RACS2Bridge_std_msgs.float_data', index=1,
      number=2, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='double_data', full_name='RACS2Bridge_std_msgs.double_data', index=2,
      number=3, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='int32_data', full_name='RACS2Bridge_std_msgs.int32_data', index=3,
      number=4, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='int64_data', full_name='RACS2Bridge_std_msgs.int64_data', index=4,
      number=5, type=3, cpp_type=2, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='string_data', full_name='RACS2Bridge_std_msgs.string_data', index=5,
      number=6, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='uint32_data', full_name='RACS2Bridge_std_msgs.uint32_data', index=6,
      number=7, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='uint64_data', full_name='RACS2Bridge_std_msgs.uint64_data', index=7,
      number=8, type=4, cpp_type=4, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='float32_array_data', full_name='RACS2Bridge_std_msgs.float32_array_data', index=8,
      number=9, type=2, cpp_type=6, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=_b('\020\001'), file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='float64_array_data', full_name='RACS2Bridge_std_msgs.float64_array_data', index=9,
      number=10, type=1, cpp_type=5, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=_b('\020\001'), file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='int32_array_data', full_name='RACS2Bridge_std_msgs.int32_array_data', index=10,
      number=11, type=5, cpp_type=1, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=_b('\020\001'), file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='int64_array_data', full_name='RACS2Bridge_std_msgs.int64_array_data', index=11,
      number=12, type=3, cpp_type=2, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=_b('\020\001'), file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='uint32_array_data', full_name='RACS2Bridge_std_msgs.uint32_array_data', index=12,
      number=13, type=13, cpp_type=3, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=_b('\020\001'), file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='uint64_array_data', full_name='RACS2Bridge_std_msgs.uint64_array_data', index=13,
      number=14, type=4, cpp_type=4, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=_b('\020\001'), file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=31,
  serialized_end=402,
)

DESCRIPTOR.message_types_by_name['RACS2Bridge_std_msgs'] = _RACS2BRIDGE_STD_MSGS
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

RACS2Bridge_std_msgs = _reflection.GeneratedProtocolMessageType('RACS2Bridge_std_msgs', (_message.Message,), dict(
  DESCRIPTOR = _RACS2BRIDGE_STD_MSGS,
  __module__ = 'RACS2Bridge_std_msgs_pb2'
  # @@protoc_insertion_point(class_scope:RACS2Bridge_std_msgs)
  ))
_sym_db.RegisterMessage(RACS2Bridge_std_msgs)


_RACS2BRIDGE_STD_MSGS.fields_by_name['float32_array_data']._options = None
_RACS2BRIDGE_STD_MSGS.fields_by_name['float64_array_data']._options = None
_RACS2BRIDGE_STD_MSGS.fields_by_name['int32_array_data']._options = None
_RACS2BRIDGE_STD_MSGS.fields_by_name['int64_array_data']._options = None
_RACS2BRIDGE_STD_MSGS.fields_by_name['uint32_array_data']._options = None
_RACS2BRIDGE_STD_MSGS.fields_by_name['uint64_array_data']._options = None
# @@protoc_insertion_point(module_scope)
