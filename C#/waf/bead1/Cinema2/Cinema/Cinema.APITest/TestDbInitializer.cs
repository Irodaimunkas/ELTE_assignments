using Cinema.Persistence;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace Cinema.APITest
{
    public static class TestDbInitializer
    {
        public static void Initialize(CinemaContext context)
        {
            var bladerunnerPath = Path.Combine("../Cinema.Persistence/App_Data", "blade_runner_2049.jpg");
            var gbphPath = Path.Combine("../Cinema.Persistence/App_Data", "grand_budapest_hotel.jpg");
            var swrosPath = Path.Combine("../Cinema.Persistence/App_Data", "sw9.jpg");
            var alienPath = Path.Combine("../Cinema.Persistence/App_Data", "alien.jpg");
            var scottpPath = Path.Combine("../Cinema.Persistence/App_Data", "scottp.jpg");
            var midsPath = Path.Combine("../Cinema.Persistence/App_Data", "midsommar.jpg");

            IList<Movie> defaultMovies = new List<Movie>();
            IList<Room> defaultRooms = new List<Room>();
            IList<Screening> defaultScreenings = new List<Screening>();

            defaultMovies.Add(new Movie
            {
                Name = "Blade Runner 2049",
                Director = "Denis Villeneuve",
                Synopsis = "Young Blade Runner K's discovery of a long-buried secret leads him to track down former Blade Runner Rick Deckard, who's been missing for thirty years.",
                LengthInMinutes = 163,
                Image = File.Exists(bladerunnerPath) ? File.ReadAllBytes(bladerunnerPath) : null,
                PostTime = DateTime.Now
            });

            defaultMovies.Add(new Movie
            {
                Name = "The Grand Budapest Hotel",
                Director = "Wes Anderson",
                Synopsis = "A writer encounters the owner of an aging high-class hotel, who tells him of his early years serving as a lobby boy in the hotel's glorious years under an exceptional concierge.",
                LengthInMinutes = 100,
                Image = File.Exists(gbphPath) ? File.ReadAllBytes(gbphPath) : null,
                PostTime = DateTime.Now
            });

            defaultMovies.Add(new Movie
            {
                Name = "Star Wars: Episode IX - The Rise of Skywalker",
                Director = "J.J. Abrams",
                Synopsis = "The surviving members of the resistance face the First Order once again, and the legendary conflict between the Jedi and the Sith reaches its peak bringing the Skywalker saga to its end.",
                LengthInMinutes = 142,
                Image = File.Exists(swrosPath) ? File.ReadAllBytes(swrosPath) : null,
                PostTime = DateTime.Now
            });

            defaultMovies.Add(new Movie
            {
                Name = "Alien",
                Director = "Ridley Scott",
                Synopsis = "After a space merchant vessel receives an unknown transmission as a distress call, one of the crew is attacked by a mysterious life form and they soon realize that its life cycle has merely begun.",
                LengthInMinutes = 117,
                Image = File.Exists(alienPath) ? File.ReadAllBytes(alienPath) : null,
                PostTime = DateTime.Now
            });

            defaultMovies.Add(new Movie
            {
                Name = "Scott Pilgrim vs. the World",
                Director = "Edgar Wright",
                Synopsis = "Scott Pilgrim must defeat his new girlfriend's seven evil exes in order to win her heart.",
                LengthInMinutes = 112,
                Image = File.Exists(scottpPath) ? File.ReadAllBytes(scottpPath) : null,
                PostTime = DateTime.Now
            });

            defaultMovies.Add(new Movie
            {
                Name = "Midsommar",
                Director = "Ari Aster",
                Synopsis = "A couple travels to Sweden to visit a rural hometown's fabled mid-summer festival. What begins as an idyllic retreat quickly devolves into an increasingly violent and bizarre competition at the hands of a pagan cult.",
                LengthInMinutes = 148,
                Image = File.Exists(midsPath) ? File.ReadAllBytes(midsPath) : null,
                PostTime = DateTime.Now
            });

            foreach (Movie movie in defaultMovies)
                context.Movies.Add(movie);

            defaultRooms.Add(new Room
            {
                Name = "Room Dave",
                Rows = 10,
                Columns = 10
            });

            defaultRooms.Add(new Room
            {
                Name = "Room Alexa",
                Rows = 5,
                Columns = 10
            });

            defaultRooms.Add(new Room
            {
                Name = "Room Geralt",
                Rows = 10,
                Columns = 5
            });

            foreach (Room room in defaultRooms)
                context.Rooms.Add(room);

            context.SaveChanges();

            defaultScreenings.Add(new Screening
            {
                MovieId = context.Movies.FirstOrDefault(i => i.Name == "Blade Runner 2049").Id,
                StartTime = new DateTime(2020, 10, 11, 16, 00, 00),
                RoomId = context.Rooms.FirstOrDefault(i => i.Name == "Room Geralt").Id
            });

            defaultScreenings.Add(new Screening
            {
                MovieId = context.Movies.FirstOrDefault(i => i.Name == "Star Wars: Episode IX - The Rise of Skywalker").Id,
                StartTime = new DateTime(2020, 10, 11, 16, 00, 00),
                RoomId = context.Rooms.FirstOrDefault(i => i.Name == "Room Dave").Id
            });

            defaultScreenings.Add(new Screening
            {
                MovieId = context.Movies.FirstOrDefault(i => i.Name == "Blade Runner 2049").Id,
                StartTime = new DateTime(2020, 10, 11, 20, 00, 00),
                RoomId = context.Rooms.FirstOrDefault(i => i.Name == "Room Dave").Id
            });

            defaultScreenings.Add(new Screening
            {
                MovieId = context.Movies.FirstOrDefault(i => i.Name == "Blade Runner 2049").Id,
                StartTime = new DateTime(2020, 11, 16, 20, 00, 00),
                RoomId = context.Rooms.FirstOrDefault(i => i.Name == "Room Geralt").Id
            });

            defaultScreenings.Add(new Screening
            {
                MovieId = context.Movies.FirstOrDefault(i => i.Name == "The Grand Budapest Hotel").Id,
                StartTime = new DateTime(2020, 10, 12, 12, 00, 00),
                RoomId = context.Rooms.FirstOrDefault(i => i.Name == "Room Dave").Id
            });

            defaultScreenings.Add(new Screening
            {
                MovieId = context.Movies.FirstOrDefault(i => i.Name == "Alien").Id,
                StartTime = new DateTime(2020, 10, 09, 09, 30, 00),
                RoomId = context.Rooms.FirstOrDefault(i => i.Name == "Room Geralt").Id
            });

            defaultScreenings.Add(new Screening
            {
                MovieId = context.Movies.FirstOrDefault(i => i.Name == "Scott Pilgrim vs. the World").Id,
                StartTime = new DateTime(2020, 09, 15, 16, 00, 00),
                RoomId = context.Rooms.FirstOrDefault(i => i.Name == "Room Alexa").Id
            });

            defaultScreenings.Add(new Screening
            {
                MovieId = context.Movies.FirstOrDefault(i => i.Name == "Midsommar").Id,
                StartTime = new DateTime(2020, 10, 11, 15, 30, 00),
                RoomId = context.Rooms.FirstOrDefault(i => i.Name == "Room Alexa").Id
            });

            foreach (Screening screening in defaultScreenings)
                context.Screenings.Add(screening);

            context.SaveChanges();
        }
    }
}
