using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Pregatire1.Data;
using Pregatire1.Models;
using System.ComponentModel.DataAnnotations;

namespace Pregatire1.Pages
{
    public class AddStudentModel : PageModel
    {
        private readonly ApplicationDbContext _context;
        
        [Required]
        [BindProperty]
        
        public Student Student { get; set; }
        public AddStudentModel(ApplicationDbContext context)
        {
            _context = context;
        }
        public void OnGet()
        {
        }

        public async Task<IActionResult> OnPost()
        {
            await _context.Studenti.AddAsync(Student);
            await _context.SaveChangesAsync();
            return RedirectToPage("Index");
        }
    }
}
