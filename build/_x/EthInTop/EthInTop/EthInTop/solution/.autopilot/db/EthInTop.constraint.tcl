set clock_constraint { \
    name clk \
    module EthInTop \
    port ap_clk \
    period 3.333 \
    uncertainty 0.9 \
}

set all_path {}

set false_path {}
