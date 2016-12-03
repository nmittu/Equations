package com.mittudev.equations;

import com.mittudev.util.ArrayListUtil;
import com.mittudev.util.MathUtil;
import com.mittudev.util.StringUtil;
import com.mittudev.util.Tuple;

import java.math.BigDecimal;
import java.util.*;

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


    public Equation(String equation){
        operators.put("^", new Tuple<>(4, "R"));
        operators.put("*", new Tuple<>(3, "L"));
        operators.put("/", new Tuple<>(3, "L"));
        operators.put("+", new Tuple<>(2, "L"));
        operators.put("-", new Tuple<>(2, "L"));
        operators.put("~", new Tuple<>(6, "R"));
        operators.put("|", new Tuple<>(4, "R"));
        operators.put("!", new Tuple<>(5, "R"));

        this.equation = equation;
        shunt();
    }

    private void shunt(){
        ArrayList<String> equationArray = new ArrayList<>(Arrays.asList(equation.replace(" ", "").split("")));
        equationArray = fixVarMult(fixParenMult(convertNegetives(combineNums(findFuncTokens(equationArray)))));
        Stack<String> operatorStack = new Stack<>();
        ArrayList<String> output = new ArrayList<>();


        for(String token : equationArray){
            if(!operators.containsKey(token) && !Arrays.asList(functions).contains(token) && !token.equals("(") && !token.equals(")") && !token.equals(",")){
                output.add(token);
            }else if (Arrays.asList(functions).contains(token)){
                operatorStack.push(token);
            }else if (token.equals(",")){
                while (operatorStack.size()>0 && !operatorStack.lastElement().equals("(")){
                    output.add(operatorStack.pop());
                }
            }else if (operators.containsKey(token)){
                while (operatorStack.size() > 0 && operators.containsKey(operatorStack.lastElement()) && ((operators.get(token).get1() == "L" && operators.get(token).get0() <= operators.get(operatorStack.lastElement()).get0()) || (operators.get(token).get1() == "R" && operators.get(token).get0() < operators.get(operatorStack.lastElement()).get0()))){
                    output.add(operatorStack.pop());
                }
                operatorStack.push(token);
            }else if (token.equals("(")){
                operatorStack.push(token);
            }else if (token.equals(")")){
                while (operatorStack.size()>0 && !operatorStack.lastElement().equals("(")){
                    output.add(operatorStack.pop());
                }
                if (operatorStack.size()>0){
                    operatorStack.pop();
                }
                if (Arrays.asList(functions).contains(operatorStack.lastElement())){
                    output.add(operatorStack.pop());
                }
            }
        }

        while (operatorStack.size() > 0){
            output.add(operatorStack.pop());
        }

        reversePolish = output;
    }

    private ArrayList<String> findFuncTokens(ArrayList<String> array){
        ArrayListUtil<String> listUtil = new ArrayListUtil<>();
        for(String func : functions){
            ArrayList<String> funcArray = new ArrayList<>(Arrays.asList(func.split("")));
            while (listUtil.search(array, funcArray) != -1){
                int i = listUtil.search(array, funcArray);
                array.set(i, func);

                for (int j = 0; j < func.length()-1; j++){
                    array.remove(i+1);
                }
            }
        }
        return array;
    }

    private ArrayList<String> combineNums(ArrayList<String> array){
        ArrayList<String> output = new ArrayList<>();

        for(String token : array){
            if(output.size()>0){
                if((StringUtil.is_number(token) || token.equals(".")) && StringUtil.is_number(output.get(output.size()-1))){
                    output.set(output.size()-1, output.get(output.size()-1)+token);
                }else {
                    output.add(token);
                }
            }else {
                output.add(token);
            }
        }
        return output;
    }

    private ArrayList<String> convertNegetives(ArrayList<String> array){
        ArrayList<Integer> indices = new ArrayListUtil<String>().indexOfAll("-", array);
        for(int i : indices){
            if(i-1<0 || operators.containsKey(array.get(i-1)) || array.get(i-1).equals("(")){
                array.set(i, "~");
            }
        }
        return array;
    }

    private ArrayList<String> fixParenMult(ArrayList<String> array){
        ArrayList<Integer> indices = new ArrayListUtil<String>().indexOfAll("(", array);
        Collections.reverse(indices);
        for(int i : indices){
            if(i-1 >= 0 && !operators.containsKey(array.get(i-1)) && !Arrays.asList(functions).contains(array.get(i-1)) && !array.get(i-1).equals(",") && !array.get(i-1).equals("(")){
                array.add(i, "*");
            }
        }

        indices = new ArrayListUtil<String>().indexOfAll(")", array);
        Collections.reverse(indices);
        for (int i : indices){
            if (i+1 < array.size() && !operators.containsKey(array.get(i+1)) && !array.get(i+1).equals(")") && !array.get(i+1).equals(",")){
                array.add(i+1, "*");
            }
        }
        return array;
    }

    private ArrayList<String> fixVarMult(ArrayList<String> array){
        for(int i = 0; i< array.size(); i++){
            if(!operators.containsKey(array.get(i)) && !StringUtil.is_number(array.get(i)) && !array.get(i).equals("(") && !array.get(i).equals(")") && !array.get(i).equals(",")){
                if (i-1 >=0 && !operators.containsKey(array.get(i-1)) && !Arrays.asList(functions).contains(array.get(i-1)) && !array.get(i-1).equals("(") && !array.get(i-1).equals(")") && !array.get(i-1).equals(",")){
                    array.add(i, "*");
                    i--;
                }
            }
        }
        return array;
    }

    public double solve(double varVal, String varName){
        ArrayList<String> reversePolish = new ArrayList<>(this.reversePolish.size());
        for(String s : this.reversePolish){
            reversePolish.add(s);
        }
        for(int i = 0; i<reversePolish.size(); i++){
            if(reversePolish.get(i).equals(varName)){
                reversePolish.set(i, Double.toString(varVal));
            }
        }

        int i = 0;
        while (i < reversePolish.size()){
            if (operators.containsKey(reversePolish.get(i))){
                if (reversePolish.get(i).equals("^")){
                    reversePolish.remove(i);
                    reversePolish.set(i-2, Double.toString(Math.pow(new Double(reversePolish.get(i-2)), new Double(reversePolish.remove(i-1)))));
                    i = i-2;
                }else if (reversePolish.get(i).equals("*")){
                    reversePolish.remove(i);
                    reversePolish.set(i-2, Double.toString(new Double(reversePolish.get(i-2)) * new Double(reversePolish.remove(i-1))));
                    i = i-2;
                }else if (reversePolish.get(i).equals("/")){
                    reversePolish.remove(i);
                    reversePolish.set(i-2, Double.toString(new Double(reversePolish.get(i-2)) / new Double(reversePolish.remove(i-1))));
                    i = i-2;
                }else if (reversePolish.get(i).equals("+")){
                    reversePolish.remove(i);
                    reversePolish.set(i-2, Double.toString(new Double(reversePolish.get(i-2)) + new Double(reversePolish.remove(i-1))));
                    i = i-2;
                }else if (reversePolish.get(i).equals("-")){
                    reversePolish.remove(i);
                    reversePolish.set(i-2, Double.toString(new Double(reversePolish.get(i-2)) - new Double(reversePolish.remove(i-1))));
                    i = i-2;
                }else if (reversePolish.get(i).equals("~")){
                    reversePolish.remove(i);
                    reversePolish.set(i-1, Double.toString(-(new Double(reversePolish.get(i-1)))));
                    i--;
                }else if (reversePolish.get(i).equals("|")){
                    reversePolish.remove(i);
                    reversePolish.set(i-1, Double.toString(Math.sqrt(new Double(reversePolish.get(i-1)))));
                    i--;
                }else if (reversePolish.get(i).equals("!")){
                    reversePolish.remove(i);
                    reversePolish.set(i-1, Double.toString(MathUtil.factorial((int) new Double(reversePolish.get(i-1)).doubleValue())));
                    i--;
                }
            }else if (Arrays.asList(functions).contains(reversePolish.get(i))){
                if (reversePolish.get(i).equals("log")){
                    reversePolish.remove(i);
                    reversePolish.set(i-2, Double.toString(MathUtil.log(new Double(reversePolish.get(i-2)), new Double(reversePolish.remove(i-1)))));
                    i = i-2;
                }else if (reversePolish.get(i).equals("ln")){
                    reversePolish.remove(i);
                    reversePolish.set(i-1, Double.toString(Math.log(new Double(reversePolish.get(i-1)))));
                    i--;
                }else if (reversePolish.get(i).equals("abs")){
                    reversePolish.remove(i);
                    reversePolish.set(i-1, Double.toString(Math.abs(new Double(reversePolish.get(i-1)))));
                    i--;
                }else if (reversePolish.get(i).equals("cos")){
                    reversePolish.remove(i);
                    reversePolish.set(i-1, Double.toString(Math.cos(new Double(reversePolish.get(i-1)))));
                    i--;
                }else if (reversePolish.get(i).equals("sin")){
                    reversePolish.remove(i);
                    reversePolish.set(i-1, Double.toString(Math.sin(new Double(reversePolish.get(i-1)))));
                    i--;
                }else if (reversePolish.get(i).equals("tan")){
                    reversePolish.remove(i);
                    reversePolish.set(i-1, Double.toString(Math.tan(new Double(reversePolish.get(i-1)))));
                    i--;
                }else if (reversePolish.get(i).equals("acos")){
                    reversePolish.remove(i);
                    reversePolish.set(i-1, Double.toString(Math.acos(new Double(reversePolish.get(i-1)))));
                    i--;
                }else if (reversePolish.get(i).equals("asin")){
                    reversePolish.remove(i);
                    reversePolish.set(i-1, Double.toString(Math.asin(new Double(reversePolish.get(i-1)))));
                    i--;
                }else if (reversePolish.get(i).equals("atan")){
                    reversePolish.remove(i);
                    reversePolish.set(i-1, Double.toString(Math.atan(new Double(reversePolish.get(i-1)))));
                    i--;
                }
            }
            i++;
        }
        Double x = new Double(reversePolish.get(0));
        return new Double(reversePolish.get(0));
    }

    public double solve(double varVal){
        return solve(varVal, "x");
    }

    public double solve(){
        return solve(0);
    }

    public boolean equals(Equation eq){
        Random r = new Random();
        ArrayList<Integer> randomNumbers = new ArrayList<>();
        for(int i = 0; i<10; i++){
            randomNumbers.add(r.nextInt(1000000));
        }

        boolean equal = true;

        for (int i : randomNumbers){
            if (solve(i) != eq.solve(i)){
                equal = false;
            }
        }

        return equal;
    }

    public boolean equals(Object eq){
        return equals((Equation) eq);
    }

    public String equation(){
        return equation;
    }

    public ArrayList<String> reversePolish(){
        return reversePolish;
    }

}
