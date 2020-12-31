#include <systemc>
#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <stdint.h>
#include "SysCFileHandler.h"
#include "ap_int.h"
#include "ap_fixed.h"
#include <complex>
#include <stdbool.h>
#include "autopilot_cbe.h"
#include "hls_stream.h"
#include "hls_half.h"
#include "hls_signal_handler.h"

using namespace std;
using namespace sc_core;
using namespace sc_dt;

// wrapc file define:
#define AUTOTB_TVIN_gmem "../tv/cdatafile/c.EthInTop.autotvin_gmem.dat"
#define AUTOTB_TVOUT_gmem "../tv/cdatafile/c.EthInTop.autotvout_gmem.dat"
// wrapc file define:
#define AUTOTB_TVIN_in "../tv/cdatafile/c.EthInTop.autotvin_in_r.dat"
#define AUTOTB_TVOUT_in "../tv/cdatafile/c.EthInTop.autotvout_in_r.dat"
// wrapc file define:
#define AUTOTB_TVIN_buffSize "../tv/cdatafile/c.EthInTop.autotvin_buffSize.dat"
#define AUTOTB_TVOUT_buffSize "../tv/cdatafile/c.EthInTop.autotvout_buffSize.dat"
// wrapc file define:
#define AUTOTB_TVIN_keep "../tv/cdatafile/c.EthInTop.autotvin_keep.dat"
#define AUTOTB_TVOUT_keep "../tv/cdatafile/c.EthInTop.autotvout_keep.dat"
// wrapc file define:
#define AUTOTB_TVIN_ethernet_stream_out_V_data_V "../tv/cdatafile/c.EthInTop.autotvin_ethernet_stream_out_V_data_V.dat"
#define AUTOTB_TVOUT_ethernet_stream_out_V_data_V "../tv/cdatafile/c.EthInTop.autotvout_ethernet_stream_out_V_data_V.dat"
#define AUTOTB_TVIN_ethernet_stream_out_V_keep_V "../tv/cdatafile/c.EthInTop.autotvin_ethernet_stream_out_V_keep_V.dat"
#define AUTOTB_TVOUT_ethernet_stream_out_V_keep_V "../tv/cdatafile/c.EthInTop.autotvout_ethernet_stream_out_V_keep_V.dat"
#define AUTOTB_TVIN_ethernet_stream_out_V_strb_V "../tv/cdatafile/c.EthInTop.autotvin_ethernet_stream_out_V_strb_V.dat"
#define AUTOTB_TVOUT_ethernet_stream_out_V_strb_V "../tv/cdatafile/c.EthInTop.autotvout_ethernet_stream_out_V_strb_V.dat"
#define AUTOTB_TVIN_ethernet_stream_out_V_last_V "../tv/cdatafile/c.EthInTop.autotvin_ethernet_stream_out_V_last_V.dat"
#define AUTOTB_TVOUT_ethernet_stream_out_V_last_V "../tv/cdatafile/c.EthInTop.autotvout_ethernet_stream_out_V_last_V.dat"
#define WRAPC_STREAM_SIZE_OUT_ethernet_stream_out_V_data_V "../tv/stream_size/stream_size_out_ethernet_stream_out_V_data_V.dat"
#define WRAPC_STREAM_EGRESS_STATUS_ethernet_stream_out_V_data_V "../tv/stream_size/stream_egress_status_ethernet_stream_out_V_data_V.dat"
#define WRAPC_STREAM_SIZE_OUT_ethernet_stream_out_V_keep_V "../tv/stream_size/stream_size_out_ethernet_stream_out_V_keep_V.dat"
#define WRAPC_STREAM_EGRESS_STATUS_ethernet_stream_out_V_keep_V "../tv/stream_size/stream_egress_status_ethernet_stream_out_V_keep_V.dat"
#define WRAPC_STREAM_SIZE_OUT_ethernet_stream_out_V_strb_V "../tv/stream_size/stream_size_out_ethernet_stream_out_V_strb_V.dat"
#define WRAPC_STREAM_EGRESS_STATUS_ethernet_stream_out_V_strb_V "../tv/stream_size/stream_egress_status_ethernet_stream_out_V_strb_V.dat"
#define WRAPC_STREAM_SIZE_OUT_ethernet_stream_out_V_last_V "../tv/stream_size/stream_size_out_ethernet_stream_out_V_last_V.dat"
#define WRAPC_STREAM_EGRESS_STATUS_ethernet_stream_out_V_last_V "../tv/stream_size/stream_egress_status_ethernet_stream_out_V_last_V.dat"

#define INTER_TCL "../tv/cdatafile/ref.tcl"

// tvout file define:
#define AUTOTB_TVOUT_PC_gmem "../tv/rtldatafile/rtl.EthInTop.autotvout_gmem.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_in "../tv/rtldatafile/rtl.EthInTop.autotvout_in_r.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_buffSize "../tv/rtldatafile/rtl.EthInTop.autotvout_buffSize.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_keep "../tv/rtldatafile/rtl.EthInTop.autotvout_keep.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_ethernet_stream_out_V_data_V "../tv/rtldatafile/rtl.EthInTop.autotvout_ethernet_stream_out_V_data_V.dat"
#define AUTOTB_TVOUT_PC_ethernet_stream_out_V_keep_V "../tv/rtldatafile/rtl.EthInTop.autotvout_ethernet_stream_out_V_keep_V.dat"
#define AUTOTB_TVOUT_PC_ethernet_stream_out_V_strb_V "../tv/rtldatafile/rtl.EthInTop.autotvout_ethernet_stream_out_V_strb_V.dat"
#define AUTOTB_TVOUT_PC_ethernet_stream_out_V_last_V "../tv/rtldatafile/rtl.EthInTop.autotvout_ethernet_stream_out_V_last_V.dat"

class INTER_TCL_FILE {
  public:
INTER_TCL_FILE(const char* name) {
  mName = name; 
  gmem_depth = 0;
  in_depth = 0;
  buffSize_depth = 0;
  keep_depth = 0;
  ethernet_stream_out_V_data_V_depth = 0;
  ethernet_stream_out_V_keep_V_depth = 0;
  ethernet_stream_out_V_strb_V_depth = 0;
  ethernet_stream_out_V_last_V_depth = 0;
  trans_num =0;
}
~INTER_TCL_FILE() {
  mFile.open(mName);
  if (!mFile.good()) {
    cout << "Failed to open file ref.tcl" << endl;
    exit (1); 
  }
  string total_list = get_depth_list();
  mFile << "set depth_list {\n";
  mFile << total_list;
  mFile << "}\n";
  mFile << "set trans_num "<<trans_num<<endl;
  mFile.close();
}
string get_depth_list () {
  stringstream total_list;
  total_list << "{gmem " << gmem_depth << "}\n";
  total_list << "{in_r " << in_depth << "}\n";
  total_list << "{buffSize " << buffSize_depth << "}\n";
  total_list << "{keep " << keep_depth << "}\n";
  total_list << "{ethernet_stream_out_V_data_V " << ethernet_stream_out_V_data_V_depth << "}\n";
  total_list << "{ethernet_stream_out_V_keep_V " << ethernet_stream_out_V_keep_V_depth << "}\n";
  total_list << "{ethernet_stream_out_V_strb_V " << ethernet_stream_out_V_strb_V_depth << "}\n";
  total_list << "{ethernet_stream_out_V_last_V " << ethernet_stream_out_V_last_V_depth << "}\n";
  return total_list.str();
}
void set_num (int num , int* class_num) {
  (*class_num) = (*class_num) > num ? (*class_num) : num;
}
  public:
    int gmem_depth;
    int in_depth;
    int buffSize_depth;
    int keep_depth;
    int ethernet_stream_out_V_data_V_depth;
    int ethernet_stream_out_V_keep_V_depth;
    int ethernet_stream_out_V_strb_V_depth;
    int ethernet_stream_out_V_last_V_depth;
    int trans_num;
  private:
    ofstream mFile;
    const char* mName;
};

static void RTLOutputCheckAndReplacement(std::string &AESL_token, std::string PortName) {
  bool no_x = false;
  bool err = false;

  no_x = false;
  // search and replace 'X' with '0' from the 3rd char of token
  while (!no_x) {
    size_t x_found = AESL_token.find('X', 0);
    if (x_found != string::npos) {
      if (!err) { 
        cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'X' on port" 
             << PortName << ", possible cause: There are uninitialized variables in the C design."
             << endl; 
        err = true;
      }
      AESL_token.replace(x_found, 1, "0");
    } else
      no_x = true;
  }
  no_x = false;
  // search and replace 'x' with '0' from the 3rd char of token
  while (!no_x) {
    size_t x_found = AESL_token.find('x', 2);
    if (x_found != string::npos) {
      if (!err) { 
        cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' on port" 
             << PortName << ", possible cause: There are uninitialized variables in the C design."
             << endl; 
        err = true;
      }
      AESL_token.replace(x_found, 1, "0");
    } else
      no_x = true;
  }
}
struct __cosim_s4__ { char data[4]; };
struct __cosim_s10__ { char data[16]; };
extern "C" void EthInTop_hw_stub(volatile void *, __cosim_s4__, __cosim_s4__, volatile void *);

extern "C" void apatb_EthInTop_hw(volatile void * __xlx_apatb_param_in, __cosim_s4__ __xlx_apatb_param_buffSize, __cosim_s4__ __xlx_apatb_param_keep, volatile void * __xlx_apatb_param_ethernet_stream_out) {
  refine_signal_handler();
  fstream wrapc_switch_file_token;
  wrapc_switch_file_token.open(".hls_cosim_wrapc_switch.log");
  int AESL_i;
  if (wrapc_switch_file_token.good())
  {

    CodeState = ENTER_WRAPC_PC;
    static unsigned AESL_transaction_pc = 0;
    string AESL_token;
    string AESL_num;{sc_bv<128> xlx_stream_ethernet_stream_out_pc_buffer;
unsigned xlx_stream_ethernet_stream_out_size;

          std::vector<sc_bv<128> > ethernet_stream_out_V_data_V_pc_buffer_Copy;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_ethernet_stream_out_V_data_V);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<128> > ethernet_stream_out_V_data_V_pc_buffer;
          int i = 0;

          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            RTLOutputCheckAndReplacement(AESL_token, "ethernet_stream_out");
  
            // push token into output port buffer
            if (AESL_token != "") {
              ethernet_stream_out_V_data_V_pc_buffer.push_back(AESL_token.c_str());
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (i > 0) {xlx_stream_ethernet_stream_out_size=ethernet_stream_out_V_data_V_pc_buffer.size();
ethernet_stream_out_V_data_V_pc_buffer_Copy=ethernet_stream_out_V_data_V_pc_buffer;
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  
          std::vector<sc_bv<128> > ethernet_stream_out_V_keep_V_pc_buffer_Copy;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_ethernet_stream_out_V_keep_V);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<128> > ethernet_stream_out_V_keep_V_pc_buffer;
          int i = 0;

          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            RTLOutputCheckAndReplacement(AESL_token, "ethernet_stream_out");
  
            // push token into output port buffer
            if (AESL_token != "") {
              ethernet_stream_out_V_keep_V_pc_buffer.push_back(AESL_token.c_str());
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (i > 0) {xlx_stream_ethernet_stream_out_size=ethernet_stream_out_V_keep_V_pc_buffer.size();
ethernet_stream_out_V_keep_V_pc_buffer_Copy=ethernet_stream_out_V_keep_V_pc_buffer;
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  
          std::vector<sc_bv<128> > ethernet_stream_out_V_strb_V_pc_buffer_Copy;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_ethernet_stream_out_V_strb_V);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<128> > ethernet_stream_out_V_strb_V_pc_buffer;
          int i = 0;

          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            RTLOutputCheckAndReplacement(AESL_token, "ethernet_stream_out");
  
            // push token into output port buffer
            if (AESL_token != "") {
              ethernet_stream_out_V_strb_V_pc_buffer.push_back(AESL_token.c_str());
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (i > 0) {xlx_stream_ethernet_stream_out_size=ethernet_stream_out_V_strb_V_pc_buffer.size();
ethernet_stream_out_V_strb_V_pc_buffer_Copy=ethernet_stream_out_V_strb_V_pc_buffer;
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  
          std::vector<sc_bv<128> > ethernet_stream_out_V_last_V_pc_buffer_Copy;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_ethernet_stream_out_V_last_V);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<128> > ethernet_stream_out_V_last_V_pc_buffer;
          int i = 0;

          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            RTLOutputCheckAndReplacement(AESL_token, "ethernet_stream_out");
  
            // push token into output port buffer
            if (AESL_token != "") {
              ethernet_stream_out_V_last_V_pc_buffer.push_back(AESL_token.c_str());
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (i > 0) {xlx_stream_ethernet_stream_out_size=ethernet_stream_out_V_last_V_pc_buffer.size();
ethernet_stream_out_V_last_V_pc_buffer_Copy=ethernet_stream_out_V_last_V_pc_buffer;
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  for (int j = 0, e = xlx_stream_ethernet_stream_out_size; j != e; ++j) {
xlx_stream_ethernet_stream_out_pc_buffer.range(63, 0) = ethernet_stream_out_V_data_V_pc_buffer_Copy[j];
xlx_stream_ethernet_stream_out_pc_buffer.range(71, 64) = ethernet_stream_out_V_keep_V_pc_buffer_Copy[j];
xlx_stream_ethernet_stream_out_pc_buffer.range(79, 72) = ethernet_stream_out_V_strb_V_pc_buffer_Copy[j];
xlx_stream_ethernet_stream_out_pc_buffer.range(127, 80) = ethernet_stream_out_V_last_V_pc_buffer_Copy[j];
__cosim_s10__ xlx_stream_elt;
((long long*)&xlx_stream_elt)[0*2+0] = xlx_stream_ethernet_stream_out_pc_buffer.range(63,0).to_int64();
((long long*)&xlx_stream_elt)[0*2+1] = xlx_stream_ethernet_stream_out_pc_buffer.range(127,64).to_int64();
((hls::stream<__cosim_s10__>*)__xlx_apatb_param_ethernet_stream_out)->write(xlx_stream_elt);
}}
    AESL_transaction_pc++;
    return ;
  }
static unsigned AESL_transaction;
static AESL_FILE_HANDLER aesl_fh;
static INTER_TCL_FILE tcl_file(INTER_TCL);
std::vector<char> __xlx_sprintf_buffer(1024);
CodeState = ENTER_WRAPC;
//gmem
aesl_fh.touch(AUTOTB_TVIN_gmem);
aesl_fh.touch(AUTOTB_TVOUT_gmem);
//in
aesl_fh.touch(AUTOTB_TVIN_in);
aesl_fh.touch(AUTOTB_TVOUT_in);
//buffSize
aesl_fh.touch(AUTOTB_TVIN_buffSize);
aesl_fh.touch(AUTOTB_TVOUT_buffSize);
//keep
aesl_fh.touch(AUTOTB_TVIN_keep);
aesl_fh.touch(AUTOTB_TVOUT_keep);
//ethernet_stream_out
aesl_fh.touch(AUTOTB_TVIN_ethernet_stream_out_V_data_V);
aesl_fh.touch(AUTOTB_TVOUT_ethernet_stream_out_V_data_V);
aesl_fh.touch(AUTOTB_TVIN_ethernet_stream_out_V_keep_V);
aesl_fh.touch(AUTOTB_TVOUT_ethernet_stream_out_V_keep_V);
aesl_fh.touch(AUTOTB_TVIN_ethernet_stream_out_V_strb_V);
aesl_fh.touch(AUTOTB_TVOUT_ethernet_stream_out_V_strb_V);
aesl_fh.touch(AUTOTB_TVIN_ethernet_stream_out_V_last_V);
aesl_fh.touch(AUTOTB_TVOUT_ethernet_stream_out_V_last_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_OUT_ethernet_stream_out_V_data_V);
aesl_fh.touch(WRAPC_STREAM_EGRESS_STATUS_ethernet_stream_out_V_data_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_OUT_ethernet_stream_out_V_keep_V);
aesl_fh.touch(WRAPC_STREAM_EGRESS_STATUS_ethernet_stream_out_V_keep_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_OUT_ethernet_stream_out_V_strb_V);
aesl_fh.touch(WRAPC_STREAM_EGRESS_STATUS_ethernet_stream_out_V_strb_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_OUT_ethernet_stream_out_V_last_V);
aesl_fh.touch(WRAPC_STREAM_EGRESS_STATUS_ethernet_stream_out_V_last_V);
CodeState = DUMP_INPUTS;
// print gmem Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_gmem, __xlx_sprintf_buffer.data());
  {  if (__xlx_apatb_param_in) {
    for (int j = 0, e = 1; j != e; ++j) {
sc_bv<128> __xlx_tmp_lv;
__xlx_tmp_lv.range(63,0) = ((long long*)__xlx_apatb_param_in)[j*2+0];
__xlx_tmp_lv.range(127,64) = ((long long*)__xlx_apatb_param_in)[j*2+1];

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_gmem, __xlx_sprintf_buffer.data()); 
      }
  }
}
  tcl_file.set_num(1, &tcl_file.gmem_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_gmem, __xlx_sprintf_buffer.data());
}
// print in Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_in, __xlx_sprintf_buffer.data());
  {
    sc_bv<64> __xlx_tmp_lv;
    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_in, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.in_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_in, __xlx_sprintf_buffer.data());
}
// print buffSize Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_buffSize, __xlx_sprintf_buffer.data());
  {
    sc_bv<32> __xlx_tmp_lv = *((int*)&__xlx_apatb_param_buffSize);
    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_buffSize, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.buffSize_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_buffSize, __xlx_sprintf_buffer.data());
}
// print keep Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_keep, __xlx_sprintf_buffer.data());
  {
    sc_bv<32> __xlx_tmp_lv = *((int*)&__xlx_apatb_param_keep);
    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_keep, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.keep_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_keep, __xlx_sprintf_buffer.data());
}
std::vector<__cosim_s10__> __xlx_apatb_param_ethernet_stream_out_stream_buf;
long __xlx_apatb_param_ethernet_stream_out_stream_buf_size = ((hls::stream<__cosim_s10__>*)__xlx_apatb_param_ethernet_stream_out)->size();
CodeState = CALL_C_DUT;
EthInTop_hw_stub(__xlx_apatb_param_in, __xlx_apatb_param_buffSize, __xlx_apatb_param_keep, __xlx_apatb_param_ethernet_stream_out);
CodeState = DUMP_OUTPUTS;

//********************** dump C output stream *******************
long __xlx_apatb_param_ethernet_stream_out_stream_buf_final_size = ((hls::stream<__cosim_s10__>*)__xlx_apatb_param_ethernet_stream_out)->size() - __xlx_apatb_param_ethernet_stream_out_stream_buf_size;
{
  while (!((hls::stream<__cosim_s10__>*)__xlx_apatb_param_ethernet_stream_out)->empty())
    __xlx_apatb_param_ethernet_stream_out_stream_buf.push_back(((hls::stream<__cosim_s10__>*)__xlx_apatb_param_ethernet_stream_out)->read());
  for (int i = 0; i < __xlx_apatb_param_ethernet_stream_out_stream_buf.size(); ++i)
    ((hls::stream<__cosim_s10__>*)__xlx_apatb_param_ethernet_stream_out)->write(__xlx_apatb_param_ethernet_stream_out_stream_buf[i]);
  }

  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVOUT_ethernet_stream_out_V_data_V, __xlx_sprintf_buffer.data());
  
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVOUT_ethernet_stream_out_V_keep_V, __xlx_sprintf_buffer.data());
  
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVOUT_ethernet_stream_out_V_strb_V, __xlx_sprintf_buffer.data());
  
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVOUT_ethernet_stream_out_V_last_V, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_ethernet_stream_out_stream_buf_final_size; j != e; ++j) {
sc_bv<128> __xlx_tmp_lv;
__xlx_tmp_lv.range(63,0) = ((long long*)&__xlx_apatb_param_ethernet_stream_out_stream_buf[__xlx_apatb_param_ethernet_stream_out_stream_buf_size+j])[0*2+0];
__xlx_tmp_lv.range(127,64) = ((long long*)&__xlx_apatb_param_ethernet_stream_out_stream_buf[__xlx_apatb_param_ethernet_stream_out_stream_buf_size+j])[0*2+1];
sc_bv<64> __xlx_tmp_0_lv = __xlx_tmp_lv.range(63, 0);
sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_0_lv.to_string(SC_HEX).c_str());
aesl_fh.write(AUTOTB_TVOUT_ethernet_stream_out_V_data_V, __xlx_sprintf_buffer.data());
sc_bv<8> __xlx_tmp_1_lv = __xlx_tmp_lv.range(71, 64);
sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_1_lv.to_string(SC_HEX).c_str());
aesl_fh.write(AUTOTB_TVOUT_ethernet_stream_out_V_keep_V, __xlx_sprintf_buffer.data());
sc_bv<8> __xlx_tmp_2_lv = __xlx_tmp_lv.range(79, 72);
sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_2_lv.to_string(SC_HEX).c_str());
aesl_fh.write(AUTOTB_TVOUT_ethernet_stream_out_V_strb_V, __xlx_sprintf_buffer.data());
sc_bv<48> __xlx_tmp_3_lv = __xlx_tmp_lv.range(127, 80);
sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_3_lv.to_string(SC_HEX).c_str());
aesl_fh.write(AUTOTB_TVOUT_ethernet_stream_out_V_last_V, __xlx_sprintf_buffer.data());
}
tcl_file.set_num(__xlx_apatb_param_ethernet_stream_out_stream_buf_final_size, &tcl_file.ethernet_stream_out_V_data_V_depth);

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVOUT_ethernet_stream_out_V_data_V, __xlx_sprintf_buffer.data());
tcl_file.set_num(__xlx_apatb_param_ethernet_stream_out_stream_buf_final_size, &tcl_file.ethernet_stream_out_V_keep_V_depth);

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVOUT_ethernet_stream_out_V_keep_V, __xlx_sprintf_buffer.data());
tcl_file.set_num(__xlx_apatb_param_ethernet_stream_out_stream_buf_final_size, &tcl_file.ethernet_stream_out_V_strb_V_depth);

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVOUT_ethernet_stream_out_V_strb_V, __xlx_sprintf_buffer.data());
tcl_file.set_num(__xlx_apatb_param_ethernet_stream_out_stream_buf_final_size, &tcl_file.ethernet_stream_out_V_last_V_depth);

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVOUT_ethernet_stream_out_V_last_V, __xlx_sprintf_buffer.data());
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_ethernet_stream_out_V_data_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_ethernet_stream_out_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_OUT_ethernet_stream_out_V_data_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_ethernet_stream_out_V_data_V, __xlx_sprintf_buffer.data());
}{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_ethernet_stream_out_V_keep_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_ethernet_stream_out_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_OUT_ethernet_stream_out_V_keep_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_ethernet_stream_out_V_keep_V, __xlx_sprintf_buffer.data());
}{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_ethernet_stream_out_V_strb_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_ethernet_stream_out_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_OUT_ethernet_stream_out_V_strb_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_ethernet_stream_out_V_strb_V, __xlx_sprintf_buffer.data());
}{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_ethernet_stream_out_V_last_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_ethernet_stream_out_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_OUT_ethernet_stream_out_V_last_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_ethernet_stream_out_V_last_V, __xlx_sprintf_buffer.data());
}CodeState = DELETE_CHAR_BUFFERS;
AESL_transaction++;
tcl_file.set_num(AESL_transaction , &tcl_file.trans_num);
}
