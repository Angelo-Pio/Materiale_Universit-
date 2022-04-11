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
            table = new Entry[this.getCapacity()];
            return;
	}

	// Restituisce il valore (intero) associato alla chiave k
	// Restituisce -1 se la chiave è assente
	public int get(String k) {
	
            int position = hashFunction(k);
            
            if(size() == 0){
                return -1;
            }
            Entry couple = table[position];
            
            if(couple == null){
                return -1;
            }
            
            if(couple.equals(DEFUNCT)){
                for (int i = position; i < table.length; ++i) {
                    int pos = quadProb(position, i);
                    if(table[pos].getKey() == k){
                        return table[pos].getValue();
                    }
                }
                return -1;
            }
            
            return couple.getValue();
	}
	
        protected int quadProb(int hash, int i){ return (hash + (i*i)) % this.getCapacity();}
        
	// Aggiorna il valore associato alla chiave k
	// Restituisce il vecchio valore o -1 se la chiave non è presente
	public int put(String k, int value) {
		
            int position = hashFunction(k);
            
            Entry couple = table[position];
            
            if(couple == null){
                couple.setValue(value);
                return -1;
            }
            
            if(couple.equals(DEFUNCT)){
                
                int p = position;
                
                for (int i = position; i < table.length; ++i) {
                    int pos = quadProb(position, i);
                    if(table[pos].getKey() == k){
                        return table[pos].getValue();
                    }
                }
                return -1;
            }
            
            int old = couple.getValue();
            couple.setValue(value);
            
            return old;
	}
	
	
	// Rimuove la coppia con chiave k
	// Restituisce il vecchio valore o -1 se la chiave non è presente
	public int remove(String k) {
		return -1;
	}
	
	// Restituisce un oggetto Iterable contenente tutte le coppie presenti
	// nella tabella hash
	public Iterable<Entry> entrySet() {
		return null;
	}
	
}


