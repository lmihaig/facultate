using Categorie;

public class Stire
{
	public Stire()
	{
		
    }
    
    public string id { get; set; }
	public string titlu { get; set; }
    public string lead { get; set; }
    public string continut { get; set; }
    public string autor { get; set; }
    public Categorie categorie { get; set; }
}
