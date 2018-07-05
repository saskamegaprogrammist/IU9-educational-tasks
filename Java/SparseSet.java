import java.util.AbstractSet;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.NoSuchElementException;

public class SparseSet<T extends Hintable> extends AbstractSet<T> {
    private ArrayList<T> dense;
    private int n;

    public SparseSet(){
        this.dense=new ArrayList<>();
        n=0;
    }
    public int size(){
        return n;
    }

    public boolean contains(T a){
        if (a.hint()<dense.size()) return (dense.get(a.hint()) == a);
        else return false;
    }

    public void clear(){
        dense.clear();
        n=0;
    }

    public boolean add(T a){
        if (contains(a)) return false;
        else {
            dense.add(a);
            a.setHint(dense.size()-1);
            this.n = dense.size();
            return true;
        }
    }
    public boolean remove(T a){
        if (contains(a)) {
            int index = a.hint();
            if (index == dense.size() - 1) {
                dense.remove(index);
                this.n = dense.size();
            }
            if (index < dense.size() - 1) {
                T last = dense.remove(dense.size() - 1);
                dense.remove(index);
                last.setHint(index);
                dense.add(index, last);
                this.n = dense.size();
            }
            return true;
        }
        else return false;
    }
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

        public T next() {

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
                T last = dense.remove(dense.size() - 1);
                dense.remove(index);
               last.setHint(index);
                dense.add(index, last);
                n = dense.size();
            }
        }
    }
}
