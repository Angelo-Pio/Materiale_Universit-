import java.util.ArrayList;
import java.util.LinkedList;

public class OpenHashTable extends AbstractHashTable {
	// Un array di Entry per la tabella
	private Entry[] table;
	// marcatore di cella vuota ma da esaminare durante probing
	private final Entry DEFUNCT = new Entry(null, 0); 
	
	// Costruttori
	public OpenHashTable(int cap, int p, double lambda) {
		super(cap, p, lambda);
	}
	public OpenHashTable(int cap, int p) {
		super(cap, p); // massimo fattore di carico predefinito
	}
	public OpenHashTable(int cap) {
		super(cap); // primo predefinito
	}
	public OpenHashTable() {
		super(); // capacità predefinita
	}
		
	// Metodi non implementati in AbstractHashTable

	// Inizializza una tabella hash vuota secondo i parametri passati al costruttore
	protected void createTable() {
        table = new Entry[getCapacity()];
    }

	// Restituisce il valore (intero) associato alla chiave k
	// Restituisce -1 se la chiave è assente
	public int get(String k) {

        // Calcola l'hashcode
        int f = find(k);

        if(f != -1){
            return table[f].getValue();
        }

		return f;
	}
	
    private int find(String k){
        // Restituisce la posizione in cui si trova k
        int hashcode = hashFunction(k);

        for (int i = hashcode; i < getCapacity(); i = hashcode + i*i ) {
            if(table[i] == null){
                return -1;
            }
            if(table[i].equals(DEFUNCT)){
                continue;
            }
            if(table[i].getKey() == k){
                return i;
            }
        }

        return -1;


    }


	// Aggiorna il valore associato alla chiave k
	// Restituisce il vecchio valore o -1 se la chiave non è presente
	public int put(String k, int value) {


        int h = hashFunction(k);
        int r = 0;
        for (int i = h; i < getCapacity(); i = h+i*i) {
            if(table[i] == null){
                r = i;
                break;
            }
            if(table[i].equals(DEFUNCT)){
                r = i;
            }
            if(table[i].getKey() == k){
                int old = table[i].getValue();
                table[i].setValue(value);
                incSize();
                return old;
            }
        }

        table[r] = new Entry(k, value);
        incSize();

        checkSize();


		return -1;
	}
	
    
	
	// Rimuove la coppia con chiave k
	// Restituisce il vecchio valore o -1 se la chiave non è presente
	public int remove(String k) {

        int h = hashFunction(k);
        for (int i = h; i < getCapacity(); i = h+i*i) {
            if(table[i] == null){
                break;
            }
            if(table[i].equals(DEFUNCT)){
                break;
            }
            if(table[i].getKey() == k){
                int old = table[i].getValue();
                table[i] = DEFUNCT;
                decSize();
                return old;
            }
        }

		return -1;
	}
	
	// Restituisce un oggetto Iterable contenente tutte le coppie presenti
	// nella tabella hash
	public Iterable<Entry> entrySet() {
        ArrayList<Entry> list = new ArrayList<>(getCapacity());
        for (Entry entry : table) {
            list.add(entry);
        }
        return list;
    }
	
}

