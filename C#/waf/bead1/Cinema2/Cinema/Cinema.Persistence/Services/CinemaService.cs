using Cinema.Persistence;
using Cinema.Persistence.DTO;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Cinema.Services
{
    public class CinemaService
    {
        private readonly CinemaContext _context;

        public CinemaService(CinemaContext context)
        {
            _context = context;
        }

        public bool UpdateSeat(Seat seat)
        {
            try
            {
                //_context.Update(seat);
                var seatObj = _context.Seats.First(i => i.Id == seat.Id);
                _context.Entry(seatObj).CurrentValues.SetValues(seat);
                _context.SaveChanges();
            }
            catch (DbUpdateConcurrencyException)
            {
                return false;
            }
            catch (DbUpdateException)
            {
                return false;
            }

            return true;
        }

        public IEnumerable<Room> GetRooms()
        {
            return _context.Rooms
                .ToList();
        }

        public Movie CreateMovie(Movie movie)
        {
            try
            {
                _context.Add(movie);
                _context.SaveChanges();
            }
            catch (DbUpdateException)
            {
                return null;
            }

            return movie;
        }

        public List<Seat> GetSeatsByScreeningId(int screeningId)
        {
            return _context.Seats
                .Where(i => i.ScreeningId == screeningId)
                .ToList();
        }

        public Seat GetSeat(int id)
        {
            return _context.Seats
                .Where(i => i.Id == id)
                .FirstOrDefault();
        }

        public Seat CreateSeat(Seat seat)
        {
            try
            {
                _context.Add(seat);
                _context.SaveChanges();
            }
            catch (DbUpdateException)
            {
                return null;
            }

            return seat;
        }

        public Screening CreateScreening(Screening screening)
        {
            try
            {
                _context.Add(screening);
                _context.SaveChanges();
            }
            catch (DbUpdateException)
            {
                return null;
            }

            return screening;
        }

        public Room GetRoom(int roomId)
        {
            return _context.Rooms
                .Where(i => i.Id == roomId)
                .FirstOrDefault();
        }

        public List<Screening> GetScreenings()
        {
            return _context.Screenings
                .ToList();
        }

        public List<Screening> GetScreeningsByMovieId(int movieId)
        {
            return _context.Screenings
                .Where(i => i.MovieId == movieId)
                .ToList();
        }

        public Screening GetScreening(int screeningId)
        {
            return _context.Screenings
                .Where(i => i.Id == screeningId)
                .FirstOrDefault();
        }

        public List<Movie> GetMovies()
        {
            return _context.Movies
                .ToList();
        }

        public Movie GetMovie(int movieId)
        {
            return _context.Movies
                .FirstOrDefault(i => i.Id == movieId);
        }
    }
}
