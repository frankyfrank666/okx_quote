#include "../ResultTop.h"

int main() {
    hls::stream<BBO> ask_price_volume_stream_in;
    BBO bbo1;
    BBO bbo2;
    BBO bbo3;

    // 1 2 3 4 5 .
    // 49 50 51 52 53 46 
    bbo1.best_price =  0x4950514649; //123.1;
    bbo1.best_volume = 0x49505149; //1231
    
    bbo1.best_price = 0x4950514650;//123.2
    bbo1.best_volume = 0x49505151;//1232
    
    bbo1.best_price = 0x4950514651;//123.3
    bbo1.best_volume = 0x0049505151;//1233
    

    ask_price_volume_stream_in.write(bbo1);
    ask_price_volume_stream_in.write(bbo2);
    ask_price_volume_stream_in.write(bbo3);

        ap_uint<32> price_out;
    ap_uint<32> volume_out;
    ResultTop(price_out, volume_out, ask_price_volume_stream_in);

    std::cout << std::hex << price_out << std::endl;
    std::cout << std::hex << volume_out;

    return 0;
}
