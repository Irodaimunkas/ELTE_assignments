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
    public class MoviesController : ControllerBase
    {
        private readonly CinemaService _service;

        public MoviesController(CinemaService service)
        {
            _service = service;
        }

        [HttpPost]
        public ActionResult<MovieDto> PostMovie(MovieDto movieDto)
        {
            var movie = _service.CreateMovie((Movie)movieDto);
            if (movie is null)
            {
                return StatusCode(StatusCodes.Status500InternalServerError);
            }
            else
            {
                return CreatedAtAction(nameof(GetMovie), new { id = movie.Id }, (MovieDto)movie);
            }
        }

        [HttpGet("{id}")]
        public ActionResult<MovieDto> GetMovie(Int32 id)
        {
            try
            {
                var movie = (MovieDto)_service.GetMovie(id);

                return movie;
            }
            catch (InvalidOperationException)
            {

                return NotFound();
            }
        }

        [HttpGet]
        public ActionResult<List<MovieDto>> GetMovies()
        {
            return _service.GetMovies().Select(movie => (MovieDto)movie).ToList();
        }
    }
}