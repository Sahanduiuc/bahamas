using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using bahamas_app.Models;
using Newtonsoft.Json;
using System.IO;
using Microsoft.AspNetCore.Hosting;

namespace bahamas_app.Controllers
{
    public class HomeController : Controller
    {
        private readonly IHostingEnvironment _hostingEnvironment;

        public HomeController(IHostingEnvironment hostingEnvironment)
        {
            _hostingEnvironment = hostingEnvironment;
        }

        public IActionResult Index()
        {
            return View();
        }

        public IActionResult About()
        {
            return View();
        }

        [HttpGet]
        public ActionResult GetCSV()
        {
            //string webRootPath = _hostingEnvironment.WebRootPath;
            //string contentRootPath = _hostingEnvironment.ContentRootPath;

            //string data = "Date,Open,High,Low,Close,Volume\n9-Jun-14,62.40,63.34,61.79,62.88,37617413\n6-Jun-14,63.37,63.48,62.15,62.50,42442096\n5-Jun-14,63.66,64.36,62.82,63.19,47352368\n4-Jun-14,62.45,63.59,62.07,63.34,36513991\n3-Jun-14,62.62,63.42,62.32,62.87,32216707\n2-Jun-14,63.23,63.59,62.05,63.08,35995537";

            //return Content(data);

            FileInfo file = new FileInfo(Path.Combine(_hostingEnvironment.ContentRootPath + "\\Data", @"data.csv"));
            return File(file.Open(FileMode.Open, FileAccess.Read), "text/csv", "data.csv");
        }

        public IActionResult Contact()
        {
            ViewData["Message"] = "Your contact page.";

            return View();
        }

        public IActionResult Error()
        {
            return View();
        }
    }
}
