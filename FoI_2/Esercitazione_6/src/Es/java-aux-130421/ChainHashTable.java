import java.util.LinkedList;
import java.util.ArrayList;

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
		int c = getCapacity();
		table = new LinkedList[c];
		for (int i = 0; i < getCapacity(); i++) {
			table[i] = new LinkedList<Entry>();
		}
	}

	// Restituisce il valore (intero) associato alla chiave k
	// Restituisce -1 se la chiave è assente
	public int get(String k) {
		int hashcode = super.hashFunction(k);

		for(int i = 0; i < table[hashcode].size() ; i++){

			Entry e = table[hashcode].get(i);
			if( e.getKey() == k){
				
				return e.getValue();
			}
		}

		return -1;
	}
	
	// Aggiorna il valore associato alla chiave k
	// Restituisce il vecchio valore o -1 se la chiave non è presente
	public int put(String k, int value) {

		// Tener conto del maxLamda e del resizing

		

		int hashcode = hashFunction(k);
		LinkedList<Entry> entryList = table[hashcode];
		for(int i = 0; i < entryList.size() ; i++){

			Entry e = entryList.get(i);
			int entryValueOld = e.getValue();
			if( e.getKey() == k){
				e.setValue(value);
				incSize();
				return entryValueOld;
			}
		}

		entryList.add(new Entry(k, value));
		incSize();

		checkSize();

		return -1;
	}
	
	
	// Rimuove la coppia con chiave k
	// Restituisce il vecchio valore o -1 se la chiave non è presente
	public int remove(String k) {
		
		int hashcode = super.hashFunction(k);

		for(int i = 0; i < table[hashcode].size() ; i++){

			Entry e = table[hashcode].get(i);
			if( e.getKey() == k){
				
				int entryValueOld = e.getValue();
				table[hashcode].remove(i);
				decSize();
				return entryValueOld;
			}
		}

		return -1;
	}
	
	// Restituisce un oggetto Iterable contenente tutte le coppie presenti
	// nella tabella hash
	public Iterable<Entry> entrySet() {

		ArrayList<Entry> list = new ArrayList<>(super.size());

		for (LinkedList<Entry> linkedList : table) {
			for (Entry entry : linkedList) {
				list.add(entry);
			}
		}
		return list;
	}

}