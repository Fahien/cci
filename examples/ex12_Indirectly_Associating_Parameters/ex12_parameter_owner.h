/*****************************************************************************
  Copyright 2006-2014 Accellera Systems Initiative Inc.
  All rights reserved.

  Copyright 2010-2015 CircuitSutra Technologies Pvt. Ltd.
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

/**
 * @file      parameter_owner.h
 * @brief     This file contains the code which defines the OWNER module and its contents.
 *            The owner module is instantiated by the TOP_MODULE
 * @author    P V S Phaneendra, CircuitSutra Technologies   <pvs@circuitsutra.com>
 * @date      9th June, 2011 (Thursday)
 */

#ifndef EXAMPLES_EX12_INDIRECTLY_ASSOCIATING_PARAMETERS_EX12_PARAMETER_OWNER_H_
#define EXAMPLES_EX12_INDIRECTLY_ASSOCIATING_PARAMETERS_EX12_PARAMETER_OWNER_H_

#include <cci>
#include <string>
#include "xreport.hpp"

/// This module declares the cci_parameters and the are  created based on the
/// names passed from the top module
SC_MODULE(ex12_parameter_owner) {
 public:
  SC_HAS_PROCESS(ex12_parameter_owner);

  ex12_parameter_owner(sc_core::sc_module_name _name,
                       std::string _param_name = "clock_speed_KHz",
                       double _freq = 10.0)
      : sc_module(_name) {
    clk = new cci::cnf::cci_param<double>(_param_name.c_str(), _freq);

    XREPORT("[OWNER C_TOR] : Parameter Name   : " << clk->get_name()
            << "\tParameter Value : " << clk->get());
  }

 private:
  // Declare an instance of mutable CCI parameter of type 'double'
  cci::cnf::cci_param<double>* clk;
};
// ex12_parameter_owner

#endif  // EXAMPLES_EX12_INDIRECTLY_ASSOCIATING_PARAMETERS_EX12_PARAMETER_OWNER_H_
