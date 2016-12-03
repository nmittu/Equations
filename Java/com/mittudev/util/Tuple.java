package com.mittudev.util;

public class Tuple<X, Y> {
    private final X x;
    private final Y y;

    public Tuple(X x, Y y) {
        this.x = x;
        this.y = y;
    }

    public X get0() {
        return x;
    }

    public Y get1() {
        return y;
    }

    public String toString() {
        return "(" + x + ", " + y + ")";
    }
}