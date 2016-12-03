package com.mittudev.util;

import java.util.ArrayList;

/**
 * Created by nickm on 12/3/2016.
 */
public class ArrayListUtil<X> {
    private  int _search(boolean forward, ArrayList<X> source, ArrayList<X> target){
        int m = source.size();
        int n = target.size();

        int end = m;
        int start = 0;

        if(n == 0 || (end - start) < n){
            return -1;
        }

        if(forward){
            for (int i = 0; i < m-n; i++){
                if(source.subList(i, i+n).equals(target)){
                    return i;
                }
            }
        }else {
            for(int i = end-n; i >= 0; i--){
                if (source.subList(i, i+n).equals(target)){
                    return i;
                }
            }
        }

        return -1;
    }

    public int search(ArrayList<X> source, ArrayList<X> target){
        return _search(true, source, target);
    }

    public int rsearch(ArrayList<X> source, ArrayList<X> target){
        return _search(false, source, target);
    }

    public ArrayList<Integer> indexOfAll(X obj, ArrayList<X> list){
        ArrayList<Integer> indexList = new ArrayList<Integer>();
        for (int i = 0; i < list.size(); i++)
            if(obj.equals(list.get(i)))
                indexList.add(i);
        return indexList;
    }
}
