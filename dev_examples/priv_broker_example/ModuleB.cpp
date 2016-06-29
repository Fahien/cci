/*****************************************************************************
  Copyright 2016 Accellera Systems Initiative Inc.
  All rights reserved.

  Copyright 2009-2010 GreenSocs
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


#include "ModuleB.h"
#include <systemc.h>

ModuleB::ModuleB(sc_core::sc_module_name name)
: sc_core::sc_module(name)
, int_param ("int_param", 50, cci::cci_broker_manager::get_current_broker(cci::cci_originator(*this)) )
, uint_param("uint_param", 12000, cci::cci_broker_manager::get_current_broker(cci::cci_originator(*this)))
, uint_param2("uint_param2", 12, cci::cci_broker_manager::get_current_broker(cci::cci_originator(*this)))
, str_param ("str_param", "This is a test string.", cci::cci_broker_manager::get_current_broker(cci::cci_originator(*this)))
, bool_param("bool_param", false, cci::cci_broker_manager::get_current_broker(cci::cci_originator(*this))) // no default value
, mC("ModuleC", new cci::gs_cci_private_broker_accessor(*this, boost::assign::list_of("int_param")))
{ 
  SC_THREAD(main_action);

  // This needs to be done during construction (NOT within the sc_thread)!
  m_broker_accessor = &cci::cci_broker_manager::get_current_broker(cci::cci_originator(*this));
}

void ModuleB::main_action() {

  wait(10, SC_SEC);
  
  // show a parameter list
  cout << endl << "**** Parameter list (visible in "<<name()<<"): " << endl;
  std::vector<std::string> vec = m_broker_accessor->get_param_list();
  std::vector<std::string>::iterator iter;
  std::stringstream ss_show;
  for (iter = vec.begin() ; iter < vec.end(); iter++) {
    ss_show << "   " << *iter << std::endl;
  }
  std::cout << ss_show.str() << std::endl<<std::endl;
  
  std::cout << "----------------------------" << std::endl;

}
