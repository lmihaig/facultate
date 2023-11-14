using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.AspNetCore.Mvc.Rendering;
using System.Linq;

namespace lab04.Pages
{
    public class DeleteStireModel : PageModel
    {
        [BindProperty]
        public Stire Stire { get; set; }
        public List<SelectListItem>
    categorie
        { get; set; }

        private readonly StiriContext _stiriContext;

        public DeleteStireModel(StiriContext stiriContext)
        {
            _stiriContext = stiriContext;
           // categorie = _stiriContext.Categorie.Select(x => new SelectListItem { Text = x.Nume, Value = x.Id.ToString() }).ToList();
        }

        public IActionResult OnPost(int id)
        {
            Stire = _stiriContext.Stire.FirstOrDefault(s => s.Id == id);
            if (Stire == null)
            {
                RedirectToPage("Index");
            }

            _stiriContext.Remove(Stire);
            _stiriContext.SaveChanges();
            return RedirectToPage("Index");
        }
    }
}
