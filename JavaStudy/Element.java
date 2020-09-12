public class Element<T>{
    private T value;
    private Element<T> parent;
    private int depth;

    public Element (T x){
        this.value=x;
        this.parent=this;
        this.depth=0;
    }

    public T x(){
        return this.value;
    }

    private Element<T> find (){
        Element <T> root;
        if (this.parent == this) root=this;
        else {
            root = this.parent = this.parent.find();
        }
        return root;
    }

    public boolean equivalent(Element<T> elem){
        return (this.find() == elem.find());
    }

    public void union(Element <T> elem){
        Element<T> r1 = this.find();
        Element<T> r2= elem.find();
        if (r1.depth < r2.depth){
            r1.parent = r2;
        }
        else{
            r2.parent=r1;
            if(r1.depth ==r2.depth && r1!=r2){
                r1.depth++;
            }
        }
    }
}
