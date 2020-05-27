using Cinema.Persistence.DTO;
using System;
using System.Collections.Generic;
using System.Text;

namespace Cinema.Desktop.ViewModel
{
    public class ScreeningViewModel : ViewModelBase
    {
        private int _id;
        private int _movieId;
        private DateTime _startTime;
        private int _roomId;
        private string _movieName;
        private string _roomName;

        public int Id 
        { 
            get => _id;
            set {
                _id = value;
                OnPropertyChanged();
            }
        }
        public int MovieId
        {
            get => _movieId;
            set
            {
                _movieId = value;
                OnPropertyChanged();
            }
        }

        public DateTime StartTime
        {
            get => _startTime;
            set
            {
                _startTime = value;
                OnPropertyChanged();
            }
        }
        public int RoomId
        {
            get => _roomId;
            set
            {
                _roomId = value;
                OnPropertyChanged();
            }
        }

        public string RoomName
        {
            get => _roomName;
            set
            {
                _roomName = value;
                OnPropertyChanged();
            }
        }

        public string MovieName
        {
            get => _movieName;
            set
            {
                _movieName = value;
                OnPropertyChanged();
            }
        }

        public static explicit operator ScreeningViewModel(ScreeningDto dto) => new ScreeningViewModel
        {
            Id = dto.Id,
            MovieId = dto.MovieId,
            StartTime = dto.StartTime,
            RoomId = dto.RoomId,
            MovieName = dto.MovieName,
            RoomName = dto.RoomName
        };

        public static explicit operator ScreeningDto(ScreeningViewModel i) => new ScreeningDto
        {
            Id = i.Id,
            MovieId = i.MovieId,
            StartTime = i.StartTime,
            RoomId = i.RoomId,
            MovieName = i.MovieName,
            RoomName = i.RoomName
        };
    }
}
