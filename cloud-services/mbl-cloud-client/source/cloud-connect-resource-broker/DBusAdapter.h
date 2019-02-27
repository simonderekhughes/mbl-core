/*
 * Copyright (c) 2019 Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef DBusAdapter_h_
#define DBusAdapter_h_

#include "MblError.h"
#include "CloudConnectExternalTypes.h"
#include "SelfEvent.h"

#include <inttypes.h>
#include <memory>
#include <string>

// to be used by Google Test testing
class TestInfra_DBusAdapterTester;

namespace mbl {

class ResourceBroker;
class DBusAdapterImpl;


/**
 * @brief Implements an interface to the D-Bus IPC.
 * This class provides an implementation for the handlers that 
 * will allow comminication between Pelion Cloud Connect D-Bus 
 * service and client applications.
 */
class DBusAdapter {
// Google test friend class (for tests to be able to reach private members)
friend class ::TestInfra_DBusAdapterTester;
public:    
    DBusAdapter(ResourceBroker &ccrb);

    // dtor must be explicitly declared and get default implementation in source in order to allow
    // member impl_ unique_ptr to reqcognize DBusAdapterImpl as a complete type and deestroy it
    virtual ~DBusAdapter();

/**
 * @brief Initializes IPC mechanism.
 * 
 * @return MblError returns value Error::None if function succeeded, 
 *         or error code otherwise.
 */
    MblError init();

/**
 * @brief Deinitializes IPC mechanism.
 * 
 * @return MblError returns value Error::None if function succeeded, 
 *         or error code otherwise.
 */
    MblError deinit();

/**
 * @brief Runs IPC event-loop.
 * @param stop_status is used in order to understand the reason for stoping the adapter
 * This can be due to calling stop() , or due to other reasons
 * @return MblError returns value Error::None if function succeeded, 
 *         or error code otherwise.
 */
    MblError run(MblError &stop_status);

/**
 * @brief Stops IPC event-loop.
 * @param stop_status is used in order to understand the reason for stoping the adapter
 *  use MblError::DBUS_ADAPTER_STOP_STATUS_NO_ERROR by default (no error)
 * @return MblError returns value Error::None if function succeeded, 
 *         or error code otherwise.
 */
    MblError stop(MblError stop_status);

/**
 * @brief Sends registration request final status to the destination 
 * client application. 
 * This function sends a final status of the registration request, 
 * that was initiated by a client application via calling 
 * register_resources API. 
 * @param ipc_request_handle is a handle to the IPC unique connection information 
 *        of the application that should be notified.
 * @param reg_status status of registration of all resources. 
 *        reg_status is SUCCESS only if registration of all resources was 
 *        successfully finished, or error code otherwise.
 * 
 * @return MblError returns Error::None if the message was successfully 
 *         delivered, or error code otherwise. 
 */
    virtual MblError update_registration_status(
        const uintptr_t ipc_request_handle, 
        const CloudConnectStatus reg_status);

/**
 * @brief Sends deregistration request final status to the destination client 
 * application. This function sends a final status of the deregistration 
 * request, that was initiated by a client application via calling 
 * deregister_resources API. 
 * @param ipc_request_handle is a handle to the IPC unique connection information
 *        of the application that should be notified.
 * @param dereg_status status of deregistration of all resources. 
 *        dereg_status is SUCCESS only if deregistration of all resources was 
 *        successfully finished, or error code otherwise.
 * @return MblError returns Error::None if the message was successfully delivered, 
 *         or error code otherwise. 
 */
    MblError update_deregistration_status(
        const uintptr_t ipc_request_handle, 
        const CloudConnectStatus dereg_status);


/**
 * @brief 
 * Send 'deferred event' to the event loop using 
 * sd_event_add_defer(). Must be called by CCRB thread only. 
 * For more details: https://www.freedesktop.org/software/systemd/man/sd_event_add_defer.html#
 * @param data - the data to be sent, must be formatted according to the data_type
 * @param data_length - length of data used, must be less than the maximum size allowed
 * @param data_type - the type of data to be sent.
 * @param callback - callback to be called when event is fired
 * @param out_event_id  - generated event id (for debug or to cancel the event)
 * @param description - optional - description for the event cause, can leave empty string or 
 * not supply at all
 * @return MblError - return MblError - Error::None for success, therwise the failure reason
 */
    MblError send_event_immediate(
        SelfEvent::EventData data,
        unsigned long data_length,
        SelfEvent::EventDataType data_type,        
        SelfEventCallback callback,
        uint64_t &out_event_id,
        const std::string description);

private:
    // forward declaration - PIMPL implementation class - defined in cpp source file
    // unique pointer impl_ will automatically  destroy the object    
    std::unique_ptr<DBusAdapterImpl> impl_;    

    // No copying or moving 
    // (see: https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#cdefop-default-operations)
    DBusAdapter(const DBusAdapter&) = delete;
    DBusAdapter & operator = (const DBusAdapter&) = delete;
    DBusAdapter(DBusAdapter&&) = delete;
    DBusAdapter& operator = (DBusAdapter&&) = delete;    
};

} // namespace mbl

#endif // DBusAdapter_h_
