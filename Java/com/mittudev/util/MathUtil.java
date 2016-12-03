package com.mittudev.util;

/**
 * Created by nickm on 12/3/2016.
 */
public class MathUtil {
    public static int factorial(int x){
        if (x <= 1){
            return 1;
        }else {
            return x*factorial(x-1);
        }
    }

    public static double log(double b, double x){
        return Math.log(x)/Math.log(b);
    }
}
