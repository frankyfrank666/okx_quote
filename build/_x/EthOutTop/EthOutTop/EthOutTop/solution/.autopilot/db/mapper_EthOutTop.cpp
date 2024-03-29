#include <systemc>
#include <vector>
#include <iostream>
#include "hls_stream.h"
#include "ap_int.h"
#include "ap_fixed.h"
using namespace std;
using namespace sc_dt;
class AESL_RUNTIME_BC {
  public:
    AESL_RUNTIME_BC(const char* name) {
      file_token.open( name);
      if (!file_token.good()) {
        cout << "Failed to open tv file " << name << endl;
        exit (1);
      }
      file_token >> mName;//[[[runtime]]]
    }
    ~AESL_RUNTIME_BC() {
      file_token.close();
    }
    int read_size () {
      int size = 0;
      file_token >> mName;//[[transaction]]
      file_token >> mName;//transaction number
      file_token >> mName;//pop_size
      size = atoi(mName.c_str());
      file_token >> mName;//[[/transaction]]
      return size;
    }
  public:
    fstream file_token;
    string mName;
};
unsigned int ap_apatb_ethernet_stream_in_V_cap_bc;
static AESL_RUNTIME_BC __xlx_ethernet_stream_in_V_size_Reader("../tv/stream_size/stream_size_in_ethernet_stream_in_V.dat");
struct __cosim_s4__ { char data[4]; };
struct __cosim_s10__ { char data[16]; };
extern "C" void EthOutTop(__cosim_s10__*, int, __cosim_s4__, __cosim_s10__*);
extern "C" void apatb_EthOutTop_hw(volatile void * __xlx_apatb_param_out, __cosim_s4__ __xlx_apatb_param_buffSize, volatile void * __xlx_apatb_param_ethernet_stream_in) {
  // Collect __xlx_out__tmp_vec
  vector<sc_bv<128> >__xlx_out__tmp_vec;
  for (int j = 0, e = 1; j != e; ++j) {
    sc_bv<128> _xlx_tmp_sc;
    _xlx_tmp_sc.range(63, 0) = ((long long*)__xlx_apatb_param_out)[j*2+0];
    _xlx_tmp_sc.range(127, 64) = ((long long*)__xlx_apatb_param_out)[j*2+1];
    __xlx_out__tmp_vec.push_back(_xlx_tmp_sc);
  }
  int __xlx_size_param_out = 1;
  int __xlx_offset_param_out = 0;
  int __xlx_offset_byte_param_out = 0*16;
  __cosim_s10__* __xlx_out__input_buffer= new __cosim_s10__[__xlx_out__tmp_vec.size()];
  for (int i = 0; i < __xlx_out__tmp_vec.size(); ++i) {
    ((long long*)__xlx_out__input_buffer)[i*2+0] = __xlx_out__tmp_vec[i].range(63, 0).to_uint64();
    ((long long*)__xlx_out__input_buffer)[i*2+1] = __xlx_out__tmp_vec[i].range(127, 64).to_uint64();
  }
  // collect __xlx_ethernet_stream_in_tmp_vec
  unsigned __xlx_ethernet_stream_in_V_tmp_Count = 0;
  unsigned __xlx_ethernet_stream_in_V_read_Size = __xlx_ethernet_stream_in_V_size_Reader.read_size();
  vector<__cosim_s10__> __xlx_ethernet_stream_in_tmp_vec;
  while (!((hls::stream<__cosim_s10__>*)__xlx_apatb_param_ethernet_stream_in)->empty() && __xlx_ethernet_stream_in_V_tmp_Count < __xlx_ethernet_stream_in_V_read_Size) {
    __xlx_ethernet_stream_in_tmp_vec.push_back(((hls::stream<__cosim_s10__>*)__xlx_apatb_param_ethernet_stream_in)->read());
    __xlx_ethernet_stream_in_V_tmp_Count++;
  }
  ap_apatb_ethernet_stream_in_V_cap_bc = __xlx_ethernet_stream_in_tmp_vec.size();
  // store input buffer
  __cosim_s10__* __xlx_ethernet_stream_in_input_buffer= new __cosim_s10__[__xlx_ethernet_stream_in_tmp_vec.size()];
  for (int i = 0; i < __xlx_ethernet_stream_in_tmp_vec.size(); ++i) {
    __xlx_ethernet_stream_in_input_buffer[i] = __xlx_ethernet_stream_in_tmp_vec[i];
  }
  // DUT call
  EthOutTop(__xlx_out__input_buffer, __xlx_offset_byte_param_out, __xlx_apatb_param_buffSize, __xlx_ethernet_stream_in_input_buffer);
// print __xlx_apatb_param_out
  sc_bv<128>*__xlx_out_output_buffer = new sc_bv<128>[__xlx_size_param_out];
  for (int i = 0; i < __xlx_size_param_out; ++i) {
    char* start = (char*)(&(__xlx_out__input_buffer[__xlx_offset_param_out]));
    __xlx_out_output_buffer[i].range(63, 0) = ((long long*)start)[i*2+0];
    __xlx_out_output_buffer[i].range(127, 64) = ((long long*)start)[i*2+1];
  }
  for (int i = 0; i < __xlx_size_param_out; ++i) {
    ((long long*)__xlx_apatb_param_out)[i*2+0] = __xlx_out_output_buffer[i].range(63, 0).to_uint64();
    ((long long*)__xlx_apatb_param_out)[i*2+1] = __xlx_out_output_buffer[i].range(127, 64).to_uint64();
  }
}
