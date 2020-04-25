using Microsoft.AspNetCore.Identity.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Cinema.Models
{
    public class CinemaContext : DbContext
    {
        public CinemaContext(DbContextOptions<CinemaContext> options)
            : base(options)
        {
        }

        public DbSet<Employee> Employees { get; set; }

        public DbSet<Movie> Movies { get; set; }

        public DbSet<Room> Rooms { get; set; }

        public DbSet<Screening> Screenings { get; set; }

        public DbSet<Seat> Seats { get; set; }
    }
}
