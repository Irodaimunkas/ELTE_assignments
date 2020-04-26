using System;
using System.Collections.Generic;
using System.Text;

namespace TodoList.Client.ViewModel
{
    public class ItemRow : ViewModelBase
    {
        private byte[] _image;
        private String _name;
        private DateTime _deadline;
        private String _description;

        public byte[] Image {
            get
            {
                return _image;
            }
            set
            {
                _image = value;
                OnPropertyChanged();
            }
        }

        public String Name {
            get
            {
                return _name;
            }
            set
            {
                _name = value;
                OnPropertyChanged();
            }
        }

        public DateTime Deadline {
            get
            {
                return _deadline;
            }
            set
            {
                _deadline = value;
                OnPropertyChanged();
            }
        }

        public String Description
        {
            get
            {
                return _description;
            }
            set 
            {
                _description = value;
                OnPropertyChanged();
            }
        }
    }
}
