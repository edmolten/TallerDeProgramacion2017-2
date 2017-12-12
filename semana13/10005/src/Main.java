import java.util.*;

public class Main{

    static final double EPS = 1e-8;
    // In Java, we can use Math.PI instead of using Math.acos(-1.0)

    static class point implements Comparable<point>{
            double x, y;                   // only used if more precision is needed
            point() { x = y = 0.0; }                         // default constructor
            point(double _x, double _y) { x = _x; y = _y; }         // user-defined
            // use EPS (1e-9) when testing equality of two floating points
            public int compareTo(point other) {      // override less than operator
                if (Math.abs(x - other.x) > EPS)                // useful for sorting
                    return (int)Math.ceil(x - other.x);       // first: by x-coordinate
                else if (Math.abs(y - other.y) > EPS)
                    return (int)Math.ceil(y - other.y);      // second: by y-coordinate
                else
                    return 0; } };                                    // they are equal

    static double dist(point p1, point p2) {                   // Euclidean distance
            return Math.hypot(p1.x - p2.x, p1.y - p2.y); }         // return double


   static point centerCircleRadius(point a, point b, double radius){
        double squaredist = Math.pow(dist(a, b), 2);
        double k = Math.sqrt(Math.pow(radius, 2)/squaredist - 0.25);

        point center = new point();

        center.x = (a.x + b.x)/2 + k*(b.y - a.y);
        center.y = (a.y + b.y)/2 + k*(a.x - b.x);

        return center;
    }


    public static void main(String[] args) {

        int x, y;
        double radio;
        boolean flag = false;
        String input;
        String[] puntos_poligono;

        Scanner reader = new Scanner(System.in);
        //ArrayList<ArrayList<Integer>> distancias = new ArrayList<ArrayList<Integer>>();
        //ArrayList<Integer> distancias_punto = new ArrayList<Integer>();
        ArrayList<point> puntos = new ArrayList<point>();

        while(true) {
            input = reader.nextLine();
            int cantidad_puntos = Integer.valueOf(input);
            if(cantidad_puntos == 0) break;

            for (int i = 0; i < cantidad_puntos; i++) {
                input = reader.nextLine();
                puntos_poligono = input.split(" ");
                x = Integer.valueOf(puntos_poligono[0]);
                y = Integer.valueOf(puntos_poligono[1]);
                point punto_nuevo = new point(x, y);
                puntos.add(punto_nuevo);
            }

            input = reader.nextLine();
            radio = Double.valueOf(input);

            if(radio == 0.0){
                flag = true;
                System.out.println("There is no way of packing that polygon.");
            }
            else if(puntos.size() == 1){
                flag = true;
                System.out.println("The polygon can be packed in the circle.");
            }
            else {
                looptotal:
                for (point punto1 : puntos) {
                    for (point punto2 : puntos.subList(puntos.indexOf(punto1) + 1, puntos.size())) {
                        if (dist(punto1, punto2) - radio * 2 > EPS){
                            flag = true;
                                System.out.println("There is no way of packing that polygon.");
                            break looptotal;
                        }
                    }
                }
            }

            if(!flag){
                loops:
                for (point punto1 : puntos) {
                    for (point punto2 : puntos) {
                        if (punto1.compareTo(punto2) == 0) continue;
                        else{
                            point auxCenter = centerCircleRadius(punto1, punto2, radio);
                            for (point punto3 : puntos) {
                                if(dist(punto3, auxCenter) - radio <= EPS ){
                                    flag = true;
                                    System.out.println("The polygon can be packed in the circle.");
                                    break loops;
                                }
                            }
                        }
                    }
                }

                if(!flag) System.out.println("There is no way of packing that polygon.");
            }

            puntos.clear();
            flag = false;
            //System.out.println(input);
            //if(input.equals("")){
                //System.out.println("hola");
            //    input = reader.nextLine();
            //}
        }
        //System.out.println("");
    }
}
