package com.mittudev.equations;

import com.mittudev.util.Tuple;

import java.util.ArrayList;
import java.util.Dictionary;
import java.util.HashMap;

/**
 * Created by nick on 12/2/16.
 */
public class Equation {
    private String equation;
    private ArrayList<String> reversePolish = new ArrayList<>();
    private static HashMap<String, Tuple<Integer, String>> operators = new HashMap<>();
    private static String[] functions = {"log",
                                         "ln",
                                         "abs",
                                         "acos",
                                         "asin",
                                         "atan",
                                         "cos",
                                         "sin",
                                         "tan"};


    public void Equation(String equation){
        operators.put("^", new Tuple<>(4, "R"));
        operators.put("*", new Tuple<>(4, "L"));
        operators.put("/", new Tuple<>(4, "L"));
        operators.put("+", new Tuple<>(4, "L"));
        operators.put("-", new Tuple<>(4, "L"));
        operators.put("~", new Tuple<>(4, "R"));
        operators.put("|", new Tuple<>(4, "R"));
        operators.put("!", new Tuple<>(4, "R"));

        this.equation = equation;
        shunt();
    }

    private void shunt(){

    }

    private ArrayList<String> findFuncTokens(ArrayList<String> array){
        for(String func : functions){

        }
        return null;
    }
}
