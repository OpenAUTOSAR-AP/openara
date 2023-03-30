/**
 * @file event_reporter.h
 * @author vin (vin@misday.com)
 * @brief
 * @version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) OpenAUTOSAR-AP 2023
 */

// R22-11

#pragma once

#include "common.h"

namespace ara
{
namespace idsm
{

// SWS_AIDSM_10101
/**
 * @brief Class for reporting security events to the IdsM .
 *
 */
class EventReporter
{

   // SWS_AIDSM_10301
   /**
    * @brief Construct a new Event Reporter object. Called by the sensor for each event type using the
    * instance specified of the event type .
    *
    * @param eventType InstanceSpecifier of the EventDefinition to be reported by this EventReporter object
    */
   EventReporter(const ara::core::Instance Specifier& eventType) noexcept;

   // SWS_AIDSM_10302
   /**
    * @brief Create a new security event at the IdsM.
    *
    * @param CountType
    */
   void ReportEvent(const CountType = 1) noexcept;

   // SWS_AIDSM_10303
   /**
    * @brief Create a new security event with a sensor-provided timestamp at the IdsM.
    *
    * @param timestamp application provided timestamp
    */
   void ReportEvent(const TimestampType timestamp, const CountType = 1) noexcept;

   // SWS_AIDSM_10304
   /**
    * @brief Create a new security event with sensor-provided context data at the IdsM.
    *
    * @param contextData context data
    */
   void ReportEvent(const ContextDataType& contextData, const CountType = 1) noexcept;

   // SWS_AIDSM_10305
   /**
    * @brief Create a new security event with sensor-provided context data and with a sensor-provided timestamp at the
    * IdsM.
    *
    * @param contextData context data
    * @param timestamp application provided timestamp
    */
   void ReportEvent(const ContextDataType& contextData, const TimestampType timestamp, const CountType = 1) noexcept;
};

} // namespace idsm
} // namespace ara