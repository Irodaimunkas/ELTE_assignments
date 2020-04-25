using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Cinema.Models;
using Cinema.Services;
using Microsoft.AspNetCore.Mvc;

namespace Cinema.Controllers
{
    public class MoviesController : Controller
    {
        public readonly CinemaService _service;

        public MoviesController(CinemaService service)
        {
            _service = service;
        }

        public IActionResult Details(int id)
        {
            try
            {
                var item = _service.GetMovie(id);

                if (item == null) throw new Exception();

                ViewData["Screenings"] = _service.GetScreeningsByMovieId(id);

                List<Room> rooms = new List<Room>();
                foreach(var screening in _service.GetScreeningsByMovieId(id))
                {
                    var curr = _service.GetRoom(screening.RoomId);
                    if (!rooms.Contains(curr))
                        rooms.Add(curr);
                }

                ViewData["Rooms"] = rooms;

                return View(item);
            }
            catch (Exception)
            {
                return NotFound();
            }
        }

        public IActionResult DisplayImage(int id)
        {
            var item = _service.GetMovie(id);
            return File(item.Image, "image/jpeg");
        }
    }
}