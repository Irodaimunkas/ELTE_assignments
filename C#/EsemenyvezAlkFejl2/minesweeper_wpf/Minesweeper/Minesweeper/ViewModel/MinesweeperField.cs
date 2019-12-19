using ELTE.Windows.Sudoku.ViewModel;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Minesweeper.ViewModel
{
    public class MinesweeperField : ViewModelBase
    {
        private String _value;
        private String _color;
        public Int32 X { get; set; }
        public Int32 Y { get; set; }
        public String Color
        {
            get
            {
                return _color;
            }
            set
            {
                _color = value;
                OnPropertyChanged();
            }
        }
        public String Value
        {
            get
            {
                return _value;
            }
            set
            {
                _value = value;
                OnPropertyChanged();
            }
        }
        public Int32 Number { get; set; }
        public DelegateCommand StepCommand { get; set; }
        public DelegateCommand AlertCommand { get; set; }
    }
}
