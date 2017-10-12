using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;

namespace BC.Application.Implementations
{
    public class VixAnalyser
    {
        public void ImportDataSet(ref List<SimplePriceCoordinate> dataSet)
        {
            var importedData = CommomFunctions.LoadCSVData(@".\wwwroot\vxdata.csv");
            dataSet = new List<SimplePriceCoordinate>();

            foreach (var data in importedData)
            {
                SimplePriceCoordinate tempPriceCoord;
                tempPriceCoord.date = CommomFunctions.ToUnixTime(Convert.ToDateTime(data[0])) * 1000;
                tempPriceCoord.value = data[1];
                dataSet.Add(tempPriceCoord);
            }
        }
    }

    public class OptionAnalyser
    {
        public void PopulateDataSet(ref Dictionary<OptionModel, List<SimplePriceCoordinate>> optionData)
        {
            optionData = new Dictionary<OptionModel, List<SimplePriceCoordinate>>();

            string[] fileEntries = Directory.GetFiles(@".\wwwroot\UnderlyingOptionsEODQuotes");

            foreach (var file in fileEntries)
            {
                var importedData = CommomFunctions.LoadCSVData(file);

                foreach (var data in importedData.Skip(1))
                {
                    SimplePriceCoordinate tempPriceCoord;
                    tempPriceCoord.date = CommomFunctions.ToUnixTime(Convert.ToDateTime(data[1])) * 1000;
                    tempPriceCoord.value = data[9];

                    OptionModel tempOption = new OptionModel(data[2],
                                            Convert.ToDateTime(data[3]),
                                            Convert.ToDouble(data[4]),
                                            ParseOptionType(data[5]));

                    if (!optionData.ContainsKey(tempOption))
                    {
                        optionData.Add(tempOption, new List<SimplePriceCoordinate>());
                    }
                    optionData[tempOption].Add(tempPriceCoord);
                }
            }
        }

        private OptionModel.OptionType ParseOptionType(string type)
        {
            if (type == "C")
                return OptionModel.OptionType.Call;
            else
                return OptionModel.OptionType.Put;
        }
    }

    public static class CommomFunctions
    {
        #region IO Functions
        public static IEnumerable<string[]> LoadCSVData(string path)
        {
            var importData = System.IO.File.ReadLines(path).Select(a => a.Split(','));
            return importData;
        }
        #endregion

        #region Convertors
        public static long ToUnixTime(DateTime date)
        {
            var epoch = new DateTime(1970, 1, 1, 0, 0, 0, DateTimeKind.Utc);
            return Convert.ToInt64((date - epoch).TotalSeconds);
        }
        #endregion
    }
}
