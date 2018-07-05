import javax.xml.bind.Element;
import java.util.*;

public class SkipList<K extends Comparable<K>,V> extends AbstractMap<K,V> {

    Element list;
    int levels;

    private class Element{
        K key;
        V value;
        Object[] links;

        public Element(K k, V v){
            this.key=k;
            this.value=v;
        }

        public Element(int l) {
            this.key=null;
            this.value=null;
            this.links = new Object[l];
        }

    }

    public SkipList(int levels) {
        this.list= new Element(levels);
        //this.list.links = new Object[levels];
        this.levels=levels;
        for (int i=0; i<levels; i++){
            list.links[i]=null;
        }

    }

    public void clear(){
        this.list.links[0]=null;
    }

    private Element next(Element e){
        return (Element) e.links[0];
    }

    private Object[] skip (K k, Object[] p){

        Element x = this.list;
        for (int i = this.levels-1; i>=0; i--){
            while (  x.links[i]!= null && ((Element)x.links[i]).key.compareTo(k)  < 0){
                x=(Element)x.links[i];
            }
            p[i]=x;
        }
        return p;
    }

    public V get(Object k){
        Object[] p = new Object[this.levels];
        this.skip((K)k, p);
        Element e=next((Element)p[0]);
        if ((e==null) || !e.key.equals(k)) return null;
        return e.value;
    }

    public boolean containsKey(Object k){
        Object[] p = new Object[this.levels];
        this.skip((K)k, p);
        Element e = next((Element)p[0]);
        return (e!=null && e.key.equals(k));
    }

    public boolean isEmpty(){
        return (this.list.links[0] == null);
    }

    public V put (K k, V v){
        V out=null;
        Object[] p = new Object[this.levels];
        this.skip(k, p);
        Element t=(Element)p[0];
        Element j = (Element)t.links[0];
        if (j !=null && j.key == k) {
            //throw new RuntimeException("this element is already there");
            out = j.value;
            remove(k);

        }
        Element e = new Element(k, v);
        e.links= new Object[this.levels];

        Random o =new Random();
        int r = o.nextInt(100);
        r*=2;
        r=Math.abs(r);
        //System.out.println(r);
        int i=0;
        //System.out.println(((Element)p[0]).value);
        while (i<this.levels && r%2 == 0){

            e.links[i] =((Element) p[i]).links[i];
            ((Element) p[i]).links[i]= e;


            i++;
            r/=2;
        }
        while (i<this.levels){
            e.links[i]=null;
            i++;
        }
        return out;
    }

    @Override
    public int size() {
        int i=0;
        Element e=(Element)this.list.links[0];
        while(e!=null){
            i++;
            e=next(e);
        }
        return i;
    }

    public void putAll(Map<? extends K,? extends V> m) {
        for (Object t : m.keySet()) {
            this.put((K) t, m.get(t));
        }
    }

    public V remove (Object k){
        Object[] p = new Object[this.levels];
        this.skip((K)k, p);
        Element e = next((Element)p[0]);
        if (e==null || !e.key.equals(k)) return null;
        for (int i=0; i<this.levels && ((Element)p[i]).links[i]  == e; i++) {
            ((Element)p[i]).links[i]=e.links[i];
        }
        return e.value;
    }

    public boolean containsValue(Object v){
        Element e=(Element)this.list.links[0];
        while(e!=null){
            if (e.value.equals(v)) return true;
            e=next(e);
        }
        return false;
    }

    public Set<K> keySet(){
        Set<K> set =new Set<K>() {

            private ArrayList<K> setK=new ArrayList<>();

            @Override
            public int size() {
                return setK.size();
            }

            @Override
            public boolean isEmpty() {
                return (setK.size()==0);
            }

            @Override
            public boolean contains(Object o) {
                for (K l: setK ) {
                    if (l.equals(o)) return true;
                }
                return false;
            }

            @Override
            public Iterator<K> iterator(){
                return new SetIterator();
            }

            class SetIterator implements Iterator<K> {
                private int pos;

                public SetIterator() {
                    pos = 0;
                }

                public boolean hasNext() {
                    return(pos<setK.size());
                }

                public K next() {

                    if (this.hasNext()){
                        pos++;
                        return setK.get(pos-1);
                    }
                    else throw new NoSuchElementException();
                }

                public void remove(){
                    setK.remove(pos-1);
                    pos--;

                }
            }

            @Override
            public Object[] toArray() {
                Object [] array = new Object[setK.size()];
                int i=0;
                for (K l: setK) {
                    array[i]=l;
                    i++;
                }
                return array;
            }


            public <T> T[] toArray(T[] a) {
                for (int i=a.length; i<a.length+setK.size(); i++){
                    a[i]=(T)setK.get(i-a.length);
                }
                return a;
            }

            @Override
            public boolean add(K k) {

                for (K l:setK) {
                    if (l.equals(k)) return false;
                }
                setK.add(k);
                return true;
            }

            @Override
            public boolean remove(Object o) {
                for (K l:setK) {
                    if (l.equals(o)) {
                        setK.remove(o);
                        return true;
                    }
                }
                return false;
            }

            @Override
            public boolean containsAll(Collection<?> c) {
                for (Object l: c) {
                    if (!this.setK.contains(l))return false;
                }
                return true;
            }

            @Override
            public boolean addAll(Collection<? extends K> c) {
                int  i=0;
                for (Object l: c) {
                    if (!setK.contains((K)c)) {
                        setK.add((K)l);
                        i++;
                    }

                }
                if (i==0) return false;
                return true;
            }

            @Override
            public boolean retainAll(Collection<?> c) {
                int  i=0;
                for (K l: setK) {
                    if (c.contains(l)) {
                        setK.remove(l);
                        i++;
                    }

                }
                if (i==0) return false;
                return true;
            }

            @Override
            public boolean removeAll(Collection<?> c) {
                int  i=0;
                for (Object l: c) {
                    if (setK.contains((K)l)) {
                        setK.remove((K)l);
                        i++;
                    }

                }
                if (i==0) return false;
                return true;
            }

            @Override
            public void clear() {
                setK.clear();
            }
        };

        Element e = (Element)list.links[0];
        while (e!=null){
            set.add(e.key);
            e=next(e);
        }

        return set;

    }

    public Set<Map.Entry<K, V>> entrySet(){
        class MyEntry<key, value> implements Map.Entry<K, V> {

            private K key;
            private V value;

            public MyEntry (K k,V v){
                this.key=k;
                this.value=v;
            }

            @Override
            public K getKey() {
                return this.key;
            }

            @Override
            public V getValue() {
                return this.value;
            }

            @Override
            public V setValue(V value) {
                V val= this.value;



                Object[] p = new Object[levels];
                SkipList.this.skip(this.key, p);
                SkipList.Element t=(SkipList.Element)p[0];
                SkipList.Element j = (SkipList.Element)t.links[0];
                if (j !=null && j.key.compareTo(this.key) == 0) {
                    //throw new RuntimeException("this element is already there");
                    SkipList.this.remove(this.key);

                }
                SkipList.Element e = new SkipList.Element(this.key, value);
                e.links= new Object[levels];

                Random o =new Random();
                int r = o.nextInt(100);
                r*=2;
                r=Math.abs(r);
                //System.out.println(r);
                int i=0;
                //System.out.println(((Element)p[0]).value);
                while (i<levels && r%2 == 0){

                    e.links[i] =((SkipList.Element) p[i]).links[i];
                    ((SkipList.Element) p[i]).links[i]= e;


                    i++;
                    r/=2;
                }
                while (i<levels){
                    e.links[i]=null;
                    i++;
                }
                this.value=value;
                return val;
            }

            @Override
            public boolean equals(Object o) {
                return false;
            }

            @Override
            public int hashCode() {
                return 0;
            }
        };

        Set<Map.Entry<K, V>> set =new Set<Map.Entry<K, V>>(){


            private ArrayList<Map.Entry<K, V>> setK = new ArrayList<>();

            @Override
            public int size() {
                return setK.size();
            }

            @Override
            public boolean isEmpty() {
                return (setK.size()==0);
            }

            @Override
            public boolean contains(Object o) {
                for (Map.Entry<K, V> l: setK ) {
                    if (l.equals(o)) return true;
                }
                return false;
            }

            @Override
            public Iterator<Map.Entry<K, V>> iterator(){
                return new SetIterator();
            }

            class SetIterator implements Iterator<Map.Entry<K, V>> {
                private int pos;

                public SetIterator() {
                    pos = 0;
                }

                public boolean hasNext() {
                    return(pos<setK.size());
                }

                public Map.Entry<K, V> next() {

                    if (this.hasNext()){
                        pos++;
                        return setK.get(pos - 1);
                    }
                    else throw new NoSuchElementException();
                }

                public void remove(){
                    Object[] p = new Object[levels];
                    skip(setK.get(pos-1).getKey(), p);
                    SkipList.Element e = (SkipList.Element)((SkipList.Element)p[0]).links[0];
                    for (int i = 0; i<levels && ((SkipList.Element)p[i]).links[i]==e; i++) {
                        ((SkipList.Element)p[i]).links[i]=e.links[i];
                    }
                }
            }

            @Override
            public Object[] toArray() {
                Object [] array = new Object[setK.size()];
                int i=0;
                for (Map.Entry<K, V> l: setK) {
                    array[i]=l;
                    i++;
                }
                return array;
            }


            public <T> T[] toArray(T[] a) {
                for (int i=a.length; i<a.length+setK.size(); i++){
                    a[i]=(T)setK.get(i-a.length);
                }
                return a;
            }

            @Override
            public boolean add(Map.Entry<K, V> k) {
                for (Map.Entry<K, V> l:setK) {
                    if (l.equals(k)) return false;
                }
                setK.add(k);
                return true;
            }

            @Override
            public boolean remove(Object o) {
                for (Map.Entry<K, V> l:setK) {
                    if (l.equals(o)) {
                        setK.remove(o);
                        //SkipList.this.remove(o);
                        return true;
                    }
                }
                return false;
            }


            @Override
            public boolean containsAll(Collection<?> c) {
                for (Object l: c) {
                    if (!this.setK.contains(l))return false;
                }
                return true;
            }

            @Override
            public boolean addAll(Collection<? extends Map.Entry<K, V>> c) {
                int  i=0;
                for (Object l: c) {
                    if (!setK.contains((Map.Entry<K, V>)c)) {
                        setK.add((Map.Entry<K, V>)l);
                        i++;
                    }

                }
                if (i==0) return false;
                return true;
            }

            @Override
            public boolean retainAll(Collection<?> c) {
                int  i=0;
                for (Map.Entry<K, V> l: setK) {
                    if (c.contains(l)) {
                        setK.remove(l);
                        i++;
                    }

                }
                if (i==0) return false;
                return true;
            }

            @Override
            public boolean removeAll(Collection<?> c) {
                int  i=0;
                for (Object l: c) {
                    if (setK.contains((Map.Entry<K, V>)l)) {
                        setK.remove((Map.Entry<K, V>)l);
                        i++;
                    }

                }
                if (i==0) return false;
                return true;
            }

            @Override
            public void clear() {
                setK.clear();
            }
        };
        Element e = (Element)list.links[0];
        while (e!=null){
            MyEntry<K, V> m = new MyEntry<K, V>(e.key,e.value);

            set.add(m);
            e=next(e);
        }
        return set;
    }

}