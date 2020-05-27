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
    public class SeatsController : ControllerBase
    {
        private readonly CinemaService _service;

        public SeatsController(CinemaService service)
        {
            _service = service;
        }

        [HttpGet("{id}")]
        public ActionResult<IEnumerable<SeatDto>> GetSeats(Int32 id)
        {
            try
            {
                var seats = _service.GetSeatsByScreeningId(id).Select(seat => (SeatDto)seat).ToList();

                return seats;
            }
            catch (InvalidOperationException)
            {

                return NotFound();
            }
        }

        public ActionResult<SeatDto> GetSeat(Int32 id)
        {
            try
            {
                return (SeatDto)_service.GetSeat(id);
            }
            catch (InvalidOperationException)
            {

                return NotFound();
            }
        }

        [HttpPost]
        public ActionResult<SeatDto> PostSeat(SeatDto seatDto)
        {
            var seat = _service.CreateSeat((Seat)seatDto);
            if (seat is null)
            {
                return StatusCode(StatusCodes.Status500InternalServerError);
            }
            else
            {
                return CreatedAtAction(nameof(GetSeat), new { id = seat.Id }, (SeatDto)seat);
            }
        }

        [HttpPut("{id}")]
        public IActionResult PutSeat(Int32 id, SeatDto seat)
        {
            if (id != seat.Id)
            {
                return BadRequest();
            }

            if (_service.UpdateSeat((Seat)seat))
            {
                return Ok();
            }
            else
            {
                return StatusCode(StatusCodes.Status500InternalServerError);
            }
        }
    }
}