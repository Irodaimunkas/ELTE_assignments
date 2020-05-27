using Cinema.Desktop.ViewModel;
using Cinema.Persistence.DTO;
using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;

namespace Cinema.Desktop.Model
{
    public class CinemaAPIService
    {
        private readonly HttpClient _client;

        public CinemaAPIService(string baseAddress)
        {
            _client = new HttpClient()
            {
                BaseAddress = new Uri(baseAddress)
            };
        }

        public async Task<bool> LoginAsync(string name, string password)
        {
            LoginDto user = new LoginDto
            {
                UserName = name,
                Password = password
            };

            HttpResponseMessage response = await _client.PostAsJsonAsync("api/Account/Login", user);

            if (response.IsSuccessStatusCode)
            {
                return true;
            }

            if (response.StatusCode == HttpStatusCode.Unauthorized)
            {
                return false;
            }

            throw new NetworkException("Service returned response: " + response.StatusCode);
        }

        public async Task LogoutAsync()
        {
            HttpResponseMessage response = await _client.PostAsync("api/Account/Logout", null);

            if (response.IsSuccessStatusCode)
            {
                return;
            }

            throw new NetworkException("Service returned response: " + response.StatusCode);
        }

        public async Task<IEnumerable<ScreeningDto>> LoadScreeningsAsync()
        {
            HttpResponseMessage response = await _client.GetAsync("api/Screenings/");

            if (response.IsSuccessStatusCode)
            {
                return await response.Content.ReadAsAsync<IEnumerable<ScreeningDto>>();
            }

            throw new NetworkException("Service returned response: " + response.StatusCode);
        }

        public async Task<List<RoomViewModel>> GetRooms()
        {
            HttpResponseMessage response = await _client.GetAsync("api/Rooms/");

            if (response.IsSuccessStatusCode)
            {
                return await response.Content.ReadAsAsync<List<RoomViewModel>>();
            }

            throw new NetworkException("Service returned response: " + response.StatusCode);
        }

        public async Task<MovieDto> GetMovie(int movieId)
        {
            HttpResponseMessage response = await _client.GetAsync("api/Movies/" + movieId);

            if (response.IsSuccessStatusCode)
            {
                return await response.Content.ReadAsAsync<MovieDto>();
            }

            throw new NetworkException("Service returned response: " + response.StatusCode);
        }

        public async Task<List<MovieViewModel>> GetMovies()
        {
            HttpResponseMessage response = await _client.GetAsync("api/Movies/");

            if (response.IsSuccessStatusCode)
            {
                return await response.Content.ReadAsAsync<List<MovieViewModel>>();
            }

            throw new NetworkException("Service returned response: " + response.StatusCode);
        }

        public async Task<MovieDto> CreateMovieAsync(MovieDto movie)
        {
            HttpResponseMessage response = await _client.PostAsJsonAsync("api/Movies/", movie);
            movie.Id = (await response.Content.ReadAsAsync<MovieDto>()).Id;

            if (!response.IsSuccessStatusCode)
            {
                throw new NetworkException("Service returned response: " + response.StatusCode);
            }

            return movie;
        }

        public async Task<ScreeningDto> CreateScreening(ScreeningDto screening)
        {
            HttpResponseMessage response = await _client.PostAsJsonAsync("api/Screenings/", screening);
            screening.Id = (await response.Content.ReadAsAsync<MovieDto>()).Id;

            if (!response.IsSuccessStatusCode)
            {
                throw new NetworkException("Service returned response: " + response.StatusCode);
            }

            return screening;
        }

        public async Task<RoomDto> GetRoom(int roomId)
        {
            HttpResponseMessage response = await _client.GetAsync("api/Rooms/" + roomId);

            if (response.IsSuccessStatusCode)
            {
                return await response.Content.ReadAsAsync<RoomDto>();
            }

            throw new NetworkException("Service returned response: " + response.StatusCode);
        }

        public async Task<IList<SeatDto>> GetSeats(int screeningId)
        {
            HttpResponseMessage response = await _client.GetAsync("api/Seats/" + screeningId);

            if (response.IsSuccessStatusCode)
            {
                return await response.Content.ReadAsAsync<IList<SeatDto>>();
            }

            throw new NetworkException("Service returned response: " + response.StatusCode);
        }

        internal async Task<SeatDto> CreateSeat(SeatDto seat)
        {
            HttpResponseMessage response = await _client.PostAsJsonAsync("api/Seats/", seat);
            seat.Id = (await response.Content.ReadAsAsync<SeatDto>()).Id;

            if (!response.IsSuccessStatusCode)
            {
                throw new NetworkException("Service returned response: " + response.StatusCode);
            }

            return seat;
        }

        internal async void UpdateSeat(SeatDto upSeat)
        {
            HttpResponseMessage response = await _client.PutAsJsonAsync($"api/Seats/{upSeat.Id}", upSeat);

            if (!response.IsSuccessStatusCode)
            {
                throw new NetworkException("Service returned response: " + response.StatusCode);
            }
        }
    }
}
