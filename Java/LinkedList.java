import java.util.Collection;

class EndOfListError extends Exception {
  EndOfListError() {
    super ( "End of List Error" );
  }
}

// Note: this code is focused on algorithm, without taking care
// of the interface and access right (i.e. everything is public).
// In a real life code, they should be carefully adjusted.
public class LinkedList<Elem> {

  // Just a reference on a cell. represent a position in a linked list.
  static class RefCell<Elem> {
    public Cell<Elem> next;

    public RefCell() {
      next = null;
    };

    public RefCell(Cell<Elem> cell) {
      next = cell;
    };

    public void insertCell(Cell<Elem> cell) {
      cell.next = next;
      next = cell;
    }

    public void insertElem(Elem val) {
      next = new Cell<Elem>(val, next);
    }

    public Cell<Elem> removeCell() throws EndOfListError {
      if (next == null) throw new EndOfListError();
      Cell<Elem> res = next;
      next = next.next;
      return res;
    }

    public Elem removeElem() throws EndOfListError{
      return removeCell().value;
    }

    public Elem getValue() throws EndOfListError {
      if (next == null) throw new EndOfListError();
      return next.value;
    }
  }

  // Cell for linked list.
  static class Cell<Elem> extends RefCell<Elem> {
    public Elem value;

    public Cell(Elem value, Cell<Elem> next) {
      this.value = value;
      this.next = next;
    }

    public Cell(Elem value) {
      this.value = value;
      this.next = null;
    }

  }

  public RefCell<Elem> begin;

  public LinkedList() {
    begin = new RefCell<Elem>();
  }

  public LinkedList(Elem e) {
    begin = new RefCell<Elem>(new Cell<Elem>(e));
  }
  public LinkedList(Cell<Elem> c) {
    begin = new RefCell<Elem>(c);
  }


  ////////////////////////////////////
  // Methods dealing with positions //
  ////////////////////////////////////
  public RefCell<Elem> ithRef(int i) throws EndOfListError {
    RefCell<Elem> cur = begin;
    for (int j = 0; j < i; j++) {
      if (cur.next == null) throw new EndOfListError();
      cur = cur.next;
    }
    return cur;
  }

  public RefCell<Elem> first() {
    return begin;
  }

  public RefCell<Elem> last() {
    RefCell<Elem> cur = begin;
    while (cur.next != null)
      cur = cur.next;
    return cur;
  }

  public RefCell<Elem> secondToLast() throws EndOfListError {
    RefCell<Elem> cur = begin;
    if (cur.next == null) throw new EndOfListError();
    while (cur.next.next != null)
      cur = cur.next;
    return cur;
  }

  public RefCell<Elem> find(Elem e) {
    RefCell<Elem> cur = begin;
    while (cur.next != null && cur.next.value != e)
      cur = cur.next;
    return cur;
  }


  //////////////////////////////////
  // Various modification methods //
  //////////////////////////////////
  public void insert(Elem value) {
    first().insertElem(value);
  }

  public void add(Elem value) {
    last().insertElem(value);
  }

  public void insert(int i, Elem value) throws EndOfListError {
    ithRef(i).insertElem(value);
  }

  private void addAllPos(RefCell<Elem> cur, Collection<? extends Elem> coll) {
    for (Elem el : coll) {
      cur.insertElem(el);
      cur = cur.next;
    }
  }

  public void addAll(Collection<? extends Elem> coll) {
    addAllPos(last(), coll);
  }

  public void addAll(int i, Collection<? extends Elem> coll) throws EndOfListError {
    addAllPos(ithRef(i), coll);
  }

  public Elem remove() throws EndOfListError {
    return begin.removeElem();
  }

  public Elem remove(int i) throws EndOfListError {
    return ithRef(i).removeElem();
  }

  public boolean removeElem(Elem e) throws EndOfListError {
    RefCell<Elem> pos = find(e);
    if (pos.next != null) {
      pos.removeElem();
      return true;
    }
    else return false;
  }


  public void clear() {
    begin.next = null;
  }


  ////////////////////
  // access methods //
  ////////////////////
  public boolean contains(Elem value) {
    return find(value).next != null;
  }

  public Elem get(int i) throws EndOfListError {
    return ithRef(i).next.value;
  }

  public int indexOf(Object value) {
    Cell<Elem> cur = begin.next;
    int i = 0;
    while (cur != null) {
      if (cur.value == value)
        return i;
      i++;
      cur = cur.next;
    }
    return -1;
  }

  public boolean isEmpty() {
    return (begin.next == null);
  }

  public int size() {
    int i = 0;
    RefCell<Elem> cur = begin;
    while (cur.next != null) {
      cur = cur.next;
      i++;
    }
    return i;
  }


  public String toString() {
    StringBuffer res = new StringBuffer("->");
    RefCell<Elem> cur = begin;
    while (cur.next != null) {
      res.append("[").append(cur.next.value).append("]->");
      cur = cur.next;
    }
    return res.toString();
  }



}
