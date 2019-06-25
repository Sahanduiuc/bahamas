#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <chrono>
#include <cmath>
#include <unordered_map>
#include <boost/algorithm/string.hpp>

/*
The MIT License

Copyright (c) 2019

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

namespace constants {

#pragma region Trade Features

    const char* TRADE_FEATURE_VOLUMES_PATH = "./data/tick_1000/volumes.bin";

    const char* TRADE_FEATURE_SETTLE_PRICES_PATH = "./data/tick_1000/settle_prices.bin";

    const char* TRADE_FEATURE_HIGH_PRICES_PATH = "./data/tick_1000/high_prices.bin";

    const char* TRADE_FEATURE_LOW_PRICES_PATH = "./data/tick_1000/low_prices.bin";

    const char* TRADE_FEATURE_OPEN_PRICES_PATH = "./data/tick_1000/open_prices.bin";

    const char* TRADE_FEATURE_OPEN_TIMESTAMPS_PATH = "./data/tick_1000/open_timestamps.bin";

    const char* TRADE_FEATURE_SETTLE_TIMESTAMPS_PATH = "./data/tick_1000/settle_timestamps.bin";

#pragma endregion
}

double* populate_buffer(const char*, size_t);
size_t get_file_size(const char*);

/*
OHLSV Bars created at 1000 tick intervals.
*/
struct trade_feature_data {
    double* open_timestamps = nullptr;
    double* close_timestamps = nullptr;
    double* open_prices = nullptr;
    double* high_prices = nullptr;
    double* settle_prices = nullptr;
    double* low_prices = nullptr;
    double* volumes = nullptr;
    size_t buff_size = 10000000UL, data_point_size = 530UL;
    static const char* dir_name;

    trade_feature_data(){
        open_timestamps = populate_buffer(constants::TRADE_FEATURE_OPEN_TIMESTAMPS_PATH, buff_size);
        close_timestamps = populate_buffer(constants::TRADE_FEATURE_SETTLE_TIMESTAMPS_PATH, buff_size);
        open_prices = populate_buffer(constants::TRADE_FEATURE_OPEN_PRICES_PATH, buff_size);
        high_prices = populate_buffer(constants::TRADE_FEATURE_HIGH_PRICES_PATH, buff_size);
        low_prices = populate_buffer(constants::TRADE_FEATURE_LOW_PRICES_PATH, buff_size);
        settle_prices = populate_buffer(constants::TRADE_FEATURE_SETTLE_PRICES_PATH, buff_size);
        volumes = populate_buffer(constants::TRADE_FEATURE_VOLUMES_PATH, buff_size);
    }

}; const char* trade_feature_data::dir_name = "./data/tick_1000/";


struct quote_feature_data{
    size_t buff_size = 10000000UL, data_point_size = 0UL;
    double* q_timestamps = nullptr;
    double* q_bid_size = nullptr;
    double* q_bid_price = nullptr;
    double* q_ask_size = nullptr;
    double* q_ask_price = nullptr;

    quote_feature_data(){
        q_timestamps = populate_buffer("./data/XBTUSD_q_timestamp.bin", buff_size);
        q_bid_size = populate_buffer("./data/XBTUSD_q_bid_size.bin", buff_size);
        q_bid_price = populate_buffer("./data/XBTUSD_q_bid_price.bin", buff_size);
        q_ask_size = populate_buffer("./data/XBTUSD_q_ask_size.bin", buff_size);
        q_ask_price = populate_buffer("./data/XBTUSD_q_ask_price.bin", buff_size);
        data_point_size = get_file_size("./data/XBTUSD_q_timestamp.bin")/sizeof(double);
    }
}; 

double* populate_buffer(const char* fname, size_t buff_size){
    double* buffer = (double*)malloc(buff_size*sizeof(double));
    std::ifstream in(fname, std::ios::in | std::ios::binary);
    in.read((char*) buffer, buff_size*sizeof(double));
    in.close();
    return buffer;
}

size_t get_file_size(const char* fname){
    std::ifstream in(fname, std::ios::in | std::ios::binary | std::ios::ate);
    return in.tellg();
}

class data_container{
public:
    data_container(){}

    template <typename Feature>
    struct data_iterator{
        using T = double;
        using iterator_category = std::forward_iterator_tag;
        using difference_type = ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        
        Feature* data_ptr;
        size_t index = 0;

        data_iterator() {}

        data_iterator(Feature* data_ptr) : data_ptr(data_ptr) {}

        data_iterator(T* entries, size_t offset) {
        }

        bool operator==(const data_iterator& other) const {
            return this->index == other.index;
        }

        bool operator!=(const data_iterator& other) const {
            return !(*this==other);
        }

        data_iterator& operator++(){
            ++index;
            return *this;
        }

        data_iterator operator++(int){
            data_iterator temp = *this;
            ++(*this);
            return temp;
        }

        T get_value(T* data_stream){
            return data_stream[index];
        }

        T* get_ptr(T* data_stream){
            return data_stream + index;
        }
    };

    using trade_iterator = data_iterator<trade_feature_data>;
    using quote_iterator = data_iterator<quote_feature_data>;

    trade_iterator begin_trades(){
        return trade_iterator(&tick_data);
    }

    quote_iterator begin_quotes(){
        return quote_iterator(&quote_data);
    }

    size_t size(){
        return tick_data.data_point_size;
    }

    size_t quote_size(){
        return quote_data.data_point_size;
    }
private:;    
    trade_feature_data tick_data;
    quote_feature_data quote_data;
};
data_container container;

using FOperand = double(*)(data_container::trade_iterator&);
using FOperation = double(*)(double, double);

const size_t MAX_CONFIG_CAPACITY = 100;

size_t config_sz = 0;
static int config[MAX_CONFIG_CAPACITY];

static FOperand operand_arr[MAX_CONFIG_CAPACITY];
static FOperation operation_arr[MAX_CONFIG_CAPACITY];

std::unordered_map<FOperand, std::string> operand_f_names;
std::unordered_map<FOperation, std::string> operation_f_names;

struct rand_config {
    rand_config() {
        std::srand((int)std::time(0));
    }

    int next() {
        return std::rand() % 1000;
    }
};

#pragma region Functions
template <int v>
inline double const_int(data_container::trade_iterator& it){
    return v;
}

inline double get_weekday(data_container::trade_iterator& it){
    return 0.0;
}

inline double get_period(data_container::trade_iterator& it){
    return 0.0;
}

template <uint n>
inline double get_close_n(data_container::trade_iterator& it){
    return 0.0;
}

template <uint n>
inline double get_open_n(data_container::trade_iterator& it){
    return 0.0;
}

inline double get_current_price(data_container::trade_iterator& it){
    return 0.0;
}

template <uint n>
inline double get_volume_n(data_container::trade_iterator& it){
    return it.get_value(it.data_ptr->volumes);
}

inline double equals(double x, double y){
    return (x == y ? 1.0 : 0.0);
}

inline double greater_than(double x, double y){
    return (x > y ? 1.0 : 0.0);
}

inline double less_than(double x, double y){
    return (x < y ? 1.0 : 0.0);
}

inline double and_op(double x, double y){
    return ((x > 0.0 && y > 0.0) ? 1.0 : 0.0);
}

inline double add_op(double x, double y){
    return x+y;
}
#pragma endregion

#pragma region Expression
struct expression_base {
    expression_base(size_t length) : 
        length(length) {}

    size_t length;

    virtual void parse(rand_config config) = 0;
};

struct expression : expression_base {
    expression(bool is_selector, std::initializer_list<expression_base*> nodes) :
        expression_base(nodes.size()), is_selector(is_selector), nodes(nodes) {}

    bool is_selector;
    std::vector<expression_base*> nodes;

    virtual void parse(rand_config config) {
        if (is_selector) {
            auto f_val = nodes[config.next() % length];
            f_val->parse(config);
        }else{
            for (auto n : nodes) {
                n->parse(config);
            }
        }
    }
};

template <typename T>
struct function_expression : expression_base {
    function_expression(std::initializer_list<T> nodes) :
        expression_base(nodes.size()), nodes(nodes) {}

    std::vector<T> nodes;

    void parse(FOperand f) {
        operand_arr[config_sz] = f;
        config[config_sz] = 0;
        config_sz++;
    }

    void parse(FOperation f) {
        operation_arr[config_sz] = f;
        config[config_sz] = 1;
        config_sz++;
    }

    virtual void parse(rand_config config) {
        T f_val = nodes[config.next() % length];
        parse(*f_val);
    }
};

struct expression_config {
    expression_config(expression_base* exp, rand_config& config) {
        config_sz = 0;
        exp->parse(config);
    }

    void print_strategy(){
        std::stringstream ss;
        size_t i = 0;
        for(; i < config_sz; i++){
            if (config[i] == 0){
                ss << operand_f_names[operand_arr[i]] << " ";
            }else{
                ss << operation_f_names[operation_arr[i]] << " ";
            }
        }
        std::cout << ss.str() << std::endl;
    }

    void eval(size_t c_begin, size_t quote_count, std::vector<double>& signals) noexcept {
        size_t c, i, calc_index;
        double op_val00, op_val01, temp_store = 0.0;
        double calc_store[100];
        data_container::trade_iterator it = container.begin_trades();

        for(c = c_begin; c < quote_count; c++){
            calc_index = 0;
            
            for (i = 0; i < config_sz; i++) {
                if (config[i] == 0){
                    op_val00 = operand_arr[i](it);
                    calc_store[calc_index] = op_val00;
                    calc_index++;
                }else{
                    op_val00 = calc_store[calc_index - 1];
                    calc_index--;
                    op_val01 = calc_store[calc_index - 1];
                    calc_index--;
                    
                    temp_store = operation_arr[i](op_val00, op_val01);
                    calc_store[calc_index] = temp_store;
                    calc_index++;
                }
            }
            
            signals[c] = calc_store[0];
            it++;
        }
    }
};

#pragma endregion

/*
Liquidate all positions for Instrument if current quote price is n standard deviations from the Average True Range.
*/
struct atr_exit {
    template <typename... Ts>
    static bool evaluate(Ts... args){
        return true;
    };
};

/*
Liquidate all positions for Instrument on next feature bar.
*/
struct feature_update_exit {
    template <typename... Ts>
    static bool evaluate(Ts... args){
        return true;
    }
};

class trading_engine{
public:
    static const uint16_t ls_direction = 1;

    struct position{        
        uint8_t units = 0;
        double entry_price = 0.0;
    };

    template <typename ExitStrategy>
    static double evaluate_strategy(expression_config& config){
        size_t i, feature_elem_count = container.size(), quote_count = container.quote_size();
 
        std::vector<double> equity_series(feature_elem_count);
        std::vector<double> signals(feature_elem_count);
        config.eval(0, feature_elem_count, signals);

        data_container::trade_iterator t_it = container.begin_trades();
        data_container::quote_iterator q_it = container.begin_quotes();
       
        double equity = 10000.0, cur_bid_price = 0.0, cur_ask_price = 0.0;
        position register btcusd_position;

        for(size_t i = 0; i < quote_count; i++, q_it++){
            if (t_it.index < feature_elem_count &&
                q_it.get_value(q_it.data_ptr->q_timestamps) > t_it.get_value(t_it.data_ptr->close_timestamps)){

                cur_bid_price = q_it.get_value(q_it.data_ptr->q_bid_price);
                cur_ask_price = q_it.get_value(q_it.data_ptr->q_ask_price);                

                if (btcusd_position.units == 0 && signals[t_it.index] == 1.0){                    
                    btcusd_position.entry_price = cur_ask_price;
                    btcusd_position.units = 1;
                }else if (btcusd_position.units > 0 && ExitStrategy::evaluate()){
                    equity += (cur_bid_price - btcusd_position.entry_price);                   
                    btcusd_position.units = 0;
                }

                equity_series[t_it.index] = equity;
                t_it++;
            }
        }
        return equity;
    }
private:
    trading_engine(){}
    ~trading_engine(){}
};

#pragma region FunctionNames
enum FTypes {INT, CLOSE_N, WEEKDAY, PERIOD, CURRENT_PRICE};

template <FTypes FType, int V>
void add_f_name(char* f_name){
    if (FType == INT){
        operand_f_names[const_int<V>] = f_name;
    }else if (FType == CLOSE_N){
        operand_f_names[get_close_n<V>] = f_name;
    }else if (FType == WEEKDAY){
        operand_f_names[get_weekday] = f_name;
    }else if (FType == PERIOD){
        operand_f_names[get_period] = f_name;
    }else if (FType == CURRENT_PRICE){
        operand_f_names[get_current_price] = f_name;
    }
}

char* format_f_name(char* f_name, int n){
    size_t len = strlen(f_name);
    f_name[len - 1] = n + 48;
    return f_name;
}

template <FTypes FType, int UBound=-1, int LBound=-1>
struct operand_name_parser{
    static void populate(char* f_name){
        add_f_name<FType, UBound>(format_f_name(f_name, UBound));
        operand_name_parser<FType, UBound-1, LBound>::populate(f_name);
    }
};

template <FTypes FType, int N>
struct operand_name_parser<FType, N,N>{
    static void populate(char* f_name){
        add_f_name<FType, N>(format_f_name(f_name, N));
    }
};

template <FTypes FType>
struct operand_name_parser<FType, -1,-1>{
    static void populate(char* f_name){
        add_f_name<FType, -1>(f_name);
    }
};


void populate_f_mappings(){
    char int_name[] = "0";
    char close_n_name[] = "Close_N-0";
    char weekday_name[] = "Weekday";
    char period_name[] = "Period";
    char current_price_name[] = "Current_Price";

    operand_name_parser<INT,9,0>::populate(int_name);
    operand_name_parser<CLOSE_N,9,0>::populate(close_n_name);
    operand_name_parser<WEEKDAY>::populate(weekday_name);
    operand_name_parser<PERIOD>::populate(period_name);
    operand_name_parser<CURRENT_PRICE>::populate(current_price_name);

    operation_f_names[equals] = "==";
    operation_f_names[greater_than] = ">";
    operation_f_names[less_than] = "<";
    operation_f_names[and_op] = "And";
    operation_f_names[add_op] = "+";
}
#pragma endregion
