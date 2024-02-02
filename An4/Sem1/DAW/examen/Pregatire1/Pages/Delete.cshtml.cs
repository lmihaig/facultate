using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Pregatire1.Data;
using Pregatire1.Models;

namespace Pregatire1.Pages
{
    public class DeleteModel : PageModel
    {
        private readonly ApplicationDbContext _context;
        [BindProperty]
        public Student Student { get; set; }
        public DeleteModel(ApplicationDbContext context)
        {
            _context = context;
        }
        public async Task<IActionResult> OnGet(int id)
        {
            var student = _context.Studenti.FirstOrDefault(u => u.StudentId == id);
            if (student != null)
            {
                _context.Studenti.Remove(student);
                await _context.SaveChangesAsync();
            }
            return RedirectToPage("Index");
        }
    }
}
