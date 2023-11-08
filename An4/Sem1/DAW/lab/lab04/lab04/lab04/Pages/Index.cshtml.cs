using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;

namespace lab04.Pages
{
    public class IndexModel : PageModel
    {
        public List<Stire> Stiri {  get; set; }
        private readonly StiriContext _stiriContext;
        private readonly ILogger<IndexModel> _logger;

        public IndexModel(ILogger<IndexModel> logger, StiriContext stiriContext)
        {
            _stiriContext = stiriContext;
            _logger = logger;
        }

        public void OnGet()
        {
            this.Stiri = _stiriContext.Stire.ToList();  
        }
    }
}