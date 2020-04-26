using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Diagnostics;
using System.Text;
using System.Threading.Tasks;
using TodoList.Client.Model;
using TodoList.Persistence;

namespace TodoList.Client.ViewModel
{
    public class MainWindowViewModel : ViewModelBase
    {
        public APIService _apiService;
        public Int32 _currListId;

        public DelegateCommand ChangeItemsCommand { get; private set; }

        public ObservableCollection<ItemRow> Rows { get; set; }

        public MainWindowViewModel(APIService apiService)
        {
            _apiService = apiService;
            _currListId = 3;
            Rows = new ObservableCollection<ItemRow>();
            GenerateRows();
        }

        public Int32 CurrListId
        { 
            get
            {
                return _currListId;
            }
            set
            {
                _currListId = value + 1;
                OnPropertyChanged("CurrListId");
                GenerateRows();
            }
        }

        public List<List> Lists
        {
            get
            {
                var results = _apiService.GetListsAsync();
                Debug.WriteLine(results);
                return results.Result;
            }
        }

        private void GenerateRows()
        {
            Rows.Clear();
            var results = _apiService.GetItemsByListIdAsync(_currListId);
            foreach(var result in results.Result)
            {
                Rows.Add(new ItemRow
                {
                    Image = result.Image,
                    Name = result.Name,
                    Deadline = result.Deadline,
                    Description = result.Description
                });
            }
        }
    }
}
