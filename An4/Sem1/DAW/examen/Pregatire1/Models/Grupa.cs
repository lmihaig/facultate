using System.ComponentModel.DataAnnotations;

namespace Pregatire1.Models
{
    public class Grupa
    {
        public int GrupaId { get; set; }

        public int Numar { get; set; }
        public string DomeniuStudiu { get; set; }
        public ICollection<Student> Studenti { get; set; }
    }
}
