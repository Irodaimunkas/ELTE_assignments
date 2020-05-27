using Cinema.Persistence.DTO;
using System;
using System.Collections.Generic;
using System.Text;

namespace Cinema.Desktop.ViewModel
{
    public class MovieViewModel : ViewModelBase
    {
        public Int32 Id { get; set; }

        public String Name { get; set; }


        public static explicit operator MovieViewModel(MovieDto dto) => new MovieViewModel
        {
            Id = dto.Id,
            Name = dto.Name
        };

        public static explicit operator MovieDto(MovieViewModel i) => new MovieDto
        {
            Id = i.Id,
            Name = i.Name
        };
    }
}
