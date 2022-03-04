
public class MatriceSparsa {


	private class Elem{
		int i;
		int j;
		int x;
		Elem next;

            public Elem(int i, int j, int x, Elem next) {
                this.i = i;
                this.j = j;
                this.x = x;
                this.next = next;
            }

            public Elem() {
            }
		
		
	}
	
	
	private int m;
	private int n;
	Elem head ;

	public MatriceSparsa(int m, int n) {
		super();
		this.m = m; this.n = n;
	}

	public int getNumRow() {
		
		return this.m;
	}

	public int getNumCol() {
		
		return this.n;
		
	}

	public void mat_remove(int i, int j){
		Elem it = this.head;
		Elem aux = it;

		while(it != null){
			if (it.i == i && it.j == j) {
				if(it.equals(this.head)){
					this.head = it.next;
					return;
				}
				aux.next = it.next;	
				return;
			}
			aux = it;
			it = it.next;
		}
	}


	public void set(int i, int j, int x) {
		
		
		if(i >= this.m || j >= this.n){
			System.out.println("Gli indici inseriti superano i limiti della matrice!");
			return;
		}

		if (x == 0) {
			this.mat_remove(i,j);
			return;
		}
		Elem toPut = new Elem(i,j,x,null);
		

		Elem it = this.head;

		if(it == null || it.i > i || (it.i == i && it.j > j)) {
			toPut.next = this.head;
			this.head = toPut;
			return;
		}
		if(it.i == i && it.j == j) {
			it.x = x;
			return;
		}
		while(it.next != null) {
			if(it.i == i && it.j == j) {
				it.x = x;
				return;
			}
			if(it.next.i > i || (it.next.i ==i && it.next.j > j)) {
				toPut.next = it.next;
				it.next = toPut;
				return;
			}
			it = it.next;
		}
		if(it.i == i && it.j == j) {
			it.x = x;
			return;
		}
		it.next = toPut;
		
			
	}

	public int get(int i, int j) {
		
		
		Elem it = head;
		while(it.next != null){
		
			if(it.i == i && it.j == j){
			
				return it.x;
			}
		
		}
		
		return 0;
		
	}

	public String toString() {
		StringBuffer ret = new StringBuffer("");
		int i,j;
		Elem it = this.head;
		for(i = 0; i< this.m; i++) {
			for (j= 0; j<this.n; j++) {
				if (it == null || (it.i > i && it.j > j)) {
					ret.append("0 ");
				}
				else if (it.i == i && it.j == j) {
					ret.append(it.x + " ");
					it = it.next;
				}
				else {
					ret.append("0 ");
				}
			}
			ret.append("\n");
		}
		return ret.toString();
	}

	public MatriceSparsa add(MatriceSparsa mat1, MatriceSparsa mat2) {
      
		
                if(mat1.getNumRow() != mat2.getNumRow() || mat1.getNumCol() != mat2.getNumCol()){
                
                    System.out.println("Addizione tra matrici non possibile");
                    return null;
                }
             
                
                Elem it = mat1.head;
                
                Elem it3 = this.head;
                
                while(it.next != null  ){

                    Elem it2 = mat2.head;
                    
                    while(it2.next != null){

                        if(it.i == it2.i && it.j == it2.j){

                            int value = it.x + it2.x; 
                            this.set(it.i,it.j,value);
                            
                           
                        }
                        
                        it2 = it2.next;

                    }
                    
                   it = it.next;
                    
                    
                }
                
                return this;
	}

	public MatriceSparsa tra(MatriceSparsa mat1, MatriceSparsa mat2) {
		// TODO: Implement here
		return null;
	}

	public MatriceSparsa mul(MatriceSparsa mat1, MatriceSparsa mat2) {
		// TODO: Implement here
		return null;
	}
        
        
        
        
}
