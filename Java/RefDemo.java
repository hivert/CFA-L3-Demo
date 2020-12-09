public class RefDemo {

    public static void changeContenu(int[] ar, int v) {
                    // Si l'on modifie le contenu de arr...
        ar[0] = v;  // ça change le contenu du tableau dans main.
    }

    public static void changeRef(int[] ar, int v) {
        ar = new int[2];  // Si l'on modifie la référence arr...
        ar[0] = v;        // ça ne change pas le contenu du tableau dans main.
    }

    public static void main(String[] args) {
        int [] arr = new int[2];
        arr[0] = 4;
        arr[1] = 5;
        int [] arr_pas_copy = arr;       // arr et arr_pas_copy se réfère au même tableau

        changeContenu(arr, 10);
        System.out.println(arr[0]);      // Affiche 10..

        changeContenu(arr_pas_copy, 15); // modifie arr_pas_copy, affiche arr
        System.out.println(arr[0]);      // Affiche 15..

        changeRef(arr, 12);              // changement de la référence dans la fonction pas reporté ici.
        System.out.println(arr[0]);      // Affiche encore 15..
    }

}
