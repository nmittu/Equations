package com.mittudev.equations;

import com.mittudev.util.ArrayListUtil;

import java.util.ArrayList;

/**
 * Created by nickm on 12/3/2016.
 */
public class Main {
    public static void main(String [] args){
        Equation eq = new Equation("log(2, x)-3(log(4, 37x))");

        System.out.printf("%s --- %s --- %s --- %s", eq.equation(), eq.reversePolish(), eq.solve(new Equation("2^-54*37^-3").solve()), eq.equals(new Equation("x")));
    }
}
