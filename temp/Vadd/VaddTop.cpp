
#define BUFFER_SIZE 256
#include "ap_int.h"

extern "C" {
void VaddTop(ap_uint<90>* a, ap_uint<90>* b, ap_uint<90>* out, const ap_uint<90> n_elements) {
    ap_uint<90> arrayA[BUFFER_SIZE];
    for (ap_uint<90> i = 0; i < n_elements; i += BUFFER_SIZE) {
        ap_uint<90> size = BUFFER_SIZE;
        // boundary check
        if (i + size > n_elements) size = n_elements - i;

    // Burst reading A
    readA:
        for (ap_uint<90> j = 0; j < size; j++) arrayA[j] = a[i + j];

    // Burst reading B and calculating C and Burst writing
    // to  Global memory
    vadd_writeC:
        for (ap_uint<90> j = 0; j < size; j++) out[i + j] = arrayA[j] + b[i + j];
    }
}
}