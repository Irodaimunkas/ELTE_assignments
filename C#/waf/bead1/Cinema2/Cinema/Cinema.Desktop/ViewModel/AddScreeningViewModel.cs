using Cinema.Desktop.Model;
using Cinema.Persistence.DTO;
using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;

namespace Cinema.Desktop.ViewModel
{
    public class AddScreeningViewModel : ViewModelBase
    {
        private readonly CinemaAPIService _service;
        private List<MovieViewModel> _movieList;
        private List<RoomViewModel> _roomList;
        private Int32 _selectedMovie;
        private Int32 _selectedRoom;
        private DateTime _dateTime;

        public List<MovieViewModel> MovieList
        {
            get => _movieList;
            set
            {
                _movieList = value;
                OnPropertyChanged();
            }
        }

        public List<RoomViewModel> RoomList
        {
            get => _roomList;
            set
            {
                _roomList = value;
                OnPropertyChanged();
            }
        }

        public Int32 SelectedMovie
        {
            get => _selectedMovie;
            set
            {
                _selectedMovie = value;
                OnPropertyChanged();
            }
        }

        public Int32 SelectedRoom
        {
            get => _selectedRoom;
            set
            {
                _selectedRoom = value;
                OnPropertyChanged();
            }
        }

        public DateTime Date
        {
            get => _dateTime;
            set
            {
                _dateTime = value;
                OnPropertyChanged();
            }
        }

        public DelegateCommand BuildWindowCommand { get; set; }

        public DelegateCommand AddScreeningCommand { get; set; }

        public event EventHandler AddingScreeningEnded;

        public AddScreeningViewModel(CinemaAPIService service)
        {
            _service = service;

            BuildWindowCommand = new DelegateCommand(_ => OnBuildWindow());
            AddScreeningCommand = new DelegateCommand(_ => OnAddScreening());
        }

        private async void OnAddScreening()
        {
            var screenings = await _service.LoadScreeningsAsync();
            var currentMovie = await _service.GetMovie(SelectedMovie);
            List<ScreeningDto> screeningInSameRoom = new List<ScreeningDto>();
            foreach(var screening in screenings)
            {
                if(screening.RoomId == SelectedRoom)
                {
                    var otherScreeningsMovie = await _service.GetMovie(screening.MovieId);
                    if(screening.StartTime < Date)
                    {
                        if(screening.StartTime.AddMinutes(otherScreeningsMovie.LengthInMinutes + 15) > Date)
                        {
                            MessageBox.Show("Another movie is already playing in there at that time!", "Error!", MessageBoxButton.OK, MessageBoxImage.Error);
                            return;
                        }
                    }
                    else
                    {
                        if (Date.AddMinutes(currentMovie.LengthInMinutes + 15) > screening.StartTime)
                        {
                            MessageBox.Show("Another movie is already playing in there at that time!", "Error!", MessageBoxButton.OK, MessageBoxImage.Error);
                            return;
                        }
                    }
                }
            }

            var upScreening = new ScreeningDto
            {
                MovieId = SelectedMovie,
                RoomId = SelectedRoom,
                StartTime = Date
            };

            _service.CreateScreening(upScreening);

            AddingScreeningEnded?.Invoke(this, EventArgs.Empty);
        }

        private async void OnBuildWindow()
        {
            MovieList = await _service.GetMovies();
            RoomList = await _service.GetRooms();

            SelectedMovie = 1;
            SelectedRoom = 1;

            Date = DateTime.Now;
        }
    }
}
