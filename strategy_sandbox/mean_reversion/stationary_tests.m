clear;

[n,s] = xlsread('USDCAD_data.csv');

startIndex = find(strcmp(s, '23/07/2007'));
endIndex = find(strcmp(s, '28/03/2012'));

o = n(:,1);
h = n(:,2);
l = n(:,3);
c = n(:,4);

filteredVal = o(startIndex:endIndex);

plot(filteredVal);

disp('ADF Test');
[ADFstat, ADFpval, critval] = augdf(filteredVal,1,1)
% 
disp('Hurst Exponent Test');
H=genhurst(log(filteredVal), 2)

disp('Variance Ratio Test');
[h,pValue] = vratiotest(log(filteredVal))
