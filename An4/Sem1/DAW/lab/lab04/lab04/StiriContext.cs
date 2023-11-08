using System;
using Stire;
using Categorie;

public class StiriContext : DbContext	
{
	public StiriContext(DbContextOptions<StiriContext> options)
	{
		base(options);
	}
	
	public DbSet<Stire> Stire { get; set; }
	public DbSet<Categorie> Categorie { get; set; }
}
