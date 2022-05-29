package com.inventory.domain;

public class Drawing extends Asset {
    private String title;
    private String author;

    public Drawing(Integer no, AssetType assetType, String title, String author) {
        super(no, assetType);
        this.title = title;
        this.author = author;
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
}
