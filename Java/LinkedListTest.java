import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;


public class LinkedListTest {


    protected LinkedList<Integer> empty, list2, list32;
    protected LinkedList.Cell<Integer> cell2;

    @Before
    public void setUp() throws Exception {
	cell2 = new LinkedList.Cell<Integer>(2, null);
	empty = new LinkedList<Integer>();
	list2 = new LinkedList<Integer>(cell2);
	list32 = new LinkedList<Integer>(new LinkedList.Cell<Integer>(3, cell2));
    }

    @Test
    public void testList() {
	assertNull(empty.begin.next);
    }

    @Test public void testCell_1(){
	assertEquals(cell2.value, (Integer) 2);
	assertNull(cell2.next);
    }
    @Test public void testCell_2(){
    LinkedList.Cell<Integer> b = new LinkedList.Cell<Integer>(4, cell2);
	assertEquals(b.value, (Integer) 4);
	assertEquals(b.next, cell2);
    }

    @Test
    public void testListCellOfElem() {
	assertEquals(list2.begin.next.value, (Integer) 2);
	assertNull(list2.begin.next.next);
    }

    @Test
    public void testListElem() {
	LinkedList<Integer> l = new LinkedList<Integer>((Integer) 3);
	assertEquals(l.begin.next.value, (Integer) 3);
	assertNull(l.begin.next.next);
    }

    @Test
    public void testListElemCellOfElem() {
	assertEquals(list32.begin.next.value, (Integer) 3);
	assertEquals(list32.begin.next.next, cell2);
    }

	@Test
	public void testithRef() throws EndOfListError {
		assertEquals(list2.ithRef(0).next, cell2);
	}

    @Test public void testInsertElem_Empty() {
	empty.insert(42);
	assertFalse(empty.isEmpty());
	assertEquals(empty.begin.next.value, (Integer) 42);
	assertNull(empty.begin.next.next);
    }
    @Test public void testInsertElem_List2() {
	list2.insert(42);
	assertEquals(list2.begin.next.value, (Integer) 42);
	assertEquals(list2.begin.next.next.value, (Integer) 2);
	assertTrue(list2.size() == 2);
    }

    @Test public void testInsertElemInt_List32_0() throws EndOfListError {
	list32.insert(0, 42);
	assertEquals(list32.ithRef(0).getValue(), (Integer) 42);
	assertEquals(list32.ithRef(1).getValue(), (Integer) 3);
	assertEquals(list32.ithRef(2).getValue(), (Integer) 2);
	assertTrue(list32.size() == 3);
    }
    @Test public void testInsertElemInt_List32_1() throws EndOfListError {
	list32.insert(1, 42);
	assertEquals(list32.ithRef(0).getValue(), (Integer) 3);
	assertEquals(list32.ithRef(1).getValue(), (Integer) 42);
	assertEquals(list32.ithRef(2).getValue(), (Integer) 2);
	assertTrue(list32.size() == 3);
    }
    @Test public void testInsertElemInt_List32_2() throws EndOfListError {
	list32.insert(2, 42);
	assertEquals(list32.ithRef(0).getValue(), (Integer) 3);
	assertEquals(list32.ithRef(1).getValue(), (Integer) 2);
	assertEquals(list32.ithRef(2).getValue(), (Integer) 42);
	assertTrue(list32.size() == 3);
    }

    @Test(expected=EndOfListError.class)
    public void testremove_Empty() throws EndOfListError {
	empty.remove();
    }

    @Test public void testremove_List2() throws EndOfListError {
	list2.remove();
	assertTrue(list2.isEmpty());
    }

    @Test public void testremove_List32() throws EndOfListError {
	list32.remove();
	assertEquals(list32.ithRef(0).getValue(), (Integer) 2);
	assertTrue(list32.size() == 1);
    }

    @Test public void testremoveInt_List32_0() throws EndOfListError {
	list32.remove(0);
	assertEquals(list32.ithRef(0).getValue(), (Integer) 2);
	assertTrue(list32.size() == 1);
    }

    @Test public void testremoveInt_List32_1() throws EndOfListError {
	list32.remove(1);
	assertEquals(list32.ithRef(0).getValue(), (Integer) 3);
	assertTrue(list32.size() == 1);
    }

    @Test(expected=EndOfListError.class)
    public void testremoveInt_List32_2() throws EndOfListError {
	list32.remove(2);
    }

    @Test
    public void testSize() throws EndOfListError {
        assertTrue(empty.size() == 0);
    }

    @Test
    public void testSize2() throws EndOfListError {
        assertTrue(list2.size() == 1);
    }

    @Test
    public void testSize32() throws EndOfListError {
        assertTrue(list32.size() == 2);
    }

    @Test public void testToString_Empty() throws EndOfListError {
	assertEquals(empty.toString(), "->");
    }
    @Test public void testToString_List2() throws EndOfListError {
	assertEquals(list2.toString(), "->[2]->");
    }
    @Test public void testToString_List32() throws EndOfListError {
	assertEquals(list32.toString(), "->[3]->[2]->");
    }

    @Test
    public void testIsEmpty_Empty() {
	assertTrue(empty.isEmpty());
    }
    @Test
    public void testIsEmpty_List2() {
	assertFalse(list2.isEmpty());
    }

    @Test
    public void testFirstCell() throws EndOfListError {
	assertEquals(list2.first().next, cell2);
    }
    @Test(expected=EndOfListError.class)
    public void emptyFirstCell() throws EndOfListError {
	empty.secondToLast();
    }

}
