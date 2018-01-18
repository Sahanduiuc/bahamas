using OptionEngine.Entities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using static OptionEngine.HomeController;

namespace OptionEngine.ViewModels
{
    public class MatrixViewModel
    {
        public Dictionary<DateTime, List<OptionModel>> MatrixData = new Dictionary<DateTime, List<OptionModel>>();

        public MatrixViewModel()
        {

        }

    }
}
