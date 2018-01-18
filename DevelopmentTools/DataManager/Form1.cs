using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DataManager
{
    public partial class Form1 : Form
    {
        bool stopLoad = false;

        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string path = @"C:\Users\shami\Desktop\OptionEngine\Data\Raw\RUT_temp";
            DirectoryInfo dirInfo = new DirectoryInfo(path);

            int c = 0;
            foreach(var file in dirInfo.GetFiles("*.csv")){
                lblLog.Text += $"\r\n Loading File {file.Name}.";
                ReadData(file.FullName);

                if (stopLoad)
                    break;
                c++;
            }
            lblLog.Text += $"\r\n {c} files loaded.";
        }

        private void ReadData(string dataPath)
        {
            List<string> headers = new List<string>();
            MatrixInstance matrixInstance = new MatrixInstance();
            bool readHeader = true;
            DateTime dataDate = new DateTime();

            using (var reader = new StreamReader(dataPath))
            {
                //Load header values list for mapping
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
                // Read Underlying data line
                var rawUnderlying = reader.ReadLine().Split(',');
                for (int j = 0; j < rawUnderlying.Length; j++)
                {
                    string colHeader = headers[j];
                    if (colHeader == "Date")
                    {
                        dataDate = ParseImportDate(rawUnderlying[j]);
                        break;
                    }
                }
                int row = 3;
                //Read Option Data
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
                                try
                                {
                                    recDate = ParseImportDate(curVal);
                                }catch(Exception ex) {
                                    //AddToLog($" Date missing on row {row}, setting recDate to underlying date.");
                                    recDate = dataDate;
                                    //stopLoad = true;
                                    //return;
                                }
                                break;
                            case "Exp.Date":
                                tempOp.ExpirationDate = ParseImportDate(curVal); ;
                                break;
                            case "Strike Price":
                                tempOp.StrikePrice = Convert.ToDouble(curVal);
                                break;
                            case "Delta":
                                tempOp.Delta = Convert.ToDouble(curVal);
                                break;
                            case "Market Price":
                                tempOp.MarketPrice = Convert.ToDouble(curVal);
                                break;
                            case "Call/Put":
                                if (curVal == "C")
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
                            case "Gamma":
                                tempOp.Gamma = Convert.ToDouble(curVal);
                                break;
                            case "Vega":
                                tempOp.Vega = Convert.ToDouble(curVal);
                                break;
                            default: break;
                        }
                    }

                    if (recDate != dataDate)
                    {
                        AddToLog($"Date for Row:{row} is not consistent with file data");
                        stopLoad = true;
                        return;
                    }

                    if (!matrixInstance.Data.ContainsKey(tempOp.ExpirationDate))
                        matrixInstance.Data.Add(tempOp.ExpirationDate, new List<OptionModel>());

                    matrixInstance.Data[tempOp.ExpirationDate].Add(tempOp);
                    row++;
                }
            }
            ExportMatrix(dataDate, matrixInstance);
        }
        int i = 0;
        private void ExportMatrix(DateTime date, MatrixInstance instance)
        {
            i++;
            string expPath = @"C:\Users\shami\Desktop\OptionEngine\Data\RUT_temp\" + $"RUT-{i} "  + date.ToString("dd-MM-yyyy") + ".csv";

            using (var stream = File.CreateText(expPath))
            {
                stream.WriteLine("Date,Exp.Date,Strike Price,Call/Put,Market Price,Delta,Gamma,Vega,Theta");
                var keys = instance.Data.Keys.ToList();
                foreach(var key in keys)
                {
                    var opDat = instance.Data[key];

                    foreach(var op in opDat)
                    {
                        string row = $"{date.ToString("dd/MM/yyyy")},{op.ExpirationDate.ToString("dd/MM/yyyy")}," +
                            $"{op.StrikePrice}," +
                            $"{op.OptionType},{op.MarketPrice},{op.Delta}," +
                            $"{op.Gamma},{op.Vega},{op.Theta}";
                        stream.WriteLine(row);
                    }
                }
            }
        }

        private void AddToLog(string s)
        {
            lblLog.Text += $"\r\n {s}";
        }

        private DateTime ParseImportDate(string val)
        {
            string date = "";

            date = val.Substring(val.Length - 2);
            date += "-" + val.Substring(val.Length - 4, 2);
            date += "-20" + val.Substring(0, 2);

            return DateTime.Parse(date);
        }
    }
}
