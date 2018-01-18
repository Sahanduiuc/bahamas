using System;
using System.Collections.Generic;
using System.Linq;
using OptionEngine.Entities;
using Microsoft.AspNetCore.Mvc;
using System.IO;
using OptionEngine.ViewModels;

namespace OptionEngine
{
    public class HomeController : Controller
    {
        static Dictionary<DateTime, MatrixViewModel> modelCollection;

        public HomeController()
        {

        }

        public IActionResult Index()
        {
            modelCollection = new Dictionary<DateTime, MatrixViewModel>();

            DirectoryInfo dirInfo = new DirectoryInfo(@"C:\Users\shami\Desktop\bahamas\data\RUT\");
            foreach (var file in dirInfo.GetFiles("*.csv"))
            {
                ImportMatrixData(file.FullName);
            }

            var dateIds = modelCollection.Keys.ToList();
            dateIds.Sort();
            return View(dateIds);
        }

        private DateTime ParseImportDate(string val)
        {
            //string date = "";

            //date = val.Substring(val.Length - 2);
            //date += "-" + val.Substring(val.Length - 4, 2);
            //date += "-20" + val.Substring(0,2); 

            return DateTime.Parse(val);
        }

        public IActionResult About()
        {
            return View();
        }

        public ActionResult GetNewData(string id)
        {
            DateTime targetDate = DateTime.Parse(id);

            Balance(ref modelCollection[targetDate].MatrixData);
            return Json(modelCollection[targetDate].MatrixData);
        }

        public ActionResult GetBacktestDates()
        {
            var dateIds = modelCollection.Keys.ToList();
            dateIds.Sort();
            return Json(dateIds);
        }

        private void Balance(ref Dictionary<DateTime, List<OptionModel>> data)
        {
            var keys = data.Keys.ToList();

            int minStrike_P = Int32.MaxValue;
            int maxStrike_P = -1;
            int minStrike_C = Int32.MaxValue;
            int maxStrike_C = -1;

            foreach (var key in keys)
            {
                var opList = data[key];
                foreach (var op in opList)
                {
                    if (op.OptionType == OptionModel.OptionTypes.Put)
                    {
                        if (op.StrikePrice > maxStrike_P)
                            maxStrike_P = op.StrikePrice;
                        if (op.StrikePrice < minStrike_P)
                            minStrike_P = op.StrikePrice;
                    } else if (op.OptionType == OptionModel.OptionTypes.Call)
                    {
                        if (op.StrikePrice > maxStrike_C)
                            maxStrike_C = op.StrikePrice;
                        if (op.StrikePrice < minStrike_C)
                            minStrike_C = op.StrikePrice;
                    }
                }
            }
            int lBound = Math.Min(minStrike_C, minStrike_P);
            int uBound = Math.Max(maxStrike_C, maxStrike_P);

            foreach (var key in keys)
            {
                var opList = data[key];
                List<OptionModel> tempList = new List<OptionModel>();

                for (int i = lBound; i <= uBound; i += 10)
                {
                    if (i >= minStrike_C && i <= maxStrike_C)
                    {
                        var targetOption = ContainsOption(opList, i, OptionModel.OptionTypes.Call);
                        if (targetOption != null)
                        {
                            tempList.Add(targetOption);
                        }
                        else
                        {
                            OptionModel temp = new OptionModel();
                            temp.StrikePrice = i;
                            temp.OptionType = OptionModel.OptionTypes.Call;
                            temp.MarketPrice = 0;
                            temp.ExpirationDate = opList[0].ExpirationDate;
                            temp.Delta = 0;
                            tempList.Add(temp);
                        }
                    }
                    if (i >= minStrike_P && i <= maxStrike_P)
                    {
                        var targetOption = ContainsOption(opList, i, OptionModel.OptionTypes.Put);
                        if (targetOption != null)
                        {
                            tempList.Add(targetOption);
                        }
                        else
                        {
                            OptionModel temp = new OptionModel();
                            temp.StrikePrice = i;
                            temp.OptionType = OptionModel.OptionTypes.Put;
                            temp.MarketPrice = 0;
                            temp.ExpirationDate = opList[0].ExpirationDate;
                            temp.Delta = 0;
                            tempList.Add(temp);
                        }
                    }
                }

                data[key] = tempList;
            }
        }

        private OptionModel ContainsOption(List<OptionModel> opList, int strike, OptionModel.OptionTypes type)
        {
            foreach(var option in opList)
            {
                if (option.StrikePrice == strike && option.OptionType == type)
                    return option;
            }

            return null;
        }

        private void ImportMatrixData(string dataPath)
        {
            List<string> headers = new List<string>();
            MatrixViewModel matrixViewModel = new MatrixViewModel();
            bool readHeader = true;
            DateTime dataDate = new DateTime();
            //double uPrice;

            using (var reader = new StreamReader(dataPath))
            {
                if (readHeader)
                {
                    var headerRaw = reader.ReadLine();
                    var headerVal = headerRaw.Split(',');

                    for (int i = 0; i < headerVal.Length; i++)
                    {
                        headers.Add(headerVal[i]);
                    }

                    readHeader = false;
                }

                //// Read Underlying data
                //var rawUnderlying = reader.ReadLine().Split(',');
                //for(int j = 0; j < rawUnderlying.Length; j++)
                //{
                //    string colHeader = headers[j];

                //    if(colHeader == "Date")
                //    {
                //        dataDate = ParseImportDate(rawUnderlying[j]);
                //        break;
                //    }
                //}

                while (!reader.EndOfStream)
                {
                    var line = reader.ReadLine();
                    var values = line.Split(',');
                    DateTime recDate = new DateTime();
                    OptionModel tempOp = new OptionModel();

                    for (int i = 0; i < values.Length; i++)
                    {
                        string colHeader = headers[i];
                        string curVal = values[i];

                        switch (colHeader)
                        {
                            case "Date":
                                recDate = ParseImportDate(curVal);
                                dataDate = recDate;
                                break;
                            case "Exp.Date":
                                tempOp.ExpirationDate = ParseImportDate(curVal); ;
                                break;
                            case "Strike Price":
                                tempOp.StrikePrice = Convert.ToInt32(curVal);
                                break;
                            case "Delta":
                                tempOp.Delta = Convert.ToDouble(curVal);
                                break;
                            case "Market Price":
                                tempOp.MarketPrice = Convert.ToDouble(curVal);
                                break;
                            case "Call/Put":
                                if (curVal == "Call")
                                {
                                    tempOp.OptionType = OptionModel.OptionTypes.Call;
                                }
                                else
                                {
                                    tempOp.OptionType = OptionModel.OptionTypes.Put;
                                }
                                break;
                            case "Theta":
                                tempOp.Theta = Convert.ToDouble(curVal);
                                break;
                            case "Vega":
                                tempOp.Vega = Convert.ToDouble(curVal);
                                break;
                            case "Gamma":
                                tempOp.Gamma = Convert.ToDouble(curVal);
                                break;
                            default: break;
                        }
                    }

                    //Include only multiples of 10
                    if (tempOp.StrikePrice % 10 == 0)
                    {
                        if (!matrixViewModel.MatrixData.ContainsKey(tempOp.ExpirationDate))
                            matrixViewModel.MatrixData.Add(tempOp.ExpirationDate, new List<OptionModel>());

                        matrixViewModel.MatrixData[tempOp.ExpirationDate].Add(tempOp);
                    }
                }
            }
            if (!modelCollection.ContainsKey(dataDate))
                modelCollection.Add(dataDate, matrixViewModel);
        }
    }
}
