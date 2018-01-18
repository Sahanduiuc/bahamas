export interface Option {
    expDate: string;
    strikePrice: number;
    mktPrice: number;
    delta: number;
    gamma: number;
    theta: number;
    vega: number;
}