using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Cinema.Persistence.DTO;
using Cinema.Services;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;

namespace Cinema.API.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class RoomsController : ControllerBase
    {
        private readonly CinemaService _service;

        public RoomsController(CinemaService service)
        {
            _service = service;
        }

        [HttpGet("{id}")]
        public ActionResult<RoomDto> GetRoom(Int32 id)
        {
            try
            {
                var screening = (RoomDto)_service.GetRoom(id);

                return screening;
            }
            catch (InvalidOperationException)
            {

                return NotFound();
            }
        }

        [HttpGet]
        public ActionResult<List<RoomDto>> GetRooms()
        {
            return _service.GetRooms().Select(room => (RoomDto)room).ToList();
        }
    }
}