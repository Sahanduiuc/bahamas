using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Xml;

namespace FundHoldingsEngine
{
    public partial class Form1 : Form
    {
        public Dictionary<string, string> TickerLookUp = new Dictionary<string, string>() {
{"ADOBE SYSTEMS INC","ADBE"},
{"AGRIUM INC","AGU"},
{"ALLISON TRANSMISSION HOLDING","ALSN"},
{"ARMSTRONG WORLD INDUSTRIES","AWI"},
{"BAKER HUGHES INC","BHI"},
{"CBRE GROUP INC","CBG"},
{"HALLIBURTON CO","HAL"},
{"MICROSOFT CORP","MSFT"},
{"MOTOROLA SOLUTIONS INC","MSI"},
{"MSCI INC","MSCI"},
{"ROCKWELL COLLINS INC","COL"},
{"TWENTY-FIRST CENTURY FOX INC","FOX"},
{"VALEANT PHARMACEUTICALS INTE","VRX"},
{"WILLIS GROUP HOLDINGS PLC","WLTW"},
{"TOWERS WATSON & CO","WLTW"},
{"PRECISION CASTPARTS CORP","PCP"},
{"WESCO INTERNATIONAL INC","WCC"},
{"ALLIANCE DATA SYSTEMS CORP","ADS"},
{"WILLIS TOWERS WATSON PLC","WLTW"},
{"DRESSER-RAND GROUP INC","DRC"},
{"EXPEDITORS INTL WASH INC","EXPD"},
{"KAR AUCTION SERVICES INC","KAR"},
{"TWENTY-FIRST CENTURY FOX","FOX"},
{"ARMSTRONG FLOORING INC","AFI"},
{"MORGAN STANLEY","MS"},
{"SEAGATE TECHNOLOGY PLC","STX"},
{"TRINITY INDUSTRIES INC","TRN"},
{"AMERICAN EXPRESS COMPANY","AXP"},
{"ALLISON TRANSMISSION HLDGS I","ALSN"},
{"ARMSTRONG WORLD INDS INC NEW","AWI"},
{"TRINITY INDS INC","TRN"},
{"WILLIS TOWERS WATSON PUB LTD","WLTW"}
        };

        public Dictionary<string, List<List<string>>> HoldingsData = new Dictionary<string, List<List<string>>>();

        public Form1()
        {
            InitializeComponent();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void cmdLoad_Click(object sender, EventArgs e)
        {
            HoldingsData = new Dictionary<string, List<List<string>>>();

            string id = idTxt.Text;

            DirectoryInfo d = new DirectoryInfo(@".\data");
            FileInfo[] Files = d.GetFiles("*.xml"); 

            foreach (FileInfo file in Files)
            {
                string dateRaw = file.Name.Substring(id.Length, 6);
                string date = "20" + dateRaw.Substring(4) + "-" + dateRaw.Substring(0,2) + "-" + dateRaw.Substring(2,2);

                if (!HoldingsData.ContainsKey(date))
                {
                    HoldingsData.Add(date, new List<List<string>>());
                }

                XmlDocument document = new XmlDocument();
                document.Load(@".\data\"+file.Name);

                long sum = 0;
                foreach (XmlElement childNode in document.DocumentElement.ChildNodes)
                {
                    List<string> instrumentData = new List<string>();
   

                    foreach(XmlElement childElem in childNode.ChildNodes)
                    {
                        instrumentData.Add(childElem.InnerText);
                    }

                    instrumentData.Insert(0, TickerLookUp[instrumentData[0].Trim()]);
                    sum += Convert.ToInt64(instrumentData[4]);

                    HoldingsData[date].Add(instrumentData);
                }

                foreach(var dataLine in HoldingsData[date])
                {
                    dataLine.Add((((Convert.ToInt64(dataLine[4]) * 1.0) / (sum * 1.0)) * 100).ToString());
                }

                Console.WriteLine("File Loaded: " + file.Name);
            }

            lblStatus.Text = "Files successfully loaded";
        }

        private void cmdProcess_Click(object sender, EventArgs e)
        {
            foreach(var date in HoldingsData.Keys)
            {
                foreach(var instrument in HoldingsData[date])
                {
                    string lineData = date;
                    foreach (var obj in instrument)
                    {
                        lineData += "," + obj;
                    }
                    lineData += "\n";
                    File.AppendAllText("HOLDINGS_13F_TCI.csv", lineData);
                }
               
            }
        }
    }
}
