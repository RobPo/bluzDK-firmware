/*
 * Copyright (c) Nordic Semiconductor ASA
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 *   1. Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 *   2. Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 *   3. Neither the name of Nordic Semiconductor ASA nor the names of other
 *   contributors to this software may be used to endorse or promote products
 *   derived from this software without specific prior written permission.
 *
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**@file
 *
 * @defgroup ant_stack_handler_types Types definitions for ANT support in SoftDevice handler.
 * @{
 * @ingroup  softdevice_handler
 * @brief    This file contains the declarations of types required for ANT stack support. These
 *           types will be defined when the preprocessor define ANT_STACK_SUPPORT_REQD is defined.
 */

#ifndef ANT_STACK_HANDLER_TYPES_H__
#define ANT_STACK_HANDLER_TYPES_H__

#ifdef ANT_STACK_SUPPORT_REQD

#include <stdlib.h>

#define ANT_STACK_EVT_MSG_BUF_SIZE      32                                                /**< Size of ANT event message buffer. This will be provided to the SoftDevice while fetching an event. */
#define ANT_STACK_EVT_STRUCT_SIZE       (sizeof(ant_evt_t))                               /**< Size of the @ref ant_evt_t structure. This will be used by the @ref softdevice_handler to internal event buffer size needed. */

/**@brief ANT stack event type. */
typedef struct
{
    uint8_t channel;                                                                      /**< Channel number. */
    uint8_t event;                                                                        /**< Event code. */
    uint8_t evt_buffer[ANT_STACK_EVT_MSG_BUF_SIZE];                                       /**< Event message buffer. */
} ant_evt_t;

/**@brief Application ANT stack event handler type. */
typedef void (*ant_evt_handler_t) (ant_evt_t * p_ant_evt);

/**@brief     Function for registering for ANT events.
 *
 * @details   The application should use this function to register for receiving ANT events from
 *            the SoftDevice. If the application does not call this function, then any ANT event
 *            that may be generated by the SoftDevice will NOT be fetched. Once the application has
 *            registered for the events, it is not possible to  possible to cancel the registration.
 *            However, it is possible to register a different function for handling the events at
 *            any point of time.
 *
 * @param[in] ant_evt_handler Function to be called for each received ANT event.
 *
 * @retval    NRF_SUCCESS     Successful registration.
 * @retval    NRF_ERROR_NULL  Null pointer provided as input.
 */
uint32_t softdevice_ant_evt_handler_set(ant_evt_handler_t ant_evt_handler);

#else

// The ANT Stack support is not required.

#define ANT_STACK_EVT_STRUCT_SIZE       0                                                 /**< Since the ANT stack support is not required, this is equated to 0, so that the @ref softdevice_handler.h can compute the internal event buffer size without having to care for ANT events.*/

#endif // ANT_STACK_SUPPORT_REQD

#endif // ANT_STACK_HANDLER_TYPES_H__

/** @} */
