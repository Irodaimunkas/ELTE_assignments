using Cinema.Persistence;
using System.Drawing;

namespace Cinema.Desktop.ViewModel
{
    public class SeatViewModel : ViewModelBase
    {
        private string _color;
        private Status _status;

        public int Id { get; set; }

        public string Name { get; set; }

        public string PhoneNumber { get; set; }

        public Status NewStatus { get; set; }

        public Status Status
        {
            get => _status;
            set
            {
                _status = value;
                OnPropertyChanged();
            }
        }

        public string Color 
        {
            get => _color;
            set
            {
                _color = value;
                OnPropertyChanged();
            }
        }

        public int X { get; set; }

        public int Y { get; set; }

        public int Number { get; set; }

        public DelegateCommand ClickCommand { get; set; }
    }
}