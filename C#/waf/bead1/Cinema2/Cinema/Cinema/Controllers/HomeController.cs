using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using Cinema.Services;

namespace Cinema.Controllers
{
    public class HomeController : Controller
    {
        private readonly ILogger<HomeController> _logger;
        private readonly CinemaService _service;

        public HomeController(ILogger<HomeController> logger, 
            CinemaService service)
        {
            _logger = logger;
            _service = service;
        }

        public IActionResult Index()
        {
            ViewData["Movies"] = _service.GetMovies();

            var screenings = _service.GetScreenings();
            return View(screenings);
        }
    }
}
