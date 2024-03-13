﻿// <auto-generated />
using System;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Metadata;
using Microsoft.EntityFrameworkCore.Migrations;
using Microsoft.EntityFrameworkCore.Storage.ValueConversion;
using Pregatire1.Data;

#nullable disable

namespace Pregatire1.Migrations
{
    [DbContext(typeof(ApplicationDbContext))]
    [Migration("20240201090135_init2")]
    partial class init2
    {
        // <inheritdoc />
        protected override void BuildTargetModel(ModelBuilder modelBuilder)
        {
#pragma warning disable 612, 618
            modelBuilder
                .HasAnnotation("ProductVersion", "8.0.1")
                .HasAnnotation("Relational:MaxIdentifierLength", 128);

            SqlServerModelBuilderExtensions.UseIdentityColumns(modelBuilder);

            modelBuilder.Entity("Pregatire1.Models.Grupa", b =>
                {
                    b.Property<int>("GrupaId")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("int");

                    SqlServerPropertyBuilderExtensions.UseIdentityColumn(b.Property<int>("GrupaId"));

                    b.Property<string>("DomeniuStudiu")
                        .IsRequired()
                        .HasColumnType("nvarchar(max)");

                    b.Property<int>("Numar")
                        .HasColumnType("int");

                    b.HasKey("GrupaId");

                    b.ToTable("Grupa");
                });

            modelBuilder.Entity("Pregatire1.Models.Student", b =>
                {
                    b.Property<int>("StudentId")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("int");

                    SqlServerPropertyBuilderExtensions.UseIdentityColumn(b.Property<int>("StudentId"));

                    b.Property<string>("AdresaDomiciuliu")
                        .IsRequired()
                        .HasColumnType("nvarchar(max)");

                    b.Property<DateOnly>("DataNasterii")
                        .HasColumnType("date");

                    b.Property<int>("GrupaId")
                        .HasColumnType("int");

                    b.Property<string>("Nume")
                        .IsRequired()
                        .HasMaxLength(100)
                        .HasColumnType("nvarchar(100)");

                    b.HasKey("StudentId");

                    b.HasIndex("GrupaId");

                    b.ToTable("Studenti");
                });

            modelBuilder.Entity("Pregatire1.Models.Student", b =>
                {
                    b.HasOne("Pregatire1.Models.Grupa", "Grupa")
                        .WithMany("Studenti")
                        .HasForeignKey("GrupaId")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("Grupa");
                });

            modelBuilder.Entity("Pregatire1.Models.Grupa", b =>
                {
                    b.Navigation("Studenti");
                });
#pragma warning restore 612, 618
        }
    }
}
