using Cinema.Desktop.Model;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Collections.Specialized;
using System.Linq;
using System.Net.Http;
using System.Text;

namespace Cinema.Desktop.ViewModel
{
    public class MainWindowViewModel : ViewModelBase
    {
        private readonly CinemaAPIService _service;
        private ObservableCollection<ScreeningViewModel> _screenings;
        private ScreeningViewModel _selectedScreening;

        /// <summary>
        /// Observables
        /// </summary>
        public ObservableCollection<ScreeningViewModel> Screenings
        {
            get => _screenings;
            set
            {
                _screenings = value;
                OnPropertyChanged();
            }
        }

        /// <summary>
        /// Fields
        /// </summary>
        public ScreeningViewModel SelectedScreening
        {
            get => _selectedScreening;
            set
            {
                _selectedScreening = value;
                OnPropertyChanged();
            }
        }

        /// <summary>
        /// Commands
        /// </summary>
        public DelegateCommand LogoutCommand { get; private set; }

        public DelegateCommand LoadScreeningsCommand { get; private set; }

        public DelegateCommand BuyTicketCommand { get; private set; }

        public DelegateCommand AddMovieCommand { get; private set; }

        public DelegateCommand AddScreeningCommand { get; private set; }


        /// <summary>
        /// Event Handlers
        /// </summary>
        public event EventHandler LogoutSucceeded;

        public event EventHandler BuyingTicket;

        public event EventHandler AddingMovie;

        public event EventHandler AddingScreening;

        /// <summary>
        /// Constructor
        /// </summary>
        public MainWindowViewModel(CinemaAPIService service)
        {
            _service = service;

            LogoutCommand = new DelegateCommand(_ => LogoutAsync());
            LoadScreeningsCommand = new DelegateCommand(_ => LoadScreeningsAsync());

            BuyTicketCommand = new DelegateCommand(_ => BuyTicket());
            AddMovieCommand = new DelegateCommand(_ => AddMovie());
            AddScreeningCommand = new DelegateCommand(_ => AddScreening());
        }

        private void AddScreening()
        {
            AddingScreening?.Invoke(this, EventArgs.Empty);
        }

        private void AddMovie()
        {
            AddingMovie?.Invoke(this, EventArgs.Empty);
        }


        /// <summary>
        /// Methods
        /// </summary>
        private void BuyTicket()
        {
            BuyingTicket?.Invoke(this, EventArgs.Empty);
        }

        private async void LoadScreeningsAsync()
        {
            try
            {
                Screenings = new ObservableCollection<ScreeningViewModel>((await _service.LoadScreeningsAsync()).Select(list =>
                {
                    var listVm = (ScreeningViewModel)list;
                    return listVm;
                }));
                SelectedScreening = Screenings.FirstOrDefault();
            }
            catch (Exception ex) when (ex is NetworkException || ex is HttpRequestException)
            {
                OnMessageApplication($"Unexpected error occured! ({ex.Message})");
            }
        }

        private async void LogoutAsync()
        {
            try
            {
                await _service.LogoutAsync();
                OnLogoutSuccess();
            }
            catch (Exception ex) when (ex is NetworkException || ex is HttpRequestException)
            {
                OnMessageApplication($"Unexpected error occured! ({ex.Message})");
            }
        }

        private void OnLogoutSuccess()
        {
            LogoutSucceeded?.Invoke(this, EventArgs.Empty);
        }
    }
}
