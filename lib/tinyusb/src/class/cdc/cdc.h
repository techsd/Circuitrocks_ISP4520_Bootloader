/**************************************************************************/
/*!
    @file     cdc.h
    @author   hathach (tinyusb.org)

    @section LICENSE

    Software License Agreement (BSD License)

    Copyright (c) 2013, hathach (tinyusb.org)
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holders nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

    This file is part of the tinyusb stack.
*/
/**************************************************************************/

/** \ingroup group_class
 *  \defgroup ClassDriver_CDC Communication Device Class (CDC)
 *            Currently only Abstract Control Model subclass is supported
 *  @{ */

#ifndef _TUSB_CDC_H__
#define _TUSB_CDC_H__

#include "common/tusb_common.h"

#ifdef __cplusplus
 extern "C" {
#endif

/** \defgroup ClassDriver_CDC_Common Common Definitions
 *  @{ */


/// CDC Pipe ID, used to indicate which pipe the API is addressing to (Notification, Out, In)
typedef enum
{
  CDC_PIPE_NOTIFICATION , ///< Notification pipe
  CDC_PIPE_DATA_IN      , ///< Data in pipe
  CDC_PIPE_DATA_OUT     , ///< Data out pipe
  CDC_PIPE_ERROR        , ///< Invalid Pipe ID
}cdc_pipeid_t;

//--------------------------------------------------------------------+
// CDC COMMUNICATION INTERFACE CLASS
//--------------------------------------------------------------------+
/// Communication Interface Subclass Codes
typedef enum
{
  CDC_COMM_SUBCLASS_DIRECT_LINE_CONTROL_MODEL = 0x01  , ///< Direct Line Control Model  [USBPSTN1.2]
  CDC_COMM_SUBCLASS_ABSTRACT_CONTROL_MODEL            , ///< Abstract Control Model  [USBPSTN1.2]
  CDC_COMM_SUBCLASS_TELEPHONE_CONTROL_MODEL           , ///< Telephone Control Model  [USBPSTN1.2]
  CDC_COMM_SUBCLASS_MULTICHANNEL_CONTROL_MODEL        , ///< Multi-Channel Control Model  [USBISDN1.2]
  CDC_COMM_SUBCLASS_CAPI_CONTROL_MODEL                , ///< CAPI Control Model  [USBISDN1.2]
  CDC_COMM_SUBCLASS_ETHERNET_NETWORKING_CONTROL_MODEL , ///< Ethernet Networking Control Model  [USBECM1.2]
  CDC_COMM_SUBCLASS_ATM_NETWORKING_CONTROL_MODEL      , ///< ATM Networking Control Model  [USBATM1.2]
  CDC_COMM_SUBCLASS_WIRELESS_HANDSET_CONTROL_MODEL    , ///< Wireless Handset Control Model  [USBWMC1.1]
  CDC_COMM_SUBCLASS_DEVICE_MANAGEMENT                 , ///< Device Management  [USBWMC1.1]
  CDC_COMM_SUBCLASS_MOBILE_DIRECT_LINE_MODEL          , ///< Mobile Direct Line Model  [USBWMC1.1]
  CDC_COMM_SUBCLASS_OBEX                              , ///< OBEX  [USBWMC1.1]
  CDC_COMM_SUBCLASS_ETHERNET_EMULATION_MODEL            ///< Ethernet Emulation Model  [USBEEM1.0]
} cdc_comm_sublcass_type_t;

/// Communication Interface Protocol Codes
typedef enum
{
  CDC_COMM_PROTOCOL_NONE                   = 0x00 , ///< No specific protocol
  CDC_COMM_PROTOCOL_ATCOMMAND                     , ///< AT Commands: V.250 etc
  CDC_COMM_PROTOCOL_ATCOMMAND_PCCA_101            , ///< AT Commands defined by PCCA-101
  CDC_COMM_PROTOCOL_ATCOMMAND_PCCA_101_AND_ANNEXO , ///< AT Commands defined by PCCA-101 & Annex O
  CDC_COMM_PROTOCOL_ATCOMMAND_GSM_707             , ///< AT Commands defined by GSM 07.07
  CDC_COMM_PROTOCOL_ATCOMMAND_3GPP_27007          , ///< AT Commands defined by 3GPP 27.007
  CDC_COMM_PROTOCOL_ATCOMMAND_CDMA                , ///< AT Commands defined by TIA for CDMA
  CDC_COMM_PROTOCOL_ETHERNET_EMULATION_MODEL        ///< Ethernet Emulation Model
} cdc_comm_protocol_type_t;

//------------- SubType Descriptor in COMM Functional Descriptor -------------//
/// Communication Interface SubType Descriptor
typedef enum
{
  CDC_FUNC_DESC_HEADER                                           = 0x00 , ///< Header Functional Descriptor, which marks the beginning of the concatenated set of functional descriptors for the interface.
  CDC_FUNC_DESC_CALL_MANAGEMENT                                  = 0x01 , ///< Call Management Functional Descriptor.
  CDC_FUNC_DESC_ABSTRACT_CONTROL_MANAGEMENT                      = 0x02 , ///< Abstract Control Management Functional Descriptor.
  CDC_FUNC_DESC_DIRECT_LINE_MANAGEMENT                           = 0x03 , ///< Direct Line Management Functional Descriptor.
  CDC_FUNC_DESC_TELEPHONE_RINGER                                 = 0x04 , ///< Telephone Ringer Functional Descriptor.
  CDC_FUNC_DESC_TELEPHONE_CALL_AND_LINE_STATE_REPORTING_CAPACITY = 0x05 , ///< Telephone Call and Line State Reporting Capabilities Functional Descriptor.
  CDC_FUNC_DESC_UNION                                            = 0x06 , ///< Union Functional Descriptor
  CDC_FUNC_DESC_COUNTRY_SELECTION                                = 0x07 , ///< Country Selection Functional Descriptor
  CDC_FUNC_DESC_TELEPHONE_OPERATIONAL_MODES                      = 0x08 , ///< Telephone Operational ModesFunctional Descriptor
  CDC_FUNC_DESC_USB_TERMINAL                                     = 0x09 , ///< USB Terminal Functional Descriptor
  CDC_FUNC_DESC_NETWORK_CHANNEL_TERMINAL                         = 0x0A , ///< Network Channel Terminal Descriptor
  CDC_FUNC_DESC_PROTOCOL_UNIT                                    = 0x0B , ///< Protocol Unit Functional Descriptor
  CDC_FUNC_DESC_EXTENSION_UNIT                                   = 0x0C , ///< Extension Unit Functional Descriptor
  CDC_FUNC_DESC_MULTICHANEL_MANAGEMENT                           = 0x0D , ///< Multi-Channel Management Functional Descriptor
  CDC_FUNC_DESC_CAPI_CONTROL_MANAGEMENT                          = 0x0E , ///< CAPI Control Management Functional Descriptor
  CDC_FUNC_DESC_ETHERNET_NETWORKING                              = 0x0F , ///< Ethernet Networking Functional Descriptor
  CDC_FUNC_DESC_ATM_NETWORKING                                   = 0x10 , ///< ATM Networking Functional Descriptor
  CDC_FUNC_DESC_WIRELESS_HANDSET_CONTROL_MODEL                   = 0x11 , ///< Wireless Handset Control Model Functional Descriptor
  CDC_FUNC_DESC_MOBILE_DIRECT_LINE_MODEL                         = 0x12 , ///< Mobile Direct Line Model Functional Descriptor
  CDC_FUNC_DESC_MOBILE_DIRECT_LINE_MODEL_DETAIL                  = 0x13 , ///< MDLM Detail Functional Descriptor
  CDC_FUNC_DESC_DEVICE_MANAGEMENT_MODEL                          = 0x14 , ///< Device Management Model Functional Descriptor
  CDC_FUNC_DESC_OBEX                                             = 0x15 , ///< OBEX Functional Descriptor
  CDC_FUNC_DESC_COMMAND_SET                                      = 0x16 , ///< Command Set Functional Descriptor
  CDC_FUNC_DESC_COMMAND_SET_DETAIL                               = 0x17 , ///< Command Set Detail Functional Descriptor
  CDC_FUNC_DESC_TELEPHONE_CONTROL_MODEL                          = 0x18 , ///< Telephone Control Model Functional Descriptor
  CDC_FUNC_DESC_OBEX_SERVICE_IDENTIFIER                          = 0x19   ///< OBEX Service Identifier Functional Descriptor
}cdc_func_desc_type_t;

//--------------------------------------------------------------------+
// CDC DATA INTERFACE CLASS
//--------------------------------------------------------------------+

// SUBCLASS code of Data Interface is not used and should/must be zero
/// Data Interface Protocol Codes
typedef enum{
  CDC_DATA_PROTOCOL_ISDN_BRI                               = 0x30, ///< Physical interface protocol for ISDN BRI
  CDC_DATA_PROTOCOL_HDLC                                   = 0x31, ///< HDLC
  CDC_DATA_PROTOCOL_TRANSPARENT                            = 0x32, ///< Transparent
  CDC_DATA_PROTOCOL_Q921_MANAGEMENT                        = 0x50, ///< Management protocol for Q.921 data link protocol
  CDC_DATA_PROTOCOL_Q921_DATA_LINK                         = 0x51, ///< Data link protocol for Q.931
  CDC_DATA_PROTOCOL_Q921_TEI_MULTIPLEXOR                   = 0x52, ///< TEI-multiplexor for Q.921 data link protocol
  CDC_DATA_PROTOCOL_V42BIS_DATA_COMPRESSION                = 0x90, ///< Data compression procedures
  CDC_DATA_PROTOCOL_EURO_ISDN                              = 0x91, ///< Euro-ISDN protocol control
  CDC_DATA_PROTOCOL_V24_RATE_ADAPTION_TO_ISDN              = 0x92, ///< V.24 rate adaptation to ISDN
  CDC_DATA_PROTOCOL_CAPI_COMMAND                           = 0x93, ///< CAPI Commands
  CDC_DATA_PROTOCOL_HOST_BASED_DRIVER                      = 0xFD, ///< Host based driver. Note: This protocol code should only be used in messages between host and device to identify the host driver portion of a protocol stack.
  CDC_DATA_PROTOCOL_IN_PROTOCOL_UNIT_FUNCTIONAL_DESCRIPTOR = 0xFE  ///< The protocol(s) are described using a ProtocolUnit Functional Descriptors on Communications Class Interface
}cdc_data_protocol_type_t;

//--------------------------------------------------------------------+
// MANAGEMENT ELEMENT REQUEST (CONTROL ENDPOINT)
//--------------------------------------------------------------------+
/// Communication Interface Management Element Request Codes
typedef enum
{
  CDC_REQUEST_SEND_ENCAPSULATED_COMMAND                    = 0x00, ///< is used to issue a command in the format of the supported control protocol of the Communications Class interface
  CDC_REQUEST_GET_ENCAPSULATED_RESPONSE                    = 0x01, ///< is used to request a response in the format of the supported control protocol of the Communications Class interface.

  CDC_REQUEST_SET_COMM_FEATURE                             = 0x02,
  CDC_REQUEST_GET_COMM_FEATURE                             = 0x03,
  CDC_REQUEST_CLEAR_COMM_FEATURE                           = 0x04,

  CDC_REQUEST_SET_AUX_LINE_STATE                           = 0x10,
  CDC_REQUEST_SET_HOOK_STATE                               = 0x11,
  CDC_REQUEST_PULSE_SETUP                                  = 0x12,
  CDC_REQUEST_SEND_PULSE                                   = 0x13,
  CDC_REQUEST_SET_PULSE_TIME                               = 0x14,
  CDC_REQUEST_RING_AUX_JACK                                = 0x15,

  CDC_REQUEST_SET_LINE_CODING                              = 0x20,
  CDC_REQUEST_GET_LINE_CODING                              = 0x21,
  CDC_REQUEST_SET_CONTROL_LINE_STATE                       = 0x22,
  CDC_REQUEST_SEND_BREAK                                   = 0x23,

  CDC_REQUEST_SET_RINGER_PARMS                             = 0x30,
  CDC_REQUEST_GET_RINGER_PARMS                             = 0x31,
  CDC_REQUEST_SET_OPERATION_PARMS                          = 0x32,
  CDC_REQUEST_GET_OPERATION_PARMS                          = 0x33,
  CDC_REQUEST_SET_LINE_PARMS                               = 0x34,
  CDC_REQUEST_GET_LINE_PARMS                               = 0x35,
  CDC_REQUEST_DIAL_DIGITS                                  = 0x36,
  CDC_REQUEST_SET_UNIT_PARAMETER                           = 0x37,
  CDC_REQUEST_GET_UNIT_PARAMETER                           = 0x38,
  CDC_REQUEST_CLEAR_UNIT_PARAMETER                         = 0x39,
  CDC_REQUEST_GET_PROFILE                                  = 0x3A,

  CDC_REQUEST_SET_ETHERNET_MULTICAST_FILTERS               = 0x40,
  CDC_REQUEST_SET_ETHERNET_POWER_MANAGEMENT_PATTERN_FILTER = 0x41,
  CDC_REQUEST_GET_ETHERNET_POWER_MANAGEMENT_PATTERN_FILTER = 0x42,
  CDC_REQUEST_SET_ETHERNET_PACKET_FILTER                   = 0x43,
  CDC_REQUEST_GET_ETHERNET_STATISTIC                       = 0x44,

  CDC_REQUEST_SET_ATM_DATA_FORMAT                          = 0x50,
  CDC_REQUEST_GET_ATM_DEVICE_STATISTICS                    = 0x51,
  CDC_REQUEST_SET_ATM_DEFAULT_VC                           = 0x52,
  CDC_REQUEST_GET_ATM_VC_STATISTICS                        = 0x53,

  CDC_REQUEST_MDLM_SEMANTIC_MODEL                          = 0x60,
}cdc_management_request_t;

//--------------------------------------------------------------------+
// MANAGEMENT ELEMENENT NOTIFICATION (NOTIFICATION ENDPOINT)
//--------------------------------------------------------------------+
/// Communication Interface Management Element Notification Codes
typedef enum
{
  NETWORK_CONNECTION               = 0x00, ///< This notification allows the device to notify the host about network connection status.
  RESPONSE_AVAILABLE               = 0x01, ///< This notification allows the device to notify the hostthat a response is available. This response can be retrieved with a subsequent \ref CDC_REQUEST_GET_ENCAPSULATED_RESPONSE request.

  AUX_JACK_HOOK_STATE              = 0x08,
  RING_DETECT                      = 0x09,

  SERIAL_STATE                     = 0x20,

  CALL_STATE_CHANGE                = 0x28,
  LINE_STATE_CHANGE                = 0x29,
  CONNECTION_SPEED_CHANGE          = 0x2A, ///< This notification allows the device to inform the host-networking driver that a change in either the upstream or the downstream bit rate of the connection has occurred
  MDLM_SEMANTIC_MODEL_NOTIFICATION = 0x40,
}cdc_notification_request_t;

//--------------------------------------------------------------------+
// FUNCTIONAL DESCRIPTOR (COMMUNICATION INTERFACE)
//--------------------------------------------------------------------+
/// Header Functional Descriptor (Communication Interface)
typedef struct ATTR_PACKED
{
  uint8_t bLength            ; ///< Size of this descriptor in bytes.
  uint8_t bDescriptorType    ; ///< Descriptor Type, must be Class-Specific
  uint8_t bDescriptorSubType ; ///< Descriptor SubType one of above CDC_FUCN_DESC_
  uint16_t bcdCDC            ; ///< CDC release number in Binary-Coded Decimal
}cdc_desc_func_header_t;

/// Union Functional Descriptor (Communication Interface)
typedef struct ATTR_PACKED
{
  uint8_t bLength                  ; ///< Size of this descriptor in bytes.
  uint8_t bDescriptorType          ; ///< Descriptor Type, must be Class-Specific
  uint8_t bDescriptorSubType       ; ///< Descriptor SubType one of above CDC_FUCN_DESC_
  uint8_t bControlInterface        ; ///< Interface number of Communication Interface
  uint8_t bSubordinateInterface    ; ///< Array of Interface number of Data Interface
}cdc_desc_func_union_t;

#define cdc_desc_func_union_n_t(no_slave)\
 struct ATTR_PACKED { \
  uint8_t bLength                         ;\
  uint8_t bDescriptorType                 ;\
  uint8_t bDescriptorSubType              ;\
  uint8_t bControlInterface               ;\
  uint8_t bSubordinateInterface[no_slave] ;\
}

/// Country Selection Functional Descriptor (Communication Interface)
typedef struct ATTR_PACKED
{
  uint8_t bLength             ; ///< Size of this descriptor in bytes.
  uint8_t bDescriptorType     ; ///< Descriptor Type, must be Class-Specific
  uint8_t bDescriptorSubType  ; ///< Descriptor SubType one of above CDC_FUCN_DESC_
  uint8_t iCountryCodeRelDate ; ///< Index of a string giving the release date for the implemented ISO 3166 Country Codes.
  uint16_t wCountryCode[]     ; ///< Country code in the format as defined in [ISO3166], release date as specified inoffset 3 for the first supported country.
}cdc_desc_func_country_selection_t;

#define cdc_desc_func_country_selection_n_t(no_country) \
  struct ATTR_PACKED {\
  uint8_t bLength                   ;\
  uint8_t bDescriptorType           ;\
  uint8_t bDescriptorSubType        ;\
  uint8_t iCountryCodeRelDate       ;\
  uint16_t wCountryCode[no_country] ;\
}

//--------------------------------------------------------------------+
// PUBLIC SWITCHED TELEPHONE NETWORK (PSTN) SUBCLASS
//--------------------------------------------------------------------+

/// \brief Call Management Functional Descriptor
/// \details This functional descriptor describes the processing of calls for the Communications Class interface.
typedef struct ATTR_PACKED
{
  uint8_t bLength            ; ///< Size of this descriptor in bytes.
  uint8_t bDescriptorType    ; ///< Descriptor Type, must be Class-Specific
  uint8_t bDescriptorSubType ; ///< Descriptor SubType one of above CDC_FUCN_DESC_

  struct {
    uint8_t handle_call    : 1; ///< 0 - Device sends/receives call management information only over the Communications Class interface. 1 - Device can send/receive call management information over a Data Class interface.
    uint8_t send_recv_call : 1; ///< 0 - Device does not handle call management itself. 1 - Device handles call management itself.
    uint8_t : 0;
  } bmCapabilities;

  uint8_t bDataInterface;
}cdc_desc_func_call_management_t;


typedef struct ATTR_PACKED
{
  uint8_t support_comm_request                    : 1; ///< Device supports the request combination of Set_Comm_Feature, Clear_Comm_Feature, and Get_Comm_Feature.
  uint8_t support_line_request                    : 1; ///< Device supports the request combination of Set_Line_Coding, Set_Control_Line_State, Get_Line_Coding, and the notification Serial_State.
  uint8_t support_send_break                      : 1; ///< Device supports the request Send_Break
  uint8_t support_notification_network_connection : 1; ///< Device supports the notification Network_Connection.
  uint8_t : 0;
}cdc_acm_capability_t;

TU_VERIFY_STATIC(sizeof(cdc_acm_capability_t) == 1, "mostly problem with compiler");

/// \brief Abstract Control Management Functional Descriptor
/// \details This functional descriptor describes the commands supported by by the Communications Class interface with SubClass code of \ref CDC_COMM_SUBCLASS_ABSTRACT_CONTROL_MODEL
typedef struct ATTR_PACKED
{
  uint8_t bLength                  ; ///< Size of this descriptor in bytes.
  uint8_t bDescriptorType          ; ///< Descriptor Type, must be Class-Specific
  uint8_t bDescriptorSubType       ; ///< Descriptor SubType one of above CDC_FUCN_DESC_
  cdc_acm_capability_t bmCapabilities ;
}cdc_desc_func_acm_t;

/// \brief Direct Line Management Functional Descriptor
/// \details This functional descriptor describes the commands supported by the Communications Class interface with SubClass code of \ref CDC_FUNC_DESC_DIRECT_LINE_MANAGEMENT
typedef struct ATTR_PACKED
{
  uint8_t bLength            ; ///< Size of this descriptor in bytes.
  uint8_t bDescriptorType    ; ///< Descriptor Type, must be Class-Specific
  uint8_t bDescriptorSubType ; ///< Descriptor SubType one of above CDC_FUCN_DESC_
  struct {
    uint8_t require_pulse_setup   : 1; ///< Device requires extra Pulse_Setup request during pulse dialing sequence to disengage holding circuit.
    uint8_t support_aux_request   : 1; ///< Device supports the request combination of Set_Aux_Line_State, Ring_Aux_Jack, and notification Aux_Jack_Hook_State.
    uint8_t support_pulse_request : 1; ///< Device supports the request combination of Pulse_Setup, Send_Pulse, and Set_Pulse_Time.
    uint8_t : 0;
  } bmCapabilities;
}cdc_desc_func_direct_line_management_t;

/// \brief Telephone Ringer Functional Descriptor
/// \details The Telephone Ringer functional descriptor describes the ringer capabilities supported by the Communications Class interface,
/// with the SubClass code of \ref CDC_COMM_SUBCLASS_TELEPHONE_CONTROL_MODEL
typedef struct ATTR_PACKED
{
  uint8_t bLength            ; ///< Size of this descriptor in bytes.
  uint8_t bDescriptorType    ; ///< Descriptor Type, must be Class-Specific
  uint8_t bDescriptorSubType ; ///< Descriptor SubType one of above CDC_FUCN_DESC_
  uint8_t bRingerVolSteps    ;
  uint8_t bNumRingerPatterns ;
}cdc_desc_func_telephone_ringer_t;

/// \brief Telephone Operational Modes Functional Descriptor
/// \details The Telephone Operational Modes functional descriptor describes the operational modes supported by
/// the Communications Class interface, with the SubClass code of \ref CDC_COMM_SUBCLASS_TELEPHONE_CONTROL_MODEL
typedef struct ATTR_PACKED
{
  uint8_t bLength            ; ///< Size of this descriptor in bytes.
  uint8_t bDescriptorType    ; ///< Descriptor Type, must be Class-Specific
  uint8_t bDescriptorSubType ; ///< Descriptor SubType one of above CDC_FUCN_DESC_
  struct {
    uint8_t simple_mode           : 1;
    uint8_t standalone_mode       : 1;
    uint8_t computer_centric_mode : 1;
    uint8_t : 0;
  } bmCapabilities;
}cdc_desc_func_telephone_operational_modes_t;

/// \brief Telephone Call and Line State Reporting Capabilities Descriptor
/// \details The Telephone Call and Line State Reporting Capabilities functional descriptor describes the abilities of a
/// telephone device to report optional call and line states.
typedef struct ATTR_PACKED
{
  uint8_t bLength            ; ///< Size of this descriptor in bytes.
  uint8_t bDescriptorType    ; ///< Descriptor Type, must be Class-Specific
  uint8_t bDescriptorSubType ; ///< Descriptor SubType one of above CDC_FUCN_DESC_
  struct {
    uint32_t interrupted_dialtone   : 1; ///< 0 : Reports only dialtone (does not differentiate between normal and interrupted dialtone). 1 : Reports interrupted dialtone in addition to normal dialtone
    uint32_t ringback_busy_fastbusy : 1; ///< 0 : Reports only dialing state. 1 : Reports ringback, busy, and fast busy states.
    uint32_t caller_id              : 1; ///< 0 : Does not report caller ID. 1 : Reports caller ID information.
    uint32_t incoming_distinctive   : 1; ///< 0 : Reports only incoming ringing. 1 : Reports incoming distinctive ringing patterns.
    uint32_t dual_tone_multi_freq   : 1; ///< 0 : Cannot report dual tone multi-frequency (DTMF) digits input remotely over the telephone line. 1 : Can report DTMF digits input remotely over the telephone line.
    uint32_t line_state_change      : 1; ///< 0 : Does not support line state change notification. 1 : Does support line state change notification
    uint32_t : 0;
  } bmCapabilities;
}cdc_desc_func_telephone_call_state_reporting_capabilities_t;

static inline uint8_t cdc_functional_desc_typeof(uint8_t const * p_desc)
{
  return p_desc[2];
}

//--------------------------------------------------------------------+
// Requests
//--------------------------------------------------------------------+
typedef struct ATTR_PACKED
{
  uint32_t bit_rate;
  uint8_t  stop_bits; ///< 0: 1 stop bit - 1: 1.5 stop bits - 2: 2 stop bits
  uint8_t  parity;    ///< 0: None - 1: Odd - 2: Even - 3: Mark - 4: Space
  uint8_t  data_bits; ///< can be 5, 6, 7, 8 or 16
} cdc_line_coding_t;

TU_VERIFY_STATIC(sizeof(cdc_line_coding_t) == 7, "size is not correct");

typedef struct ATTR_PACKED
{
  uint16_t dte_is_present : 1; ///< Indicates to DCE if DTE is presentor not. This signal corresponds to V.24 signal 108/2 and RS-232 signal DTR.
  uint16_t half_duplex_carrier_control : 1;
  uint16_t : 14;
} cdc_line_control_state_t;

TU_VERIFY_STATIC(sizeof(cdc_line_control_state_t) == 2, "size is not correct");

/** @} */

#ifdef __cplusplus
 }
#endif

#endif

/** @} */
