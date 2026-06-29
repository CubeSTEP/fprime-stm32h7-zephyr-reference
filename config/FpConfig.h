/**
 * \file: FpConfig.h
 * \brief C-compatible configuration header for F Prime configuration
 */
#ifndef FPCONFIG_H_
#define FPCONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <Fw/Types/BasicTypes.h>
#include <Platform/PlatformTypes.h>

// Direct port calls
#ifndef FW_DIRECT_PORT_CALLS
#define FW_DIRECT_PORT_CALLS 0
#endif

// Disable object-name storage to keep the embedded build smaller.
#ifndef FW_OBJECT_NAMES
#define FW_OBJECT_NAMES (0)
#endif

#if FW_OBJECT_NAMES == 1
#define FW_OPTIONAL_NAME(name) name
#else
#define FW_OPTIONAL_NAME(name) ""
#endif

#if FW_OBJECT_NAMES == 1
#ifndef FW_OBJECT_TO_STRING
#define FW_OBJECT_TO_STRING (1)
#endif
#else
#define FW_OBJECT_TO_STRING (0)
#endif

#ifndef FW_OBJECT_REGISTRATION
#define FW_OBJECT_REGISTRATION (1)
#endif

#ifndef FW_QUEUE_REGISTRATION
#define FW_QUEUE_REGISTRATION (1)
#endif

#ifndef FW_USE_PRINTF_FAMILY_FUNCTIONS_IN_STRING_FORMATTING
#define FW_USE_PRINTF_FAMILY_FUNCTIONS_IN_STRING_FORMATTING (1)
#endif

#ifndef FW_PORT_TRACING
#define FW_PORT_TRACING (1)
#endif

#ifndef FW_PORT_SERIALIZATION
#define FW_PORT_SERIALIZATION (1)
#endif

#ifndef FW_SERIALIZATION_TYPE_ID
#define FW_SERIALIZATION_TYPE_ID (0)
#endif

#if FW_SERIALIZATION_TYPE_ID
#ifndef FW_SERIALIZATION_TYPE_ID_BYTES
#define FW_SERIALIZATION_TYPE_ID_BYTES (4)
#endif
#endif

#ifndef FW_ASSERT_LEVEL
#define FW_ASSERT_LEVEL (FW_FILENAME_ASSERT)
#endif

#ifndef FW_ASSERTIONS_ALWAYS_ABORT
#define FW_ASSERTIONS_ALWAYS_ABORT 0
#endif

#if FW_OBJECT_NAMES
#ifndef FW_OBJ_NAME_BUFFER_SIZE
#define FW_OBJ_NAME_BUFFER_SIZE (80)
#endif
#endif

#ifndef FW_CMD_CHECK_RESIDUAL
#define FW_CMD_CHECK_RESIDUAL (1)
#endif

#ifndef FW_ENABLE_TEXT_LOGGING
#define FW_ENABLE_TEXT_LOGGING (1)
#endif

#ifndef FW_SERIALIZABLE_TO_STRING
#define FW_SERIALIZABLE_TO_STRING (1)
#endif

#ifndef FW_AMPCS_COMPATIBLE
#define FW_AMPCS_COMPATIBLE (0)
#endif

#ifndef POSIX_THREADS_ENABLE_NAMES
#define POSIX_THREADS_ENABLE_NAMES (1)
#endif

#ifdef __cplusplus
}
#endif

#endif
