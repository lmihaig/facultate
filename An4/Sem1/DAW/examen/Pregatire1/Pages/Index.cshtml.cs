using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.EntityFrameworkCore;
using Pregatire1.Data;
using Pregatire1.Models;
using Pregatire1;

namespace Pregatire1.Pages
{
    public class IndexModel : PageModel
    {
        private readonly ILogger<IndexModel> _logger;
        private readonly ApplicationDbContext _context;
        public IEnumerable<Student> Studenti { get; set; }
        public IEnumerable<Grupa> Grupa { get; set; }
        public IndexModel(ILogger<IndexModel> logger, ApplicationDbContext db)
        {
            _logger = logger;
            _context = db;
        }

        public void OnGet()
        {
            Studenti = _context.Studenti.Include(s => s.Grupa);
            Grupa = _context.Grupa.Include(s => s.Studenti); 
        }
    }
}
