using System;
using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace Pregatire1.Migrations
{
    // <inheritdoc />
    public partial class init : Migration
    {
        // <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "Grupa",
                columns: table => new
                {
                    GrupaId = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Numar = table.Column<int>(type: "int", nullable: false),
                    DomeniuStudiu = table.Column<string>(type: "nvarchar(max)", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Grupa", x => x.GrupaId);
                });

            migrationBuilder.CreateTable(
                name: "Studenti",
                columns: table => new
                {
                    StudentId = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Nume = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    DataNasterii = table.Column<DateOnly>(type: "date", nullable: false),
                    AdresaDomiciuliu = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    GrupaId = table.Column<int>(type: "int", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Studenti", x => x.StudentId);
                    table.ForeignKey(
                        name: "FK_Studenti_Grupa_GrupaId",
                        column: x => x.GrupaId,
                        principalTable: "Grupa",
                        principalColumn: "GrupaId",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateIndex(
                name: "IX_Studenti_GrupaId",
                table: "Studenti",
                column: "GrupaId");
        }

        // <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "Studenti");

            migrationBuilder.DropTable(
                name: "Grupa");
        }
    }
}
