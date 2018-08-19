import math
from numba import jit

import settings

@jit
def calculate_call_price(underlying_price, strike, volatility, dte):
    rate = settings.LIBOR_rate
    return underlying_price * _norm_cdf(_d_j(1, underlying_price, strike, rate, volatility, dte)) - strike * math.exp(-rate * dte) * _norm_cdf(_d_j(2, underlying_price, strike, rate, volatility, dte))

@jit
def calculate_call_delta(underlying_price, strike, volatility, dte):
    rate = settings.LIBOR_rate
    return _norm_cdf(_d_j(1, underlying_price, strike, rate, volatility, dte))

@jit
def calculate_put_price(underlying_price, strike, volatility, dte):
    rate = settings.LIBOR_rate
    return -underlying_price * _norm_cdf(-_d_j(1, underlying_price, strike, rate, volatility, dte)) + strike * math.exp(-rate * dte) * _norm_cdf(-_d_j(2, underlying_price, strike, rate, volatility, dte))    

@jit
def calculate_put_delta(underlying_price, strike, volatility, dte):
    rate = settings.LIBOR_rate
    return _norm_cdf(_d_j(1, underlying_price, strike, rate, volatility, dte)) - 1

@jit
def calculate_iv(underlying_price, strike, dte, option_price, option_type):
    high = 500.0
    low = 0.0
    mid = 0.0

    for i in range(500):
        mid = (high + low) / 2
        if mid < 0.00001:
            mid = 0.00001

        estimate = 0.0
        if option_type == 'C':
            estimate = calculate_call_price(underlying_price, strike, mid, dte)
        elif option_type == 'P':
            estimate = calculate_put_price(underlying_price, strike, mid, dte)

        if estimate > option_price:
            high = mid
        elif estimate <= option_price:
            low = mid
            
    return mid

@jit
def _norm_pdf(val):
    return (1.0 / (math.pow(2 * math.pi, 0.5))) * math.exp(-0.5 * val * val)

@jit
def _norm_cdf(val):
    k = 1.0 / (1.0 + 0.2316419 * val)
    k_sum = k * (0.319381530 + k * (-0.356563782 + k * (1.781477937 + k * (-1.821255978 + 1.330274429 * k))))

    if val >= 0.0:
        return (1.0 - (1.0 / (math.pow(2 * math.pi, 0.5))) * math.exp(-0.5 * val * val) * k_sum)
    else:
        return 1.0 - _norm_cdf(-val)
            
@jit
def _d_j(j, S, K, r, v, T):
    return (math.log(S / K) + (r + (math.pow(-1, j - 1)) * 0.5 * v * v) * T) / (v * (math.pow(T, 0.5)))

