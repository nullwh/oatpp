/***************************************************************************
 *
 * Project         _____    __   ____   _      _
 *                (  _  )  /__\ (_  _)_| |_  _| |_
 *                 )(_)(  /(__)\  )( (_   _)(_   _)
 *                (_____)(__)(__)(__)  |_|    |_|
 *
 *
 * Copyright 2018-present, Leonid Stryzhevskyi <lganzzzo@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ***************************************************************************/

#ifndef oatpp_web_protocol_CommunicationError_hpp
#define oatpp_web_protocol_CommunicationError_hpp

#include "oatpp/core/data/IODefinitions.hpp"

namespace oatpp { namespace web { namespace protocol {
  
class CommunicationError : public std::runtime_error {
private:
  oatpp::data::v_io_size m_ioStatus;
  oatpp::String m_message;
public:
  
  CommunicationError(oatpp::data::v_io_size ioStatus, const oatpp::String& message);
  oatpp::data::v_io_size getIOStatus();
  oatpp::String& getMessage();
  
};
  
template<class Status>
class ProtocolError : public CommunicationError {
public:
  
  struct Info {
    
    Info()
      : ioStatus(0)
    {}
    
    Info(oatpp::data::v_io_size pIOStatus, const Status& pStatus)
      : ioStatus(pIOStatus)
      , status(pStatus)
    {}
    
    oatpp::data::v_io_size ioStatus;
    Status status;
    
  };
  
private:
  Info m_info;
public:
  
  ProtocolError(const Info& info, const oatpp::String& message)
    : CommunicationError(info.ioStatus, message)
    , m_info(info)
  {}
  
  Info getInfo() {
    return m_info;
  }
  
};
  
}}}

#endif /* oatpp_web_protocol_CommunicationError_hpp */
