using BC.Application.Implementations;
using Microsoft.AspNetCore.Mvc;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace BC.Application.Controllers
{
    public class NoteBookController : Controller
    {
        public IActionResult Index()
        {
            var model = new NotebookViewModel();
            model.Title = "VXX Analysis";

            TimeSeriesModel tmm = new TimeSeriesModel("VXX Price (Historic)");
            model.TimeSeries.Add(tmm);

            return View(model);
        }

        public JsonResult GetVixData()
        {
            var model = new VixViewModel();
            return Json(model.Data);
        }

        public JsonResult GetOptionData()
        {
            var model = new OptionViewModel();
            return Json(model.Data);
        }
    }
}
