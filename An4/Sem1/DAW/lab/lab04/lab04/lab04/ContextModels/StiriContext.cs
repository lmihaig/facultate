using System;
using static Stire;
using static Categorie;
using Microsoft.EntityFrameworkCore;

public class StiriContext : DbContext	
{
	public StiriContext(DbContextOptions<StiriContext> options) : base(options)
	{
		
	}
	
	public DbSet<Stire> Stire { get; set; }
	public DbSet<Categorie> Categorie { get; set; }
}
