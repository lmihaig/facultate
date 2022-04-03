package util;

public class RegNumberGeneratorSingleton {
    // Proprietate statica care reține referinta catre singura instanta permisa a
    // clasei
    private static RegNumberGeneratorSingleton INSTANCE;
    private Integer code = 0;

    // Constructorul default (implicit) este privat
    private RegNumberGeneratorSingleton() {
    }

    // Metoda statica de tip factory pentru a furniza referinta spre singura
    // instanta a clasei
    public static RegNumberGeneratorSingleton getInstance() {
        if (INSTANCE == null) {
            INSTANCE = new RegNumberGeneratorSingleton();
        }
        return INSTANCE;
    }

    // getters, setters as needed
    public Integer getNewCode() {
        this.code = this.code + 1;
        return this.code;
    }

}