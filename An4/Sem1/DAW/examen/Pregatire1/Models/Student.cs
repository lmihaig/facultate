using Microsoft.AspNetCore.Mvc;
using System.ComponentModel.DataAnnotations;
namespace Pregatire1.Models
{
    public class Student
    {
        public int StudentId { get; set; }


		public string Nume { get; set; }


		public DateOnly DataNasterii {  get; set; }


		public string AdresaDomiciuliu { get; set; }

        public int GrupaId { get; set; }
        public Grupa Grupa { get; set; }
    }
}
