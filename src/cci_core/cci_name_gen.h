/*****************************************************************************
  Copyright 2016 Accellera Systems Initiative Inc.
  All rights reserved.

  Copyright 2011 GreenSocs
  All rights reserved.
  Authors:
      Christian Schroeder <schroeder@eis.cs.tu-bs.de>

  Copyright 2016 Ericsson
  All rights reserved.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
 *****************************************************************************/

#ifndef CCI_CORE_CCI_NAME_GEN_H_INCLUDED_
#define CCI_CORE_CCI_NAME_GEN_H_INCLUDED_

#include "cci_cfg/cci_config_macros.h"

CCI_OPEN_NAMESPACE_

/// Generate a cci-wide unique name.
/**
 * Keeps the first name as it is, later adds _number, beginning with _0
 *
 * @param name name of the CCI element
 *
 * @return pointer to the name
 */
const char* cci_gen_unique_name(const char* name);

/// Get cci name pointer
/**
 * @param name name of the CCI element
 *
 * @return pointer to the name if exists or NULL if the name doesn't exist.
 */
const char* cci_get_name(const char* name);

CCI_CLOSE_NAMESPACE_

#endif