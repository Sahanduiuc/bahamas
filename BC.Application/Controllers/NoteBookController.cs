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
            return View();
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
