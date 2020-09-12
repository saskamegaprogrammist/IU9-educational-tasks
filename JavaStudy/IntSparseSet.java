import java.util.AbstractSet;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.NoSuchElementException;

public class IntSparseSet extends AbstractSet<Integer>  {
    private ArrayList<Integer> dense;
    private int [] sparse;
    private int n;
    private int low;

    public IntSparseSet(int low, int high){
        int u = high - low;
        this.dense = new ArrayList<Integer>();
        this.sparse = new int[u];
        this.n=0;
        this.low=low;
    }

    @Override
    public int size() {
        return n;
    }

    public boolean contains(int a){
        //System.out.println(a + " " + (a-low) + " " + sparse[a-low]);
        return (0<=sparse[a-low] && sparse[a-low] <this.n && (int)dense.get(sparse[a-low])== a);
    }

    @Override
    public void clear() {
        this.dense.clear();
        this.n=0;
    }

    public boolean add(Integer a){
        if (contains(a) || (int)a<low || (int)a>= (sparse.length+low)) return false;
        else {
            dense.add(a);
            sparse[(int)a - low] = dense.size() - 1;
            this.n = dense.size();
            return true;
        }
    }

    @Override
    public boolean remove(Object a){
        if (contains(a)) {
            int index = sparse[(int)a - low];
            if (index == dense.size() - 1) {
                dense.remove(index);
                this.n = dense.size();
            }
            if (index < dense.size() - 1) {
                int last = dense.remove(dense.size() - 1);
                dense.remove(index);
                sparse[last - low] = index;
                dense.add(index, last);
                this.n = dense.size();
            }
            return true;
        }
        else return false;
    }


    @Override
    public Iterator iterator(){
        return new SetIterator();
    }

    private class SetIterator implements Iterator {
        private int pos;

        public SetIterator() {
            pos = 0;
        }

        public boolean hasNext() {
            return(pos<dense.size());
        }

        public Integer next() {

            if (this.hasNext()){
                pos++;
                return dense.get(pos - 1);
            }
            else throw new NoSuchElementException();
        }

        public void remove(){
            int index = pos-1;
            if (index == dense.size() - 1) {
                dense.remove(index);
                n = dense.size();
            }
            if (index < dense.size() - 1) {
                int last = dense.remove(dense.size() - 1);
                dense.remove(index);
                sparse[last - low] = index;
                dense.add(index, last);
                n = dense.size();
            }
        }
    }
}
