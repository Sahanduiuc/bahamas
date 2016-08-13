using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.IO;
using TicTacTec.TA.Library;

namespace talib_test
{
    public class Macdres
    {
        public int Index { get; set; }
        public double Macd { get; set; }
        public double Signal { get; set; }
        public double MacdHistogram { get; set; }
    }

    /// <summary>
    /// Interaction logic for Window1.xaml
    /// </summary>
    public partial class Window1 : Window
    {

        public static List<string[]> parseCSV(string path)
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


        public Window1()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            int i;
            string curDir=Directory.GetCurrentDirectory();
            string fileName=curDir+@"\msft.csv";
            List<string[]> parsedData = parseCSV(fileName);
            int nCount = parsedData.Count;
            double[] closingPricesArr = new double[nCount - 1];
            for (i = 0; i < nCount - 1; i++)
                closingPricesArr[i] = Convert.ToDouble(parsedData[i + 1][6]);

            int startIdx = 100;
            int endIdx = 1000;
            int optInFastPeriod = 12;
            int optInSlowPeriod = 26;
            int optInSignalPeriod = 9;
            double[] inReal = closingPricesArr;

            int outBegIdx;
            int outNBElement;

            double[] outMACD = new double[endIdx - startIdx+1];
            double[] outMACDSignal = new double[endIdx - startIdx + 1];
            double[] outMACDHist = new double[endIdx - startIdx + 1];

            Core.RetCode res = Core.Macd(startIdx, endIdx, inReal, optInFastPeriod, optInSlowPeriod, optInSignalPeriod, out  outBegIdx, out  outNBElement, outMACD, outMACDSignal, outMACDHist);
            List<Macdres> resarr = new List<Macdres>(endIdx - startIdx + 1);
            int counter=0;
            for (i = startIdx; i < endIdx - startIdx + 1; i++)
            {
                Macdres macdres = new Macdres();
                macdres.Index = i;
                macdres.Macd = outMACD[counter];
                macdres.Signal = outMACDSignal[counter];
                macdres.MacdHistogram = outMACDHist[counter];
                resarr.Add(macdres);
                counter++;
            }
            listView1.ItemsSource = resarr;
        }
    }
}
