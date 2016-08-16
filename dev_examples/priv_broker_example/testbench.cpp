/*****************************************************************************
  Copyright 2016 Accellera Systems Initiative Inc.
  All rights reserved.

  Copyright 2010 GreenSocs
  All rights reserved.
  Authors:
      Christian Schroeder <schroeder@eis.cs.tu-bs.de>
      Mark Burton <mark@greensocs.com>

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


#include <systemc>
#include <cci_configuration>
#include <boost/assign/list_of.hpp>
#include "ModuleA.h"
#include "ObserverModule.h"

class Top
: public sc_core::sc_module
{
  
public:
  
  SC_HAS_PROCESS(Top);
  Top(sc_core::sc_module_name name) {
    
    // Note: This would also be possible:
    // Private broker for Modules A and A2
    //   Parameters "ModuleA.int_param" and "ModuleA2.int_param" are public
    //top_privBroker = new cci::gs_cci_private_broker_accessor(*this, boost::assign::list_of("ModuleA.int_param")("ModuleA2.int_param"), cci::cci_originator(*this));
    
    // Private broker for Module A
    //   Parameter "ModuleA.int_param" is public
    moduleA_privBroker = new cci::gs_cci_private_broker_handle(*this, boost::assign::list_of("ModuleA.int_param"));
    a = new ModuleA("ModuleA", moduleA_privBroker);
    
    // Private broker for Module A2
    //   Parameter "ModuleA2.int_param" is public
    moduleA2_privBroker = new cci::gs_cci_private_broker_handle(*this, boost::assign::list_of("ModuleA2.int_param"));
    a2 = new ModuleA("ModuleA2", moduleA2_privBroker);
    
    observer = new ObserverModule("Observer");    
  }
  
  ~Top() {
    delete observer;
    delete a2;
    delete moduleA2_privBroker;
    delete a;
    delete moduleA_privBroker;
  }
  
protected:
  
  ModuleA* a;
  ModuleA* a2;
  ObserverModule* observer;
  
  cci::cci_broker_if* moduleA_privBroker;
  cci::cci_broker_if* moduleA2_privBroker;
  
};


/// Testbench for the CCI example application which uses the GreenSocs demo implemenation
int sc_main(int argc, char *argv[]) {
  //sc_core::sc_report_handler::set_actions(sc_core::SC_WARNING, sc_core::SC_ABORT);
  sc_core::sc_report_handler::set_actions(sc_core::SC_ERROR, sc_core::SC_ABORT);
  //sc_core::sc_report_handler::set_actions("/ASI/CCI/set_param_failed",  sc_core::SC_DISPLAY);
  //sc_core::sc_report_handler::set_actions("/ASI/CCI/cci_value_failure", sc_core::SC_DISPLAY);


  Top top("Top");

  std::cout << std::endl << "------ sc_start() ----------------" << std::endl << std::endl;
  sc_core::sc_start(); 
  std::cout << std::endl << "------ sc_start() returned -------" << std::endl << std::endl;
  
  return EXIT_SUCCESS; 
  
}


