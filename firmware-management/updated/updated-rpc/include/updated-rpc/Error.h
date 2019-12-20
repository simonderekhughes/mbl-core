/*
 * Copyright (c) 2019 Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef UPDATED_UPDATEDRPC_ERROR_H
#define UPDATED_UPDATEDRPC_ERROR_H

#include "updated-rpc/updated-rpc.grpc.pb.h"

#include <stdexcept>

namespace updated {
namespace rpc {

/**
 * Class for exceptions related to RPC.
 */
class Error
    : public std::runtime_error
{
    // "inherit" std::runtime_error's ctors
    using std::runtime_error::runtime_error;
};

/**
 * Class for exceptions created from grpc::Status. I.e. for errors at the gRPC
 * level.
 */
class GrpcError
    : public Error
{
public:
    /**
     * Create a GrpcError from a grpc::Status.
     */
    explicit GrpcError(const grpc::Status& grpc_status);

    /**
     * Get the grpc::Status that corresponds to this exception.
     */
    const grpc::Status& grpc_status() const;

private:
    grpc::Status grpc_status_;
};

/**
 * Class for exceptions created from ErrorCodeMessage. I.e. for errors at the
 * application level that have been obtained via an RPC.
 */
class UpdateDRpcError
    : public Error
{
public:
    /**
     * Create an UpdateDRpcError from an ErrorCodeMessage.
     */
    explicit UpdateDRpcError(const ErrorCodeMessage& error_code_message);

    /**
     * Get the ErrorCodeMessage that corresponds to this exception.
     */
    const ErrorCodeMessage& error_code_message() const;

private:
    ErrorCodeMessage error_code_message_;
};

/**
 * Get an error message string from a grpc::Status.
 */
const char* grpc_status_to_str(const grpc::Status& grpc_status);

/**
 * Throw an exception if the given grpc::Status represents an error.
 */
void throw_on_grpc_error(const grpc::Status& grpc_status);

/**
 * Get an error message string from an ErrorCodeMessage.
 */
const char* updated_rpc_error_code_message_to_str(const ErrorCodeMessage& error_code_message);

/**
 * Throw an exception if the given ErrorCodeMessage represents an error.
 */
void throw_on_updated_rpc_error(const ErrorCodeMessage& error_code_message);

} // namespace rpc
} // namespace updated

#endif // UPDATED_UPDATEDRPC_ERROR_H