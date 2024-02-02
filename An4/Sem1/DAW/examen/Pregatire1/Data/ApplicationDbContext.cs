using Microsoft.EntityFrameworkCore;
using Pregatire1.Models;

namespace Pregatire1.Data
{
    public class ApplicationDbContext : DbContext
    {
        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options) : base(options) { }
        public DbSet<Student> Studenti { get; set; }
        public DbSet<Grupa> Grupa { get; set; }
    }
}
