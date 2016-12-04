package com.mittudev.equations;

import com.mittudev.util.ArrayListUtil;

import java.util.ArrayList;

/**
 * Created by nickm on 12/3/2016.
 */
public class Main {
    public static void main(String [] args){
        Equation eq = new Equation("add(2, abs(-3))");
        eq.addFunc("add", 2, (double[] argz) -> argz[0]+argz[1]);

        System.out.printf("%s --- %s --- %s --- %s", eq.equation(), eq.reversePolish(), eq.solve(new Equation("2^-54*37^-3").solve()), eq.equals(new Equation("x")));
    }
}
