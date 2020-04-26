using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;
using TodoList.Client.Model;
using TodoList.Client.ViewModel;

namespace TodoList.Client
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        public APIService _apiService;
        public MainWindowViewModel _MWViewModel;
        public MainWindow _mainWindow;

        App()
        {
            _apiService = new APIService(ConfigurationManager.AppSettings["baseAddress"]);
            _MWViewModel = new MainWindowViewModel(_apiService);
            _mainWindow = new MainWindow();
            _mainWindow.DataContext = _MWViewModel;
            _mainWindow.Show();
        }
    }
}
