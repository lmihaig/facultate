using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.AspNetCore.Mvc.Rendering;

namespace lab04.Pages
{
    public class AdaugaStireModel : PageModel
    {
        [BindProperty]
        public  Stire Stire { get; set; }
        public List<SelectListItem> categorie {  get; set; }

        private readonly StiriContext _stiriContext;

        public AdaugaStireModel(StiriContext stiriContext)
        {
            _stiriContext = stiriContext;
            categorie = _stiriContext.Categorie.Select(x => new SelectListItem { Text = x.Nume, Value = x.Id.ToString() }).ToList();
        }

        public void OnGet()
        {
            Stire = new Stire();

        }

        public IActionResult OnPost()
        {
            _stiriContext.Add(Stire);
            _stiriContext.SaveChanges();
            return RedirectToPage("Index");
        }
    }
}
