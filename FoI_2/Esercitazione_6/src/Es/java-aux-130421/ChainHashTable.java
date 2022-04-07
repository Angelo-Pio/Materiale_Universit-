import java.util.LinkedList;

public class ChainHashTable extends AbstractHashTable {
	// Un array di LinkedList per le liste di trabocco 
	// L'array table implementa la tabella hash
	private LinkedList<Entry> [] table;
	
	// Costruttori
	public ChainHashTable(int cap, int p, double lambda) {
		super(cap, p, lambda);
	}
	public ChainHashTable(int cap, int p) {
		super(cap, p); // massimo fattore di carico predefinito
	}
	public ChainHashTable(int cap) {
		super(cap); // primo predefinito
	}
	public ChainHashTable() {
		super(); // capacità predefinita
	}
	
	// Metodi non implementati in AbstractHashTable

	// Inizializza una tabella hash vuota secondo i parametri passati al costruttore
	protected void createTable() {
            int cap = this.getCapacity();
            this.table = (LinkedList<Entry>[]) new LinkedList[cap];
        }

	// Restituisce il valore (intero) associato alla chiave k
	// Restituisce -1 se la chiave è assente
	public int get(String k) {
	   
            if(size() == 0) return -1;
            
            int index = hashFunction(k);
            LinkedList<Entry> list = table[index];
            
            if(list == null) return -1;
            
            for (int j = 0; j < list.size(); j++) {
                
                Entry entry = list.get(j);
                
                if(entry.getKey() == k){
                    
                    return entry.getValue();
                }
            }	
            return -1;
                
	}
	
	// Aggiorna il valore associato alla chiave k
	// Restituisce il vecchio valore o -1 se la chiave non è presente
	public int put(String k, int value) {
            
            int old = -1;
            
            if(size() + 1 < getCapacity() * getMaxLambda()){
                resize(2*getCapacity() - 1);
            }
            
            int index = hashFunction(k);
            LinkedList<Entry> list = table[index];
            
            if(list == null){
                
                list = new LinkedList<>();
                list.addLast(new Entry(k, value));
                incSize();
                
            }else{
            
                for (int j = 0; j < list.size(); j++) {

                    Entry entry = list.get(j);

                    if(entry.getKey() == k){

                        old = entry.getValue();
                        entry.setValue(value);
                    }
                }
                
                if(old == -1){list.addLast(
                        new Entry(k, value)); 
                        incSize();
                }
                
            }
            
            return old;
            
        }
	
	
	// Rimuove la coppia con chiave k
	// Restituisce il vecchio valore o -1 se la chiave non è presente
	public int remove(String k) {
            if (isEmpty())
			return -1;
		int i = hashFunction(k);
		if (table[i] == null)
			return -1;
		for (Entry e: table[i])
			if (e.getKey().equals(k)) {
				int old = e.getValue();
				table[i].remove(e);
				decSize();
				if (table[i].size() == 0)
					table[i] = null;
				return old;
			}
		return -1;
        }
	
	// Restituisce un oggetto Iterable contenente tutte le coppie presenti
	// nella tabella hash
	public Iterable<Entry> entrySet() {
            LinkedList<Entry> pairs;
		if (isEmpty())
			return null;
		pairs = new LinkedList<Entry>();
		for (int i = 0; i < table.length; i++)
			if (table[i] != null)
				for (Entry e: table[i])
					pairs.addLast(e);
		return pairs;
            
	}

}


