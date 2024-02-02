using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Pregatire1.Data;
using Pregatire1.Models;

namespace Pregatire1.Pages
{
    public class EditStudentModel : PageModel
    {
        private readonly ApplicationDbContext _context;
        
        
        [BindProperty]
        public Student Student { get; set; }


        public EditStudentModel(ApplicationDbContext context)
        {
            _context = context;
        }
        public void OnGet(int id)
        {
            Student = _context.Studenti.FirstOrDefault(u => u.StudentId == id);
        }

        public async Task<IActionResult> OnPost()
        {
            _context.Studenti.Update(Student);
            await _context.SaveChangesAsync();
            return RedirectToPage("Index");
        }
    }
}
