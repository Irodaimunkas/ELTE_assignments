using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;
using Minesweeper.Persistence;
using Minesweeper.Model;
using Minesweeper.ViewModel;
using Minesweeper.View;

namespace Minesweeper
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        private MinesweeperModel _model;
        private MinesweeperViewModel _viewModel;
        private LoadWindow _loadWindow;
        private SaveWindow _saveWindow;
        private MainWindow _view;

        public App()
        {
            Startup += new StartupEventHandler(App_Startup);
        }

        private void App_Startup(object sender, StartupEventArgs e)
        {
            IMinesweeperDataAccess dataAccess;
            dataAccess = new MinesweeperDbDataAccess("name=MinesweeperModel");

            _model = new MinesweeperModel(dataAccess);
            _model.NewGame(6);

            _viewModel = new MinesweeperViewModel(_model);
            _viewModel.LoadGameOpen += new EventHandler(ViewModel_LoadGameOpen);
            _viewModel.LoadGameClose += new EventHandler<String>(ViewModel_LoadGameCloseAsync);
            _viewModel.SaveGameOpen += new EventHandler(ViewModel_SaveGameOpen);
            _viewModel.SaveGameClose += new EventHandler<String>(ViewModel_SaveGameClose);

            _view = new MainWindow();
            _view.DataContext = _viewModel;
            _view.Show();
        }

        private async void ViewModel_SaveGameClose(object sender, string name)
        {
            if (name != null)
            {
                try
                {
                    // felülírás ellenőrzése
                    var games = await _model.ListGamesAsync();
                    if (games.All(g => g.Name != name) ||
                        MessageBox.Show("Biztos, hogy felülírja a meglévő mentést?", "Sudoku",
                            MessageBoxButton.YesNo, MessageBoxImage.Question) == MessageBoxResult.Yes)
                    {
                        await _model.SaveGameAsync(name);
                    }
                }
                catch
                {
                    MessageBox.Show("Játék mentése sikertelen!", "Hiba!", MessageBoxButton.OK, MessageBoxImage.Error);
                }
            }

            _saveWindow.Close(); // játékállapot mentő ablak bezárása
        }

        private void ViewModel_SaveGameOpen(object sender, EventArgs e)
        {
            _viewModel.SelectedGame = null; // kezdetben nincsen kiválasztott elem
            _viewModel.NewName = String.Empty;

            _saveWindow = new SaveWindow(); // létrehozzuk a játék állapot mentő ablakot
            _saveWindow.DataContext = _viewModel;
            _saveWindow.ShowDialog(); // megjelenítjük dialógusként
        }

        private async void ViewModel_LoadGameCloseAsync(object sender, string name)
        {
            if (name != null)
            {
                try
                {
                    await _model.LoadGameAsync(name);
                }
                catch
                {
                    MessageBox.Show("Játék betöltése sikertelen!", "Hiba!", MessageBoxButton.OK, MessageBoxImage.Error);
                }
            }

            _loadWindow.Close(); // játékállapot betöltőtő ablak bezárása
        }

        private void ViewModel_LoadGameOpen(object sender, EventArgs e)
        {
            _viewModel.SelectedGame = null; // kezdetben nincsen kiválasztott elem

            _loadWindow = new LoadWindow(); // létrehozzuk a játék állapot betöltő ablakot
            _loadWindow.DataContext = _viewModel;
            _loadWindow.ShowDialog(); // megjelenítjük dialógusként
        }
    }
}
