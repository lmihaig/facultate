package com.inventory.domain;

public abstract class Asset {
    private Integer no;
    private AssetType assetType;

    public Asset(Integer no, AssetType assetType) {
        this.no = no;
        this.assetType = assetType;
    }

    public Integer getNo() {
        return no;
    }

    public void setNo(Integer no) {
        this.no = no;
    }

    public AssetType getAssetType() {
        return assetType;
    }

    public void setAssetType(AssetType assetType) {
        this.assetType = assetType;
    }
}
