using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Cinema.Persistence;
using Cinema.Persistence.DTO;
using Cinema.Services;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;

namespace Cinema.API.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class ScreeningsController : ControllerBase
    {
        private readonly CinemaService _service;

        public ScreeningsController(CinemaService service)
        {
            _service = service;
        }

        [HttpGet]
        public ActionResult<IEnumerable<ScreeningDto>> GetScreenings()
        {
            var screenings = _service.GetScreenings().Select(screening => (ScreeningDto)screening).ToList();

            List<ScreeningDto> output = new List<ScreeningDto>();

            foreach(var screening in screenings)
            {
                screening.MovieName = _service.GetMovie(screening.MovieId).Name;
                screening.RoomName = _service.GetRoom(screening.RoomId).Name;
                output.Add(screening);
            }
            return output;
        }

        [HttpGet("{id}")]
        public ActionResult<ScreeningDto> GetScreening(Int32 id)
        {
            try
            {
                var screening = (ScreeningDto)_service.GetScreening(id);
                screening.MovieName = _service.GetMovie(screening.MovieId).Name;
                screening.RoomName = _service.GetRoom(screening.RoomId).Name;

                return screening;
            }
            catch (InvalidOperationException)
            {

                return NotFound();
            }
        }

        [HttpPost]
        public ActionResult<ScreeningDto> PostScreening(ScreeningDto screeningDto)
        {
            var screening = _service.CreateScreening((Screening)screeningDto);
            if (screening is null)
            {
                return StatusCode(StatusCodes.Status500InternalServerError);
            }
            else
            {
                return CreatedAtAction(nameof(GetScreening), new { id = screening.Id }, (ScreeningDto)screening);
            }
        }
    }
}