using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Text;

namespace Cinema.Persistence.DTO
{
    public class MovieDto
    {
        [Key]
        public Int32 Id { get; set; }

        [Required]
        public String Name { get; set; }

        [Required]
        public String Director { get; set; }

        [DataType(DataType.MultilineText)]
        public String Synopsis { get; set; }

        [Required]
        [DisplayName("Length")]
        public Int32 LengthInMinutes { get; set; }

        public byte[] Image { get; set; }

        [Required]
        [DataType(DataType.Date)]
        public DateTime PostTime { get; set; }

        public static explicit operator Movie(MovieDto dto) => new Movie
        {
            Id = dto.Id,
            Name = dto.Name,
            Director = dto.Director,
            Synopsis = dto.Synopsis,
            LengthInMinutes = dto.LengthInMinutes,
            Image = dto.Image,
            PostTime = dto.PostTime
        };

        public static explicit operator MovieDto(Movie i) => new MovieDto
        {
            Id = i.Id,
            Name = i.Name,
            Director = i.Director,
            Synopsis = i.Synopsis,
            LengthInMinutes = i.LengthInMinutes,
            Image = i.Image,
            PostTime = i.PostTime
        };
    }
}
