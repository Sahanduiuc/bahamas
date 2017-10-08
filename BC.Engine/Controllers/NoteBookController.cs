using BC.Engine.Implementations;
using Microsoft.AspNetCore.Mvc;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace BC.Engine.Controllers
{
    [Route("api/[controller]")]
    public class NoteBookController : Controller
    {
        [HttpGet]
        public IActionResult Get()
        {
            return Json(null);
        }

        [Route("GetVixData")]
        [HttpGet]
        public IActionResult GetVixData()
        {
            var model = new VixViewModel();
            return Json(model.Data);
        }  
        
        [Route("GetOptionData")]
        [HttpGet]
        public IActionResult GetOptionData()
        {
            var model = new OptionViewModel();
            return Json(model.Data);
        }
    }
}
