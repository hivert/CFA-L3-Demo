public class Demo {
    public static void main(String args[]) throws EndOfListError
    {
        LinkedList<Integer> lst = new LinkedList<Integer>();

        System.out.println("len(lst) = "+lst.size());
        lst.insert(2);
        lst.insert(5);
        System.out.println("len(lst) = "+lst.size());
        System.out.println("lst[0] = "+lst.ithRef(0).getValue());
        System.out.println("lst[1] = "+lst.ithRef(1).getValue());
        System.out.println(lst);
        lst.insert(1, 12);
        System.out.println(lst);
        lst.insert(0, 15);
        System.out.println(lst);
        lst.remove(2);
        System.out.println(lst);
    }

}
