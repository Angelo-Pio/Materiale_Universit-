public class Driver {


    public static void main(String[] argv) {
        /*sentitevi liberi di aggiungere nuovi test nel main */
    	BST b = new BST();
    	
        b.insert("Se");
        b.insert("usi");
        b.insert("il");
        b.insert("package");
        b.insert("il");
        b.insert("prof");
        b.insert("Lazzeretti");
        b.insert("ha");
        b.insert("difficolta");
        b.insert("a");
        b.insert("compilare");
        b.insert("Se");
        b.insert("il");
        b.insert("codice");
        b.insert("non");
        b.insert("compila");
        b.insert("con");
        b.insert("javac");
        b.insert("dovrai");
        b.insert("ripetere");
        b.insert("l");
        b.insert("esame");


        System.out.println("\tAlbero: \n");
        b.BST_print();

        String k = "se";
        System.out.println("\n\tRicerca valore");

        int c=b.find(k);
        if (c==-1)
            System.out.println("Non implementato"); 
        else if (c==0)
            System.out.println("Nodo con chiave "+k+" NON trovato"); 
        else
            System.out.println("Nodo con chiave "+k+" trovato: "+ c + " occorrenze"); 

        k= "ripete";
        c=b.find(k);
        if (c==-1)
            System.out.println("Non implementato"); 
        else if (c==0)
            System.out.println("Nodo con chiave "+k+" NON trovato"); 
        else
            System.out.println("Nodo con chiave "+k+" trovato: "+ c + " occorrenze"); 
        
        k= "il";
        c=b.find(k);
        if (c==-1)
            System.out.println("Non implementato"); 
        else if (c==0)
            System.out.println("Nodo con chiave "+k+" NON trovato"); 
        else
            System.out.println("Nodo con chiave "+k+" trovato: "+ c + " occorrenze"); 
     
        System.out.println("\n\tRicerca stringa più frequente");
        String max = b.mostFrequentString();
        System.out.println("Stringa più frequente:  "+ max);

        System.out.println("\n\ttest bilanciamento:");
        int result = b.isBalanced();
        if (result==-1)
            System.out.println("Non implementato");
        else if (result==0)
            System.out.println("Non bilanciato");
        else
            System.out.println("Bilanciato");
        
    }
}
