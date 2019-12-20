using ELTE.Windows.Sudoku.ViewModel;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Minesweeper.Model;
using System.Collections.ObjectModel;
using System.Windows.Forms;
using Minesweeper.Persistence;

namespace Minesweeper.ViewModel
{
    public class MinesweeperViewModel : ViewModelBase
    {
        private MinesweeperModel _model;
        private SaveEntry _selectedGame;
        private String _newName = String.Empty;

        //commands
        public DelegateCommand NewGameEasyCommand { get; private set; }
        public DelegateCommand NewGameMediumCommand { get; private set; }
        public DelegateCommand NewGameHardCommand { get; private set; }
        public DelegateCommand LoadGameOpenCommand { get; private set; }
        public DelegateCommand LoadGameCloseCommand { get; private set; }
        public DelegateCommand SaveGameOpenCommand { get; private set; }
        public DelegateCommand SaveGameCloseCommand { get; private set; }

        //collections
        public ObservableCollection<MinesweeperField> Fields { get; set; }
        public ObservableCollection<SaveEntry> Games { get; set; }


        //properties
        public SaveEntry SelectedGame
        {
            get { return _selectedGame; }
            set
            {
                _selectedGame = value;
                if (_selectedGame != null)
                    NewName = String.Copy(_selectedGame.Name);

                OnPropertyChanged();
                LoadGameCloseCommand.RaiseCanExecuteChanged();
                SaveGameCloseCommand.RaiseCanExecuteChanged();
            }
        }

        public String NewName
        {
            get { return _newName; }
            set
            {
                _newName = value;

                OnPropertyChanged();
                SaveGameCloseCommand.RaiseCanExecuteChanged();
            }
        }

        public String MapSize { get { return _model.Size.ToString(); } }
        public String Player { get { return _model.CurrPlayer.ToString(); } }

        //events
        public event EventHandler LoadGameOpen;
        public event EventHandler<String> LoadGameClose;
        public event EventHandler<String> SaveGameClose;
        public event EventHandler SaveGameOpen;

        public MinesweeperViewModel(MinesweeperModel model)
        {
            _model = model;
            _model.Draw += new EventHandler(Model_OnDraw);
            _model.PlayerLost += new EventHandler<MinesweeperEventArgs>(Model_OnPlayerLost);
            _model.Loaded += new EventHandler((x, y) => GenerateTable());

            NewGameEasyCommand = new DelegateCommand(param => OnNewGame(6));
            NewGameMediumCommand = new DelegateCommand(param => OnNewGame(10));
            NewGameHardCommand = new DelegateCommand(param => OnNewGame(16));
            LoadGameOpenCommand = new DelegateCommand(async param =>
            {
                Games = new ObservableCollection<SaveEntry>(await _model.ListGamesAsync());
                OnLoadGameOpen();
            });
            LoadGameCloseCommand = new DelegateCommand(
                param => SelectedGame != null, // parancs végrehajthatóságának feltétele
                param => { OnLoadGameClose(SelectedGame.Name); });
            SaveGameOpenCommand = new DelegateCommand(async param =>
            {
                Games = new ObservableCollection<SaveEntry>(await _model.ListGamesAsync());
                OnSaveGameOpen();
            });
            SaveGameCloseCommand = new DelegateCommand(
                param => NewName.Length > 0, // parancs végrehajthatóságának feltétele
                param => { OnSaveGameClose(NewName); });

            Fields = new ObservableCollection<MinesweeperField>();
            GenerateTable();
        }

        private void OnSaveGameClose(string name)
        {
            if (SaveGameClose != null)
                SaveGameClose(this, name);
        }

        private void OnSaveGameOpen()
        {
            if (SaveGameOpen != null)
                SaveGameOpen(this, EventArgs.Empty);
        }

        private void OnLoadGameClose(string name)
        {
            if (LoadGameClose != null)
                LoadGameClose(this, name);
        }

        private void OnLoadGameOpen()
        {
            if (LoadGameOpen != null)
                LoadGameOpen(this, EventArgs.Empty);
        }

        private void GenerateTable()
        {
            OnPropertyChanged("MapSize");
            Fields.Clear();
            for (Int32 i = 0; i < _model.Size; i++) // inicializáljuk a mezőket
            {
                for (Int32 j = 0; j < _model.Size; j++)
                {
                    Fields.Add(new MinesweeperField
                    {
                        X = i,
                        Y = j,
                        Color = "White",
                        Value = String.Empty,
                        Number = i * _model.Size + j,
                        StepCommand = new DelegateCommand(param => OnStep(Convert.ToInt32(param))),
                        AlertCommand = new DelegateCommand(param => OnAlert(Convert.ToInt32(param)))
                    });
                }
            }
            RefreshTable();
        }

        private void RefreshTable()
        {
            foreach (MinesweeperField field in Fields)
            {
                if (_model.Map[field.X, field.Y].fieldType == Persistence.FieldType.BOMB && _model.Map[field.X, field.Y].visible)
                {
                    field.Color = "Black";
                }
                else
                {
                    if (_model.Map[field.X, field.Y].visible)
                    {
                        field.Value = _model.Map[field.X, field.Y].value.ToString();
                    }
                    else
                    {
                        field.Value = String.Empty;
                    }
                }
            }

            OnPropertyChanged("Player");
        }

        private void OnStep(Int32 index)
        {
            MinesweeperField field = Fields[index];
            _model.Step(field.X, field.Y);
            RefreshTable();
        }

        private void OnAlert(Int32 index)
        {
            MinesweeperField field = Fields[index];
            if (field.Color == "Red") field.Color = "White";
            else field.Color = "Red";
            RefreshTable();
        }

        private void OnNewGame(Int32 mapSize)
        {
            _model.NewGame(mapSize);
            GenerateTable();
        }

        private void Model_OnDraw(object sender, EventArgs e)
        {
            RefreshTable();
            MessageBox.Show("Draw",
                                "Game Over",
                                MessageBoxButtons.OK,
                                MessageBoxIcon.Asterisk);
            OnNewGame(_model.Size);
        }

        private void Model_OnPlayerLost(object sender, MinesweeperEventArgs e)
        {
            RefreshTable();
            MessageBox.Show(e.Player + " won",
                                "Game Over",
                                MessageBoxButtons.OK,
                                MessageBoxIcon.Asterisk);
            OnNewGame(_model.Size);
        }
    }
}
