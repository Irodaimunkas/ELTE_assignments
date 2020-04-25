using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Cinema.Models;
using Cinema.Services;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;

namespace Cinema.Controllers
{
    public class ScreeningsController : Controller
    {
        public readonly CinemaService _service;

        public ScreeningsController(CinemaService service)
        {
            _service = service;
        }

        public IActionResult Booking(int id)
        {
            var screening = _service.GetScreening(id);

            ViewData["Screening"] = screening;
            ViewData["Movie"] = _service.GetMovie(screening.MovieId);

            var room = _service.GetRoom(screening.RoomId);

            ViewData["Room"] = room;

            if(_service.GetSeatsByScreeningId(id).Count <= 0)
            {
                for(Int32 i = 0; i < room.Rows; i++)
                {
                    for (Int32 j = 0; j < room.Columns; j++)
                    {
                        _service.CreateSeat(new Seat
                        {
                            ScreeningId = screening.Id,
                            RoomId = room.Id,
                            Row = i,
                            Column = j,
                            Status = Status.Free
                        });
                    }
                }
            }

            ViewData["Seats"] = _service.GetSeatsByScreeningId(id);

            return View();
        }

        [HttpPost]
        public IActionResult Booking(SeatsViewModel viewModel, Int32 movieId)
        {
            if (ModelState.IsValid)
            {
                var seatsInDatab = _service.GetSeatsByScreeningId(viewModel.ScreeningId);

                foreach(var seat in seatsInDatab)
                {
                    if(seat.Status != viewModel.Seats[seat.Row][seat.Column])
                    {
                        var upSeat = new Seat
                        {
                            Id = seat.Id,
                            ScreeningId = seat.ScreeningId,
                            RoomId = seat.RoomId,
                            Row = seat.Row,
                            Column = seat.Column,
                            Status = viewModel.Seats[seat.Row][seat.Column],
                            BookerName = viewModel.BookerName,
                            PhoneNumber = viewModel.PhoneNumber
                        };
                        _service.UpdateSeat(upSeat);
                    }
                }

                return RedirectToAction("Index", "Home");
            }

            ViewData["Screening"] = _service.GetScreening(viewModel.ScreeningId);
            ViewData["Room"] = _service.GetRoom(viewModel.RoomId);
            ViewData["Movie"] = _service.GetMovie(movieId);
            ViewData["Seats"] = _service.GetSeatsByScreeningId(viewModel.ScreeningId);
            return View(viewModel);
        }
    }
}
