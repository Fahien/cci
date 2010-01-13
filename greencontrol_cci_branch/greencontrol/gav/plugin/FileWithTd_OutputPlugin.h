//   GreenControl framework
//
// LICENSETEXT
//
//   Copyright (C) 2007 : GreenSocs Ltd
// 	 http://www.greensocs.com/ , email: info@greensocs.com
//
//   Developed by :
//   
//   Christian Schroeder <schroeder@eis.cs.tu-bs.de>,
//   Wolfgang Klingauf <klingauf@eis.cs.tu-bs.de>
//     Technical University of Braunschweig, Dept. E.I.S.
//     http://www.eis.cs.tu-bs.de
//
//
//   This program is free software.
// 
//   If you have no applicable agreement with GreenSocs Ltd, this software
//   is licensed to you, and you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 2 of the License, or
//   (at your option) any later version.
// 
//   If you have a applicable agreement with GreenSocs Ltd, the terms of that
//   agreement prevail.
// 
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
// 
//   You should have received a copy of the GNU General Public License
//   along with this program; if not, write to the Free Software
//   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
//   02110-1301  USA 
// 
// ENDLICENSETEXT

#ifndef __FileWithTd_OutputPlugin_h__
#define __FileWithTd_OutputPlugin_h__

#include <time.h>
#include <stdio.h>
#include "OutputPlugin_base.h"
#include "gav_plugin.h"

#include <greensocket/generic/gs_quantumkeeper.h>

namespace gs {
namespace av {
      
  GAV_REGISTER_PLUGIN(12, TXT_TD_FILE_OUT, FileWithTd_OutputPlugin)
 
  /// Output Plugin which observes GreenConfig gs_param parameters and prints out changes to a human-readable text file
  class FileWithTd_OutputPlugin 
  : public OutputPlugin_base {
    
  public:
    
    /// Constructor with filename
    /**
     * Checks and manipulates the file name:
     * If the given file name has no extension (no dot in it)
     * the extension '.log' will be added automatically.
     *
     * Does NOT create the file etc.
     *
     * @param file_name  Filename of the output file.
     * @param ev_listn   Pointer to event listener that may be used by this.
     */
    FileWithTd_OutputPlugin(const char* file_name, event_listener<OutputPlugin_base> *ev_listn)
    : OutputPlugin_base(file_name, ev_listn, TXT_TD_FILE_OUT),
      filename(file_name)
    {
      // Check for any file extension
      std::string filename_str = filename;
      if (filename_str.find(".") == string::npos) {
        filename_str += ".log";
        filename = filename_str.c_str();
        GAV_DUMP_N(name(), "Add file extension: "<<filename.c_str());
      }
    }
    
  protected:
    /// Init function called on first usage, not called during construction!
    /**
     * Opens the file, prints time and date in it.
     */
    void init() {
      GAV_DUMP_N(name(), "Init Output Plugin: Open file '"<<filename.c_str()<<"' to write observed parameters to.");
      // create time
      time_t rawtime;
      struct tm * timeinfo;
      time ( &rawtime );
      timeinfo = localtime ( &rawtime );
      // write time to file
      outp_file = fopen(filename.c_str(), "w+t");
      fprintf (outp_file, "Simulation time: %s\n", asctime (timeinfo) );
    }
  public:
    
    /// Destructor
    ~FileWithTd_OutputPlugin() {
      if (is_used) {
        if ( fclose(outp_file) == -1 )
          SC_REPORT_ERROR(name(), "Closing output file failed!");
      }
    }

    /// Callback function
    void config_callback(gs_param_base &par) {
      // check for destructing parameters: remove them from callback list if removed
      if (par.is_destructing()) {
        remove(par);
      }
      // only perform output action when not paused (or stopped)
      else if (is_running) {
        fprintf(outp_file, "@%s (+ %s) /%d: ", sc_time_stamp().to_string().c_str(),
                gs::gs_quantumkeeper::getTD().to_string().c_str(), (unsigned)sc_delta_count());
        fprintf(outp_file, "%s = %s", par.getName().c_str(), par.getString().c_str()); 
        fprintf(outp_file, "\n");
      }
    }
    
    /// Special function to write a raw string to the file (needed by debug/system messages)
    void pure_output(const std::string& outp) {
      if (!is_used) { this->init(); is_used = true; } // needed because observe() may be not called
      if (is_running)
        fprintf(outp_file, "%s", outp.c_str());
    };
    
  protected:
    
    /// Output file pointer
    FILE *outp_file;
    
    /// Filename
    std::string filename;
    
  };
  
  
} // end namespace av
} // end namespace gs

#endif