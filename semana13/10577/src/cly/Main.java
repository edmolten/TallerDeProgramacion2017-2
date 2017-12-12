package cly;

import java.text.DecimalFormat;
import java.text.NumberFormat;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {

    static class point {
        double x, y;
        point(Scanner reader) {
            String p = reader.nextLine();
            String[] coords = p.split(" ");
            x = Double.valueOf(coords[0]);
            y = Double.valueOf(coords[1]);
        }

        point(double v, double v1) {
            x = v;
            y = v1;
        }
    }

    static class tri{
        final double x1;
        final double y1;
        final double x2;
        final double y2;
        final double x3;
        final double y3;
        final double A;
        final double B;
        final double C;
        final double D;
        final double x;
        final double y;
        tri(point p1, point p2, point p3){
                x1 = p1.x;
                y1 = p1.y;
                x2 = p2.x;
                y2 = p2.y;
                x3 = p3.x;
                y3 = p3.y;
                A = x1*(y2-y3)-y1*(x2-x3)+x2*y3-x3*y2;
                B = (p2(x1)+p2(y1))*(y3-y2)+(p2(x2)+p2(y2))*(y1-y3)+(p2(x3)+p2(y3))*(y2-y1);
                C = (p2(x1)+p2(y1))*(x2-x3)+(p2(x2)+p2(y2))*(x3-x1)+(p2(x3)+p2(y3))*(x1-x2);
                D = (p2(x1)+p2(y1))*(x3*y2-x2*y3)+ (p2(x2)+p2(y2))*(x1*y3-x3*y1)+(p2(x3)+p2(y3)*(x2*y1-x1*y2));
                x = - B/(2*A);
                y = -C/(2*A);
        }

        double p2(double a) {
            return Math.pow(a,2);
        }

        double getR() {
            return Math.sqrt((p2(B)+p2(C)-4*A*D)/(4*p2(A)));

        }
    }

    static point  rotate_point(double ox,double oy,double angle,point p)
    {
        double x = Math.cos(angle)*(p.x-ox)-Math.sin(angle)*(p.y-oy)+ox;
        double y = Math.sin(angle)*(p.x-ox)+Math.cos(angle)*(p.y-oy)+oy;
        return new point(x, y);
    }

    static double dist(point p1, point p2) {                   // Euclidean distance
        return Math.hypot(p1.x - p2.x, p1.y - p2.y); }         // return double

    public static void main(String[] args) {
        Scanner reader = new Scanner(System.in);
        ArrayList<point> points;
        int test = 1;
        while(true){
            int n = Integer.valueOf(reader.nextLine());
            if(n == 0) break;
            points = new ArrayList<>();
            point[] three_points = new point[3];
            for( int i = 0; i < 3 ; i++){
                three_points[i] = new point(reader);
            }
            points.add(three_points[0]);
            tri t = new tri(three_points[0],three_points[1],three_points[2]);
            double angle = 360.0 / n;
            for(int i=1;i<n;i++){
                double rotAngle = angle;// * i;
                double rads = rotAngle*Math.PI/180.0;
                point p = rotate_point(t.x, t.y, rads, points.get(0));
                points.add (0,p);
            }
            double longestX = 0;
            double longestY = 0;
            for(point polyPoint : points){
                double distX = Math.abs(t.x - polyPoint.x);
                double distY = Math.abs(t.y - polyPoint.y);
                if (distX >= longestX){
                    longestX = distX;
                }
                if (distY >= longestY){
                    longestY = distY;
                }
            }
            NumberFormat nf = new DecimalFormat("#0.000");
            nf.setMaximumFractionDigits(3);
            String result = nf.format(longestY*2*longestX*2);
            System.out.println("Polygon " + String.valueOf(test)+ ": " + result );
            test++;
        }
    }
}
