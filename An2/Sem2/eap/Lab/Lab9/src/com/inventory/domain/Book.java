package com.inventory.domain;

public class Book extends Asset {
    private String title;
    private String author;
    private String isbn;

    public Book(Integer no, AssetType assetType, String title, String author, String isbn) {
        super(no, assetType);
        this.title = title;
        this.author = author;
        this.isbn = isbn;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getAuthor() {
        return author;
    }

    public void setAuthor(String author) {
        this.author = author;
    }

    public String getIsbn() {
        return isbn;
    }

    public void setIsbn(String isbn) {
        this.isbn = isbn;
    }
}
