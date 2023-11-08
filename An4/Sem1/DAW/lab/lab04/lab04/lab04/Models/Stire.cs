using System.ComponentModel.DataAnnotations.Schema;
using static Categorie;

public class Stire
{
	public Stire()
	{
		
    }
    
    public int Id { get; set; }
	public string Titlu { get; set; }
    public string Lead { get; set; }
    public string Continut { get; set; }
    public string Autor { get; set; }
    public Categorie Categorie { get; set; }
    public int CategorieId { get; set; }
}
