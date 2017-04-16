/*****************************************************************************

  Licensed to Accellera Systems Initiative Inc. (Accellera) under one or
  more contributor license agreements.  See the NOTICE file distributed
  with this work for additional information regarding copyright ownership.
  Accellera licenses this file to you under the Apache License, Version 2.0
  (the "License"); you may not use this file except in compliance with the
  License.  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
  implied.  See the License for the specific language governing
  permissions and limitations under the License.

 ****************************************************************************/

/**
 * @file   rapidjson.h
 * @brief  internal include file for the RapidJSON library
 * @author Philipp A. Hartmann, OFFIS/Intel
 *
 * This file provides a local indirection to include RapidJSON from within
 * the CCI library.  RapidJSON is used for serialization from/to
 * @ref cci_value.
 *
 * @note This file is @b not part of the public API!
 */

#ifndef CCI_RAPIDJSON_H_INCLUDED_
#define CCI_RAPIDJSON_H_INCLUDED_

///@cond CCI_HIDDEN_FROM_DOXYGEN

#include "cci_core/cci_cmnhdr.h"

#include <stdexcept>
#include <iosfwd>

// --------------------------------------------------------------------------
// configure RapidJSON

#define RAPIDJSON_NAMESPACE \
  CCI_NAMESPACE::rapidjson
#define RAPIDJSON_NAMESPACE_BEGIN \
  CCI_OPEN_NAMESPACE_ namespace rapidjson {
#define RAPIDJSON_NAMESPACE_END \
  } CCI_CLOSE_NAMESPACE_

// enable support for std::string
#define RAPIDJSON_HAS_STD_STRING 1

// parse floating point numbers with full precision
#define RAPIDJSON_PARSE_DEFAULT_FLAGS \
  ::RAPIDJSON_NAMESPACE::kParseFullPrecisionFlag

// don't use explicit member iterator class
#define RAPIDJSON_NOMEMBERITERATORCLASS 1

RAPIDJSON_NAMESPACE_BEGIN

struct AssertException
  : std::logic_error
{
  AssertException( const char* msg )
    : std::logic_error(msg) {}
};

// throw on failing assertions
#define RAPIDJSON_ASSERT( expr ) \
  ((void)(( expr ) ? 0 : \
    ( throw ::RAPIDJSON_NAMESPACE::AssertException( #expr ), 0 )))

RAPIDJSON_NAMESPACE_END

#include "rapidjson/rapidjson.h"

// throw exception by default
#define RAPIDJSON_PARSE_ERROR_EARLY_RETURN( what ) \
  ((void)0)
#define RAPIDJSON_PARSE_ERROR_NORETURN(parseErrorCode,offset) \
  throw ::RAPIDJSON_NAMESPACE::ParseException( \
               ::RAPIDJSON_NAMESPACE::parseErrorCode, \
               #parseErrorCode,offset \
  )

#include "rapidjson/error/error.h"
#include "rapidjson/error/en.h"

RAPIDJSON_NAMESPACE_BEGIN

struct ParseException
  : std::runtime_error, ParseResult
{
  ParseException( ParseErrorCode code, const char* msg, size_t offset )
     : std::runtime_error(msg), ParseResult(code,offset) {}
};

RAPIDJSON_NAMESPACE_END

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/ostreamwrapper.h"
#include "rapidjson/writer.h"

///@endcond

#endif // CCI_RAPIDJSON_H_INCLUDED_
