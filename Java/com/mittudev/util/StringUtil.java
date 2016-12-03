package com.mittudev.util;

/**
 * Created by nickm on 12/3/2016.
 */
public class StringUtil {
    public static boolean is_number(String string){
        try {
            Double.parseDouble(string);
        }catch (NumberFormatException e){
            return false;
        }

        return true;
    }
}
