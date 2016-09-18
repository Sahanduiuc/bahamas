﻿using System;
using System.CodeDom;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TicTacTec.TA.Library;

namespace bahamas_system.Bahamas_System.GE.Operators.Functions
{
    public class SMA: Function
    {
        private List<string[]> parseCSV(string path)
        {
            List<string[]> parsedData = new List<string[]>();

            try
            {
                using (StreamReader readFile = new StreamReader(path))
                {
                    string line;
                    string[] row;

                    while ((line = readFile.ReadLine()) != null)
                    {
                        row = line.Split(',');
                        parsedData.Add(row);
                    }
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }

            return parsedData;
        }

        public override void Evaluate(int delta)
        {
            int i;
            string curDir = Directory.GetCurrentDirectory();
            string fileName = curDir + @"\msft.csv";
            List<string[]> parsedData = parseCSV(fileName);
            int nCount = parsedData.Count;
            double[] closingPricesArr = new double[nCount - 1];
            for (i = 0; i < nCount - 1; i++)
                closingPricesArr[i] = Convert.ToDouble(parsedData[i + 1][6]);

            int startIdx = 0;
            int endIdx = nCount - 2;
            int optInPeriod = (int) StrategyManager.ResultsStack.Pop().ValueResult;

            double[] outVals = new double[endIdx - startIdx + 1]; ;
            double[] inReal = closingPricesArr;

            int outBegIdx;
            int outNBElement;

            Core.RetCode status = Core.Sma(startIdx, endIdx, inReal, optInPeriod, 
                out outBegIdx, out outNBElement, outVals);

            ExpressionResult result = new ExpressionResult();
            result.ValueResult = (float) outVals[delta-optInPeriod+1];
            StrategyManager.ResultsStack.Push(result);

            //Console.WriteLine(optInPeriod + " - " + result.ValueResult);
        }

        public override string ToString()
        {
            return "SMA";
        }
    }
}