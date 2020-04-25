using Cinema.Models;
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

        public List<Seat> GetSeatsByScreeningId(int screeningId)
        {
            return _context.Seats
                .Where(i => i.ScreeningId == screeningId)
                .ToList();
        }

        public bool CreateSeat(Seat seat)
        {
            try
            {
                _context.Add(seat);
                _context.SaveChanges();
            }
            catch (DbUpdateException)
            {
                return false;
            }

            return true;
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
