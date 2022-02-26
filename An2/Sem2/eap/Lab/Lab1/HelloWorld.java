public class HelloWorld {
    public static void main(String[] args) {
        System.out.println("boop");

        boolean cumvremnoi = true;
        System.out.println(cumvremnoi);

        short varsta = 184;
        System.out.println(varsta);

        char eu = 'E';
        System.out.println(eu);

        System.out.println(eu + String.valueOf(varsta));

        boolean isOpen = true;
        Boolean isOpenWrap = Boolean.valueOf(isOpen);
        System.out.println(isOpenWrap.compareTo(Boolean.valueOf("true")));
        
    }
}
