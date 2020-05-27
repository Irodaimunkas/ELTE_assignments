using Cinema.Desktop.Model;
using Cinema.Desktop.View;
using Cinema.Desktop.ViewModel;
using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;

namespace Cinema.Desktop
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        private CinemaAPIService _service;
        private MainWindowViewModel _mainViewModel;
        private LoginViewModel _loginViewModel;
        private BuyTicketViewModel _buyTicketViewModel;
        private AddMovieViewModel _addMovieViewModel;
        private AddScreeningViewModel _addScreeningViewModel;

        private MainWindow _mainView;
        private LoginWindow _loginView;
        private BuyTicketWindow _buyTicketView;
        private AddMovie _addMovieView;
        private AddScreening _addScreeningView;

        public App()
        {
            Startup += App_Startup;
        }

        private void App_Startup(object sender, StartupEventArgs e)
        {
            _service = new CinemaAPIService(ConfigurationManager.AppSettings["baseAddress"]);

            _loginViewModel = new LoginViewModel(_service);

            _loginViewModel.LogintSucceeded += ViewModel_LoginSucceeded;
            _loginViewModel.LoginFailed += ViewModel_LoginFailed;
            _loginViewModel.MessageApplication += ViewModel_MessageApplication;

            _loginView = new LoginWindow
            {
                DataContext = _loginViewModel
            };

            
            _mainViewModel = new MainWindowViewModel(_service);
            _mainViewModel.LogoutSucceeded += ViewModel_LogoutSucceeded;
            _mainViewModel.MessageApplication += ViewModel_MessageApplication;
            _mainViewModel.BuyingTicket += ViewModel_BuyingTicket;
            _mainViewModel.AddingMovie += ViewModel_AddingMovie;
            _mainViewModel.AddingScreening += ViewModel_AddingScreening;

            _mainView = new MainWindow
            {
                DataContext = _mainViewModel
            };

            _loginView.Show();
        }

        private void ViewModel_AddingScreening(object sender, EventArgs e)
        {
            _mainView.Close();

            _mainViewModel.LogoutSucceeded -= ViewModel_LogoutSucceeded;
            _mainViewModel.MessageApplication -= ViewModel_MessageApplication;
            _mainViewModel.BuyingTicket -= ViewModel_BuyingTicket;
            _mainViewModel.AddingMovie -= ViewModel_AddingMovie;
            _mainViewModel.AddingScreening -= ViewModel_AddingScreening;

            _addScreeningViewModel = new AddScreeningViewModel(_service);

            _addScreeningView = new AddScreening
            {
                DataContext = _addScreeningViewModel
            };

            _addScreeningViewModel.AddingScreeningEnded += ViewModel_AddingScreeningEnded;

            _addScreeningView.ShowDialog();
        }

        private void ViewModel_AddingScreeningEnded(object sender, EventArgs e)
        {
            _addScreeningViewModel.AddingScreeningEnded -= ViewModel_AddingScreeningEnded;

            _addScreeningView.Close();

            _mainViewModel = new MainWindowViewModel(_service);
            _mainViewModel.LogoutSucceeded += ViewModel_LogoutSucceeded;
            _mainViewModel.MessageApplication += ViewModel_MessageApplication;
            _mainViewModel.BuyingTicket += ViewModel_BuyingTicket;
            _mainViewModel.AddingMovie += ViewModel_AddingMovie;
            _mainViewModel.AddingScreening += ViewModel_AddingScreening;

            _mainView = new MainWindow
            {
                DataContext = _mainViewModel
            };

            _mainView.Show();
        }

        private void ViewModel_AddingMovie(object sender, EventArgs e)
        {
            _addMovieViewModel = new AddMovieViewModel(_service);

            _addMovieView = new AddMovie
            {
                DataContext = _addMovieViewModel
            };

            _addMovieViewModel.StartingImageChange += ViewModel_StartingImageChange;
            _addMovieViewModel.AddingMovieEnded += ViewModel_AddingMovieEnded;

            _addMovieView.ShowDialog();
        }

        private void ViewModel_AddingMovieEnded(object sender, EventArgs e)
        {
            _addMovieViewModel.StartingImageChange -= ViewModel_StartingImageChange;
            _addMovieViewModel.AddingMovieEnded -= ViewModel_AddingMovieEnded;

            _addMovieView.Close();
        }

        private async void ViewModel_StartingImageChange(object sender, EventArgs e)
        {
            OpenFileDialog dialog = new OpenFileDialog
            {
                CheckFileExists = true,
                Filter = "Images|*.jpg;*.jpeg;*.bmp;*.tif;*.gif;*.png;",
                InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.MyPictures)
            };

            if (dialog.ShowDialog(_addMovieView).GetValueOrDefault(false))
            {
                _addMovieViewModel.ImagePath = dialog.FileName;
                _addMovieViewModel.Image = await File.ReadAllBytesAsync(dialog.FileName);
            }
        }

        private void ViewModel_CheckedOut(object sender, EventArgs e)
        {
            _buyTicketViewModel.CheckedOut -= ViewModel_CheckedOut;
            _buyTicketView.Close();
        }

        private void ViewModel_BuyingTicket(object sender, EventArgs e)
        {
            _buyTicketViewModel = new BuyTicketViewModel(_service, _mainViewModel);

            _buyTicketView = new BuyTicketWindow
            {
                DataContext = _buyTicketViewModel
            };

            _buyTicketViewModel.CheckedOut += ViewModel_CheckedOut;

            _buyTicketView.ShowDialog();
        }

        private void ViewModel_LogoutSucceeded(object sender, EventArgs e)
        {
            _mainView.Hide();
            _loginView.Show();
        }

        private void ViewModel_MessageApplication(object sender, MessageEventArgs e)
        {
            MessageBox.Show(e.Message, "Cinema Reciptionist App", MessageBoxButton.OK, MessageBoxImage.Asterisk);
        }

        private void ViewModel_LoginFailed(object sender, EventArgs e)
        {
            MessageBox.Show("Login failed!", "Cinema Reciptionist App", MessageBoxButton.OK, MessageBoxImage.Asterisk);
        }

        private void ViewModel_LoginSucceeded(object sender, EventArgs e)
        {
            _loginView.Hide();
            _mainView.Show();
        }
    }
}
