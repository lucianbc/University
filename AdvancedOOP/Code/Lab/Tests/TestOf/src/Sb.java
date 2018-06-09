import java.io.*;
import java.sql.ResultSet;
import java.util.List;
import java.util.stream.Collectors;

class Bulk {
    public void metoda() {
        System.out.println("Normal");
    }
}

public class Sb extends Bulk {
    public void metoda(){
        System.out.println("Speciala");
    }

    public static void main(String[] args) {
        Sb s = new Sb();
//        s.metoda();
//
//        List<Integer> l = new LinkedList<>();
//        l.add(3);
//
//
//        List<Double> d = s.transform(l);
//        System.out.println(d);

        s.write(new int[] {1, 2, 3});
    }

    public int getEx(int [] vec) {
        int min = vec[0];
        int max = vec[0];

        return min;
//        return max;
    }

    public List<Double> transform(List<Integer> list) {
        return list.stream().map(Integer::doubleValue).collect(Collectors.toList());
    }

    public void write(int[] numbers) {
        try(FileOutputStream fos = new FileOutputStream("myFile.txt"); PrintWriter writer = new PrintWriter(fos)) {

            for (int i = 0; i < numbers.length - 1; i++) {
                writer.print(numbers[i] + ", ");
            }

            writer.print(numbers[numbers.length - 1]);
        } catch (FileNotFoundException ex) {
            System.out.println("Fisierul nu a putut fi gasit sau creeat");
        } catch (IOException e) {
            System.out.println("Eroare la scrierea in fisier");
        }
    }

    public void rset(ResultSet resultSet) throws Exception{
        System.out.println("asd");
    }
}

