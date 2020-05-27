using Cinema.API.Controllers;
using Cinema.Persistence;
using Cinema.Persistence.DTO;
using Cinema.Services;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using Xunit;

namespace Cinema.APITest
{
    public class APITest : IDisposable
    {
        private readonly CinemaContext _context;
        private readonly CinemaService _service;
        private readonly SeatsController _seatsController;
        private readonly MoviesController _movieController;
        private readonly RoomsController _roomController;
        private readonly ScreeningsController _screeningsController;

        public APITest()
        {
            var options = new DbContextOptionsBuilder<CinemaContext>()
                .UseInMemoryDatabase("TestDb")
                .Options;

            _context = new CinemaContext(options);
            TestDbInitializer.Initialize(_context);
            _service = new CinemaService(_context);
            _seatsController = new SeatsController(_service);
            _movieController = new MoviesController(_service);
            _roomController = new RoomsController(_service);
            _screeningsController = new ScreeningsController(_service);

            for (Int32 i = 0; i < 10; i++)
            {
                for (Int32 j = 0; j < 10; j++)
                {
                    _service.CreateSeat(new Seat
                    {
                        ScreeningId = 4,
                        RoomId = 1,
                        Column = j,
                        Row = i,
                        BookerName = "trial_n",
                        PhoneNumber = "+36702795955"
                    });
                }
            }
        }

        public void Dispose()
        {
            _context.Database.EnsureDeleted();
            _context.Dispose();
        }

        [Fact]
        public void GetMoviesTest()
        {
            var result = _movieController.GetMovies();

            var content = Assert.IsAssignableFrom<List<MovieDto>>(result.Value);
            Assert.Equal(6, content.Count);
        }

        [Theory]
        [InlineData(1)]
        [InlineData(2)]
        [InlineData(3)]
        public void GetMovieTest(Int32 id)
        {
            // Act
            var result = _movieController.GetMovie(id);

            // Assert
            var content = Assert.IsAssignableFrom<MovieDto>(result.Value);
            Assert.Equal(id, content.Id);
        }

        [Fact]
        public void PostMovieTest()
        {
            var midsPath = Path.Combine("../Cinema.Persistence/App_Data", "midsommar.jpg");

            // Arrange
            var newMovie = new MovieDto
            {
                Name = "trial",
                Director = "trial_d",
                PostTime = DateTime.Now,
                LengthInMinutes = 150,
                Synopsis = "trial_s",
                Image = File.Exists(midsPath) ? File.ReadAllBytes(midsPath) : null
            };
            var count = _context.Movies.Count();

            // Act
            var result = _movieController.PostMovie(newMovie);

            // Assert
            var objectResult = Assert.IsAssignableFrom<CreatedAtActionResult>(result.Result);
            var content = Assert.IsAssignableFrom<MovieDto>(objectResult.Value);
            Assert.Equal(count + 1, _context.Movies.Count());
        }

        [Theory]
        [InlineData(1)]
        [InlineData(2)]
        [InlineData(3)]
        public void GetRoomTest(Int32 id)
        {
            var result = _roomController.GetRoom(id);

            // Assert
            var content = Assert.IsAssignableFrom<RoomDto>(result.Value);
            Assert.Equal(id, content.Id);
        }

        [Fact]
        public void GetRoomsTest()
        {
            var result = _roomController.GetRooms();

            // Assert
            var content = Assert.IsAssignableFrom<List<RoomDto>>(result.Value);
            Assert.Equal(3, content.Count());
        }

        [Fact]
        public void GetScreeningsTest()
        {
            // Act
            var result = _screeningsController.GetScreenings();

            // Assert
            var content = Assert.IsAssignableFrom<IEnumerable<ScreeningDto>>(result.Value);
            Assert.Equal(8, content.Count());
        }

        [Theory]
        [InlineData(1)]
        [InlineData(2)]
        [InlineData(3)]
        public void GetScreening(Int32 id)
        {
            // Act
            var result = _screeningsController.GetScreening(id);

            // Assert
            var content = Assert.IsAssignableFrom<ScreeningDto>(result.Value);
            Assert.Equal(id, content.Id);
        }

        [Fact]
        public void PostScreeningTest()
        {
            // Arrange
            var newScreening = new ScreeningDto
            {
                MovieId = 2,
                RoomId = 2,
                StartTime = new DateTime(2025, 05, 05, 05, 05, 05)
            };
            var count = _context.Screenings.Count();

            // Act
            var result = _screeningsController.PostScreening(newScreening);

            // Assert
            var objectResult = Assert.IsAssignableFrom<CreatedAtActionResult>(result.Result);
            var content = Assert.IsAssignableFrom<ScreeningDto>(objectResult.Value);
            Assert.Equal(count + 1, _context.Screenings.Count());
        }

        [Fact]
        public void GetSeatsTest()
        {
            // Act
            var result = _seatsController.GetSeats(4);

            // Assert
            var content = Assert.IsAssignableFrom<IEnumerable<SeatDto>>(result.Value);
            Assert.Equal(100, content.Count());
        }

        [Theory]
        [InlineData(1)]
        [InlineData(2)]
        [InlineData(3)]
        public void GetSeatTest(Int32 id)
        {
            // Act
            var result = _seatsController.GetSeat(id);

            // Assert
            var content = Assert.IsAssignableFrom<SeatDto>(result.Value);
            Assert.Equal(id, content.Id);
        }

        [Fact]
        public void PutSeatTest()
        {
            // Arrange
            var newSeat = new SeatDto
            {
                Id = 4,
                BookerName = "trial_overwrite"
            };
            var result = _seatsController.PutSeat(4, newSeat);

            // Assert
            var objectResult = _service.GetSeat(4);
            Assert.Equal("trial_overwrite", objectResult.BookerName);
        }
    }
}
