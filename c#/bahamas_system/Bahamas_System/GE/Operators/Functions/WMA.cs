﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TicTacTec.TA.Library;

namespace bahamas_system.Bahamas_System.GE.Operators.Functions
{
    public class WMA: Function
    {
        public override void Evaluate(int delta)
        {
            int i;
            var equityData = DataManager.GetEquityData(
                StrategyManager.ResultsStack.Pop().StringResult);
            int nCount = equityData.Count;
            double[] closingPricesArr = new double[nCount - 1];
            for (i = 0; i < nCount - 1; i++)
                closingPricesArr[i] = Convert.ToDouble(equityData[i + 1][6]);

            int startIdx = 0;
            int endIdx = nCount - 2;
            int optInPeriod = (int) StrategyManager.ResultsStack.Pop().ValueResult;

            double[] outVals = new double[endIdx - startIdx + 1]; ;
            double[] inReal = closingPricesArr;

            int outBegIdx;
            int outNBElement;

            Core.RetCode status = Core.Wma(startIdx, endIdx, inReal, optInPeriod,
                out outBegIdx, out outNBElement, outVals);

            ExpressionResult result = new ExpressionResult();
            result.ValueResult = (float) outVals[delta-optInPeriod+1];
            StrategyManager.ResultsStack.Push(result);
        }

        public override string ToString()
        {
            return "EMA";
        }
    }
}