package com.company.enums;

public enum CountryEnum {
    ROMANIA("RO", "+40"),
    ITALIA("IT", "+39"),
    GRECIA("GR", "+30"),
    BULGARIA("BG", "+359");

    private final String code;
    private final String phoneCode;

    CountryEnum(String code, String phoneCode) {
        this.code = code;
        this.phoneCode = phoneCode;
    }

    public String getCode() {
        return code;
    }

    public String getPhoneCode() {
        return phoneCode;
    }
}
