using Cinema.Desktop.Model;
using Cinema.Persistence.DTO;
using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;

namespace Cinema.Desktop.ViewModel
{
    public class AddMovieViewModel : ViewModelBase
    {
        private readonly CinemaAPIService _service;
        private string _imagePath;

        public int Id { get; set; }

        public String Name { get; set; }

        public String Director { get; set; }

        public String Synopsis { get; set; }

        public Int32 LengthInMinutes { get; set; }

        public byte[] Image { get; set; }

        public String ImagePath 
        {
            get => _imagePath;
            set
            {
                _imagePath = value;
                OnPropertyChanged();
            }
        }

        public DelegateCommand ChangeImageCommand { get; set; }

        public DelegateCommand AddMovieCommand { get; set; }

        public event EventHandler StartingImageChange;

        public event EventHandler AddingMovieEnded;

        public AddMovieViewModel(CinemaAPIService service)
        {
            _service = service;

            ChangeImageCommand = new DelegateCommand(_ => StartingImageChange?.Invoke(this, EventArgs.Empty));
            AddMovieCommand = new DelegateCommand(_ => AddingMovie());
        }

        private async void AddingMovie()
        {
            if(Name is null || Name.Length <= 0 || Director is null || Director.Length <= 0 || Synopsis is null || Synopsis.Length <= 0 || LengthInMinutes <= 0 || Image is null || Image.Length <= 0)
            {
                MessageBox.Show("Missing information!", "Error!", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            var movie = new MovieDto
            {
                Name = Name,
                Director = Director,
                Synopsis = Synopsis,
                LengthInMinutes = LengthInMinutes,
                Image = Image,
                PostTime = DateTime.Now
            };

            await _service.CreateMovieAsync(movie);

            AddingMovieEnded?.Invoke(this, EventArgs.Empty);
        }
    }
}
