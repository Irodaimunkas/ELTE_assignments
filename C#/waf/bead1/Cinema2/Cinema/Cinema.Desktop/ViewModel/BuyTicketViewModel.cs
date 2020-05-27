using Cinema.Desktop.Model;
using Cinema.Persistence.DTO;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Text;
using System.Text.RegularExpressions;
using System.Windows;

namespace Cinema.Desktop.ViewModel
{
    public class BuyTicketViewModel : ViewModelBase
    {
        private readonly CinemaAPIService _service;
        private int _screeningId;
        private int _rows;
        private int _columns;
        private string _name;
        private string _phoneNumber;
        private MainWindowViewModel _mainWindowViewModel;

        public ObservableCollection<SeatViewModel> Seats { get; set; }

        public int ScreeningId
        {
            get => _screeningId;
            set
            {
                _screeningId = value;
                OnPropertyChanged();
            }
        }

        public int Rows
        {
            get => _rows;
            set
            {
                _rows = value;
                OnPropertyChanged();
            }
        }

        public int Columns
        {
            get => _columns;
            set
            {
                _columns = value;
                OnPropertyChanged();
            }
        }

        public string Name
        {
            get => _name;
            set
            {
                _name = value;
                OnPropertyChanged();
            }
        }

        public string PhoneNumber
        {
            get => _phoneNumber;
            set
            {
                _phoneNumber = value;
                OnPropertyChanged();
            }
        }

        public DelegateCommand BuildWindowCommand { get; private set; }

        public DelegateCommand CheckoutCommand { get; private set; }

        public event EventHandler CheckedOut;

        public BuyTicketViewModel(CinemaAPIService service,
            MainWindowViewModel mainWindowViewModel)
        {
            _service = service;
            _mainWindowViewModel = mainWindowViewModel;

            BuildWindowCommand = new DelegateCommand(_ => SetWindow());
            CheckoutCommand = new DelegateCommand(_ => Checkout());

            Seats = new ObservableCollection<SeatViewModel>();
        }

        private void Checkout()
        {
            if(PhoneNumber is null || PhoneNumber.Length <= 0)
            {
                MessageBox.Show("Phone number required!", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }
            else if(!Regex.Match(PhoneNumber, @"^\+?[0-9]{2}[0-9]{9}$").Success)
            {
                MessageBox.Show("Not a phone number!", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            if(Name is null || Name.Length <= 0)
            {
                MessageBox.Show("Name required!", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            foreach(var seat in Seats)
            {
                if(seat.Status != seat.NewStatus)
                {
                    var upSeat = new SeatDto
                    {
                        Id = seat.Id,
                        ScreeningId = ScreeningId,
                        RoomId = _mainWindowViewModel.SelectedScreening.RoomId,
                        Row = seat.X,
                        Column = seat.Y,
                        Status = seat.NewStatus,
                        BookerName = Name,
                        PhoneNumber = PhoneNumber
                    };

                    _service.UpdateSeat(upSeat);
                }
            }
            CheckedOut?.Invoke(this, EventArgs.Empty);
        }

        private async void SetWindow()
        {
            Seats.Clear();
            ScreeningId = _mainWindowViewModel.SelectedScreening.Id;
            var room = await _service.GetRoom(_mainWindowViewModel.SelectedScreening.RoomId);
            Rows = room.Rows;
            Columns = room.Columns;

            var seats = await _service.GetSeats(ScreeningId);

            if(seats.Count <= 0)
            {
                for (Int32 i = 0; i < Rows; i++)
                {
                    for (Int32 j = 0; j < Columns; j++)
                    {
                        var seat = await _service.CreateSeat(new SeatDto
                        {
                            ScreeningId = _mainWindowViewModel.SelectedScreening.Id,
                            RoomId = room.Id,
                            Row = i,
                            Column = j,
                            Status = Persistence.Status.Free
                        });

                        Seats.Add(new SeatViewModel
                        {
                            Id = seat.Id,
                            Status = Persistence.Status.Free,
                            NewStatus = Persistence.Status.Free,
                            Color = "White",
                            X = i,
                            Y = j,
                            Number = i * Math.Max(Rows, Columns) + j,
                            ClickCommand = new DelegateCommand(param => OnClickCommand(Convert.ToInt32(param)))
                        }); ;
                    }
                }
            }
            else
            {
                foreach (var seat in seats)
                {
                    Seats.Add(new SeatViewModel
                    {
                        Id = seat.Id,
                        Status = seat.Status,
                        NewStatus = seat.Status,
                        X = seat.Row,
                        Y = seat.Column,
                        Number = seat.Row * Math.Max(Rows, Columns) + seat.Column,
                        PhoneNumber = seat.PhoneNumber,
                        Name = seat.BookerName,
                        ClickCommand = new DelegateCommand(param => OnClickCommand(Convert.ToInt32(param)))
                    });
                }

                foreach (var seat in Seats)
                {
                    switch (seat.Status)
                    {
                        case Persistence.Status.Booked:
                            seat.Color = "Orange";
                            break;
                        case Persistence.Status.Free:
                            seat.Color = "White";
                            break;
                        case Persistence.Status.Sold:
                            seat.Color = "Black";
                            break;
                    }
                }
            }
        }

        private void OnClickCommand(int index)
        {
            SeatViewModel seat = Seats[index];

            Name = seat.Name;
            PhoneNumber = seat.PhoneNumber;

            if (seat.Status != Persistence.Status.Sold)
            {
                if(seat.NewStatus == Persistence.Status.Free && seat.Status == Persistence.Status.Free)
                {
                    seat.NewStatus = Persistence.Status.Sold;
                    seat.Color = "Yellow";
                }else if (seat.NewStatus == Persistence.Status.Sold && seat.Status == Persistence.Status.Free)
                {
                    seat.NewStatus = Persistence.Status.Free;
                    seat.Color = "White";
                }
                else if(seat.NewStatus == Persistence.Status.Booked && seat.Status == Persistence.Status.Booked)
                {
                    seat.NewStatus = Persistence.Status.Sold;
                    seat.Color = "Yellow";
                }
                else if (seat.NewStatus == Persistence.Status.Sold && seat.Status == Persistence.Status.Booked)
                {
                    seat.NewStatus = Persistence.Status.Booked;
                    seat.Color = "Orange";
                }
            }
        }
    }
}
