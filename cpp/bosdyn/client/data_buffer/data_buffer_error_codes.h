/**
 * Copyright (c) 2021 Boston Dynamics, Inc.  All rights reserved.
 *
 * Downloading, reproducing, distributing or otherwise using the SDK Software
 * is subject to the terms and conditions of the Boston Dynamics Software
 * Development Kit License (20191101-BDSDK-SL).
 */


#pragma once

#include <bosdyn/api/data_buffer.pb.h>

#include "bosdyn/client/error_codes/proto_enum_to_stderror_macro.h"

DEFINE_PROTO_ENUM_ERRORCODE_HEADER_API(RecordTextMessagesResponse_Error_Type)
DEFINE_PROTO_ENUM_ERRORCODE_HEADER_API(RecordOperatorCommentsResponse_Error_Type)
DEFINE_PROTO_ENUM_ERRORCODE_HEADER_API(RecordDataBlobsResponse_Error_Type)
DEFINE_PROTO_ENUM_ERRORCODE_HEADER_API(RecordSignalTicksResponse_Error_Type)
DEFINE_PROTO_ENUM_ERRORCODE_HEADER_API(RecordEventsResponse_Error_Type)
