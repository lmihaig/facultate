package com.inventory;

import com.inventory.domain.Asset;
import com.inventory.domain.AssetType;
import com.inventory.domain.Book;
import com.inventory.domain.Drawing;

import java.util.ArrayList;
import java.util.List;

/**
 * The main description of the Java Collections can be consulted in the Java documentation:
 * https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/util/doc-files/coll-overview.html
 */
public class WorkWithCollections {

    public static void main(String[] args) {
        List<Asset> myAssets= new ArrayList<>();
        myAssets.add(new Book(1, AssetType.BOOK, "Jane Eyre", "Charlotte Bronte", "2212123"));
        myAssets.add(new Book(2, AssetType.BOOK, "Odyssey", "Homer", "987655789"));
        myAssets.add(new Drawing(3, AssetType.DRAWING, "The Night Watch", "Rembrandt"));
        myAssets.add(new Drawing(3, AssetType.DRAWING, "View of Delft", "Vermeer"));

        for (Asset myAsset : myAssets) {
            System.out.println(myAsset.getNo() + " " + myAsset.getAssetType());
        }

    }
}
