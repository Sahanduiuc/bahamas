using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace BC.Application.Implementations
{
    public class VixViewModel
    {
        private List<SimplePriceCoordinate> data;
        private VixAnalyser analyser;

        public List<SimplePriceCoordinate> Data { get { return data; } }

        public VixViewModel()
        {
            analyser = new VixAnalyser();
            analyser.ImportDataSet(ref data);
        }
    }

    public class OptionViewModel
    {
        private Dictionary<OptionModel, List<SimplePriceCoordinate>> data;
        private OptionAnalyser analyser;

        public List<SimplePriceCoordinate> Data
        {
            get
            {
                return data.ElementAt(350).Value;
            }
        }

        public OptionViewModel()
        {
            analyser = new OptionAnalyser();
            analyser.PopulateDataSet(ref data);
        }
    }
}
